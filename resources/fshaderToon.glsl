#version 330

in vec4 normal;
in vec4 position;
out vec4 colorOut;

// Struct que representa un material amb tots els seus parametres
struct stMaterial {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 transparency;
    float shininess;
};

// Struct que representa una llum amb tots els seus parametres
struct stLight {
    int type;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 coefficients;
    vec3 position;
    vec3 direction;
    float angle;
};


// Material de l'objecte
uniform stMaterial material;

// Array d'objectes tipus Light
// Array de 10 elements. Aquest valor sempre ha de ser un numero. No pot ser una variable!
uniform stLight lights[10];

// Llum ambient global
uniform vec3 globalAmbientLight;

uniform vec4 obs;

float toon_factor(vec4 pointToLight){
    //producte escalar:
    float factor;
    float p_escalar = dot(normal, pointToLight);

    if (p_escalar > 0.75)
            factor = 0.75;
        else if (p_escalar > 0.5)
            factor = 0.5;
        else if (p_escalar > 0.25)
            factor = 0.25;
        else
            factor = 0;

    return factor;
}

float silhouette_emphasis_factor(vec4 pointToObs){
    float alpha = dot(normal, -pointToObs);
    return 1 - alpha;
}

vec4 blinn_phong ()
{
    vec3 ca = vec3(0);
    vec3 cd = vec3(0);
    vec3 cs = vec3(0);
    vec4 H, L, V, direction;
    float d, attenuationFactor;

    int nLights = lights.length();

    //Per cada Light (nomes per llums puntuals, si es direccional no te posicio, pero si direccio)
    for(int i=0; i<nLights; i++){

        // PointLight o SpotLight
        if (lights[i].type == 0 || lights[i].type == 2){

            float a = lights[i].coefficients[0];
            float b = lights[i].coefficients[1];
            float c = lights[i].coefficients[2];

            d = length(vec4(lights[i].position,1) - position);

            // Ens assegurem que l'atenuacio estigui entre 0 i 1
            attenuationFactor = max(min(1./(c + b*d + a*d*d),1.),0.);

            L = normalize(vec4(lights[i].position,1) - position);

        // DirectionalLight
        }else if(lights[i].type == 1){
            attenuationFactor = 1.;
            L = normalize(vec4(-lights[i].direction,0));
        }

        V = normalize(obs - position);

        H = normalize(V + L);

        //Component ambient
        ca += material.ambient * lights[i].ambient;

        //Component difusa
        //cd += attenuationFactor * lights[i].diffuse * material.diffuse * silhouette_emphasis_factor(V) * toon_factor(L) * max(dot(normal, normalize(L)), 0.0f);
        cd += attenuationFactor * lights[i].diffuse * material.diffuse * toon_factor(L) * max(dot(normal, normalize(L)), 0.0f);

        //Component especular
        cs += attenuationFactor * lights[i].specular * material.specular * pow(max(dot(normal, H), 0.0f), material.shininess);
       }

    //Retornem la llum ambient global més les tres components
    return vec4(globalAmbientLight*material.ambient + ca + cd + cs, 1);
}

void main()
{
    colorOut = blinn_phong();
}
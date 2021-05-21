#version 330

in vec4 normal;
in vec4 position;
in vec2 coordTexture;
out vec4 colorOut;

uniform sampler2D texMap;

uniform int hasTexture;

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
    float sharpness;
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
            factor = 0.03;

    return factor;
}

float silhouette_emphasis_factor(vec4 pointToObs){
    float alpha = dot(normal, -pointToObs);
    return 1 - alpha;
}

vec4 blinn_phong (vec3 diffuse)
{
    vec3 ca = vec3(0);
    vec3 cd = vec3(0);
    vec3 cs = vec3(0);
    vec4 H, L, V, direction;
    float d, attenuationFactor, angle, a, b, c;

    int nLights = lights.length();

    //Per cada Light (nomes per llums puntuals, si es direccional no te posicio, pero si direccio)
    for(int i=0; i<nLights; i++){

        // PointLight
        if (lights[i].type == 0){

            a = lights[i].coefficients[0];
            b = lights[i].coefficients[1];
            c = lights[i].coefficients[2];

            d = length(vec4(lights[i].position,1) - position);

            // Ens assegurem que l'atenuacio estigui entre 0 i 1
            attenuationFactor = max(min(1./(c + b*d + a*d*d),1.),0.);

            L = normalize(vec4(lights[i].position,1) - position);

        }// DirectionalLight
        else if(lights[i].type == 1){
            attenuationFactor = 1.;
            L = normalize(vec4(-lights[i].direction,0));
        }
        // SpotLight
        else if (lights[i].type == 2){

            attenuationFactor = 1.;
            L = normalize(vec4(-lights[i].direction,1) - position);

            // Direccio de la llum (normalitzada)
            vec4 D = vec4(normalize(lights[i].direction),0);

            // Comprovem si estem dins el con del Spotlight
            angle = (180.0/3.14)*(acos(dot(-L, D)));

            // Si esta a fora del con, la llum no actua (att=0)
            if (angle > lights[i].angle){
              attenuationFactor = 0.0;
            } else {
              attenuationFactor = pow(dot(-L, D),100-lights[i].sharpness);
            }
        }

        V = normalize(obs - position);

        H = normalize(V + L);

        //Component ambient
        ca += material.ambient * lights[i].ambient;

        //Component difusa
        //cd += attenuationFactor * lights[i].diffuse * material.diffuse * silhouette_emphasis_factor(V) * toon_factor(L) * max(dot(normal, normalize(L)), 0.0f);
        cd += attenuationFactor * lights[i].diffuse * diffuse * toon_factor(L) * max(dot(normal, normalize(L)), 0.0f);

        //Component especular
        cs += attenuationFactor * lights[i].specular * material.specular * pow(max(dot(normal, H), 0.000001f), material.shininess);
       }

    //Retornem la llum ambient global més les tres components
    return vec4(globalAmbientLight*material.ambient + ca + cd + cs, 1);
}

void main()
{
    vec3 diffuse;
    if (hasTexture == 1) {
        diffuse = vec3(texture(texMap, coordTexture).rgb);
    } else {
        diffuse = material.diffuse;
    }
    colorOut = blinn_phong(diffuse);
}

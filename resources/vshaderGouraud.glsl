#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;
layout (location = 2) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;
uniform int hasTexture;

uniform sampler2D texMap;

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

out vec4 color;
out vec2 coordTexture;

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

            d = length(vec4(lights[i].position,1) - vPosition);

            // Ens assegurem que l'atenuacio estigui entre 0 i 1
            attenuationFactor = max(min(1./(c + b*d + a*d*d),1.),0.);

            L = normalize(vec4(lights[i].position,1) - vPosition);

        }// DirectionalLight
        else if(lights[i].type == 1){
            attenuationFactor = 1.;
            L = normalize(vec4(-lights[i].direction,0));
        }
        // SpotLight
        else if (lights[i].type == 2){

            attenuationFactor = 1.;
            L = normalize(vec4(-lights[i].direction,1) - vPosition);

            // Direccio de la llum (normalitzada)
            vec4 D = vec4(normalize(lights[i].direction),0);

            // Comprovem si estem dins el con del Spotlight
            angle = (180.0/3.14)*(acos(dot(-L, D)));

            // Si esta a fora del con, la llum no actua (att=0)
            if (angle > lights[i].angle){
              attenuationFactor = 0.0;
            }
        }

        V = normalize(obs - vPosition);

        H = normalize(V + L);

        //Component ambient
        ca += material.ambient * lights[i].ambient;

        //Component difusa
        cd += attenuationFactor * lights[i].diffuse * diffuse * max(dot(vNormal, normalize(L)), 0.0f);

        //Component especular
        cs += attenuationFactor * lights[i].specular * material.specular * pow(max(dot(vNormal, H), 0.0001f), material.shininess);
       }

    //Retornem la llum ambient global més les tres components
    return vec4(globalAmbientLight*material.ambient + ca + cd + cs, 1);
}

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    vec3 diffuse;
    if (hasTexture == 1) {
        diffuse = vec3(texture(texMap, vCoordTexture).rgb);
    } else {
        diffuse = material.diffuse;
    }
    coordTexture = vCoordTexture;
    color = blinn_phong(diffuse);
}

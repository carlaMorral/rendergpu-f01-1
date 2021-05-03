#version 330

layout (location = 0) in vec4 vPosition;

uniform mat4 model_view;
uniform mat4 projection;

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

// Struct que representa la llum ambient global
struct stGlobal {
    vec3 globalLight;
};

// Material de l'objecte
uniform stMaterial material;

// Array d'objectes tipus Light
// Array de 10 elements. Aquest valor sempre ha de ser un numero. No pot ser una variable!
uniform stLight lights[10];

// Llum ambient global
uniform stGlobal globalAmbientLight;


out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    //color = vec4(globalAmbientLight.globalLight,1);
    //color = vec4(lights[0].specular,1);
    color = vec4(0,material.shininess/20.0, material.shininess/20.0, 1);
}

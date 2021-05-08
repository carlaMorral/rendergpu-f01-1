#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

// Struct que representa una llum amb tots els seus parametres
struct stLight{
    int type;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 coefficients;
    vec3 position;
    vec3 direction;
    float angle;
};

// Array d'objectes tipus Light
uniform stLight lights[10]; // Array de 10 elements. Aquest valor sempre ha de ser un numero. No pot ser una variable!

// Struct que representa la llum ambient global
struct stGlobal
{
    vec3 globalLight;
};

// Llum ambient global
uniform stGlobal globalAmbientLight;

void main(void)
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Comprovem que el primer element de la llista de llums te el valor diffuse esperat
    //color = vec4(globalAmbientLight.globalLight,1);
    color = vNormal;
}


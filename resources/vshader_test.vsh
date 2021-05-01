layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

// Struct que representa una llum amb tots els seus parametres
struct Light{
    int type;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 coefficients;
    vec4 position;
    vec3 direction;
    float angle;
};

// Array d'objectes tipus Light
uniform Light lights[10]; // Array de 10 elements. Aquest valor sempre ha de ser un numero. No pot ser una variable!


// Struct que representa la llum ambient global
struct GlobalAmbientLight
{
    vec4 globalLight;
};

// Llum ambient global
uniform GlobalAmbientLight globalAmbientLight;

void main(void)
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Comprovem que el primer element de la llista de llums te el valor diffuse esperat
    color = lights[0].diffuse;
}

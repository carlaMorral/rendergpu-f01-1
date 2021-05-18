#version 330

in vec4 color;
in vec2 coordTexture;
out vec4 colorOut;

uniform sampler2D texMap;
uniform int hasTexture;


void main()
{
    if (hasTexture == 1) {
        colorOut = color*0.25 + vec4(vec3(texture(texMap, coordTexture).rgb)*0.75, 1);
    } else {
        colorOut = color;
    }
}


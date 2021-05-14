#version 330

in vec4 color;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;

uniform int hasTexture;

void main()
{
    if (hasTexture == 1) {
        colorOut = vec4(texture(texMap, v_texcoord).rgb, 1.0f);
    } else {
        colorOut = color;
    }
}


#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vCoordTexture;

out vec4 position;
out vec3 v_texcoord;

void main()
{
    position = vPosition;
    v_texcoord = normalize(position.xyz);
}

#version 330

in vec3 v_texcoord;
out vec4 colorOut;

uniform samplerCube texEnvironment;

void main(void)
{
    colorOut = vec4(vec3(texture(texEnvironment, v_texcoord.xyz).rgb), 1.0f);
}

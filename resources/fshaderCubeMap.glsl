#version 330

in vec4 position;
in vec3 coordTexture;
out vec4 colorOut;

uniform samplerCube texEnvironment;

void main()
{
    colorOut = vec4(texture(texEnvironment, coordTexture.xyz).rgb, 1.0f);
}

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

// Material de l'objecte
uniform stMaterial material;


vec2 rot(vec2 p, vec2 pivot, float a) {
    float s = sin(a);
    float c = cos(a);

    p -= pivot;
    p = vec2(p.x*c-p.y*s, p.x*s+p.y*c);
    p += pivot;

    return p;
}

void main()
{
        if(hasTexture == 1){
            //Si té coordenades de textura, podem fer mandelbrot: z_{n+1} = (z_n)^2 + c
            //Si la successió és acotada (pertany al conjunt) -> negre
            //Si la successió no és acotada -> color segons velocitat amb la que tendeix a infinit

            float MAX_ITER = 255; //nombre màxim iteracions
            float r = 2; //Radi escapament
            float r2 = r*r;
            vec2 c = vec2(coordTexture.x-0.5, coordTexture.y-0.5)*4; //Transformem u,v per centrar imatge
            vec2 z=vec2(0); //z_0
            float iter; //Si no esta en float, la divisió la tracta com entera

            for(iter = 0; iter<MAX_ITER ; iter++){
                z = vec2(z.x*z.x-z.y*z.y, 2.*z.x*z.y) + c;
                if(length(z) > r) break;
            }
            if(iter > MAX_ITER){
                colorOut = vec4(0,0,0,1);
            }else{
                float dist = length(z);
                float fracIter = (dist-r) / (r2 - r);
                iter += fracIter;
                float m = sqrt(iter/255);
                vec4 col = vec4(sin(.3*m*20.)*.5+.5, sin(.45*m*20.)*.5+.5, sin(.65*m*20.)*.5+.5, 1);
                colorOut = vec4(col);
            }
        }else {
            colorOut = vec4(1,1,1,1);
        }


}

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

float toon_factor(vec4 pointToLight){
    //producte escalar:
    float factor;
    float p_escalar = dot(normal, pointToLight);

    if (p_escalar > 0.75)
            factor = 0.75;
        else if (p_escalar > 0.5)
            factor = 0.5;
        else if (p_escalar > 0.25)
            factor = 0.25;
        else
            factor = 0;

    return factor;
}

float silhouette_emphasis_factor(vec4 pointToObs){
    //http://ivl.calit2.net/wiki/images/8/82/15_ToonShadingS16.pdf
    float alpha = max(0, dot(normal, pointToObs));
    return alpha;
}

vec3 rgb2hsv(vec3 rgb){ //h=r s=g v=b

    vec3 hsv;
    float m, M, delta;

    m = min(rgb.x, min(rgb.y, rgb.z));
    M = max(rgb.x, max(rgb.y, rgb.z));

    hsv.z = M;
    delta = M - m;

    if (delta < 0.00001)
    {
        hsv.y = 0;
        hsv.x = 0;
        return hsv;
    }
    if( M > 0.0 ) {
        hsv.y = (delta / M);
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        hsv.y = 0.0;
        hsv.x = 0.0;                            // its now undefined
        return hsv;
    }

    if( rgb.x >= M - 0.0001 )
        hsv.x = ( rgb.y - rgb.z ) / delta;
    else
    if( rgb.y >= M - 0.0001 )
        hsv.x = 2.0 + ( rgb.z - rgb.x ) / delta;  // between cyan & yellow
    else
        hsv.x = 4.0 + ( rgb.x - rgb.y ) / delta;  // between magenta & cyan

    hsv.x *= 60.0;                              // degrees

    if( hsv.x < 0.0 )
        hsv.x += 360.0;

    return hsv;
}


vec3 hsv2rgb(vec3 hsv)
{
    float hh, p, q, t, ff;
    vec3 rgb;

    if(hsv.y <= 0.0) {       // < is bogus, just shuts up warnings
        rgb.x = hsv.z;
        rgb.y = hsv.z;
        rgb.z = hsv.z;
        return rgb;
    }
    hh = hsv.x;
    if(hh >= 360.0){
        hh = 0.0;
    }
    hh /= 60.0;
    int i = int(hh); //Auto cast
    float ifloat = float(i);
    ff = hh - ifloat;
    p = hsv.z * (1.0 - hsv.y);
    q = hsv.z * (1.0 - (hsv.y * ff));
    t = hsv.z * (1.0 - (hsv.y * (1.0 - ff)));

    switch(i) {
    case 0:
        rgb.x = hsv.z;
        rgb.g = t;
        rgb.z = p;
        break;
    case 1:
        rgb.x = q;
        rgb.y = hsv.z;
        rgb.z = p;
        break;
    case 2:
        rgb.x = p;
        rgb.y = hsv.z;
        rgb.z = t;
        break;
    case 3:
        rgb.x = p;
        rgb.y = q;
        rgb.z = hsv.z;
        break;
    case 4:
        rgb.x = t;
        rgb.y = p;
        rgb.z = hsv.z;
        break;
    case 5:
    default:
        rgb.x = hsv.z;
        rgb.y = p;
        rgb.z = q;
        break;
    }
    return rgb;
}

vec4 blinn_phong (vec3 diffuse)
{
    vec3 cd = vec3(0);
    vec4 L, V;
    float d, attenuationFactor, angle, a, b, c;

    int nLights = lights.length();

    //Per cada Light (nomes per llums puntuals, si es direccional no te posicio, pero si direccio)
    for(int i=0; i<nLights; i++){

        // PointLight
        if (lights[i].type == 0){

            L = normalize(vec4(lights[i].position,1) - position);

        }// DirectionalLight
        else if(lights[i].type == 1){

            L = normalize(vec4(-lights[i].direction,0));

        }
        // SpotLight
        else if (lights[i].type == 2){

            L = normalize(vec4(-lights[i].direction,1) - position);

        }

        V = normalize(obs - position);

        vec3 hsv = rgb2hsv(diffuse);

        hsv.z *= toon_factor(L);

        vec3 rgb = hsv2rgb(hsv);

        if (silhouette_emphasis_factor(V) < 0.01){
            rgb = vec3(0,0,0);
        }

        cd += rgb;

    }

    cd /= nLights;

    return vec4(globalAmbientLight*material.ambient + cd, 1);
}


void main()
{
    vec3 diffuse;
    if (hasTexture == 1) {
        diffuse = vec3(texture(texMap, coordTexture).rgb);
    } else {
        diffuse = material.diffuse;
    }

    colorOut = blinn_phong(diffuse);
}

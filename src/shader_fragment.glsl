#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
in vec4 color_v;
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE 0
#define PLAYER 1
#define FIELD  2
#define SKYSPHERE 3
#define PLANE 4
#define GOAL 5
#define GOAL2  6
#define GOAL3  7
#define SUN 8
#define CONE 9

uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform bool gouraud;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;
uniform sampler2D TextureImage4;
uniform sampler2D TextureImage5;
uniform sampler2D TextureImage6;
uniform sampler2D TextureImage7;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    // vec4 r = vec4(0.0,0.0,0.0,0.0); // PREENCHA AQUI o vetor de reflexão especular ideal
    vec4 r = normalize(-l + 2 * n * dot(n, l));

    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
    vec3 Kd0 = vec3(0.0,0.0,0.0);
    float epsilon = 0.0001;

    // Testa se é o id da esfera
    if ( object_id == SPHERE )
    {
        // PREENCHA AQUI as coordenadas de textura da esfera, computadas com
        // projeção esférica EM COORDENADAS DO MODELO. Utilize como referência
        // o slides 134-150 do documento Aula_20_Mapeamento_de_Texturas.pdf.
        // A esfera que define a projeção deve estar centrada na posição
        // "bbox_center" definida abaixo.

        // Você deve utilizar:
        //   função 'length( )' : comprimento Euclidiano de um vetor
        //   função 'atan( , )' : arcotangente. Veja https://en.wikipedia.org/wiki/Atan2.
        //   função 'asin( )'   : seno inverso.
        //   constante M_PI
        //   variável position_model

        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        p = position_model - bbox_center;

        float ro = length(p);
        float theta = atan(p.x, p.z);
        float phi = asin(p.y/ro);

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + (M_PI_2))/(M_PI);

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage1
        Kd0 = texture(TextureImage1, vec2(U,V)).rgb;
    }
    // Testa se é o id do sol
    if ( object_id == SUN )
    {
        // PREENCHA AQUI as coordenadas de textura da esfera, computadas com
        // projeção esférica EM COORDENADAS DO MODELO. Utilize como referência
        // o slides 134-150 do documento Aula_20_Mapeamento_de_Texturas.pdf.
        // A esfera que define a projeção deve estar centrada na posição
        // "bbox_center" definida abaixo.

        // Você deve utilizar:
        //   função 'length( )' : comprimento Euclidiano de um vetor
        //   função 'atan( , )' : arcotangente. Veja https://en.wikipedia.org/wiki/Atan2.
        //   função 'asin( )'   : seno inverso.
        //   constante M_PI
        //   variável position_model

        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        p = position_model - bbox_center;

        float ro = length(p);
        float theta = atan(p.x, p.z);
        float phi = asin(p.y/ro);

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + (M_PI_2))/(M_PI);

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage7
        Kd0 = texture(TextureImage7, vec2(U,V)).rgb;
    }
    // Testa se é o id do jogador
    else if ( object_id == PLAYER )
    {
        // PREENCHA AQUI as coordenadas de textura do coelho, computadas com
        // projeção planar XY em COORDENADAS DO MODELO. Utilize como referência
        // o slides 99-104 do documento Aula_20_Mapeamento_de_Texturas.pdf,
        // e também use as variáveis min max definidas abaixo para normalizar
        // as coordenadas de textura U e V dentro do intervalo [0,1]. Para
        // tanto, veja por exemplo o mapeamento da variável 'p_v' utilizando
        // 'h' no slides 158-160 do documento Aula_20_Mapeamento_de_Texturas.pdf.
        // Veja também a Questão 4 do Questionário 4 no Moodle.

        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.5,0.5,0.5);
        q = 20.0;

        U = texcoords.x;
        V = texcoords.y;
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage4
        Kd0 = texture(TextureImage4, vec2(U,V)).rgb;

    }
    // Testa se é o id do campo
    else if ( object_id == FIELD )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        // Kd = vec3(0.2,0.2,0.2);
        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.2,0.2,0.2);
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage2
        Kd0 = texture(TextureImage2, vec2(U,V)).rgb;
    }
    // Testa se é o id do plano
    else if ( object_id == PLANE)
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x * 30;
        V = texcoords.y * 30;
        // Kd = vec3(0.2,0.2,0.2);
        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.4,0.4,0.4);
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage3
        Kd0 = texture(TextureImage3, vec2(U,V)).rgb;
    }
    // Testa se é o id de um dos cones
    else if ( object_id >= CONE && object_id <= 22)
    {
        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.4,0.4,0.4);
        q = 20.0;

        U = texcoords.x;
        V = texcoords.y;
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage5
        Kd0 = texture(TextureImage5, vec2(U,V)).rgb;
    }
    // Testa se é o id de um dos adversarios
    else if ( object_id == GOAL || object_id == GOAL2 || object_id == GOAL3)
    {
        Ks = vec3(0.3,0.3,0.3);
        Ka = vec3(0.4,0.4,0.4);
        q = 20.0;

        U = texcoords.x;
        V = texcoords.y;
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage6
        Kd0 = texture(TextureImage6, vec2(U,V)).rgb;
    }
    // Testa se é o id da skysphere
    else if ( object_id == SKYSPHERE )
    {
        // PREENCHA AQUI as coordenadas de textura da esfera, computadas com
        // projeção esférica EM COORDENADAS DO MODELO. Utilize como referência
        // o slides 134-150 do documento Aula_20_Mapeamento_de_Texturas.pdf.
        // A esfera que define a projeção deve estar centrada na posição
        // "bbox_center" definida abaixo.

        // Você deve utilizar:
        //   função 'length( )' : comprimento Euclidiano de um vetor
        //   função 'atan( , )' : arcotangente. Veja https://en.wikipedia.org/wiki/Atan2.
        //   função 'asin( )'   : seno inverso.
        //   constante M_PI
        //   variável position_model

        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        vec4 p_l = bbox_center + 11* ((position_model - bbox_center)/(length(position_model - bbox_center)));
        vec4 p_v = p_l - bbox_center;


        float theta = atan(p_v.x, p_v.z) + epsilon;
        float phi = asin(p_v.y/11) + epsilon;

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + (M_PI_2))/(M_PI);
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
    }


   // Espectro da fonte de iluminação
    vec3 I = vec3(100.0,100.0,1.0); // PREENCH AQUI o espectro da fonte de luz

    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2,0.2,0.2); // PREENCHA AQUI o espectro da luz ambiente

    // Termo difuso utilizando a lei dos cossenos de Lambert
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l)); // PREENCHA AQUI o termo difuso de Lambert

    // Termo ambiente
    vec3 ambient_term = Ka * Ia; // PREENCHA AQUI o termo ambiente

    // Termo especular utilizando o modelo de iluminação de Phong
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r, v)), q); // PREENCH AQUI o termo especular de Phong

    vec4 h = (v + l)/normalize(v + l);
    vec3 blinn_phong = Ks * I * pow(max(0, dot(h, n)), q); //Blinn-Phong

    // NOTE: Se você quiser fazer o rendering de objetos transparentes, é
    // necessário:
    // 1) Habilitar a operação de "blending" de OpenGL logo antes de realizar o
    //    desenho dos objetos transparentes, com os comandos abaixo no código C++:
    //      glEnable(GL_BLEND);
    //      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 2) Realizar o desenho de todos objetos transparentes *após* ter desenhado
    //    todos os objetos opacos; e
    // 3) Realizar o desenho de objetos transparentes ordenados de acordo com
    //    suas distâncias para a câmera (desenhando primeiro objetos
    //    transparentes que estão mais longe da câmera).
    // Alpha default = 1 = 100% opaco = 0% transparente

    // Cor final do fragmento calculada com uma combinação dos termos difuso,
    // especular, e ambiente. Veja slide 129 do documento Aula_17_e_18_Modelos_de_Iluminacao.pdf.
    color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;

    if(object_id == SKYSPHERE){
        color.rgb = Kd0 ;
    }
    else if(object_id == SUN && gouraud){
        color.rgb = Kd0 * color_v.rgb;
    }
    else{
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));
        color.rgb = (Kd0 * (lambert + 0.01));
    }
    // NOTE: Se você quiser fazer o rendering de objetos transparentes, é
    // necessário:
    // 1) Habilitar a operação de "blending" de OpenGL logo antes de realizar o
    //    desenho dos objetos transparentes, com os comandos abaixo no código C++:
    //      glEnable(GL_BLEND);
    //      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 2) Realizar o desenho de todos objetos transparentes *após* ter desenhado
    //    todos os objetos opacos; e
    // 3) Realizar o desenho de objetos transparentes ordenados de acordo com
    //    suas distâncias para a câmera (desenhando primeiro objetos
    //    transparentes que estão mais longe da câmera).
    // Alpha default = 1 = 100% opaco = 0% transparente

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}

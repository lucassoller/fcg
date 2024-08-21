#include "collisions.h"
#include <algorithm>

// FONTE: https://www.realtimerendering.com/intersections.html
// FONTE: https://realtimecollisiondetection.net/books/rtcd/

namespace collisions
{
    // Função para verificar a colisão entre um cilindro e uma esfera
    bool checkCollision(const Cylinder &cylinder, const Sphere &sphere)
    {
        // Calcula a altura mínima e máxima do cilindro ao longo do eixo Y
        float minCylinderHeight = cylinder.center.y - cylinder.height / 2;
        float maxCylinderHeight = cylinder.center.y + cylinder.height / 2;

        // Calcula a distância ao quadrado entre os centros da esfera e do cilindro no plano XZ
        float distanceFromAxis = pow(cylinder.center.x - sphere.center.x, 2) + pow(cylinder.center.z - sphere.center.z, 2);
        float distanceSquared;

        // Verifica se a esfera está na mesma faixa de altura do cilindro
        if (sphere.center.y >= minCylinderHeight && sphere.center.y <= maxCylinderHeight)
        {
            // Se estiver, a distância ao quadrado é calculada com base na distância do eixo
            distanceSquared = distanceFromAxis;
        }
        // Se a esfera estiver abaixo da base do cilindro
        else if (sphere.center.y < minCylinderHeight)
        {
            // Calcula a distância ao quadrado entre o centro da esfera e a base do cilindro
            distanceSquared = distance(sphere.center, (cylinder.center - glm::vec4{0, cylinder.height / 2, 0, 0}));
        }
        // Se a esfera estiver acima do topo do cilindro
        else
        {
            // Calcula a distância ao quadrado entre o centro da esfera e o topo do cilindro
            distanceSquared = distance(sphere.center, (cylinder.center + glm::vec4{0, cylinder.height / 2, 0, 0}));
        }

        // Soma dos raios da esfera e do cilindro
        float radiusSum = sphere.radius + cylinder.radius;

        // Retorna true se a distância ao quadrado for menor ou igual ao quadrado da soma dos raios (colisão detectada)
        return distanceSquared <= (radiusSum * radiusSum);
    }


    // Função para verificar a colisão entre um cilindro e um cilindro
    bool checkCollision(const Cylinder &cylinder1, const Cylinder &cylinder2)
    {
        // Verifica se as alturas dos cilindros se sobrepõem
        float minHeight1 = cylinder1.center.y - cylinder1.height / 2;
        float maxHeight1 = cylinder1.center.y + cylinder1.height / 2;
        float minHeight2 = cylinder2.center.y - cylinder2.height / 2;
        float maxHeight2 = cylinder2.center.y + cylinder2.height / 2;

        bool heightOverlap = (minHeight1 <= maxHeight2 && maxHeight1 >= minHeight2);

        // Calcula a distância ao quadrado entre os centros dos cilindros no plano XZ
        float distanceFromAxisSquared = pow(cylinder1.center.x - cylinder2.center.x, 2) + pow(cylinder1.center.z - cylinder2.center.z, 2);

        // Soma dos raios dos cilindros
        float radiusSum = cylinder1.radius + cylinder2.radius;

        // Verifica se a distância ao quadrado entre os centros é menor ou igual ao quadrado da soma dos raios
        bool baseOverlap = distanceFromAxisSquared <= (radiusSum * radiusSum);

        // A colisão ocorre se houver sobreposição tanto na altura quanto na base
        return heightOverlap && baseOverlap;
    }

    // Função para verificar a colisão entre uma esfera e um plano
    bool checkCollision(const Sphere& sphere, const Plane& plane) {
        // Função para calcular a distância entre o centro da esfera e o plano
        float distanceToPlane = dotproduct(plane.normal, sphere.center) - plane.distance;
        return std::abs(distanceToPlane) <= sphere.radius;
    }

    // Função para verificar a colisão entre um cilindro e um plano
    bool checkCollision(const Cylinder& cylinder, const Plane& plane) {

        // Função para calcular a distância entre o centro do cilindro e o plano
        float distanceToPlane = dotproduct(plane.normal, cylinder.center) - plane.distance;
        return std::abs(distanceToPlane) <= cylinder.radius;
    }

    // Produto escalar entre dois vetores u e v definidos em um sistema de
    // coordenadas ortonormal.
    float dotproduct(glm::vec4 u, glm::vec4 v)
    {
        float u1 = u.x;
        float u2 = u.y;
        float u3 = u.z;
        float v1 = v.x;
        float v2 = v.y;
        float v3 = v.z;

        return u1*v1 + u2*v2 + u3*v3;
    }
}

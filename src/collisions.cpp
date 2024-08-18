#include "collisions.h"
#include <algorithm>

namespace collisions
{

    bool checkCollision(const Cylinder &cylinder, const Sphere &sphere)
    {

        float minCylinderHeight = cylinder.center.y - cylinder.height / 2;
        float maxCylinderHeight = cylinder.center.y + cylinder.height / 2;
        float distanceFromAxis = pow(cylinder.center.x - sphere.center.x, 2) + pow(cylinder.center.z - sphere.center.z, 2);
        float distanceSquared;

        if (sphere.center.y >= minCylinderHeight && sphere.center.y <= maxCylinderHeight)
        {
            distanceSquared = distanceFromAxis;
        }
        else if (sphere.center.y < minCylinderHeight)
        {
            distanceSquared = distance(sphere.center, (cylinder.center - glm::vec4{0, cylinder.height / 2, 0, 0}));
        }
        else
        {
            distanceSquared = distance(sphere.center, (cylinder.center + glm::vec4{0, cylinder.height / 2, 0, 0}));
        }

        float radiusSum = sphere.radius + cylinder.radius;
        return distanceSquared <= (radiusSum * radiusSum);
    }

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


    // Função para calcular a distância entre o centro da esfera e o plano
    bool checkCollision(const Sphere& sphere, const Plane& plane) {
        float distanceToPlane = dotproduct(plane.normal, sphere.center) - plane.distance;
        return std::abs(distanceToPlane) <= sphere.radius;
    }

    // Função para calcular a distância entre o centro do cilindro e o plano
    bool checkCollision(const Cylinder& cylinder, const Plane& plane) {

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
        float u4 = u.w;
        float v1 = v.x;
        float v2 = v.y;
        float v3 = v.z;
        float v4 = v.w;

        return u1*v1 + u2*v2 + u3*v3;
    }

}

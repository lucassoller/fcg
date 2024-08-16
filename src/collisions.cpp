#include "collisions.h"
#include <algorithm>

namespace collisions
{
    float SqDistPointAABB(const glm::vec4 &point, const glm::vec4 &bbox_min, const glm::vec4 &bbox_max)
    {
        float sqDist = 0.0f;

        if (point.x < bbox_min.x)
            sqDist += (bbox_min.x - point.x) * (bbox_min.x - point.x);
        if (point.x > bbox_max.x)
            sqDist += (point.x - bbox_max.x) * (point.x - bbox_max.x);

        if (point.y < bbox_min.y)
            sqDist += (bbox_min.y - point.y) * (bbox_min.y - point.y);
        if (point.y > bbox_max.y)
            sqDist += (point.y - bbox_max.y) * (point.y - bbox_max.y);

        if (point.z < bbox_min.z)
            sqDist += (bbox_min.z - point.z) * (bbox_min.z - point.z);
        if (point.z > bbox_max.z)
            sqDist += (point.z - bbox_max.z) * (point.z - bbox_max.z);

        return sqDist;
    }

    bool checkCollision(const Sphere &sphere,
                        const glm::vec3 &bbox_min, const glm::vec3 &bbox_max, const glm::mat4 &modelMatrix)
    {
        glm::vec4 minPoint = modelMatrix * glm::vec4(bbox_min, 1.0f);
        glm::vec4 maxPoint = modelMatrix * glm::vec4(bbox_max, 1.0f);

        // Compute squared distance between sphere center and AABB
        float sqDist = SqDistPointAABB(sphere.center, minPoint, maxPoint);

        // Sphere and AABB intersect if the (squared) distance
        // between them is less than the (squared) sphere radius
        return sqDist <= sphere.radius * sphere.radius;
    }

    // Computes the square distance between a point p and an AABB b

    bool checkCollision(const Cylinder &cylinder, const glm::vec4 &point)
    {
        float minCylinderHeight = cylinder.center.y - cylinder.height / 2;
        float maxCylinderHeight = cylinder.center.y + cylinder.height / 2;
        float distanceFromAxis = pow(cylinder.center.x - point.x, 2) + pow(cylinder.center.z - point.z, 2);

        return minCylinderHeight <= point.y && point.y <= maxCylinderHeight && distanceFromAxis <= (cylinder.radius * cylinder.radius);
    }

    float distance(glm::vec4 a, glm::vec4 b)
    {
        return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
    }

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

    // Fun��o para calcular a dist�ncia entre o centro da esfera e o plano
    bool checkCollision(const Sphere& sphere, const Plane& plane) {
        float distanceToPlane = dotproduct(plane.normal, sphere.center) - plane.distance;
        return std::abs(distanceToPlane) <= sphere.radius;
    }

    // Fun��o para calcular a dist�ncia entre o centro do cilindro e o plano
    bool checkCollision(const Cylinder& cylinder, const Plane& plane) {

        float distanceToPlane = dotproduct(plane.normal, cylinder.center) - plane.distance;
        return std::abs(distanceToPlane) <= cylinder.radius;
    }

        // Fun��o para verificar a colis�o entre a caixa e o plano
    bool checkCollision(const glm::vec3 &bboxmin, const glm::vec3 &bboxmax, const glm::mat4 &modelMatrix, const Plane& plane) {

        glm::vec4 bbox_min = modelMatrix * glm::vec4(bboxmin, 1.0f);
        glm::vec4 bbox_max = modelMatrix * glm::vec4(bboxmax, 1.0f);
        // Encontre todos os v�rtices da caixa
        glm::vec4 corners[8] = {
            glm::vec4(bbox_min.x, bbox_min.y, bbox_min.z, 1.0f),
            glm::vec4(bbox_max.x, bbox_min.y, bbox_min.z, 1.0f),
            glm::vec4(bbox_min.x, bbox_max.y, bbox_min.z, 1.0f),
            glm::vec4(bbox_max.x, bbox_max.y, bbox_min.z, 1.0f),
            glm::vec4(bbox_min.x, bbox_min.y, bbox_max.z, 1.0f),
            glm::vec4(bbox_max.x, bbox_min.y, bbox_max.z, 1.0f),
            glm::vec4(bbox_min.x, bbox_max.y, bbox_max.z, 1.0f),
            glm::vec4(bbox_max.x, bbox_max.y, bbox_max.z, 1.0f)
        };

        // Verifica a dist�ncia de cada v�rtice ao plano
        bool isColliding = false;
        for (const auto& corner : corners) {
            float distance = dotproduct(plane.normal, corner) - plane.distance;
            if (std::abs(distance) <= 0.0f) {
                // Se a dist�ncia ao plano � zero, h� uma colis�o
                isColliding = true;
                break;
            }
        }

        // Verifica se a caixa est� cruzando o plano
        if (!isColliding) {
            // Para uma caixa, os planos de face podem intersectar o plano
            glm::vec4 boxPlanes[6][2] = {
                {glm::vec4(bbox_min.x, bbox_min.y, bbox_min.z, 1.0f), glm::vec4(bbox_max.x, bbox_min.y, bbox_min.z, 1.0f)},
                {glm::vec4(bbox_min.x, bbox_min.y, bbox_max.z, 1.0f), glm::vec4(bbox_max.x, bbox_min.y, bbox_max.z, 1.0f)},
                {glm::vec4(bbox_min.x, bbox_min.y, bbox_min.z, 1.0f), glm::vec4(bbox_min.x, bbox_max.y, bbox_min.z, 1.0f)},
                {glm::vec4(bbox_min.x, bbox_min.y, bbox_max.z, 1.0f), glm::vec4(bbox_min.x, bbox_max.y, bbox_max.z, 1.0f)},
                {glm::vec4(bbox_min.x, bbox_min.y, bbox_min.z, 1.0f), glm::vec4(bbox_min.x, bbox_min.y, bbox_max.z, 1.0f)},
                {glm::vec4(bbox_max.x, bbox_min.y, bbox_min.z, 1.0f), glm::vec4(bbox_max.x, bbox_min.y, bbox_max.z, 1.0f)}
            };

            for (const auto& planePair : boxPlanes) {
                glm::vec4 corner1 = planePair[0];
                glm::vec4 corner2 = planePair[1];

                float dist1 = dotproduct(plane.normal, corner1) - plane.distance;
                float dist2 = dotproduct(plane.normal, corner2) - plane.distance;

                if ((dist1 <= 0.0f && dist2 >= 0.0f) || (dist1 >= 0.0f && dist2 <= 0.0f)) {
                    // Se os pontos est�o em lados opostos do plano
                    isColliding = true;
                    break;
                }
            }
        }

        return isColliding;
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

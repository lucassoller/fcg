#pragma once

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace collisions {

    struct Cylinder {
        float radius;
        float height;
        glm::vec4 center;
    };

    struct Sphere {
        glm::vec4 center;
        float radius;
    };

    struct Plane {
        glm::vec4 normal;
        float distance;
    };

    bool checkCollision(const Cylinder& cylinder, const Plane& plane);
    bool checkCollision(const Cylinder& cylinder, const Sphere& sphere);
    bool checkCollision(const Cylinder& cylinder1, const Cylinder& cylinder2);
    bool checkCollision(const Sphere& sphere, const Plane& plane);
    float dotproduct(glm::vec4 u, glm::vec4 v);

}


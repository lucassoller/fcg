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

    bool checkCollision(const Sphere& sphere, const glm::vec3& bbox_min, const glm::vec3& bbox_max, const glm::mat4& modelMatrix);
    bool checkCollision(const Cylinder& cylinder, const glm::vec4& point);
    bool checkCollision(const Cylinder& cylinder, const Sphere& sphere);
    bool checkCollision(const Sphere& sphere, const Plane& plane);
    float dotproduct(glm::vec4 u, glm::vec4 v);

}

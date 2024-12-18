#ifndef PARTICLE_H
#define PARTICLE_H

#include "../glm/glm.hpp"

#include "texture.h"

#include <chrono>
#include <array>

class Particle{
    public:
        Particle(int ttl_ms, glm::vec3 position, glm::vec4 rgba);
        ~Particle() = default;
        Particle& operator=(const Particle&) = default; 

        void update(glm::vec3 vec);
        int getTtl();
        glm::vec3 getPosition();
        friend void swap_particles(Particle &p1, Particle &p2);
    private:
        int ttl_ms;
        glm::vec3 position;
        glm::vec4 rgba;
};
       

#endif

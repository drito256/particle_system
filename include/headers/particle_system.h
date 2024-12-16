#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "../glm/glm.hpp"
#include "particle.h"
#include "texture.h"

#include <vector>


class ParticleSystem{
    public:
        ParticleSystem(Texture texture, glm::vec3 position, glm::vec4 starting_color,
                        glm::vec4 ending_color, int frequency_ms);
        void update_position(glm::vec3 vec); // update position on whole system
        void update(glm::vec3 vec); // update each particle

    private:
        Texture texture;
        std::vector<Particle> particles;
        glm::vec3 pos;
        glm::vec3 starting_color;
        glm::vec3 ending_color;
        int frequency_ms;
};

#endif

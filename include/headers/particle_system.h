#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include "particle.h"
#include "../glad/glad.h"

#include <chrono>
#include <random>
#include <vector>
#include <iostream>


class ParticleSystem{
    public:
        ParticleSystem(Texture texture, glm::vec3 position, glm::vec3 velocity,
                       glm::vec4 starting_color, glm::vec4 ending_color,
                       int particles_per_s);
        void update_position(glm::vec3 vec); // update position on whole system
        void update(std::mt19937& gen, std::uniform_real_distribution<>& dis); // update each particle

    private:
        Texture texture;
        std::vector<Particle> particles;
        glm::vec3 pos;
        glm::vec3 velocity;
        glm::vec3 starting_color;
        glm::vec3 ending_color;
        int particles_per_s;
        int max_particles = 10000;
        std::chrono::high_resolution_clock::time_point start_time;

        unsigned int vao;
        unsigned int vbo;
        unsigned int instance_vbo;

        void generate_particle(std::mt19937& gen, std::uniform_real_distribution<>& dis);
        void setup_buffers();
        void render();
};

#endif

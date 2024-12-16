#include "../include/headers/particle_system.h"



ParticleSystem::ParticleSystem(Texture texture, glm::vec3 position,
                               glm::vec4 starting_color, glm::vec4 ending_color,
                               int frequency_ms)
                            :texture{texture}
                            ,pos{position}
                            ,starting_color{starting_color}
                            ,ending_color{ending_color}
                            ,frequency_ms{frequency_ms}
{}

void ParticleSystem::update_position(glm::vec3 vec){
    this->pos += vec;
}

void ParticleSystem::update(glm::vec3 vec){ // treba uvest random faktor
    for(int i = 0; i < particles.size(); i++){
        if(particles[i].getTtl() <= 0){
            swap_particles(particles[i], particles.back());
            particles.pop_back();
        }
        else{
            particles[i].update(vec);
        }
    }
}



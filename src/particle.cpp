#include "../include/headers/particle.h"


Particle::Particle(int ttl_ms, glm::vec3 position, Texture texture, glm::vec4 rgba)
                    :ttl_ms{ttl_ms}
                    ,position{position}
                    ,texture{texture}
                    ,rgba{rgba}
                    {}

void Particle::update(glm::vec3 vec){
    this->position += vec;
}

int Particle::getTtl(){
    return this->ttl_ms;
}

void swap_particles(Particle &p1, Particle &p2){
    Particle temp = p1;
    p1 = p2;
    p2 = temp;
}

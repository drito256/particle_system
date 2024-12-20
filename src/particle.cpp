#include "../include/headers/particle.h"


Particle::Particle(int ttl_ms, glm::vec3 position, glm::vec3 velocity,glm::vec4 rgba)
                    :ttl_ms{ttl_ms}
                    ,position{position}
                    ,velocity{velocity}
                    ,rgba{rgba}
                    {}

void Particle::update(){
    this->position += velocity;
    applyGravity((1000 - this->ttl_ms)/1000.0 * 50);
    this->ttl_ms--;
}

void Particle::applyGravity(double strength){
    this->position.y -= strength;
}

int Particle::getTtl(){
    return this->ttl_ms;
}

glm::vec3 Particle::getPosition(){
    return this->position;
}

glm::vec3 Particle::getVelocity(){
    return this->velocity;
}

void swap_particles(Particle &p1, Particle &p2){
    Particle temp = p1;
    p1 = p2;
    p2 = temp;
}

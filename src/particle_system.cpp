#include "../include/headers/particle_system.h"
#include <chrono>



ParticleSystem::ParticleSystem(Texture texture, glm::vec3 position,
                               glm::vec4 starting_color, glm::vec4 ending_color,
                               int particles_per_s)
                            :texture{texture}
                            ,pos{position}
                            ,starting_color{starting_color}
                            ,ending_color{ending_color}
                            ,particles_per_s{particles_per_s}
{
    start_time = std::chrono::high_resolution_clock::now();
    setup_buffers();
}

void ParticleSystem::update_position(glm::vec3 vec){
    this->pos += vec;
}

void ParticleSystem::update(glm::vec3 vec){

    generate_particle();

    for(int i = 0; i < particles.size(); i++){
        if(particles[i].getTtl() <= 0){
            swap_particles(particles[i], particles.back());
            particles.pop_back();
        }
        else{
            // nadodati radnom komponentu na vec
            particles[i].update(vec);
        }
    }

    std::vector<glm::vec3> instance_data(max_particles);
    for(int i = 0; i < particles.size(); i++){
        instance_data[i] = particles[i].getPosition();
    }

    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, max_particles * sizeof(glm::vec4), instance_data.data());
}

void ParticleSystem::generate_particle(){
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);

    if(elapsed.count() / 1000.0 >= 1.0 / particles_per_s){
        start_time = std::chrono::high_resolution_clock::now();
        std::cout << "xxx\n";        
        Particle p{1000,
                   this->pos,
                   glm::vec4(1, 0, 0, 0),
        };
        particles.push_back(p);
    }

}

void ParticleSystem::setup_buffers(){
    
    float quad_vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, max_particles * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1); // ovo ce mozda trebat mijenjat za vise atributa cestice

    glBindVertexArray(0);
}

void ParticleSystem::render(){
    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, max_particles);
    glBindVertexArray(0);
}


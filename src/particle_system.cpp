#include "../include/headers/particle_system.h"
#include <random>



ParticleSystem::ParticleSystem(Texture texture, glm::vec3 position, 
                               glm::vec3 velocity, glm::vec4 starting_color,
                               glm::vec4 ending_color, int particles_per_s)
                            :texture{texture}
                            ,pos{position}
                            ,velocity{velocity}
                            ,starting_color{starting_color}
                            ,ending_color{ending_color}
                            ,particles_per_s{particles_per_s}
{
    start_time = std::chrono::high_resolution_clock::now();
    setup_buffers();
}

void ParticleSystem::update_position(glm::vec3 vec){
    this->pos = vec;
}

void ParticleSystem::update(std::mt19937& gen, std::uniform_real_distribution<>& dis){

    generate_particle(gen, dis);
    for(int i = 0; i < particles.size(); i++){
        if(particles[i].getTtl() <= 0){
            swap_particles(particles[i], particles.back());
            particles.pop_back();
        }
        else{
            particles[i].update();
        }
    }

    std::vector<glm::vec3> instance_data(max_particles);
    for(int i = 0; i < particles.size(); i++){
        instance_data[i] = particles[i].getPosition();
    }
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, max_particles * sizeof(glm::vec3), instance_data.data());
    
    render();
}

void ParticleSystem::generate_particle(std::mt19937& gen, std::uniform_real_distribution<>& dis){

    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);

    if(elapsed.count() / 1000.0 >= 1.0 / particles_per_s){
        start_time = std::chrono::high_resolution_clock::now();

        glm::vec3 particle_vec = velocity;
        glm::vec3 random_factor = glm::vec3(dis(gen), dis(gen), dis(gen));
        particle_vec += random_factor;
        Particle p{1000,
                   this->pos,
                   glm::vec3(particle_vec),
                   glm::vec4(1, 0, 0, 0.5),
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

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, max_particles * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1); // ovo ce mozda trebat mijenjat za vise atributa cestica
    glBindVertexArray(0);
}

void ParticleSystem::render(){
    glBindTexture(GL_TEXTURE_2D, this->texture.getID());

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particles.size());
    glBindVertexArray(0);
}


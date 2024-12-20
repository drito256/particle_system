#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "../include/headers/shader.h"
#include "../include/headers/camera.h"
#include "../include/headers/particle_system.h"

// Standard Headers
#include <iostream>
#include <cstdlib>
#include <random>

int width = 1280;
int height = 800;
float fov = 45.f;

void processInput(GLFWwindow *window, Camera &c);

void framebuffer_size_callback(GLFWwindow* window, int w, int h){
	width = w;
	height = h;
	glViewport(0,0,width,height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	fov -= (float)yoffset;
	if(fov < 1.0f)
		fov = 1.0f;
	if(fov > 45.f)
		fov = 45.f;
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
//    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")\n";
}


int main(int argc, char * argv[]) {
	GLFWwindow* window;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "title", nullptr, nullptr);
	if(window == nullptr){
		std::cout << "failed to create opengl context" << std::endl;
		exit(1);
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to init glad" << std::endl;
		return -1;
	}
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 0.5);

    //Camera camera(glm::vec3(-35, -4, -14), -90.f, 0.f);
    Camera camera(glm::vec3(0), -90.f, 0.f);
    Shader shader("shaders/shader.vert", "shaders/shader.frag");

    stbi_set_flip_vertically_on_load(true);
    Texture texture("../res/spark2.png"); 
    ParticleSystem ps(texture, glm::vec3{0,0,-100}, glm::vec3{0,1,1},
                      glm::vec4{100, 0, 100, 255}, glm::vec4{100, 0, 100, 255}, 100 );


	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
    
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window, camera);
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
        shader.use();   
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", camera.getProjectionMatrix());
        shader.setVec3("cameraUp", camera.getUp());
        shader.setVec3("cameraRight", camera.getRight());

        ps.update(gen, dis);

        double mousex, mousey;
        glfwGetCursorPos(window, &mousex, &mousey);
        ps.update_position(glm::vec3(-50 + mousex/10, 50 -mousey/10,-100));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window, Camera& c)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        c.updatePosition(c.getFront());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        c.updatePosition(-c.getFront());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        c.updatePosition(-glm::normalize(glm::cross(c.getFront(), c.getUp())));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        c.updatePosition(glm::normalize(glm::cross(c.getFront(), c.getUp())));

    if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	    c.updateRotation(2.f, 0.f);
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	    c.updateRotation(-2.f ,0.f);
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	    c.updateRotation(0.f, 2.f);
    if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	    c.updateRotation(0.f ,-2.f);

}

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "../include/headers/shader.h"
#include "../include/headers/camera.h"
#include "../include/headers/particle_system.h"

// Standard Headers
#include <iostream>
#include <cstdlib>

int width = 1280;
int height = 800;
float fov = 45.f;

void processInput(GLFWwindow *window, Camera& c);
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

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to init glad" << std::endl;
		return -1;
	}
	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
    
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
        
   

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

#include <aq/common.hpp>

#include <GLFW\glfw3.h>

#include <iostream>



//#include "../include/aq/common.hpp"


int main(int argc, char** argv)
{
	GLFWwindow* window;
	if (!glfwInit())
		return 1;

	window = glfwCreateWindow(800, 600, "AQ", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);


	while (!glfwWindowShouldClose(window))
	{

		// render



		glfwSwapBuffers(window);
		glfwPollEvents();
	}





	//std::cout << "testing\n";
	//std::cin.ignore(); //keep console on screen until input

	glfwTerminate();
	return 0;
}
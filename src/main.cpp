#include <aq/common.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>



GLOBAL const int g_windowWidth =  800;
GLOBAL const int g_windowHeight = 600;

//#include "../include/aq/common.hpp"


void glfwHints() {
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char** argv)
{

	GLFWwindow* window;
	if (!glfwInit())
		return 1;

	glfwHints();

	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "AQ", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewInit();  //init glew after gl context
	


	float vertices[] = { // x,y coords
		0.0f, 0.5f,  // 1
		-0.5f, -0.5f, // 2
		0.5f, -0.5f, // 3
	};

	//put data into vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW  - one upload, many draw
	// GL_DYNAMIC_DRAW - data changed, but still lots of drawing
	// GL_STREAM_DRAW - changes a LOT, every frame

	// define shaders
	const char* vertexShaderText = {
		"#version 120\n"
		"\n"
		"attribute vec2 position;"
		"void main()"
		"{"
		"	gl_Position = vec4(position, 0.0, 1.0);"
		"}"		
	};

	const char* fragmentShaderText = {
		"#version 120\n"
		"\n"
		"void main()"
		"{"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"}"
	};

	// compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// set attribute?
	glBindAttribLocation(shaderProgram, 0, "position");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	//handle escape / F11
	bool running = true;
	bool fullscreen = false;

	while (running)
	{

		// begin render
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		{
			//draw
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window))
			running = false;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) // close window
			running = false;

		if (glfwGetKey(window, GLFW_KEY_F11)) // toggle fullscreen
		{
			fullscreen = !fullscreen;
			GLFWwindow* newwindow;

			if (fullscreen)
			{
				const GLFWvidmode* modes = glfwGetVideoMode(glfwGetPrimaryMonitor()); // get current video mode to set fullscreen res
				newwindow = glfwCreateWindow(modes[0].width, modes[0].height, "AQ", glfwGetPrimaryMonitor(), window);
			}
			else
				newwindow = glfwCreateWindow(g_windowWidth,g_windowHeight, "AQ", nullptr, window);

			glfwDestroyWindow(window);
			window = newwindow;
			glfwMakeContextCurrent(window);
			

		}

	}





	//std::cout << "testing\n";
	//std::cin.ignore(); //keep console on screen until input
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
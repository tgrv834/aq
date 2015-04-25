#include <aq/common.hpp>
#include <aq/shaderprogram.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

GLOBAL const int g_windowWidth =  800;
GLOBAL const int g_windowHeight = 600;

//#include "../include/aq/common.hpp"




INTERNAL void glfwHints() {
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	float vertices[] = { // x,y coords  -> x, y, r, g, b
		//tri strip to make square
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 2    top right
		-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // 3   top left
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 0   bot right
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 1  bot left		
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
	//in-line way
//  const char* vertexShaderText = { "#version",};
//	const char* fragmentShaderText = {
	//from file
	//std::string vertexShaderSource = stringFromFile("data/shaders/default.vert.glsl");
	//const char* vertexShaderText = vertexShaderSource.c_str();
	//std::string fragmentShaderSource = stringFromFile("data/shaders/default.frag.glsl");
	//const char* fragmentShaderText = fragmentShaderSource.c_str();

	AQ::ShaderProgram shaderProgram;
	shaderProgram.attachShaderFromFile(AQ::ShaderType::Vertex, "data/shaders/default.vert.glsl");
	shaderProgram.attachShaderFromFile(AQ::ShaderType::Fragment, "data/shaders/default.frag.glsl");

	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.link();
	shaderProgram.use();


	// compile shaders
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	//glCompileShader(vertexShader);
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	//glCompileShader(fragmentShader);

	//GLuint shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);

	// set attribute?
	//glBindAttribLocation(shaderProgram, 0, "vertPosition");
	//glBindAttribLocation(shaderProgram, 1, "vertColor");

	//glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);


	//GLint uniColor = glGetUniformLocation(shaderProgram, "uniColor");
	




	//handle escape / F11
	bool running = true;
	bool fullscreen = false;

	while (running)
	{

		// begin render
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		{
			//float time = glfwGetTime(); //since init
			//glUniform3f(uniColor, 0.0f, 0.0f, 0.5f * sin(3.0f * time));


			//draw
			glEnableVertexAttribArray(0); //vertposition
			glEnableVertexAttribArray(1); //vertcolor

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);  // from vertex data, grab 2 into attrib 0 (pos), every 5 floats
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid*)(2*sizeof(float)) ); // from vertex data, grab 3 into attib 1 (color), every 5, offset by 2

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glDisableVertexAttribArray(0); //vertposition
			glDisableVertexAttribArray(1); //vertcolor
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
#include <aq/common.hpp>
#include <aq/shaderprogram.hpp>
#include <aq/image.hpp>

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

	float vertices[] = { // x,y coords  -> x, y, r, g, b, s, t
		//tri strip to make square
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // 0    top right - blue
		-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 1   top left - white
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 2   bot right - green
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 3  bot left - red
	};


	//put data into vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	AQ::ShaderProgram shaderProgram;
	shaderProgram.attachShaderFromFile(AQ::ShaderType::Vertex, "data/shaders/default.vert.glsl");
	shaderProgram.attachShaderFromFile(AQ::ShaderType::Fragment, "data/shaders/default.frag.glsl");

	shaderProgram.bindAttributeLocation(0, "vertPosition");
	shaderProgram.bindAttributeLocation(1, "vertColor");
	shaderProgram.bindAttributeLocation(2, "vertTexCoord");
	shaderProgram.link();
	shaderProgram.use();


	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	

	float pixels[] = {
		0, 0, 1,    1, 0, 0,
		0, 1, 0,    1, 1, 0,
	};

	//load tex
	AQ::Image image;
	image.loadFromFile("data/textures/rock1.jpg");
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixelPtr());
	glActiveTexture(GL_TEXTURE0);
	shaderProgram.setUniform("uniTex", 0);
	

	//handle escape / F11
	bool running = true;
	bool fullscreen = false;

	while (running)
	{

		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);

		}


		// begin render
		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		{
			//float time = glfwGetTime(); //since init
			//glUniform3f(uniColor, 0.0f, 0.0f, 0.5f * sin(3.0f * time));


			//draw
			glEnableVertexAttribArray(0); //vertposition
			glEnableVertexAttribArray(1); //vertcolor
			glEnableVertexAttribArray(2); //verttexcoord

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)0);  // from vertex data, grab 2 into attrib 0 (pos), every 5 floats
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(2 * sizeof(float)) ); // from vertex data, grab 3 into attib 1 (color), every 5, offset by 2
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(5 * sizeof(float))); 

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glDisableVertexAttribArray(0); //vertposition
			glDisableVertexAttribArray(1); //vertcolor
			glDisableVertexAttribArray(2); //verttexcoord
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
//Eric Ramírez Valdovinos
//423095203
//Práctica 4: Modelado geométrico
//Fecha de entrega: 29 de febrero de 2025
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f; //nos permite modificar la vista directamente una vez ejecutado el programa, para observar el modelo desde diferentes ángulos
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4: Modelado geometrico Voxel Art Canguro - Eric Ramirez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.608f, 0.220f, 0.016f,//Front
		0.5f, -0.5f, 0.5f,  0.608f, 0.220f, 0.016f,
		0.5f,  0.5f, 0.5f, 0.608f, 0.220f, 0.016f,
		0.5f,  0.5f, 0.5f,  0.608f, 0.220f, 0.016f,
		-0.5f,  0.5f, 0.5f, 0.608f, 0.220f, 0.016f,
		-0.5f, -0.5f, 0.5f, 0.608f, 0.220f, 0.016f,
		
	    -0.5f, -0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,//Back
		 0.5f, -0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,
		 0.5f,  0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,
		 0.5f,  0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,
	    -0.5f,  0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,
	    -0.5f, -0.5f,-0.5f, 0.5176f, 0.2039f, 0.0078f,
		
		 0.5f, -0.5f,  0.5f,  0.5176f, 0.2039f, 0.0078f,
		 0.5f, -0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		 0.5f,  0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		 0.5f,  0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		 0.5f,  0.5f,  0.5f,  0.5176f, 0.2039f, 0.0078f,
		 0.5f,  -0.5f, 0.5f, 0.5176f, 0.2039f, 0.0078f,
      
		-0.5f,  0.5f,  0.5f,  0.5176f, 0.2039f, 0.0078f,
		-0.5f,  0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		-0.5f, -0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		-0.5f, -0.5f, -0.5f,  0.5176f, 0.2039f, 0.0078f,
		-0.5f, -0.5f,  0.5f,  0.5176f, 0.2039f, 0.0078f,
		-0.5f,  0.5f,  0.5f,  0.5176f, 0.2039f, 0.0078f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		
		-0.5f,  0.5f, -0.5f, 0.765f, 0.376f, 0.000,
		0.5f,  0.5f, -0.5f,  0.765f, 0.376f, 0.000f,
		0.5f,  0.5f,  0.5f,  0.765f, 0.376f, 0.000f,
		0.5f,  0.5f,  0.5f,  0.765f, 0.376f, 0.000f,
		-0.5f,  0.5f,  0.5f, 0.765f, 0.376f, 0.000f,
		-0.5f,  0.5f, -0.5f, 0.765f, 0.376f, 0.000f,
	};

	float verticesojosnegros[] = {
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,//Front
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		};

	float verticesbeigeclaro[] = {
		-0.5f, -0.5f, 0.5f, 0.812f, 0.643f, 0.392f,//Front
		0.5f, -0.5f, 0.5f,  0.812f, 0.643f, 0.392f,
		0.5f,  0.5f, 0.5f, 0.812f, 0.643f, 0.392f,
		0.5f,  0.5f, 0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f, 0.5f, 0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f, 0.5f, 0.812f, 0.643f, 0.392f,

		-0.5f, -0.5f,-0.5f, 0.812f, 0.643f, 0.392f,//Back
		 0.5f, -0.5f,-0.5f, 0.812f, 0.643f, 0.392f,
		 0.5f,  0.5f,-0.5f, 0.812f, 0.643f, 0.392f,
		 0.5f,  0.5f,-0.5f, 0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f,-0.5f, 0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f,-0.5f, 0.812f, 0.643f, 0.392f,

		 0.5f, -0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		 0.5f, -0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		 0.5f,  0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		 0.5f,  0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		 0.5f,  0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		 0.5f,  -0.5f, 0.5f, 0.812f, 0.643f, 0.392f,

		-0.5f,  0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f,  0.5f,  0.812f, 0.643f, 0.392f,

		-0.5f, -0.5f, -0.5f, 0.812f, 0.643f, 0.392f,
		0.5f, -0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		0.5f, -0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		0.5f, -0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f,  0.5f, 0.812f, 0.643f, 0.392f,
		-0.5f, -0.5f, -0.5f, 0.812f, 0.643f, 0.392f,

		-0.5f,  0.5f, -0.5f, 0.812f, 0.643f, 0.392f,
		0.5f,  0.5f, -0.5f,  0.812f, 0.643f, 0.392f,
		0.5f,  0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		0.5f,  0.5f,  0.5f,  0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f,  0.5f, 0.812f, 0.643f, 0.392f,
		-0.5f,  0.5f, -0.5f, 0.812f, 0.643f, 0.392f,
		};

	float verticesrositaboca[] = {
		-0.5f, -0.5f, 0.5f, 0.659f, 0.353f, 0.235f,//Front
		0.5f, -0.5f, 0.5f,  0.659f, 0.353f, 0.235f,
		0.5f,  0.5f, 0.5f, 0.659f, 0.353f, 0.235f,
		0.5f,  0.5f, 0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f, 0.5f, 0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f, 0.5f, 0.659f, 0.353f, 0.235f,

		-0.5f, -0.5f,-0.5f, 0.659f, 0.353f, 0.235f,//Back
		 0.5f, -0.5f,-0.5f, 0.659f, 0.353f, 0.235f,
		 0.5f,  0.5f,-0.5f, 0.659f, 0.353f, 0.235f,
		 0.5f,  0.5f,-0.5f, 0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f,-0.5f, 0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f,-0.5f, 0.659f, 0.353f, 0.235f,

		 0.5f, -0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		 0.5f, -0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		 0.5f,  0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		 0.5f,  0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		 0.5f,  0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		 0.5f,  -0.5f, 0.5f, 0.659f, 0.353f, 0.235f,

		-0.5f,  0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f,  0.5f,  0.659f, 0.353f, 0.235f,

		-0.5f, -0.5f, -0.5f, 0.659f, 0.353f, 0.235f,
		0.5f, -0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		0.5f, -0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		0.5f, -0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f,  0.5f, 0.659f, 0.353f, 0.235f,
		-0.5f, -0.5f, -0.5f, 0.659f, 0.353f, 0.235f,

		-0.5f,  0.5f, -0.5f, 0.659f, 0.353f, 0.235f,
		0.5f,  0.5f, -0.5f,  0.659f, 0.353f, 0.235f,
		0.5f,  0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		0.5f,  0.5f,  0.5f,  0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f,  0.5f, 0.659f, 0.353f, 0.235f,
		-0.5f,  0.5f, -0.5f, 0.659f, 0.353f, 0.235f,
		};


	GLuint VAOs[4], VBOs[4]; //lo usaremos asi para indicar que vertex utilizar

	glGenVertexArrays(4, VAOs);
	glGenBuffers(4, VBOs);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAOs[0]);
	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//repetimos para cada color y guardamos en los buffer|
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesojosnegros), verticesojosnegros, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//color de panza beige claro
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbeigeclaro), verticesbeigeclaro, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//color de boca rosita
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesrositaboca), verticesrositaboca, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.510f, 0.655f, 0.725f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAOs[0]); //usaremos el primer arreglo de vertices para el cuerpo, cabeza, orejas, cola y brazos


		//OREJA IZQUIERDA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.28, 0.15f));
		model = glm::translate(model, glm::vec3(-1.1f, 7.5, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OREJA DERECHA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.28, 0.15f));
		model = glm::translate(model, glm::vec3(1.1f, 7.5, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CABEZA
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.4f)); // escalado de la cabeza de la mama
		model = glm::translate(model, glm::vec3(0.0f, 2.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);
		
		//PECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.9f, 0.5f));
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//TRONCO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0, 1.0f, 1.1f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAIDA COLA VERTICAL
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 1.2f, 0.18f));
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAIDA COLA HORIZONTAL
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 0.2f, 0.50f));
		model = glm::translate(model, glm::vec3(0.0f, -4.3f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//BRAZO IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.1f)); 
		model = glm::translate(model, glm::vec3(-3.8f, 2.7f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ANTEBRAZO IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.1, 0.5f)); // 
		model = glm::translate(model, glm::vec3(-3.8f, 6.1, 0.2f)); //
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//BRAZO DERECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.1f));
		model = glm::translate(model, glm::vec3(3.8f, 2.7f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ANTEBRAZO DERECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.1, 0.5f)); // 
		model = glm::translate(model, glm::vec3(3.8f, 6.1, 0.2f)); //
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//MUSLO IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.65f, 0.8f));
		model = glm::translate(model, glm::vec3(-3.0f, -0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//MUSLO DERECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.65f, 0.8f));
		model = glm::translate(model, glm::vec3(3.0f, -0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FEMUR DERECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.3f));
		model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//FEMUR IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.3f));
		model = glm::translate(model, glm::vec3(3.0f, -1.0f, -0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PIE DERECHO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.1f, 0.7f));
		model = glm::translate(model, glm::vec3(-3.0f, -8.5f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PIE IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.1f, 0.7f));
		model = glm::translate(model, glm::vec3(3.0f, -8.5f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CABEZA CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OREJA IZQUIERDA CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.05f));
		model = glm::translate(model, glm::vec3(-1.5f, 8.0f, 9.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OREJA DERECHA CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.05f));
		model = glm::translate(model, glm::vec3(1.5f, 8.0f, 9.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAMBIAMOS AL COLOR BEIGE
		glBindVertexArray(VAOs[2]);

		//TROMPA MAMA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.2f, 0.3f)); // trompa madre
		model = glm::translate(model, glm::vec3(0.0f, 7.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//TROMPA CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.1f, 0.2f)); // trompa madre
		model = glm::translate(model, glm::vec3(0.0f, 5.75f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PANZA MAMA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 0.1f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 8.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//BOLSA MAMA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8, 0.01f, 0.6f));
		model = glm::translate(model, glm::vec3(0.0f, 50.0f, 0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PECHERA MAMA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.9f, 0.1f));
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CARA MAMA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.05f)); // escalado de la cabeza de la mama
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 4.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAMBIAMOS COLOR A ROSITA PARA LA BOCA
		glBindVertexArray(VAOs[3]);

		//BOQUITA CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.04f, 0.02f)); 
		model = glm::translate(model, glm::vec3(0.0f, 13.6f, 35.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//BOCA MADRE
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.1f, 0.02f));
		model = glm::translate(model, glm::vec3(0.0f, 14.5f, 22.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAMBIAMOS AL COLOR NEGRO OJOS Y NARICES
		glBindVertexArray(VAOs[1]);

		//OJO IZQUIERDO MADRE
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.02f)); 
		model = glm::translate(model, glm::vec3(-1.2f, 17.5f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OJO DERECHO MADRE
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.02f));
		model = glm::translate(model, glm::vec3(1.2f, 17.5f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//NARIZ MADRE
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.05f, 0.02f));
		model = glm::translate(model, glm::vec3(0.0f, 31.5f, 22.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OJO IZQUIERDO CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.02f));
		model = glm::translate(model, glm::vec3(-1.3f, 13.4f, 30.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//OJO DERECHO CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.02f));
		model = glm::translate(model, glm::vec3(1.3f, 13.4f, 30.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//NARIZ CRIA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.02f, 0.01f, 0.02f));
		model = glm::translate(model, glm::vec3(0.0f, 60.0f, 35.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the screen buffers
		glfwSwapBuffers(window);
		//glBindVertexArray(0); // desvinculamos al final del frame
	}
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 //función para controlar el movimiento de la cámara, 
	 // utilizando las teclas WASD para mover en el plano horizontal, Page Up y Page Down para mover verticalmente,
	 // y las flechas izquierda y derecha para rotar la vista alrededor del eje Y. 
	 // La tecla Escape se utiliza para cerrar la ventana.
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot += 0.9f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot -= 0.9f;
 }



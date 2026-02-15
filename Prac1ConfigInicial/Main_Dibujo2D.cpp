// Práctica 2: Dibujo de Primitivas en 2D
// Autor: Eric Ramírez Valdovinos
// Fecha: 15/02/2026
// Descripción: Usando diferentes primitivas de OpenGL buscando dibujar una imagen con los puntos dados.
 
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de cabra con primitivas en 2D - Eric Ramírez", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		// ===== PATA TRASERA =====
		-0.84f, -0.88f, 0.0f,   1.0f, 0.0f, 0.5f, // 0  Pezuña trasera inicio
		-0.89f, -0.75f, 0.0f,   1.0f, 0.5f, 0.0f, // 1  Pezuña trasera final
		-0.86f, -0.68f, 0.0f,   1.0f, 0.3f, 0.3f, // 2  Talón trasero
		-0.80f, -0.60f, 0.0f,   0.8f, 0.2f, 0.6f, // 3  Rodilla trasera
		-0.76f, -0.56f, 0.0f,   1.0f, 1.0f, 0.0f, // 4  Inicio cola
		-0.71f, -0.44f, 0.0f,   1.0f, 0.4f, 0.5f, // 5  Cadera
		-0.68f, -0.35f, 0.0f,   0.7f, 0.8f, 0.3f, // 6  Trasero superior
		// COLA
		-0.6f, -0.3f, 0.0f,   0.2f, 1.0f, 0.5f, // 7  Espalda baja
		-0.55f, -0.25f, 0.0f,   0.3f, 0.9f, 0.4f, // 8  Espalda media
		-0.51f, -0.14f, 0.0f,   1.0f, 0.5f, 0.0f, // 9  Hombro
		-0.50f, -0.05f, 0.0f,   1.0f, 0.0f, 1.0f, // 10  Base cabeza
		-0.55f,  0.00f, 0.0f,   1.0f, 0.2f, 0.6f, // 11 Mejilla
		-0.59f,  0.08f, 0.0f,   1.0f, 0.6f, 0.2f, // 12 Frente
		-0.50f,  0.10f, 0.0f,   1.0f, 0.5f, 0.5f, // 13 Hocico superior
		-0.40f,  0.10f, 0.0f,   1.0f, 1.0f, 0.0f, // 14 Punta hocico
		-0.30f, 0.11f, 0.0f,   0.5f, 0.0f, 1.0f, // 15 Barbilla
		-0.20f,  0.14f, 0.0f,   1.0f, 0.0f, 0.0f, // 16 Cuello frontal
		-0.10f, 0.18f, 0.0f,   0.8f, 0.8f, 0.8f, // 17 Cuello superior
		-0.01f, 0.2f, 0.0f,   1.0f, 0.5f, 0.5f, // 18 Cuello final
		0.15f, 0.3f, 0.0f,   1.0f, 0.5f, 0.5f, // 19
		0.25f, 0.35f, 0.0f,   1.0f, 0.3f, 0.7f, // 20
		0.33f, 0.41f, 0.0f,   0.6f, 0.2f, 0.8f, // 21
		0.40f, 0.45f, 0.0f,   1.0f, 0.7f, 0.3f, // 22
		0.47f, 0.47f, 0.0f,   0.7f, 0.7f, 0.2f, // 23
		0.57f, 0.49f, 0.0f,   1.0f, 0.4f, 0.4f, // 24
		0.58, 0.55f, 0.0f,   1.0f, 0.8f, 0.2f, // 25
		0.59f, 0.55f, 0.0f,   1.0f, 0.9f, 0.1f, // 26
		0.63f, 0.51f, 0.0f,   1.0f, 0.6f, 0.3f, // 27
		0.63f, 0.56f, 0.0f,   1.0f, 0.7f, 0.2f, // 28
		0.60f, 0.64f, 0.0f,   1.0f, 0.3f, 0.9f, // 29
		0.56f, 0.70f, 0.0f,   1.0f, 0.5f, 0.7f, // 30
		0.51f, 0.72f, 0.0f,   1.0f, 0.7f, 0.5f, // 31
		0.42f, 0.76f, 0.0f,   1.0f, 0.8f, 0.4f, // 32
		0.35f, 0.71f, 0.0f,   1.0f, 0.4f, 0.8f, // 33
		0.27f, 0.6f, 0.0f,   1.0f, 0.2f, 0.8f, // 34
		0.29f, 0.76f, 0.0f,   1.0f, 0.9f, 0.3f, // 35
		0.30f, 0.80f, 0.0f,   1.0f, 0.5f, 0.5f, // 36
		0.34f, 0.84f, 0.0f,   1.0f, 0.6f, 0.4f, // 37
		0.4f, 0.89f, 0.0f,   1.0f, 0.7f, 0.3f, // 38
		0.42f, 0.90f, 0.0f,   1.0f, 0.8f, 0.2f, // 39	
		0.5f, 0.90f, 0.0f,   1.0f, 0.9f, 0.1f, // 40
		0.6f, 0.88f, 0.0f,   1.0f, 0.6f, 0.4f, // 41
		0.65f,0.85f, 0.0f,   1.0f, 0.4f, 0.6f, // 42
		0.70f, 0.77f, 0.0f,   1.0f, 0.2f, 0.2f, // 43 Curva externa
		0.75f, 0.7f, 0.0f,   1.0f, 0.3f, 0.7f, // 44 Curva externa
		0.79f, 0.6f, 0.0f,   1.0f, 0.5f, 0.5f, // 45 Curva externa
		0.81f, 0.51f, 0.0f,   1.0f, 0.6f, 0.4f, // 46
		0.80f, 0.45f, 0.0f,   1.0f, 0.7f, 0.3f, // 47
		0.81f, 0.36f, 0.0f,   1.0f, 0.8f, 0.2f, // 48
		0.82f, 0.30f, 0.0f,   1.0f, 0.9f, 0.1f, // 49
		0.84f, 0.26f, 0.0f,   1.0f, 0.5f, 0.5f, // 50
		0.80f, 0.20f, 0.0f,   1.0f, 0.6f, 0.4f, // 51
		0.79f, 0.14f, 0.0f,   1.0f, 0.7f, 0.3f, // 52
		0.75f, 0.06f, 0.0f,   1.0f, 0.8f, 0.2f, // 53
		0.74f, 0.10f, 0.0f,   1.0f, 0.9f, 0.1f, // 54
		0.75f, -0.02f, 0.0f,   1.0f, 0.5f, 0.5f, // 55
		0.73f, -0.05f, 0.0f,   1.0f, 0.6f, 0.4f, // 56
		0.71f, -0.07f, 0.0f,   1.0f, 0.7f, 0.3f, // 57
		0.68f, -0.06f, 0.0f,   1.0f, 0.8f, 0.2f, // 58
		0.61f, 0.03f, 0.0f,   1.0f, 0.9f, 0.1f, // 59
		0.52f, 0.02f, 0.0f,   1.0f, 0.5f, 0.5f, // 60
		0.54f, 0.09f, 0.0f,   1.0f, 0.6f, 0.4f, // 61
		0.55f, 0.14f, 0.0f,   1.0f, 0.7f, 0.3f, // 62
		0.59f, 0.16f, 0.0f,   1.0f, 0.8f, 0.2f, // 63
		0.55f, 0.18f, 0.0f,   1.0f, 0.9f, 0.1f, // 64
		0.54f, 0.14f, 0.0f,   1.0f, 0.5f, 0.5f, // 65
		0.50f, 0.0f, 0.0f,   1.0f, 0.6f, 0.4f, // 66
		0.41f, -0.21f, 0.0f,   1.0f, 0.7f, 0.3f, // 67
		0.5, -0.38f, 0.0f,   1.0f, 0.8f, 0.2f, // 68
		0.4, -0.5f, 0.0f,   1.0f, 0.9f, 0.1f, // 69
		0.3, -0.6f, 0.0f,   1.0f, 0.5f, 0.5f, // 70
		0.2, -0.7f, 0.0f,   1.0f, 0.6f, 0.4f, // 71
		0.18, -0.65f, 0.0f,   1.0f, 0.7f, 0.3f, // 72
		0.15, -0.60f, 0.0f,   1.0f, 0.8f, 0.2f, // 73
		0.20, -0.54f, 0.0f,   1.0f, 0.9f, 0.1f, // 74
		0.21, -0.50f, 0.0f,   1.0f, 0.5f, 0.5f, // 75
		0.3f, -0.48f, 0.0f,   1.0f, 0.0f, 0.5f, // 76
		0.38f, -0.40f, 0.0f,   1.0f, 0.7f, 0.3f, // 77
		0.28f, -0.38f, 0.0f,   1.0f, 0.8f, 0.2f, // 78
		0.22f, -0.37f, 0.0f,   1.0f, 0.9f, 0.1f, // 79
		0.12f, -0.30f, 0.0f,   1.0f, 0.5f, 0.5f, // 80
		0.0f, -0.29f, 0.0f,   1.0f, 0.6f, 0.4f, // 81
		-0.15f, -0.28f, 0.0f,   1.0f, 0.7f, 0.3f, // 82
		-0.35f, -0.40f, 0.0f,   1.0f, 0.8f, 0.2f, // 83
		-0.6f, -0.48f, 0.0f,   1.0f, 0.9f, 0.1f, // 84
		-0.69f, -0.60f, 0.0f,   1.0f, 0.5f, 0.5f, // 85
		-.8f, -.8f, 0.0f,   1.0f, 0.6f, 0.4f, // 86 Pata trasera final (cerca de la inicial para cerrar forma)




	};

	unsigned int indices[] = {  // note that we start from 0!
		// Delineado del contorno (Silhouette)
		0,1,2,0,86,2,86,2,85,3,4,85,2,3,85,4,5,85,5,84,85,5,6,84,6,7,84,7,84,83,7,8,83,8,9,83,
		82,83,9,10,9,82,10,14,82,13,14,10,11,12,13,11,10,13,14,82,15,82,15,16,82,16,17,82,81,17,
		81,18,19,81,17,18,81,80,19,19,20,79,79,78,20,80,79,19,78,67,21,67,21,66,21,22,78,
		66,65,22,20,21,78,65,66,22,67,66,22,23,24,65,22,23,65,23,24,64,63,64,24,64,65,23,
		63,24,48,24,25,48,25,26,27,48,47,27,27,28,47,47,46,28,45,46,28,28,29,45,44,45,29,
		30,29,44,43,44,30,30,31,43,42,43,31,41,42,31,40,41,31,31,32,40,39,40,32,38,39,32,
		33,32,38,37,38,33,36,37,33,35,36,33,34,33,35,48,49,63,49,50,63,51,50,63,52,51,63,
		52,53,63,53,54,63,55,54,63,56,55,63,56,55,53,57,56,63,58,57,63,59,58,63,59,60,61,
		61,62,59,62,63,59,67,78,77,67,77,68,77,68,69,77,76,69,76,77,69,76,77,69,70,69,76,
		70,75,76,74,75,70,74,70,75,74,70,71,71,72,74,72,73,74,78,67,22

		// Nota: El último conecta con el principio o cerca de él para cerrar formas
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10); // tamaño del punto
        //glDrawArrays(GL_POINTS,0,4); // dibujar  puntos
		//glDrawArrays(GL_POINTS, 2,1); // dibujar  puntos
        
        //glDrawArrays(GL_LINES,2,3); //unir puntos
		//glDrawArrays(GL_LINE_LOOP, 0, 4); //unir lineas desde el punto x al ultimo punto y
		//glDrawArrays(GL_TRIANGLES, 0, 3); //dibujar triangulo con los puntos 1,2,3
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //dibujar triangulo con los puntos 1,2,3 usando indices
		glDrawElements(GL_TRIANGLES, 300, GL_UNSIGNED_INT, 0);
		// Opcional: Aumentar grosor de línea para estilo "neon"
		glLineWidth(2.0f);
		glPointSize(10.0f); // Para ver los vertices como puntos guía

		//glDrawArrays(GL_POINTS, 0, 87);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// 2. Dibujar las Líneas conectando los puntos (Usando los indices del EBO)
		// Nota: Como estamos usando indices, usamos glDrawElements
		// GL_LINE_STRIP: Une punto A con B, B con C...
		//glDrawElements(GL_LINE_STRIP, 88, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}
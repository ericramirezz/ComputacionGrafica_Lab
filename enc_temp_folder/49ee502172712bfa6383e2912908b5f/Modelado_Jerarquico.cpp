//Eric Ramírez Valdovinos
//423095203
//Práctica 5: Modelado Jerárquico (Garra mecánica)
//Fecha de entrega: 08/03/2026

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float hombro = 0.0f,
codo = 0.0f, muneca = 0.0f,
dedo1a = 90.0f, dedo1b = -90.0f, dedo1c = -54.0f,
dedo2a = 90.0f, dedo2b = -90.0f, dedo2c = -54.0f,
dedo3a = 90.0f, dedo3b = -90.0f, dedo3c = -54.0f,
dedo4a = 90.0f, dedo4b = -90.0f, dedo4c = -54.0f,
dedo5a = 90.0f, dedo5b = -90.0f, dedo5c = -54.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5: Modelado jerarquico (Garra mecanica) - Eric Ramirez", nullptr, nullptr);

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
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.969f, 0.945f, 0.765f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Modelo base de la garra
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //aplicamos la rotación del hombro
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f)); //matriz auxiliar para el brazo que tiene una traslación respecto al hombro
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f)); //escalamos el cubo para formar el brazo
		color = glm::vec3(0.447f, 0.455f, 0.459f); //color del brazo acero
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //actualizamos el color del shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); //enviamos la matriz de modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos el brazo


		//Modelo base 2 de la garra
		model = glm::translate(modelTemp, glm::vec3(0.0f, -1.5f, 0.0f)); //matriz auxiliar para el antebrazo que tiene una traslación respecto al brazo
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 0.0, 1.0f)); //aplicamos la rotación del codo
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f)); //matriz auxiliar para el antebrazo que tiene una traslación respecto al codo
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f)); //escalamos el cubo para formar el antebrazo
		color = glm::vec3(0.447f, 0.455f, 0.459f); //color del antebrazo
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); 

		//Modelo mano
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.7f, 0.0f)); //matriz auxiliar para la mano que tiene una traslación respecto al antebrazo
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(0.0f, 0.0, 1.0f)); //aplicamos la rotación del codo para que la mano gire con el antebrazo
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); //matriz auxiliar para la mano que tiene una traslación respecto al codo
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f)); //escalamos el cubo para formar la mano
		color = glm::vec3(0.447f, 0.455f, 0.459f); //color de la mano
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// PINZA 1
		//modelo dedo1a
		model = glm::translate(modelTemp, glm::vec3(0.31f, -0.35f, 0.375f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(-1.0f, 0.0, 1.0f)); //aplicamos la rotación del dedo1 para que gire con la mano
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f)); //escalamos el cubo para formar el dedo1
		color = glm::vec3(0.000f, 0.000f, 0.000f); //color del dedo1
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// modelo dedo1b
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(-1.0f, 0.0, 1.0f)); //aplicamos la rotación del dedo1 para que gire con la mano
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f)); //escalamos el cubo para formar el dedo1
		color = glm::vec3(0.165f, 0.239f, 0.376f); //color del dedo1
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//modelo dedo1c
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(-1.0f, 0.0, 1.0f)); //aplicamos la rotación del dedo1 para que gire con la mano
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.0f)); //matriz auxiliar para el dedo1 que tiene una traslación respecto a la mano
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f)); //escalamos el cubo para formar el dedo1
		color = glm::vec3(0.984f, 0.737f, 0.016f); //color del dedo
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		modelTemp = modelTemp2; //regresamos la matriz temporal al estado de la mano para que el siguiente dedo tenga la misma base de transformación

		// PINZA 2
		//modelo dedo2a
		model = glm::translate(modelTemp, glm::vec3(-0.31f, -0.35f, 0.375f)); 
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(-1.0f, 0.0, -1.0f)); //aplicamos  una rotación opuesta a la del dedo1 para que el dedo2 gire en sentido contrario al dedo1
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); 
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f)); 
		color = glm::vec3(0.000f, 0.000f, 0.000f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// modelo dedo2b
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(-1.0f, 0.0, -1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); 
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f)); 
		color = glm::vec3(0.165f, 0.239f, 0.376f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//modelo dedo2c
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(-1.0f, 0.0, -1.0f)); 
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.984f, 0.737f, 0.016f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		modelTemp = modelTemp2;

		// PINZA 3
		//modelo dedo3a
		model = glm::translate(modelTemp, glm::vec3(-0.4f, -0.35f, -0.05f));
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(0.0f, 0.0, -1.0f)); //como ya no esta en un vertice, ahora rotamos solo en Z para que el dedo gire en sentido contrario a los dedos 1 y 2
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.000f, 0.000f, 0.000f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// modelo dedo3b
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0, -1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f));
		color = glm::vec3(0.165f, 0.239f, 0.376f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//modelo dedo3c
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(0.0f, 0.0, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.984f, 0.737f, 0.016f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		modelTemp = modelTemp2;

		// PINZA 4
		//modelo dedo4a
		model = glm::translate(modelTemp, glm::vec3(0.4f, -0.35f, -0.05f));
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(0.0f, 0.0, 1.0f)); //invertimos la rotación para que el dedo 3, porque esta en la arista contraria de la base
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.000f, 0.000f, 0.000f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// modelo dedo4b
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f));
		color = glm::vec3(0.165f, 0.239f, 0.376f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//modelo dedo4c
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(0.0f, 0.0, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.984f, 0.737f, 0.016f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		modelTemp = modelTemp2;

		// PINZA 5
		//modelo dedo5a
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.35f, -0.40f));
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(1.0f, 0.0, 0.0f)); //ahora solo tenemos que rotar en Y para abrir la garra de hasta arriba del pentagono 
		//que estamos formando con las 5 garras
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.000f, 0.000f, 0.000f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// modelo dedo5b
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(1.0f, 0.0, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f));
		color = glm::vec3(0.165f, 0.239f, 0.376f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//modelo dedo5c
		model = glm::translate(modelTemp, glm::vec3(0.0f, -0.55f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(1.0f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 1.2f, 0.2f));
		color = glm::vec3(0.984f, 0.737f, 0.016f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);//limpia configuración de VAO
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX += 0.1f;
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX -= 0.1f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot += 0.30f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot -= 0.30f;
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		 codo += 0.20f;
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		 codo -= 0.20f;
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 muneca += 0.20f;
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 muneca -= 0.20f;
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	 {
		 dedo1a += 0.3f; dedo1b -= 0.3f; dedo1c -= 0.18f;
		 dedo2a += 0.3f; dedo2b -= 0.3f; dedo2c -= 0.18f;
		 dedo3a += 0.3f; dedo3b -= 0.3f; dedo3c -= 0.18f;
		 dedo4a += 0.3f; dedo4b -= 0.3f; dedo4c -= 0.18f;
		 dedo5a += 0.3f; dedo5b -= 0.3f; dedo5c -= 0.18f;
		 if (dedo1a > 90.0f or dedo1b < -90.0f or dedo1c < -54.0f) {// hacemos esto para truncar el movimiento de los dedos para que no se sobrepasen su posición inicial de retracción
			dedo1a = 90.0f, dedo1b = -90.0f, dedo1c = -54.0f,
			dedo2a = 90.0f, dedo2b = -90.0f, dedo2c = -54.0f,
			dedo3a = 90.0f, dedo3b = -90.0f, dedo3c = -54.0f,
			dedo4a = 90.0f, dedo4b = -90.0f, dedo4c = -54.0f,
			dedo5a = 90.0f, dedo5b = -90.0f, dedo5c = -54.0f;
		 }
	 }

	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	 {
		 dedo1a -= 0.3f; dedo1b += 0.3f; dedo1c += 0.18f;
		 dedo2a -= 0.3f; dedo2b += 0.3f; dedo2c += 0.18f;
		 dedo3a -= 0.3f; dedo3b += 0.3f; dedo3c += 0.18f;
		 dedo4a -= 0.3f; dedo4b += 0.3f; dedo4c += 0.18f;
		 dedo5a -= 0.3f; dedo5b += 0.3f; dedo5c += 0.18f;
		 if (dedo1a < 26.0f or dedo1b > -26.0f or dedo1c > -15.0f) { //hacemos esto para truncar el movimiento de los dedos para que no se sobrepasen su estiuramiento máximo
			 dedo1a = 26.0f; dedo1b = -26.0f; dedo1c = -15.0f;
			 dedo2a = 26.0f; dedo2b = -26.0f; dedo2c = -15.0f;
			 dedo3a = 26.0f; dedo3b = -26.0f; dedo3c = -15.0f;
			 dedo4a = 26.0f; dedo4b = -26.0f; dedo4c = -15.0f;
			 dedo5a = 26.0f; dedo5b = -26.0f; dedo5c = -15.0f;
		 }

	 }
 }



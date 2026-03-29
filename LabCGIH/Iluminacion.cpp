// Eric Ramírez Vadlovinos
// 423095203
// Practica 8: Materiales e iluminación – Sol y Luna
// Fecha de entrega: 29/03/2026

#include <string>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SOIL2/SOIL2.h"
#include "stb_image.h"

const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

Camera camera(glm::vec3(0.0f, 1.0f, 9.0f));
bool keys[1024] = {};
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//parámetros del modelo jerárquico
const float radio = 3.5f;
const float vel_traslacion = 0.65f;   // rad/segundo

//inclinación del plano orbital respecto al eje X (grados).
const float ang_inclinacion = 25.0f;

float angulo_sol = 0.0f;
float angulo_luna = 0.5f; 

bool modoDia = true;   // true = Sol , false = Luna

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        WIDTH, HEIGHT,
        "Practica 8: Materiales e Iluminacion (Sol y Luna) - Eric Ramirez",
        nullptr, nullptr);

    if (!window) { glfwTerminate(); return EXIT_FAILURE; }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) return EXIT_FAILURE;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    //modelo de luna
    Model luna((char*)"Models/luna.obj");

	//modelo de sol
    Model sol((char*)"Models/sun.obj");

    //modelo pelota playa central
    Model planetaPelota((char*)"Models/beach_ball.obj");

    GLuint texturaPlaneta;
    glGenTextures(1, &texturaPlaneta);
    glBindTexture(GL_TEXTURE_2D, texturaPlaneta);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int texW, texH, nrCh;
    unsigned char* img = stbi_load("Models/Image_0.png", &texW, &texH, &nrCh, 0);
    if (img)
    {
        GLenum fmt = (nrCh == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, texW, texH, 0, fmt, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(img);

    glm::mat4 projection = glm::perspective(
        glm::radians(camera.GetZoom()),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
        0.1f, 100.0f);

    //abrimos el game loop
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

		// avanzamos angulos de traslacion alrededor de la pelota
        angulo_sol += vel_traslacion * deltaTime;
        angulo_luna += vel_traslacion * deltaTime;
        if (angulo_sol > glm::two_pi<float>()) angulo_sol -= glm::two_pi<float>();
        if (angulo_luna > glm::two_pi<float>()) angulo_luna -= glm::two_pi<float>();

        //Implementamos un modelo jerarquico para no tener que usar funciones sen y cos
        //asi todo el sistema gira alrededor de la posicion inial de la pelota

        float tiltRad = glm::radians(ang_inclinacion); //inclinamos 25 grados la orbita de la luna y el sol

		//pelota es el nodo raíz del sistema, no tiene transformaciones propias, solo sirve de referencia para el sol y la luna
        //inclina el sistema completo 25° en X.
        //sube y baja en diagonal conforme da vueltas.
        glm::mat4 nodoRaiz_pelota = glm::rotate(
            glm::mat4(1.0f),
            tiltRad,
            glm::vec3(1.0f, 0.0f, 0.0f));

        // hereda nodoRaiz_pelota y añade la rotación animada en Y local.
        glm::mat4 nodoOrbitaSol = glm::rotate( //sol
			nodoRaiz_pelota, // hereda la inclinación
            angulo_sol,
            glm::vec3(0.0f, 1.0f, 0.0f));

        //traslada al radio de la órbita en el eje X local.
        glm::mat4 nodoPosicionSol = glm::translate(
            nodoOrbitaSol,
			glm::vec3(radio, 0.0f, 0.0f)); //esta alejado del origen (pelota) a la distancia del radio

        //esta es la posición que pasamos al shader como luz.
        glm::vec3 posSolMundo = glm::vec3(
            nodoPosicionSol * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        //añade escala y spin propio. Hereda la posición.
        glm::mat4 modelSol = glm::scale(nodoPosicionSol, glm::vec3(0.6f));
        modelSol = glm::rotate(modelSol,
            angulo_sol * 2.0f,
            glm::vec3(0.0f, 1.0f, 0.0f));

        //repetimos el proceso con los nodos para la luna
        glm::mat4 nodoOrbitaLuna = glm::rotate(
            nodoRaiz_pelota,
            angulo_luna,
            glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 nodoPosicionLuna = glm::translate(
            nodoOrbitaLuna,
            glm::vec3(radio, 0.0f, 0.0f));

        glm::vec3 posLunaMundo = glm::vec3(
            nodoPosicionLuna * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glm::mat4 modelLuna = glm::scale(nodoPosicionLuna, glm::vec3(1.5f));
        modelLuna = glm::rotate(modelLuna,
            angulo_luna * 2.0f,
            glm::vec3(0.0f, 1.0f, 0.0f));

        //posición de la fuente de luz activa
        //si modoDia es True, se usa la posicion del sol, de otra froma la de la luna.
        glm::vec3 posActiva = modoDia ? posSolMundo : posLunaMundo;

        glClearColor(0.01f, 0.01f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();

		//usamos el shader de iluminación para dibujar la pelota, que es el objeto que recibe la luz del sol/luna.
        lightingShader.Use();

        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
            camera.GetPosition().x,
            camera.GetPosition().y,
            camera.GetPosition().z);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"),
            1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"),
            1, GL_FALSE, glm::value_ptr(view));

		if (modoDia) // si es de día, la luz es cálida y brillante, con un ambient muy bajo para que haya sombras reales
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].position"),
                posActiva.x, posActiva.y, posActiva.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].ambient"),
                0.15f, 0.15f, 0.05f);   // sombras
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].diffuse"),
				1.00f, 0.95f, 0.95f);     //luz difusa cálida
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].specular"),
				1.00f, 0.95f, 1.0f);     //reflejo  brillante

            //configuramos la luz de los materiales
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"),
				0.50f, 0.55f, 0.40f);//hace que la pelota regleje la luz ambiental del sol
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"),
				0.96f, 1.0f, 0.90f); //hace que la pelota tenga un color claro, casi blanco al reflejar la luz del sol
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"),
				0.98f, 0.90f, 0.90f); // reflejo muy brillante
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"),
				1.0f);// brillo muy alto para que el reflejo del sol sea un punto muy pequeño y brillante
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].position"),
                posActiva.x, posActiva.y, posActiva.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].ambient"),
				0.2f, 0.15f, 0.2f); //alta oscutridad para le modo noche
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].diffuse"),
				0.9f, 0.9f, 0.9f); //aunque la luz de la luna es blanca, el ambiente oscuro hace que el color difuso se vea más apagado
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lights[0].specular"),
                0.05f, 0.10f, 0.05f); //reflejo bajo para simular una luz fría

            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"),
                0.23f, 0.23f, 0.26f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"),
                0.32f, 0.54f, 0.25f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"),
                0.3f, 0.03f, 0.15f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"),
                0.2f); // ponemos un valor bajo para que la luz lunar se esparza y no se concetre tan fuerte
        }

        //NODO PLANETA
        // El planeta es hijo del nodoRaiz_pelota (hereda la inclinación).
        // Se queda en el origen (sin traslación) y solo escala
        // y gira sobre sí mismo.
        glm::mat4 modelPlaneta = glm::scale(nodoRaiz_pelota, glm::vec3(0.1f));
         
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"),
            1, GL_FALSE, glm::value_ptr(modelPlaneta));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturaPlaneta);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "texture_diffusse"), 0); //le pasamos la textura al shader

		planetaPelota.Draw(lightingShader); //dibujamos la pelota, que es el objeto que recibe la luz del sol/luna

		lampShader.Use();//usamos el shader de la lámpara para dibujar el sol y la luna, que son las fuentes de luz
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "projection"),
            1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "view"),
            1, GL_FALSE, glm::value_ptr(view));

        if (modoDia)
        {
            glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"),
                1, GL_FALSE, glm::value_ptr(modelSol));
			sol.Draw(lampShader);//dibujamos el sol, que es la fuente de luz activa en modo día
        }
        else
        {
            glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"),
                1, GL_FALSE, glm::value_ptr(modelLuna));
			luna.Draw(lampShader);//dibujamos la luna, que es la fuente de luz activa en modo noche
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)   keys[key] = true;
        if (action == GLFW_RELEASE) keys[key] = false;
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        modoDia = !modoDia;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = (GLfloat)xPos;
        lastY = (GLfloat)yPos;
        firstMouse = false;
    }
    GLfloat xOffset = (GLfloat)xPos - lastX;
    GLfloat yOffset = lastY - (GLfloat)yPos;
    lastX = (GLfloat)xPos;
    lastY = (GLfloat)yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}
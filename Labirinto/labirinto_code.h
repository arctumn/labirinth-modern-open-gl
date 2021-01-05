#ifndef __LAB_CODE_H__
#define __LAB_CODE_H__
#endif


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader_m.h>
#include <camera.h>
#include <model.h>
#include <iostream>
#include "GenerateLab.h"
#include <filesystem>
#include <audio/irrKlang.h>
#include <time.h>
#include "text_renderer.h"





// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool fullscreen = false;
bool noclip = false;
bool mapa = false;
bool textEnabled = false;
time_t start;
bool end_game = false;
int FOV = 10;


//Lab LIMITS
const pair<float, float> BOTTOM_LEFT  = std::make_pair(-0.5f, -0.5f);


//flag Saida com o objeto da colision
pair<int, int> pos; // make_pair(posX, posZ);
pair<int, bool> colldisable; // make_pair(indice_que_represanta_pair_pos, false);
pair<pair<int,int>,pair<int,bool>> saida = make_pair(pos,colldisable);
int countSaida = 0;

//UNIT SIZE
const float UNIT_SIZE = 1.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Pos Matrix

int** matrix;


// lighting
glm::vec3 lightPos;
glm::vec3 startPosCamera;

const float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
glm::mat4 * load(Model obj, int *amount, float scale, glm::mat4 * matrices);
void produceExit(GLFWwindow *window, glm::mat4 *matrices, Model obj, int getAmount);
void hideWorld(Shader shadow,bool apagar);
void showDistance(float x1, float z1, float x2, float z2);
bool pointInside(float point_x, float point_z, float box_x, float box_z);
void endGame(TextRenderer *texto);
void guiaText(TextRenderer *texto, float resultado, float fps);
void playMusic();
float distancia(float x1, float z1, float x2, float z2);
void setShaders(Shader shadow);
void atribuir(unsigned int VBO, unsigned int lightVAO);

std::vector<pair<float, float>> posicoesColision(std::vector<pair<float, float>> cubePos, int *amount);





void gameLoop
(
	GLFWwindow * window,
	Shader lampShader,
	unsigned int VAO,
	unsigned int lightVAO,
	Shader cube,
	int amount,
	glm::mat4 * modelMatrices,
	Model wall,
	std::vector<pair<float, float>> cubePos,
	TextRenderer * texto,
	int nbFrames,
	double lastTime,
	int fps,
	double resultado,
	glm::vec3 lastPos,
	bool collided
);



using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		textEnabled = true;
	}
	//else { textEnabled = false; }
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		camera.MovementSpeed = 15.0f;
		noclip = !noclip;
		FOV = 20;
	}
	if (noclip == false) { camera.Position.y = 0; camera.MovementSpeed = 5.0f; FOV = 5; }
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		camera.Position.y = 10;
	}
	else if (noclip == false) camera.Position.y = 0;
	if (!end_game) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.ProcessKeyboard(FORWARD, deltaTime);
			lightPos.x = camera.Position.x;
			lightPos.y = 1;
			lightPos.z = camera.Position.z;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.ProcessKeyboard(BACKWARD, deltaTime);
			lightPos.x = camera.Position.x;
			lightPos.y = 1;
			lightPos.z = camera.Position.z;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.ProcessKeyboard(LEFT, deltaTime);
			lightPos.x = camera.Position.x;
			lightPos.y = 1;
			lightPos.z = camera.Position.z;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.ProcessKeyboard(RIGHT, deltaTime);
			lightPos.x = camera.Position.x;
			lightPos.y = 1;
			lightPos.z = camera.Position.z;
		}
		if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {

			// Toggle fullscreen flag.
			fullscreen = !fullscreen;

			glfwSetWindowMonitor(window, fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, SCR_WIDTH, SCR_HEIGHT, GLFW_DONT_CARE);

		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos); // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}

glm::mat4 *load(Model obj, int * getAmount, float scale, glm::mat4 *matrices)
{
	unsigned int len = sized;

	unsigned int amount = 0;

	//calcula a quantitades de nao p
	for (unsigned int i = 0; i < len; i++)
		for (unsigned int j = 0; j < len; j++)
			if (matrix[i][j]) amount++;

	*getAmount = amount;
	matrices = new glm::mat4[amount];
	srand((int)glfwGetTime()); // initialize random seed	

	glm::vec3 position(0, 0, 0);
	bool firstH = true;
	int a = 0;
	for (unsigned int i = 0; i < len; i++)
		for (unsigned int j = 0; j < len; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			// only calculates what is needed skips positioning useless blocks
			if (!matrix[i][j])
				continue;
			//model = glm::translate(model, glm::vec3(i, 100,j));
			else {
				if (i == saida.first.first && j == saida.first.second) {
					saida.second.first = a;
					saida.second.second = false;
				}
				model = glm::translate(model, glm::vec3(i, 0, j));
			}
			model = glm::scale(model, glm::vec3(scale));
			if (firstH) {
				int tamanho = (int)sqrtf(powf(0, 2.0) + powf(0, 2.0));
				//std::cout << "\nLado do model " << tamanho << " coordenadas x: " << i << " z: " << j;
				position.x = (float)i;
				position.z = (float)j;
				firstH = false;
			}
			else {
				int tamanho = (int)sqrtf(powf(i - position.x, 2.0) + powf(j - position.z, 2.0));
				//std::cout << "\nTamanho do model: " << tamanho << " coordenadas x: " << i << " z: " << j;
				position.x = i;
				position.z = j;
			}
			//}

			//glm::length(model);
			// 4. now add to list of matrices
			matrices[a] = model;
			a++;
		}

	//writeToPos(matrices, obj, amount);

	return matrices;

}

void setShaders(Shader shadow) {

	glm::vec3 pointLightColors[] =
	{
		glm::vec3(0.1f, 0.1f, 0.1f),
	};

	shadow.use();
	shadow.setVec3("viewPos", camera.Position);
	shadow.setFloat("material.shininess", 32.0f);
	//cube.use();
	glUniform3f(glGetUniformLocation(shadow.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shadow.ID, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shadow.ID, "dirLight.diffuse"), 0.05f, 0.05f, 0.05);
	glUniform3f(glGetUniformLocation(shadow.ID, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
	// Point light 1
	glUniform3f(glGetUniformLocation(shadow.ID, "pointLights[0].position"), camera.Position.x, camera.Position.y + 1, camera.Position.z);
	glUniform3f(glGetUniformLocation(shadow.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
	glUniform3f(glGetUniformLocation(shadow.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform3f(glGetUniformLocation(shadow.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(shadow.ID, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shadow.ID, "pointLights[0].linear"), 0.14);
	glUniform1f(glGetUniformLocation(shadow.ID, "pointLights[0].quadratic"), 0.07);

	// SpotLight
	glUniform3f(glGetUniformLocation(shadow.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(shadow.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(shadow.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shadow.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shadow.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shadow.ID, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shadow.ID, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(shadow.ID, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(shadow.ID, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
	glUniform1f(glGetUniformLocation(shadow.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
}

void produceExit(GLFWwindow* window, glm::mat4* matrices, Model obj, int getAmount) {
	if (saida.second.second)
		return;

	float distancia = sqrtf(powf(saida.first.first - camera.Position.x, 2.0) + powf(saida.first.second - camera.Position.z, 2.0));
	if (distancia < (float)sized / 3) {
		std::cout << "\nDistancia: " << distancia << "\n";
		matrices[saida.second.first] = glm::translate(matrices[saida.second.first], glm::vec3(666, 0, 0));
		//writeToPos(matrices, obj, getAmount);
		saida.second.second = true;

	}

}


void gameLoop
(
	GLFWwindow * window,
	Shader lampShader,
	unsigned int VAO,
	unsigned int lightVAO,
	Shader cube,
	int amount,
	glm::mat4 * modelMatrices,
	Model wall,
	std::vector<pair<float, float>> cubePos,
	TextRenderer * texto,
	int nbFrames,
	double lastTime,
	int fps,
	double resultado,
	glm::vec3 lastPos,
	bool collided
)
{
	while (!glfwWindowShouldClose(window))
	{


		camera.Zoom = 50.0f;
		// per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		// world transformation
		glm::mat4 model = glm::mat4(1.0f);

		{
			lampShader.use();
			lampShader.setMat4("projection", projection);
			lampShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lampShader.setMat4("model", model);
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		{
			setShaders(cube);
			cube.use();
			cube.setMat4("projection", projection);
			cube.setMat4("view", view);


			for (int i = 0; i < amount; i++) {
				cube.setMat4("model", modelMatrices[i]);
				time_t end = time(NULL);
				cube.use();

				produceExit(window, modelMatrices, wall, amount);
				if (distancia(cubePos[i].first, cubePos[i].second, camera.Position.x, camera.Position.z) < FOV)
					wall.Draw(cube);
				//Esconde o mundo do jogador
				hideWorld(cube, (end - start) % 8 == 0);
			}
		}

		endGame(texto);

		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			resultado = 1000.0 / double(nbFrames);
			fps = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}
		guiaText(texto, resultado, fps);

		if (saida.second.second) cubePos[saida.second.first] = std::make_pair(999.0f, 999.0f);

		if (!noclip) {
			for (int i = 0; i < amount; i++)
				if (pointInside(camera.Position.x, camera.Position.z, cubePos[i].first, cubePos[i].second)) {
					camera.Position = lastPos;
					collided = true;
					break;
				}
				else collided = false;
		}
		if (!collided) lastPos = camera.Position;


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void hideWorld(Shader shadow, bool apagar) {
	if (apagar) {
		shadow.use();
		shadow.setFloat("visibility", 0.0);
	}
	else {
		shadow.use();
		shadow.setFloat("visibility", 1.0);
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void showDistance(float x1, float z1, float x2, float z2) {
	cout << "Distance = " << sqrtf(powf(x2 - x1, 2.0f) + powf(z2 - z1, 2.0f)) << endl;
}



bool pointInside(float point_x, float point_z, float box_x, float box_z) {
	if (point_x >= box_x - 0.2f && point_x <= box_x + UNIT_SIZE + 0.2f)
		if (point_z >= box_z - 0.2f && point_z <= box_z + UNIT_SIZE + 0.2f)
			return true;
	return false;
}

void playMusic() {
	SoundEngine->play2D("./music/Loyalty_Freak_Music_-_07_-_A_really_dark_alley.mp3", true);
}
void endGame(TextRenderer *texto) {
	if ((int)camera.Position.x < 0 || (int)camera.Position.z < 0)
	{
		srand(time(NULL));
		texto->Load("fonts/ARIALNB.TTF", 50);
		float colors_red = (rand() % 100) / 100.0f;
		float colors_green = (rand() % 100) / 100.0f;
		float colors_blue = (rand() % 100) / 100.0f;

		//std::cout << "r: " << colors_red << " g:" << colors_green << " b:" << colors_blue << endl;;
		texto->RenderText("THE END!", SCR_WIDTH / 2, SCR_HEIGHT / 2, 1, glm::vec3(colors_red, colors_green, colors_blue));
		if (noclip == false)
			camera.MovementSpeed = 0.f;
		else {
			camera.MovementSpeed = 10.f;
		}
		end_game = true;
		noclip = true;
	}
}
void guiaText(TextRenderer *texto, float resultado, float fps) {
	if (textEnabled) {
		ostringstream *stringEscrita = new ostringstream;
		*stringEscrita << "Latency: " << resultado << " ms";
		texto->RenderText(stringEscrita->str(), 25.0f, 25.0f, 0.5);
		stringEscrita->str("");
		*stringEscrita << "Exit x: " << saida.first.first << " z: " << saida.first.second;
		texto->RenderText(stringEscrita->str(), SCR_WIDTH - 150.0f, 50.0f, 0.5);
		stringEscrita->str("");
		*stringEscrita << " x: " << (int)camera.Position.x << " z: " << (int)camera.Position.z;
		texto->RenderText(stringEscrita->str(), SCR_WIDTH - 150.0f, 25.0f, 0.5);
		stringEscrita->str("");
		*stringEscrita << "FPS: " << fps;
		texto->RenderText(stringEscrita->str(), 25.0f, 50.0f, 0.5);
		//stringEscrita->str("");
		delete stringEscrita;
	}
}
float distancia(float x1, float z1, float x2, float z2) {
	return sqrtf(powf(x2 - x1, 2.0f) + powf(z2 - z1, 2.0f));
}

void atribuir(unsigned int VBO, unsigned int lightVAO) {
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// lightsource 1

		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
}


std::vector<pair<float, float>> posicoesColision(std::vector<pair<float, float>> cubePos,int *amount) {
	for (unsigned int i = 0; i < sized; i++)
		for (unsigned int j = 0; j < sized; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			// only calculates what is needed skips positioning useless blocks
			if (!matrix[i][j])
				continue;
			//model = glm::translate(model, glm::vec3(i, 100,j));
			else {
				cubePos.push_back(std::make_pair(BOTTOM_LEFT.first + i * UNIT_SIZE, BOTTOM_LEFT.second + j * UNIT_SIZE));
				*amount++;
			}
		}
	return cubePos;
}
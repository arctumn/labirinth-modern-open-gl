#pragma once
#include "./labirinto_code.h"
using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

int main()
{

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Labirinto", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	//-----------BEGIN------------//

	matrix = new int* [sized];
	for (int i = 0; i < sized; i++) matrix[i] = new int[sized];
	CriaLab(matrix);
	while (true) {
		int i = rand() % sized;
		int j = rand() % sized;
		if (!matrix[i][j]) {
			camera.Position = glm::vec3(i + rand() % 100 / 100, 0, j + rand() % 100 / 100);
			startPosCamera = camera.Position;
			lightPos = camera.Position;
			lightPos.y = 1;
			break; 
		}
	}
	saida.first = EscolheSaida(matrix, camera); // Candidados para Saídas
	
	// build and compile our shader program
	// ------------------------------------
	Shader lampShader("shaders/2.1.lamp.vs", "shaders/2.1.lamp.fs");
	Shader cube("shaders/cube.vs", "shaders/cube.fs");
	Model wall("objects/rock/wall.obj");

	TextRenderer *texto = new TextRenderer(SCR_WIDTH, SCR_HEIGHT);
	
	int amount = 0;

	glm::mat4 *modelMatrices = NULL;
	modelMatrices = load(wall, &amount, 0.5f, modelMatrices);
	std::ostringstream in;
	
	const int value = amount;
	pair<float, float> *cubePos = (pair<float, float> *)calloc(amount,sizeof(pair<float,float>));
	int h = 0;
	for (unsigned int i = 0; i < sized; i++)
		for (unsigned int j = 0; j < sized; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			// only calculates what is needed skips positioning useless blocks
			if (!matrix[i][j])
				continue;
			//model = glm::translate(model, glm::vec3(i, 100,j));
			else {
				cubePos[h] = std::make_pair(BOTTOM_LEFT.first+i*UNIT_SIZE, BOTTOM_LEFT.second + j * UNIT_SIZE);
				h++;
			}
		}


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
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
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO;
	unsigned int lightVAO;
	{
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
	bool firstTime = true;
	float lastXthis = 0;
	float lastZtihs = 0;

	glm::vec3 lastPos(camera.Position);

	float movementSpeed = camera.MovementSpeed;
	bool collided = false;

	std::thread music_player(playMusic);

	int nbFrames = 0;
	double lastTime = 0.0;
	time_t end;

	bool apagar = false,atualizar = true;
	double resultado = 0;
	ostringstream stringEscrita;
	start = time(NULL);
	int fps = 0;
	
	cube.use();
	cube.setInt("material.diffuse", 0);
	cube.setInt("material.specular", 1);


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
		glm::vec3 pointLightColors[] = 
		{
			glm::vec3(0.1f, 0.1f, 0.1f),
		};

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
				cube.use();
				cube.setVec3("viewPos", camera.Position);
				cube.setFloat("material.shininess", 32.0f);
				//cube.use();
				glUniform3f(glGetUniformLocation(cube.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
				glUniform3f(glGetUniformLocation(cube.ID, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
				glUniform3f(glGetUniformLocation(cube.ID, "dirLight.diffuse"), 0.05f, 0.05f, 0.05);
				glUniform3f(glGetUniformLocation(cube.ID, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
				// Point light 1
				glUniform3f(glGetUniformLocation(cube.ID, "pointLights[0].position"), camera.Position.x, camera.Position.y+1, camera.Position.z);
				glUniform3f(glGetUniformLocation(cube.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
				glUniform3f(glGetUniformLocation(cube.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
				glUniform3f(glGetUniformLocation(cube.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
				glUniform1f(glGetUniformLocation(cube.ID, "pointLights[0].constant"), 1.0f);
				glUniform1f(glGetUniformLocation(cube.ID, "pointLights[0].linear"), 0.14);
				glUniform1f(glGetUniformLocation(cube.ID, "pointLights[0].quadratic"), 0.07);

				// SpotLight
				glUniform3f(glGetUniformLocation(cube.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
				glUniform3f(glGetUniformLocation(cube.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
				glUniform3f(glGetUniformLocation(cube.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
				glUniform3f(glGetUniformLocation(cube.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(cube.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
				glUniform1f(glGetUniformLocation(cube.ID, "spotLight.constant"), 1.0f);
				glUniform1f(glGetUniformLocation(cube.ID, "spotLight.linear"), 0.09);
				glUniform1f(glGetUniformLocation(cube.ID, "spotLight.quadratic"), 0.032);
				glUniform1f(glGetUniformLocation(cube.ID, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
				glUniform1f(glGetUniformLocation(cube.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));



				cube.setMat4("projection", projection);
				cube.setMat4("view", view);
				//cube.use();
				//cube.setInt("texture_diffuse1", 0);
				//cube.setFloat("visibility", 0.3);
				
				cube.use();
				for (int i = 0; i < amount; i++) {
				cube.setMat4("model", modelMatrices[i]);
				end = time(NULL);
				cube.use();

				produceExit(window, modelMatrices, wall, amount);
				if(distancia(cubePos[i].first,cubePos[i].second,camera.Position.x,camera.Position.z) < FOV)
					wall.Draw(cube);
				//Esconde o mundo do jogador
				hideWorld(cube, (end - start) % 8 == 0);
			}
		}

		endGame(texto);


		if (textEnabled)
		{
			texto->Load("fonts/ARIALNB.TTF", 24);
			
		}
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0){
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

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &lightVAO);
	//glDeleteVertexArrays(1, &lightVAO2);
	glDeleteBuffers(1, &VBO);
	std::free(cubePos);
	for (size_t i = 0; i < sized; i++){
		std::free(matrix[i]);
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	music_player.join();
	glfwTerminate();
	return 0;
}



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
	camera.ProcessMouseScroll((float) yoffset);
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
				int tamanho = (int) sqrtf(powf(0, 2.0) + powf(0, 2.0));
				//std::cout << "\nLado do model " << tamanho << " coordenadas x: " << i << " z: " << j;
				position.x =(float) i;
				position.z =(float) j;
				firstH = false;
			}
			else {
				int tamanho = (int) sqrtf(powf(i - position.x, 2.0) + powf(j - position.z, 2.0));
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



void produceExit(GLFWwindow* window, glm::mat4* matrices, Model obj, int getAmount) {
	if(saida.second.second)
		return;

	float distancia = sqrtf(powf(saida.first.first - camera.Position.x, 2.0) + powf(saida.first.second - camera.Position.z, 2.0));
	if (distancia < (float) sized/3){
		std::cout << "\nDistancia: " << distancia << "\n";
		matrices[saida.second.first] = glm::translate(matrices[saida.second.first], glm::vec3(666, 0, 0));
		//writeToPos(matrices, obj, getAmount);
			saida.second.second = true;

	}

}


void hideWorld(Shader shadow, bool apagar) {
	if (apagar) {
		shadow.use();
		shadow.setFloat("visibility", 0.0);
	}
	else {
		shadow.use();
		shadow.setFloat("visibility", 0.3);
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
	SoundEngine->play2D("./music/Loyalty_Freak_Music_-_07_-_A_really_dark_alley.mp3",true);
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
void guiaText(TextRenderer *texto,float resultado, float fps) {
	if (textEnabled) {
		ostringstream stringEscrita;
		stringEscrita << "Latency: " << resultado << " ms";
		texto->RenderText(stringEscrita.str(), 25.0f, 25.0f, 0.5);
		stringEscrita.str("");
		stringEscrita << "Exit x: " << saida.first.first << " z: " << saida.first.second;
		texto->RenderText(stringEscrita.str(), SCR_WIDTH - 150.0f, 50.0f, 0.5);
		stringEscrita.str("");
		stringEscrita << " x: " << (int)camera.Position.x << " z: " << (int)camera.Position.z;
		texto->RenderText(stringEscrita.str(), SCR_WIDTH - 150.0f, 25.0f, 0.5);
		stringEscrita.str("");
		stringEscrita << "FPS: " << fps;
		texto->RenderText(stringEscrita.str(), 25.0f, 50.0f, 0.5);
		stringEscrita.str("");
	}
}
float distancia(float x1, float z1, float x2, float z2) {
	return sqrtf(powf(x2 - x1, 2.0f) + powf(z2 - z1, 2.0f));
}
//#pragma once
#include "./labirinto_code.h"


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
	CriaLab(matrix,sized);
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
	saida.first = EscolheSaida(matrix, camera,sized); // Candidados para Saídas
	
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
	int h = 0;
	std::vector<pair<float, float>> cubePos = posicoesColision(cubePos,&h);// = (pair<float, float> *)calloc(amount,sizeof(pair<float,float>));
	



	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO = 0;
	unsigned int lightVAO = 0;
	
	atribuir(VBO, lightVAO);

	bool firstTime = true;
	float lastXthis = 0;
	float lastZtihs = 0;

	glm::vec3 lastPos(camera.Position);

	float movementSpeed = camera.MovementSpeed;
	bool collided = false;

	
	int nbFrames = 0;
	double lastTime = 0.0;
//	time_t end;

	
	double resultado = 0;
	ostringstream stringEscrita;
	start = time(NULL);
	int fps = 0;
	
	cube.use();
	cube.setInt("material.diffuse", 0);
	cube.setInt("material.specular", 1);
	texto->Load("fonts/ARIALNB.TTF", 24);

	gameLoop(window,lampShader,VBO,lightVAO,cube,amount,modelMatrices,wall,cubePos,texto,nbFrames,lastTime,fps,resultado,lastPos,collided);

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &lightVAO);
	//glDeleteVertexArrays(1, &lightVAO2);
	glDeleteBuffers(1, &VBO);
	//std::free(cubePos);
	for (size_t i = 0; i < sized; i++){
		std::free(matrix[i]);
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	
	glfwTerminate();
	return 0;
}




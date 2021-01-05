#pragma once

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
int FOV = 5;


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
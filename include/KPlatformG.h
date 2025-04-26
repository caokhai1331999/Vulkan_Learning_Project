#if !defined(PLATFORMG_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#include "stdio.h"
#include <iostream>

#if !defined
#define GLAD_LIB_AND_SHADER
#include <glad/glad.h>
#include <glad/glad.c>//must be place
#endif

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <C_Model.h>
#include "shader_s.h"
#include "camera.h"
// #include "stdint.h"
// #include <glm/glm.hpp>


using namespace std;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera;

glm::vec3 HorizalVel = {};
glm::vec3 VerticalVel = {};

bool firstMouse = true;

float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
// NOTE: fov stands for field of view
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float StandardFPS = 60;
float StandardFrame = 0.0f;

struct Platform{
    GLFWwindow* window;
    unsigned int VBO;
    unsigned int VAO;

    unsigned int PlaneVBO;
    unsigned int PlaneVAO;

    unsigned int EBO;
    Platform(){
        window = NULL;
    };
};

// struct LightingSouce{
    
// };

bool Init(Platform* PlatForm);
void CreateVertexStuff(Platform* p);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
// void LoadTexture();
unsigned int* LoadTexture();
void loadTexture(char const * path, unsigned int* textureID);

#define PLATFORMG_H
#endif

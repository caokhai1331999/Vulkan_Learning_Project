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
#if !defined
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include "shader_s.h"
#include "camera.h"
// #include "stdint.h"
// #include <glm/glm.hpp>


using namespace std;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
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
    // Shader ourShader("7.3.camera.vs", "7.3.camera.fs");
    Platform(){
        window = NULL;
    };
};

bool Init(Platform* PlatForm);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int* LoadTexture();

#define PLATFORMG_H
#endif

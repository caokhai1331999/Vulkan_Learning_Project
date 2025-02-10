/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey Muratori's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct Platform{
    GLFWwindow* window;
    Platform(){
        window = nullptr;
    }
}Platform;


void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindow* tempWindow = nullptr;
    tempWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    Platform.window = tempWindow;
}

void initVulkan() {
    initWindow();
}

void mainLoop() {
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
}

void cleanup() {
    glfwDestroyWindow();
    glfwTerminate();
}

void run() {
    initVulkan();
    mainLoop();
    cleanup();
}

    

int main() {
    try {
        run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

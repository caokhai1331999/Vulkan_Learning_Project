#if !defined(PLATFORM_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct Platform{
    GLFWwindow* window = nullptr;
    VkInstance instance;
    Platform(){
        window = nullptr;
    }
};

// #if !defined
// extern Platform platform = {};
// #endif


void run(Platform* p);
void initWindow(Platform* p);
void initVulkan(Platform* p);
void createInstance(Platform* p);
void mainLoop(Platform* p);
void cleanup(Platform*p);

#define PLATFORM_H
#endif

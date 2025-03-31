/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey Muratori's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#include "Platform.h"

void initWindow(Platform* p) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* tempWindow = nullptr;
    tempWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    p->window = tempWindow;
}

void initVulkan(Platform* p) {
    initWindow(p);
    createInstance(p);
}

void createInstance(Platform* p){
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    // NOTE: Create Instance to be able to use vulkan

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> requiredExtensions;

    for(uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }

    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    
    if(vkCreateInstance(&createInfo, nullptr, &p->instance)!= VK_SUCCESS){
        throw std::runtime_error("Failed to create instance\n");
    }else{
        printf("Success create instance for Vulkan\n");
    }

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties>extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::cout<<"Available extension\n";
    for(const auto& extension:extensions){
        std::cout<<'\t'<<extension.extensionName<<'\n';
    };
}

void mainLoop(Platform* p) {
    while(!glfwWindowShouldClose(p->window)){
        glfwPollEvents();
    }
}

void cleanup(Platform* p) {
    vkDestroyInstance(p->instance, nullptr);    
    glfwDestroyWindow(p->window);
    glfwTerminate();
}

void run(Platform* p) {
    initVulkan(p);
    mainLoop(p);
    cleanup(p);
}


#include "shader_s.h"
#include "KPlatformG.h"
#include "Windows.h"
// #include <stdio.h>
// #include "shader_s.h"
// #include "camera.h"

#pragma once

#define INIT(name) bool name(Platform* PlatForm)
typedef INIT(INIT_);

#define FRAMEBUFFER_SIZE_CALLBACK(name) void name(GLFWwindow* window, int width, int height)
typedef FRAMEBUFFER_SIZE_CALLBACK(FRAMEBUFFER_SIZE_CALLBACK_);

#define MOUSE_CALLBACK(name) void name(GLFWwindow* window, double xpos, double ypos)
typedef MOUSE_CALLBACK(MOUSE_CALLBACK_);

#define SCROLL_CALLBACK(name) void name(GLFWwindow* window, double xoffset, double yoffset)
typedef SCROLL_CALLBACK(SCROLL_CALLBACK_);

#define PROCESSINPUT(name) void name(GLFWwindow *window)
typedef PROCESSINPUT(PROCESSINPUT_);

#define LOAD_TEXTURE(name) unsigned int* name()
typedef LOAD_TEXTURE(LOAD_TEXTURE_);

HMODULE PlatformLibrary;

INIT_* Init_ = nullptr;
FRAMEBUFFER_SIZE_CALLBACK_* framebuffer_size_callback_ = nullptr;
MOUSE_CALLBACK_* mouse_callback_ = nullptr;
SCROLL_CALLBACK_* scroll_callback_ = nullptr;
PROCESSINPUT_* processInput_ = nullptr;
LOAD_TEXTURE_* LoadTexture_ = nullptr;

void GetFunction(){

    if(!CopyFile("Platform.dll", "Platform_Copy.dll", false)){
        printf("Failed to copy dll file\n");
    } else {
        PlatformLibrary = LoadLibrary("Platform_Copy.dll");
        printf(" Succeed copying dll file\n");        
    }

    if(PlatformLibrary){

        Init_ =(INIT_*) GetProcAddress( PlatformLibrary, "Init");
        framebuffer_size_callback_ =(FRAMEBUFFER_SIZE_CALLBACK_*) GetProcAddress(PlatformLibrary, "framebuffer_size_callback");
        mouse_callback_ = (MOUSE_CALLBACK_*)GetProcAddress(PlatformLibrary, "mouse_callback");
        scroll_callback_ = (SCROLL_CALLBACK_*)GetProcAddress(PlatformLibrary, "scroll_callback");
        processInput_ = (PROCESSINPUT_*)GetProcAddress(PlatformLibrary, "processInput");
        LoadTexture_ = (LOAD_TEXTURE_*)GetProcAddress(PlatformLibrary, "LoadTexture");

        printf("Load Library successfully\n");
    } else {
        printf("Failed to load game code\n");        
    }
}

int main(int* argc, char** argv[])
{
    GetFunction();
    Platform* PlatForm = new Platform;

    if (!Init_(PlatForm)){
        printf("Can not Init Platform\n");
        return -1;
    } else {
        Shader ourShader("7.3.camera.vs", "7.3.camera.fs");
        printf("Init platform successfully\n");
    }
    // build and compile our shader zprogram
    // ------------------------------------
    //NOTE: Why crashed
    printf("Game crash before shader\n");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    printf("Game crash after this vertext array\n");
    
    // Load and create textures
    unsigned int texture1, texture2;
    unsigned int* texture;
    texture = LoadTexture_();
    texture1 = texture[0];
    texture2 = texture[1];
    printf("Game crash after this texture\n");
    
    float count = 0.0f;
    float lastFrame = 0.0f;

    bool ToPositive = true;
    float x = 1.0f;
    float y = 1.0f;
    float z = 1.0f;
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    delete []texture;

    int delayTime = 0;
    // render loop
    // -----------
    float currentFrame = 0.0f;
    currentFrame = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(PlatForm->window))
    {

        if(delayTime >= 40){
            FreeLibrary(PlatformLibrary);
            GetFunction();
            delayTime = 0;
            printf("Reload game code successfully\n");
        } else {
            delayTime++;
        }
        // per-frame time logic
        // --------------------
        //Why the lastFrame and currentFrame time gap is so much
        // input
        // -----
        processInput_(PlatForm->window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)

        //NOTE: These line create a region of space that appeared on screen
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);
        // render boxes
        glBindVertexArray(VAO);

        x = 1.0f;
        y = 1.0f;
        z = 1.0f;


        if(deltaTime > (float)(1/30)){            

            // Update frame whenever it meet the condition
        currentFrame = lastFrame;

        // NOTE: The for loop messed up the rythm of i increment
        count += ToPositive?0.1f:-0.1f;
        
        if(count > 10.0f){
            ToPositive = false;
        } if ( count < -10.0f){
            ToPositive = true;
        }
        
        }

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            // the glm::mat4 is for create a cube
            //
            // Don't understand this step
            model = glm::translate(model,cubePositions[i]);
            float angle = 50.0f;
            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));

            if (i==1 || i==3) {                
            // time += 0.1f;
            model = glm::rotate(model,(float)glfwGetTime()*glm::radians(50.0f),glm::vec3(0.0f,1.0f,1.0f));
            model = glm::translate(model, count*glm::vec3(0.3f*x, 0.3f*y, 0.3f*z));
            // printf("lastFrame is: %f, CurrentTime is: %f\n", StandardFrame, currentFrame);
                

            // printf("Count is :%f\n", count);

            // NOTE: translate is to move he thing
            // printf("Current time is: %f \n", glfwGetTime());
            }
            else if (i==2||i==5||i==9){
                model = glm::rotate(model,(float)glfwGetTime()*glm::radians(50.0f),glm::vec3(0.6f,0.0f,0.0f));
                model = glm::translate(model, count*glm::vec3(0.3f*x, 0.3f*(-y), 0.3f*z));                
            }
            else{
            model = glm::rotate(model,(float)glfwGetTime()*glm::radians(50.0f),glm::vec3(1.0f,0.0f,1.0f));
            model = glm::translate(model, count*glm::vec3(0.3f*(-x), 0.3f*(-y), 0.3f*(-z)));                            
            }
            //every third cude rotate
//            if (i%3==0)
            // NOTE: Time to play with the cube movement
            ourShader.setMat4("model",model);
            glDrawArrays(GL_TRIANGLES,0,36);

            lastFrame = static_cast<float>(glfwGetTime());
            deltaTime = lastFrame - currentFrame;

            printf("Current frame time is:%f\n", currentFrame);
            printf("Last Frame time is:%f\n", lastFrame);
            printf("Frame time is:%f\n", deltaTime);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(PlatForm->window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    delete PlatForm;
    PlatForm = nullptr;
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

#include "KPlatformG.h"
#include "Windows.h"
// #include <stdio.h>
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
static bool firstLoad = false;
INIT_* Init_ = nullptr;
FRAMEBUFFER_SIZE_CALLBACK_* framebuffer_size_callback_ = nullptr;
MOUSE_CALLBACK_* mouse_callback_ = nullptr;
SCROLL_CALLBACK_* scroll_callback_ = nullptr;
PROCESSINPUT_* processInput_ = nullptr;
LOAD_TEXTURE_* LoadTexture_ = nullptr;

struct Material{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;    
};


void GetFunction(){

    if(!CopyFile("Platform.dll", "Platform_Copy.dll", false)){
        printf("Failed to copy dll file\n");
    } else {
        PlatformLibrary = LoadLibrary("Platform_Copy.dll");
        printf(" Succeed copying dll file\n");        
    }

    if(PlatformLibrary){

        if(!firstLoad){
        Init_ =(INIT_*) GetProcAddress( PlatformLibrary, "Init");
            firstLoad = true;
        }
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
// NOTE: Try not to copy code. Remember its logic

int main(int* argc, char** argv[])
{
    // GetFunction();
    Platform* PlatForm = new Platform;
    if (!Init(PlatForm)){
        printf("Can not Init Platform\n");
        return -1;
    } else {
        printf("Init platform successfully\n");
    }

    float LampMovingSpeed = 0.5f;
    Material cyan_plastic = {{0.0, 0.1, 0.06}, // Have to recalculate this number
                             {0.0, 0.50980392, 0.50980392},
                             {0.50196078, 0.50196078, 0.50196078}
                             ,0.25};

    // NOTE: I have to recall this function to load gl function
    // LoadGLFunctions();        
    Shader* ourShader = nullptr;
    ourShader = new Shader("7.3.camera.vs", "7.3.camera.fs");

    Shader* lampShader = nullptr;
    lampShader = new Shader("1.lamp.vs", "1.lamp.fs");
    printf("Lamp Shader ID:%d\n", lampShader->ID);
    
    Shader* objectShader = nullptr;
    objectShader = new Shader("1.object.vs", "1.object.fs");
    printf("Lighted object ID:%d\n", objectShader->ID);

// Shader ourShader("7.3.camera.vs", "7.3.camera.fs");
    
    
    // build and compile our shader zprogram
    // ------------------------------------
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //

    // world space positions of our cubes

    CreateVertexStuff(PlatForm);

    int index = 0;
    
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

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };  

    glm::vec3 lightColor[] = {
        glm::vec3( 1.0f,  0.588f,  0.29f),
        glm::vec3( 1.0f, 1.0f, 1.0f),
        glm::vec3(0.698f, 1.0f, 0.29f),
        glm::vec3( 0.549f, 0.29f, 1.0f)
    };  
    
    // Load and create textures
    unsigned int* textures  = nullptr;
    textures = new unsigned int();
    // textures = LoadTexture();
    textures = LoadTexture();    
    objectShader->use();

    objectShader->setInt("material.emissionMap", 4);
    objectShader->setInt("material.diffuseMap", 2);
    objectShader->setInt("material.specularMap", 3);

    objectShader->setVec3("pointlights[0].position",  pointLightPositions[0]);
    objectShader->setVec3("pointlights[0].ambient", 0.05f, 0.05f, 0.05f);
    objectShader->setVec3("pointlights[0].diffuse", 0.8f, 0.8f, 0.8f);
    objectShader->setVec3("pointlights[0].specular", 1.0f, 1.0f, 1.0f);
    objectShader->setFloat("pointlights[0].constant",  1.0f);
    objectShader->setFloat("pointlights[0].linear",    0.09f);
    objectShader->setFloat("pointlights[0].quadratic", 0.032f);	    

    objectShader->setVec3("pointlights[1].position",  pointLightPositions[1]);
    objectShader->setVec3("pointlights[1].ambient", 0.05f, 0.05f, 0.05f);
    objectShader->setVec3("pointlights[1].diffuse", 0.8f, 0.8f, 0.8f);
    objectShader->setVec3("pointlights[1].specular", 1.0f, 1.0f, 1.0f);
    objectShader->setFloat("pointlights[1].constant",  1.0f);
    objectShader->setFloat("pointlights[1].linear",    0.09f);
    objectShader->setFloat("pointlights[1].quadratic", 0.032f);	    

    objectShader->setVec3("pointlights[2].position",  pointLightPositions[2]);
    objectShader->setVec3("pointlights[2].ambient", 0.05f, 0.05f, 0.05f);
    objectShader->setVec3("pointlights[2].diffuse", 0.8f, 0.8f, 0.8f);
    objectShader->setVec3("pointlights[2].specular", 1.0f, 1.0f, 1.0f);
    objectShader->setFloat("pointlights[2].constant",  1.0f);
    objectShader->setFloat("pointlights[2].linear",    0.09f);
    objectShader->setFloat("pointlights[2].quadratic", 0.032f);	    

    objectShader->setVec3("pointlights[3].position",  pointLightPositions[3]);
    objectShader->setVec3("pointlights[3].ambient", 0.05f, 0.05f, 0.05f);
    objectShader->setVec3("pointlights[3].diffuse", 0.8f, 0.8f, 0.8f);
    objectShader->setVec3("pointlights[3].specular", 1.0f, 1.0f, 1.0f);
    objectShader->setFloat("pointlights[3].constant",  1.0f);
    objectShader->setFloat("pointlights[3].linear",    0.09f);
    objectShader->setFloat("pointlights[3].quadratic", 0.032f);	    
    

    // Set light color and position for one cube
    objectShader->setFloat("material.shininess", 20.0f);

    // FOR THE SIMPLEST TYPE(DIRECTIONAL LIGHT)
    objectShader->setVec3("dirlight.direction",  -0.2f, -1.0f, -0.3f);
    objectShader->setVec3("dirlight.ambient", 0.05f, 0.05f, 0.05f);
    objectShader->setVec3("dirlight.diffuse", 0.4f, 0.4f, 0.4f);
    objectShader->setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);    
    
    for(int i = 0; i < 5; i++){
        printf("Texture index %d: %d\n", i, textures[i]);
    }

    
    float count = 0.0f;
    float lastFrame = 0.0f;

    bool ToPositive = true;
    float x = 1.0f;
    float y = 1.0f;
    float z = 1.0f;
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    // NOTE: second argument indicate the GLenum texture index that was already initialized
    
    int delayTime = 0;
    // render loop
    // -----------
    float currentFrame = 0.0f;
    currentFrame = static_cast<float>(glfwGetTime());

    int MoveCount = 0;
    int PreMoveCount = 0;

    int MovingCount = 0;
    int PreMovingCount = 0;

    int MCount = 0;
    int PreMCount = 0;

    glm::vec3 objectPos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 lightPos = glm::vec3(1.0f, 0.0f, 5.0f);

    while (!glfwWindowShouldClose(PlatForm->window))
    {
        glm::mat4 cubeModel = glm::mat4(1.0f);            
        glm::mat4 lightModel = glm::mat4(1.0f);            
        lightModel = scale(lightModel, glm::vec3(2.0f));
        // NOTE: Have to load model inside the game loop

        // if(delayTime >= 120){
        //     FreeLibrary(PlatformLibrary);
        //     GetFunction();
        //     delayTime = 0;
        //     printf("Reload game code successfully\n");
        // } else {
        //     delayTime++;
        // }


        processInput(PlatForm->window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        // NOTE: mat4 is to create a 3D space
        // WORKING!!
        //========================================= 
        //NOTE: These line create a region of space that appeared on screen

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // camera/view transformation
        glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);

        // ====================================================================
        // ON WORKING!!: Cube drawing

        // Variate Light Pos
        // lightPos.x += 5.0f *(sin(glfwGetTime())* 2.0f + 1.0f)* LampMovingSpeed;
        // lightPos.y += 5.0f *(sin(glfwGetTime())* 1.5f + 1.5f)* LampMovingSpeed;
        // lightPos.z += 5.0f *(sin(glfwGetTime())* 2.0f + 1.5f)* LampMovingSpeed;
        // =======================

        // Move Model
        // ================================
        lampShader->use();
        lampShader->setMat4("view", view);
        lampShader->setMat4("projection", projection);

        for (int i = 0; i < 4; i++){

        // Variate Light Color
        if(i == 1){            
            lightColor[i].x = sin(glfwGetTime()* 2.0f);
            lightColor[i].y = sin(glfwGetTime()* 0.7f);
            lightColor[i].z = sin(glfwGetTime()* 1.3f);
        }

            // NOTE: Draw Lamp
        lampShader->setVec3("lightColor", lightColor[i]);
        lightModel = glm::translate(lightModel, pointLightPositions[i]);
        lampShader->setMat4("model", lightModel);
        // ================================        
        // FIXED: We have to bind to shader to appropriate VAO before drawing something

        glBindVertexArray(PlatForm->VAO);
        // Draw a cube here (6 per face we have 6 faces so 36 indices)
        glDrawArrays(GL_TRIANGLES, 0, 36);        
            // ================================================================
        }
        //===================================================================
        // NOTE: Calculate ambient and diffuse based on light Color
        glm::vec3 diffuseColor = lightColor[1] * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        // ==================================================================

        // Set General Model spec for two object cubes
        objectShader->use();
        cubeModel = translate(cubeModel, objectPos + static_cast<float >(3.5)*glm::vec3(1.0, 0.0, 1.0)); // NOTE: The vector position is x,y,z

        objectShader->setVec3("ViewPos", camera.Position);
        objectShader->setMat4("view", view);
        objectShader->setMat4("projection", projection);
        objectShader->setMat4("model", cubeModel);
        // ==================================================================
        // FOR THE MY MOST INTERESTING TYPE (POINT LIGHT)
        
        // FOR SPOTLIGHT
        objectShader->setVec3("spotlight.position", camera.Position);
        objectShader->setVec3("spotlight.direction", camera.Front);
        objectShader->setVec3("spotlight.ambient", 0.0f, 0.0f, 0.0f);
        objectShader->setVec3("spotlight.diffuse", 1.0f, 1.0f, 1.0f);
        objectShader->setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        objectShader->setFloat("spotlight.constant", 1.0f);
        objectShader->setFloat("spotlight.linearTerm", 0.09f);
        objectShader->setFloat("spotLight.quadraticTerm ", 0.032f);
        objectShader->setFloat("spotlight.cutOff", glm::cos(glm::radians(40.0f)));
        objectShader->setFloat("spotlight.outerCutOff", glm::cos(glm::radians(42.5f)));

        objectShader->setMat4("model", cubeModel);
        glBindVertexArray(PlatForm->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Then Move the model to different Position
        cubeModel = translate(cubeModel, objectPos + static_cast<float >(-3.5)*glm::vec3(1.0, 0.0, 1.0)); // NOTE: The vector position is x,y,z
        objectShader->use();
        // Bind Texture to shader
        // Then Draw it out
        // Draw a cube here (6 per face we have 6 faces so 36 indices)
        objectShader->setMat4("model", cubeModel);
        glBindVertexArray(PlatForm->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // =====================================================================
        // CYAN PLASTIC ONE
        objectShader->setVec3("material.diffuse", cyan_plastic.diffuse);
        objectShader->setVec3("material.specular", cyan_plastic.specular);
        objectShader->setFloat("material.shininess", cyan_plastic.shininess);        
        
        cubeModel = translate(cubeModel, objectPos + static_cast<float >(3.5)*glm::vec3(1.0, 1.0, -1.0)); // NOTE: The vector position is x,y,z
        objectShader->setMat4("model", cubeModel);
        glBindVertexArray(PlatForm->VAO);
        // Draw a cube here (6 per face we have 6 faces so 36 indices)
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //===========================================================
        
        // render boxes        
        x = 1.0f;
        y = 1.0f;
        z = 1.0f;

        // ourShader->use();
        // ourShader->setMat4("projection", projection);
        // ourShader->setMat4("view", view);

        if(deltaTime > (float)(1/30)){            

            // Update frame whenever it meet the condition
            currentFrame = lastFrame;

            // NOTE: The for loop messed up the rythm of i increment
            // Shader lampShader("lightingSource.vs", "color.fs");

            count += ToPositive?0.1f:-0.1f;        
            if(count > 10.0f){
                ToPositive = false;
            } if ( count < -10.0f){
                ToPositive = true;
            }
        
        }

        for (unsigned int i = 0; i < 10; i++)
        {
            // the glm::mat4 is for create a cube
            glm::mat4 model = glm::mat4(1.0f);
            //
            // Don't understand this step
            model = glm::translate(model,cubePositions[i]);
            float angle = 50.0f;
            // These linears for moving cubes

            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));

            if (i==1 || i==3) {                
                // time += 0.1f;
                model = glm::rotate(model,(float)sin(glfwGetTime())*glm::radians(50.0f),glm::vec3(0.0f,1.0f,1.0f));
                model = glm::translate(model, (float)sin(glfwGetTime())* (3.0f) *glm::vec3(0.3f*x, 0.3f*y, 0.3f*z));
                // printf("lastFrame is: %f, CurrentTime is: %f\n", StandardFrame, currentFrame);
                
                // printf("Count is :%f\n", count);

                // NOTE: translate is to move he thing
                // printf("Current time is: %f \n", glfwGetTime());
            }
            else if (i==2||i==5||i==9){
                model = glm::rotate(model,(float)sin(glfwGetTime())*glm::radians(50.0f),glm::vec3(0.6f,0.0f,0.0f));
                model = glm::translate(model, (float)cos(glfwGetTime())* (3.0f) * glm::vec3(0.3f*x, 0.3f*(-y), 0.3f*z));
            }
            else{
                model = glm::rotate(model,(float)glfwGetTime()*glm::radians(50.0f),glm::vec3(1.0f,0.0f,1.0f));
                model = glm::translate(model, (float)(sin(glfwGetTime()) + cos(glfwGetTime())) * (3.0f) * glm::vec3(0.3f*(-x), 0.3f*(-y), 0.3f*(-z)));
            }
                        //every third cube rotate
//            if (i%3==0)
            // NOTE: Time to play with the cube movement
            objectShader->use();
            ourShader->setMat4("model",model);            
            glBindVertexArray(PlatForm->VAO);
            glDrawArrays(GL_TRIANGLES,0,36);
            
            lastFrame = static_cast<float>(glfwGetTime());
            deltaTime = lastFrame - currentFrame;

            // printf("Current frame time is:%f\n", currentFrame);
            // printf("Last Frame time is:%f\n", lastFrame);
            // printf("Frame time is:%f\n", deltaTime);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(PlatForm->window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &PlatForm->VAO);
    glDeleteBuffers(1, &PlatForm->VBO);

    delete ourShader;
    ourShader = nullptr;

    delete lampShader;
    lampShader = nullptr;

    delete objectShader;
    objectShader = nullptr;

    delete PlatForm;
    PlatForm = nullptr;

    delete textures;
    textures = nullptr;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

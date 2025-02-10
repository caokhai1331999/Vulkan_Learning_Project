#include "KPlatformG.h"
// #include <stdio.h>
// #include "shader_s.h"
// #include "camera.h"

#pragma once

int main(int* argc, char** argv[])
{
    Platform* PlatForm = new Platform;
    if (!Init(PlatForm)){
        return -1;
    }
    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.3.camera.vs", "7.3.camera.fs");    
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

    // Load and create textures
    unsigned int texture1, texture2;
    unsigned int* texture;
    texture = LoadTexture();
    texture1 = texture[0];
    texture2 = texture[1];

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

    // render loop
    // -----------
    float currentFrame = 0.0f;
    currentFrame = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(PlatForm->window))
    {
        // per-frame time logic
        // --------------------
        //Why the lastFrame and currentFrame time gap is so much
        // input
        // -----
        processInput(PlatForm->window);

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

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

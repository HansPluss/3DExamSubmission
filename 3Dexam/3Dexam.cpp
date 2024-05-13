#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <ctime> 
#include <stb/stb_image.h>

#include "Resources/Shaders/shaderClass.h"
#include "Player.h"
#include "Resources/ImportedCode/LSM.h"
#include "Texture.h"
#include "Camera.h"
#include "MathFunctions.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test Win", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram("default.vert", "default.frag");
    shaderProgram.Activate(); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    //glEnable(GL_DEPTH_TEST);
    
    Player myPlayer(1.0f, glm::vec3(0, 0, 20), 0.1f, 0.0f, 0.5f, 1);
    Player terrain(1.0f, glm::vec3(-20, 0, 0), 0.1f, 0.0f, 0.5f, 2);
    Player NPC(1.0f, glm::vec3(1, 1, 10), 1.0f, 1.0f, 1.0f, 1);

    Player collectible(1.0f, glm::vec3(0, 1, 10), 0.1f, 0.6f, 0.5f, 1);
    glm::uvec4 xCoords = glm::vec4(10, 2, 3, 20);
    glm::uvec4 yCoords = glm::vec4(2, 4, 2, 5);

    Player graph(1.0f, glm::vec3(0, 0, 0), 0.1f, 0.6f, 0.5f, 3);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 10.0f, 40.0f));

    Texture texture("Resources/Textures/icon.jpg", shaderProgram);


    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render the triangle

        myPlayer.inputs(window);
        camera.Inputs(window);
       
        collectible.CheckSphereCollision(myPlayer);
        terrain.calculateBarycentricCoordinates(myPlayer.position, true);
        terrain.calculateBarycentricCoordinates(collectible.position, true);
        terrain.calculateBarycentricCoordinates(NPC.position, true);
        NPC.InterpolatePoints(xCoords, yCoords, xCoords.x, xCoords.w);
        //Set render distance and FOV
        glm::mat4 viewproj = camera.Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");

        glBindTexture(GL_TEXTURE_2D, texture.texture);
       

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, myPlayer.position);
        //model = glm::scale(model, glm::vec3(0, 0, 0)); for scaling the object
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model));
        myPlayer.BindVAO();
        myPlayer.GetVBO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, myPlayer.mVertecies.size());
        myPlayer.UnbindVAO();

        glm::mat4 Collectiblemodel = glm::mat4(1.0f);
        Collectiblemodel = glm::translate(Collectiblemodel, collectible.position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * Collectiblemodel));
        collectible.BindVAO();
        collectible.GetVBO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, collectible.mVertecies.size());
        collectible.UnbindVAO();

        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glm::mat4 NPCmodel = glm::mat4(1.0f);
        NPCmodel = glm::translate(NPCmodel, NPC.position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * NPCmodel));
        NPC.BindVAO();
        NPC.GetVBO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, NPC.mVertecies.size());
        NPC.UnbindVAO();

        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, terrain.position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model1));
        terrain.BindVAO();
        terrain.GetVBO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, terrain.mVertecies.size());
        terrain.UnbindVAO();
        
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glm::mat4 graphmodel = glm::mat4(1.0f);
        graphmodel = glm::translate(graphmodel, graph.position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * graphmodel));
        graph.BindVAO();
        graph.GetVBO().Bind();
        glDrawArrays(GL_LINE_STRIP, 0, graph.mVertecies.size());
        graph.UnbindVAO();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

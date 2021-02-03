#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ShaderProgram.hpp"

const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Shader";
const int gWindowWidth = 800;
const int gWindowWHeight = 600;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;

void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow *window);
bool initOpenGL();

// BASIC STEPS FOR DRAWING WITH MODERN OPENGL
// 1. Create BUFFER in GPU memory for the mesh
// 2. Fill the buffer ith mesh data (vertices)
// 3. Create SHADERS for knowing HOW to draw your mesh
// 4. Define the vertex format for the mesh verticies
// 5. Draw the mesh
//      1. Set the shader as current
//      2. Set the buffer as current
//      3. Draw the buffer

// BASIC STEPS FOR CREATING SHADERS
// 1. Create Vertex Shader
// 2. Create Fragment Shader
// 3. Compile the shaders
// 4. Create a Shader Program
// 5. Attach the shaders to the Program
// 6. Link the compiled shaders into a single Program
// 7. Use the Program






int main() {
    
    if (!initOpenGL()) {
        std::cerr << "GLFW initialization failded" << std::endl;
        return -1;
    }
    
    // ---------
    
    //HINT: The reason because openg uses GLfloat typedef on float is because different os and machines may use their own size of float. The c float still work with GLfloat.
    
    //      TRIANGLE
    GLfloat vertices[] = {
    //   x     y     z
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    GLuint indices[] = {
      0, 1, 2, //tri 0
      0, 2, 3  //tri 1
    };
    
    //OpenGL object - generic place in gpu to hold data
    //For minimize tranfer data from cpu to gpu
    //Buffer for positions
    GLuint vbo; //vertex buffer object id
    glGenBuffers(1, &vbo); // Init buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //May be:
    //GL_STATIC_DRAW - create once, set up once, use a lot
    //GL_DYNAMIC_DRAW - create once, changing a lot, use a lot
    //GL_STREAM_DRAW - create once, using ones
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //Vertex array object - hold information about buffer
    GLuint vao; //Vertex array object id
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //Position attribute
    glVertexAttribPointer(
                          /*index*/0,
                          /*size*/3,
                          /*type*/GL_FLOAT,
                          /*normalized*/GL_FALSE,
                          /*stride*/0,
                          /*pointer(offset)*/NULL);
    glEnableVertexAttribArray(0);
    
    
    GLuint ibo; //index buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    
    //------ Sahders ---------
    
    ShaderProgram shaderProgram;
    shaderProgram.loadShaders("/Users/vitalycloud/Desktop/MyFirstOpenGL/MyFirstOpenGL/bin/basic.vert",
        "/Users/vitalycloud/Desktop/MyFirstOpenGL/MyFirstOpenGL/bin/basic.frag");
    
    
    
    
    // ---------
    
    //Main Application Loop
    while(!glfwWindowShouldClose(gWindow)) {
        
        showFPS(gWindow);
        glfwPollEvents(); //Keyaboard, mouse etc.
        
        //Possible bits to clear:
        //GL_COLOR_BUFFER_BIT <- SELECTED
        //GL_DEPTH_BUFFER_BIT
        //GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProgram.use();
        
        // -----------
        glBindVertexArray(vao); //bind
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        glBindVertexArray(0);  //unbind
        // -----------
        
        //Double buffer eliminates flicking
        glfwSwapBuffers(gWindow);
        
    }
    

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    
    glfwTerminate();
    return 0;
}

bool initOpenGL() {
    if(!glfwInit()) {
        std::cerr << "GLFW initialization failded" << std::endl;
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    gWindow = glfwCreateWindow(gWindowWidth, gWindowWHeight, APP_TITLE, NULL, NULL);
    
    if(gWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(gWindow);
    glfwSetKeyCallback(gWindow, glfw_onKey);
    
    //Get function pointers to OpenGL
    if(glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failded" << std::endl;
        return false;
    }
    
    //To properly configurate Modern OpenGL
    glewExperimental = GL_TRUE;
    
    //Every frame we clear screen with color
    glClearColor(.23f, .38f, .47f, 1.0f);
    return true;
}

void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode) {
    //Close app on esc key
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        gWireframe = !gWireframe;
        if (gWireframe == true) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void showFPS(GLFWwindow *window) {
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime(); //returns number of seconds sincce GLFW started, as a double
    
    elapsedSeconds = currentSeconds - previousSeconds;
    
    //limit text update 4 time per second
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;
        
        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed << APP_TITLE
        << "   " << "FPS: " << fps << "   "
        << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());
        
        frameCount = 0;
    }
    frameCount++;
}

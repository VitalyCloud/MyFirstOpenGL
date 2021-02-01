#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Window 1";
const int gWindowWidth = 800;
const int gWindowWHeight = 600;
bool gFullscreen = false;

void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow *window);

int main() {
    
    if(!glfwInit()) {
        std::cerr << "GLFW initialization failded" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *pWindow = NULL;
    
    if(gFullscreen) {
        GLFWmonitor *pMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor); //Info about monitor
        if(pVmode != NULL) {
            pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
        }
    } else {
        pWindow = glfwCreateWindow(gWindowWidth, gWindowWHeight, APP_TITLE, NULL, NULL);
    }
    
    
    if(pWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(pWindow);
    
    glfwSetKeyCallback(pWindow, glfw_onKey);
    
    //Get function pointers to OpenGL
    if(glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failded" << std::endl;
        return -1;
    }
    
    //To properly configurate Modern OpenGL
    glewExperimental = GL_TRUE;
    
    //Main Application Loop
    while(!glfwWindowShouldClose(pWindow)) {
        
        showFPS(pWindow);
        glfwPollEvents(); //Keyaboard, mouse etc.
        
        //Every frame we clear screen with color
        glClearColor(.23f, .38f, .47f, 1.0f);
        //Possible bits to clear:
        //GL_COLOR_BUFFER_BIT <- SELECTED
        //GL_DEPTH_BUFFER_BIT
        //GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Double buffer eliminates flicking
        glfwSwapBuffers(pWindow);
        
    }
    
    
    glfwTerminate();
    return 0;
}

void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode) {
    //Close app on esc key
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
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

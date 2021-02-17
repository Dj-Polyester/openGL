#if !defined(INPUT_H)
#define INPUT_H

#include "Global.h"

struct Input
{
    bool running;
    Input();
    ~Input();
};

Input::Input():running(true) {

}

// void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     switch (key)
//     {
//     case GLFW_KEY_W:
//         break;
//     case GLFW_KEY_A:
//         break;
//     case GLFW_KEY_S:
//         break;
//     case GLFW_KEY_D:
//         break;
//     case GLFW_KEY_ESCAPE:
//         glfwSetWindowShouldClose(window, true);
//         break;
//     default:
//         break;
//     }     
// }

#endif // INPUT_H

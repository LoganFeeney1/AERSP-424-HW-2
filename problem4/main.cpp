/************************************************************************************************************************
Logan Feeney
Homework 2
Probem 4
3/31/24
************************************************************************************************************************/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

int main() 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(500, 500, "Lift Equation Plot using OpenGL", NULL, NULL);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // draw X and Y axes
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);   // white for axes
        glVertex2f(-0.9, -0.9);     // start just above and to the right of bottom left corner
        glVertex2f(1.0, -0.9);      // x-axis ends at bottom right
        glVertex2f(-0.9, -0.9);     // start just above and to the right of bottom left corner
        glVertex2f(-0.9, 1.0);      // y-axis ends at top left
        glEnd();

        // Plot lift equation
        glColor3f(0.0, 1.0, 0.0);   // green color for the lift curve
        float rho = 1.225;          // ideal sea level air density (kg/m^3)
        float S = 16.17;            // cessna 172 wing area (m^2)
        float CL = 1.60;            // cessna 172 CL_max (no flaps)
        float V_min = 26;           // minimum velocity (m/s)
        float V_max = 63;           // maximum velocity (m/s)
        float L_max = 0.5 * rho * V_max * V_max * S * CL;  // maximum lift for scaling

        glBegin(GL_LINE_STRIP);
        for (float V = V_min; V <= V_max; V += 0.1)
        {
            float L = 0.5 * rho * V * V * S * CL;  // calculate lift
            float x = (V - V_min) / (V_max - V_min) * 2 - 0.9;  // normalize and scale for OpenGL
            float y = (L / L_max) * 2 - 0.9;  // normalize and scale for OpenGL

            glVertex2f(x, y);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}







// BasicProj GLFW version

#include <iostream>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description);

void init(void)
{
    // Here we can also Init GLAD and other extensions

    // End extensions section

    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0


    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    glLoadIdentity();
    glOrtho(0.0, 200.0, 0.0, 150.0, -1.0, 1.0);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    GLuint regHex;

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    glBegin(GL_LINES);                 // Draw following shape as lines
        glVertex2i(180,15);
        glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);                 // Draw following shape as lines
        glVertex2i(15,180);
        glVertex2i(1145,10);
    glEnd();

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}


int main(void)
{
    GLFWwindow* window;
    // Set error callback ( can be called before init )
    glfwSetErrorCallback(error_callback);

    // init GLFW and OpenGL
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW, exiting..." << std::endl;
        return -1;
    }

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // Create new GLFW window
    window = glfwCreateWindow(400,300, "An example OpenGL program", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error initializing GLFW main window, exiting..." << std::endl;
        return -1;
    }
    glfwSetWindowPos(window, 50, 100);
    // Set window as Main Window
    glfwMakeContextCurrent(window);

    init();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        lineSegment();
        /* Swap front and back buffers */
        // OpenGL uses double buffering by default
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void error_callback(int error, const char* description)
{
    std::cout << "GLFW Error: " << description << std::endl;
}
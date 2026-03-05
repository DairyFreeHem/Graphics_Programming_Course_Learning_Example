#include <iostream>
#include <GLFW/glfw3.h>



GLubyte bitShape [20] = {
0x1c, 0x0F,
0x1c, 0x0F, 
0x1c, 0x0F, 
0x1c, 0x0F, 
0x1c, 0x0F,
0xff, 0x8F, 
0x7f, 0x0F, 
0x3e, 0x0F, 
0x1c, 0x0F, 
0x08, 0x00};

void drawBitmap(void)
{

    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.0,0.0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glRasterPos2i(30,40);
    glBitmap(16,10,0.0,0.0,20.0,15.0,bitShape);

    glRasterPos2i(90,40);
    glBitmap(15,10,0.0,0.0,20.0,15.0,bitShape);

    glFlush();


}

// BasicProj GLFW version

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
    window = glfwCreateWindow(400,300, "Bitmap drawing example" , NULL, NULL);
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

        drawBitmap();
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
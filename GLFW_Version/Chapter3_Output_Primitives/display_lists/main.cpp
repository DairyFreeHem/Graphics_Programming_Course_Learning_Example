#include <iostream>
#include <GLFW/glfw3.h>
#include<math.h>

class screenPt
{
    	private:
		GLint x, y;
	public:
        screenPt(void)
        {
            this->x = this->y = 0;
        }

        void setCoords(GLint xCoord, GLint yCoord)
        {
            this->x = xCoord;
            this->y = yCoord;
        }

        GLint getx(void) const
        {
            return this->x;
        }

        GLint gety(void) const
        {
            return this->y;
        }

};

const double TWO_PI = 6.2831853;

GLsizei winWidth = 100, winHeight = 100;
GLuint regHex;


void error_callback(int error, const char* description);

void init(void)
{
    // Here we can also Init GLAD and other extensions

    // End extensions section

    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0


	screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;


	circCtr.setCoords (winWidth , winHeight);
	glClearColor(1.0, 1.0, 1.0, 0.0);    // Set display window (White #FFFFFF)

	regHex = glGenLists(1);              // Set the identifier for the display lists
	glNewList(regHex, GL_COMPILE);       // Init new display list
	glColor3f(1.0, 0.0, 0.0);            
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		theta = TWO_PI * k / 6.0;
		hexVertex.setCoords(circCtr.getx() + 50 * cos(theta), circCtr.gety() + 50 * sin(theta));
		glVertex2i(hexVertex.getx(), hexVertex.gety());
	}
	glEnd();
	glEndList();
	glOrtho(0.0, 200.0, 0.0, 150.0, -1.0, 1.0);   // Set Orthographic window to 200 x 150 dimension window

}


void regHexagon(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(regHex);

	glFlush();
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
    window = glfwCreateWindow(400,300, "GL Display List example", NULL, NULL);
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

        regHexagon();
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
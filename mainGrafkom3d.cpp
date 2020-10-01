#include <iostream>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Shape.h"
#include "glm/ext.hpp"
using namespace std;

const float LIGHT_INTENSITY = 2;
const float SPECULAR_MULTIPLIER = 0.5;
const float SHINYNESS = 32;
const Vertex AMBIENCE_MULTIPLIER(0.1, 0.1, 0.1);

GLFWwindow* window;
GLuint VertexArrayID;
Hierarchy* tornado, * tornado2;

int WINDOW_WIDTH = 1300, WINDOW_HEIGHT = 900;
Mesh mesh("asset/object/wolf.obj",70, Vertex(1,1,1)), mesh2("asset/object/Groudon.obj",3, Vertex(0.5,0.3,0.4)), mesh3("asset/object/cat.obj", 50, Vertex(1, 0, 0));
Vertex light_source = Vertex(0.2, 0.8, 2);
Vertex light_color = Vertex(1, 1, 1);
Vertex eye = Vertex(0, 1, 2);

void mouseMoveEvent(GLFWwindow* window, double x, double y)
{
	double mod_x = (float)(x - (WINDOW_WIDTH / 2)) / (float)(WINDOW_WIDTH / 2);
	double mod_y = (float)(WINDOW_HEIGHT - y - (WINDOW_HEIGHT / 2)) / (float)(WINDOW_HEIGHT / 2);
}
void mouseClickEvent(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		double mod_x = (float)(x - (WINDOW_WIDTH / 2)) / (float)(WINDOW_WIDTH / 2);
		double mod_y = (float)(WINDOW_HEIGHT - y - (WINDOW_HEIGHT / 2)) / (float)(WINDOW_HEIGHT / 2);
		if (action == GLFW_PRESS)
		{
			printf("LEFT CLICK ON : (%lf, %lf)\n", mod_x, mod_y);
		}
		else if (action == GLFW_RELEASE)
		{
			printf("LEFT RELEASE ON : (%lf, %lf)\n", mod_x, mod_y);
		}
	}
}
void screenResizeEvent(GLFWwindow* window, int width, int height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void keyboardPressEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(0.01, 0, 0));
		mesh2.Translate(Vertex(0.01, 0, 0));
		mesh3.Translate(Vertex(0.01, 0, 0));
	
		tornado->translate(Vertex(0.01, 0, 0));
		tornado->translate(Vertex(0.01, 0, 0));
		tornado->getChild(0)->getParent()->Translate(Vertex(0.01, 0, 0));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0.01, 0, 0));

		tornado2->translate(Vertex(0.01, 0, 0));
		tornado2->translate(Vertex(0.01, 0, 0));
		tornado2->getChild(0)->getParent()->Translate(Vertex(0.01, 0, 0));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0.01, 0, 0));
	}
	else if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(-0.01, 0, 0));
		mesh2.Translate(Vertex(-0.01, 0, 0));
		mesh3.Translate(Vertex(-0.01, 0, 0));

		tornado->translate(Vertex(-0.01, 0, 0));
		tornado->translate(Vertex(-0.01, 0, 0));
		tornado->getChild(0)->getParent()->Translate(Vertex(-0.01, 0, 0));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(-0.01, 0, 0));

		tornado2->translate(Vertex(-0.01, 0, 0));
		tornado2->translate(Vertex(-0.01, 0, 0));
		tornado2->getChild(0)->getParent()->Translate(Vertex(-0.01, 0, 0));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(-0.01, 0, 0));
	}
	else if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(0, -0.01, 0));
		mesh2.Translate(Vertex(0, -0.01, 0));
		mesh3.Translate(Vertex(0, -0.01, 0));

		tornado->translate(Vertex(0, -0.01, 0));
		tornado->translate(Vertex(0, -0.01, 0));
		tornado->getChild(0)->getParent()->Translate(Vertex(0, -0.01, 0));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, -0.01, 0));

		tornado2->translate(Vertex(0, -0.01, 0));
		tornado2->translate(Vertex(0, -0.01, 0));
		tornado2->getChild(0)->getParent()->Translate(Vertex(0, -0.01, 0));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, -0.01, 0));
	}
	else if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(0, 0.01, 0));
		mesh2.Translate(Vertex(0, 0.01, 0));
		mesh3.Translate(Vertex(0, 0.01, 0));

		tornado->translate(Vertex(0, 0.01, 0));
		tornado->translate(Vertex(0, 0.01, 0));
		tornado->getChild(0)->getParent()->Translate(Vertex(0, 0.01, 0));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0.01, 0));

		tornado2->translate(Vertex(0, 0.01, 0));
		tornado2->translate(Vertex(0, 0.01, 0));
		tornado2->getChild(0)->getParent()->Translate(Vertex(0, 0.01, 0));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0.01, 0));
	}
	else if (key == GLFW_KEY_Z && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(0, 0, 0.01));
		mesh2.Translate(Vertex(0, 0, 0.01));
		mesh3.Translate(Vertex(0, 0, 0.01));

		tornado->translate(Vertex(0, 0, 0.01));
		tornado->translate(Vertex(0, 0, 0.01));
		tornado->getChild(0)->getParent()->Translate(Vertex(0, 0, 0.01));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0, 0.01));

		tornado2->translate(Vertex(0, 0, 0.01));
		tornado2->translate(Vertex(0, 0, 0.01));
		tornado2->getChild(0)->getParent()->Translate(Vertex(0, 0, 0.01));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0, 0.01));
	}
	else if (key == GLFW_KEY_X && action == GLFW_REPEAT)
	{
		mesh.Translate(Vertex(0, 0, -0.01));
		mesh2.Translate(Vertex(0, 0, -0.01));
		mesh3.Translate(Vertex(0, 0, -0.01));

		tornado->translate(Vertex(0, 0, -0.01));
		tornado->translate(Vertex(0, 0, -0.01));
		tornado->getChild(0)->getParent()->Translate(Vertex(0, 0, -0.01));
		tornado->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0, -0.01));

		tornado2->translate(Vertex(0, 0, -0.01));
		tornado2->translate(Vertex(0, 0, -0.01));
		tornado2->getChild(0)->getParent()->Translate(Vertex(0, 0, -0.01));
		tornado2->getChild(0)->getChild(0)->getParent()->Translate(Vertex(0, 0, -0.01));
	}
	else if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
	{
		mesh.Rotate(eye, Vertex(0, 1, 0), -1);
		mesh2.Rotate(eye, Vertex(0, 1, 0), -1);
		mesh3.Rotate(eye, Vertex(0, 1, 0), -1);

		tornado->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), -1);
		tornado->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), -1);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), -1);
		tornado->getChild(0)->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), -1);

		//coba->drawPolygon();
		//coba->drawPolyline();
		//coba->Rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		//coba->Rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);

		tornado2->drawPolygon();
		tornado2->drawPolyline();
		tornado2->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), -1);
		tornado2->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), -1);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), -1);
		tornado2->getChild(0)->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), -1);
	}
	else if (key == GLFW_KEY_E && action == GLFW_REPEAT)
	{
		mesh.Rotate(eye, Vertex(0, 1, 0), 1);
		mesh2.Rotate(eye, Vertex(0, 1, 0), 1);
		mesh3.Rotate(eye, Vertex(0, 1, 0), 1);

		tornado->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 1);
		tornado->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 1);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 1);
		tornado->getChild(0)->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 1);

		//coba->drawPolygon();
		//coba->drawPolyline();
		//coba->Rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		//coba->Rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);

		tornado2->drawPolygon();
		tornado2->drawPolyline();
		tornado2->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 1);
		tornado2->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 1);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), 1);
		tornado2->getChild(0)->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), 1);

	}
	else if (key == GLFW_KEY_R && action == GLFW_REPEAT)
	{
		mesh.Rotate(eye, Vertex(1, 0, 0), -1);
		mesh2.Rotate(eye, Vertex(1, 0, 0), -1);
		mesh3.Rotate(eye, Vertex(1, 0, 0), -1);

		tornado->rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		tornado->rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		tornado->getChild(0)->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), -1);

		//coba->drawPolygon();
		//coba->drawPolyline();
		//coba->Rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		//coba->Rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);

		tornado2->drawPolygon();
		tornado2->drawPolyline();
		tornado2->rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		tornado2->rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
		tornado2->getChild(0)->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), -1);
	}
	else if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		mesh.Rotate(eye, Vertex(1, 0, 0), 1);
		mesh2.Rotate(eye, Vertex(1, 0, 0), 1);
		mesh3.Rotate(eye, Vertex(1, 0, 0), 1);

		tornado->rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
		tornado->rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 1);
		tornado->getChild(0)->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 1);

		//coba->drawPolygon();
		//coba->drawPolyline();
		//coba->Rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		//coba->Rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);

		tornado2->drawPolygon();
		tornado2->drawPolyline();
		tornado2->rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
		tornado2->rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
		tornado2->getChild(0)->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 1);
	}
	mesh.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
	mesh2.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
	mesh3.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
}
void initializeGLFW() {
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}
void initializeWindow() {
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Computer Graphics", NULL, NULL);
	if (window == NULL) {
		printf("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouseMoveEvent);
	glfwSetMouseButtonCallback(window, mouseClickEvent);
	glfwSetKeyCallback(window, keyboardPressEvent);
	glfwSetFramebufferSizeCallback(window, screenResizeEvent);

	glEnable(GL_DEPTH_TEST);
}
void initializeGLEW() {
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
		return;
	}
}

void initializeShapes() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	char vertexShader[][100] = { "shaders/vertex2.shader", "Vertex.shader"  };
	char fragmentShader[][100] = { "shaders/fragment2.shader", "shaders/triangle/red.shader", "shaders/triangle/blue.shader", "shaders/triangle/yellow.shader", "shaders/triangle/brown.shader" };
	char fragmentOutlineShader[][100] = { "shaders/fragment_outline2.shader","shaders/triangle/fragment_outline_1.shader" };

	mesh.InitializeBuffer();
	mesh.InitializeShader(vertexShader[0], fragmentShader[0]);
	mesh.InitializeOutlineShader(vertexShader[0], fragmentOutlineShader[0]);
	mesh.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
	mesh.Translate(Vertex(-1, 0, 0));
	//cout << mesh.GetPosition().x << endl;

	mesh2.InitializeBuffer();
	mesh2.InitializeShader(vertexShader[0], fragmentShader[0]);
	mesh2.InitializeOutlineShader(vertexShader[0], fragmentOutlineShader[0]);
	mesh2.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
	mesh2.Translate(Vertex(1, 0, 0.1));
	mesh2.Rotate(mesh2.GetPosition(), Vertex(0, 1, 0), -180);
	//cout << mesh2.GetPosition().x << endl;

	mesh3.InitializeBuffer();
	mesh3.InitializeShader(vertexShader[0], fragmentShader[0]);
	mesh3.InitializeOutlineShader(vertexShader[0], fragmentOutlineShader[0]);
	mesh3.CalculateColors(light_source, light_color, AMBIENCE_MULTIPLIER, eye, SPECULAR_MULTIPLIER, SHINYNESS, LIGHT_INTENSITY);
	mesh3.Translate(Vertex(-1, 0, 0.5));

	Vertex control_pts[8] =
	{
		Vertex(-0.02, 0.02),
		Vertex(-0.05, 0.15),
		Vertex(-0.15, 0.35),
		Vertex(-0.25, 0.55),
		Vertex(-0.35, 0.75),
		Vertex(-0.375, 0.79),
		//Vertex(-0.4, 0.8),
		//Vertex(-0.45, 0.9)
	};

	//coba = new Hierarchy(new Box1(-0.5, 0.5, 0));
	tornado = new Hierarchy(new Vase(control_pts, 8, 0, 0, 0, 25, 1));
	tornado2 = new Hierarchy(new Vase(control_pts, 8, 1, 0, 0, 25, 1));

	//tornado->addChild(new Hierarchy(new Box1(tornado->getParent()->GetPosition().x, tornado->getParent()->GetPosition().y + 0.75, tornado->getParent()->GetPosition().z)));
	tornado->addChild(new Hierarchy(new Box(tornado->getParent()->GetPosition().x, tornado->getParent()->GetPosition().y + 0.75, tornado->getParent()->GetPosition().z)));
	tornado->getChild(0)->addChild(new Hierarchy(new Box(tornado->getParent()->GetPosition().x, tornado->getParent()->GetPosition().y + 0.8, tornado->getParent()->GetPosition().z)));
	tornado->getChild(0)->getChild(0)->rotate(tornado->getChild(0)->getChild(0)->getParent()->GetPosition(), tornado->getChild(0)->getChild(0)->getParent()->GetEuler(2), 45);

	//tornado2->addChild(new Hierarchy(new Box1(tornado2->getParent()->GetPosition().x, tornado2->getParent()->GetPosition().y + 0.75, tornado2->getParent()->GetPosition().z)));
	tornado2->addChild(new Hierarchy(new Box(tornado2->getParent()->GetPosition().x, tornado->getParent()->GetPosition().y + 0.75, tornado->getParent()->GetPosition().z)));
	tornado2->getChild(0)->addChild(new Hierarchy(new Box(tornado2->getParent()->GetPosition().x, tornado->getParent()->GetPosition().y + 0.8, tornado->getParent()->GetPosition().z)));
	tornado2->getChild(0)->getChild(0)->rotate(tornado2->getChild(0)->getChild(0)->getParent()->GetPosition(), tornado2->getChild(0)->getChild(0)->getParent()->GetEuler(2), 45);

	//coba->initiateBuffer();
	//coba->InitializeShader(vertexShader[0], fragmentShader[0]);
	//coba->initiateOutlineShader(vertexShader[0], fragmentOutlineShader[0]);
	//coba->resetEuler();

	tornado->initiateBuffer();
	tornado->initiateShader(vertexShader[1], fragmentShader[1]);
	tornado->getChild(0)->getParent()->InitializeShader(vertexShader[1], fragmentShader[3]);
	tornado->getChild(0)->getChild(0)->getParent()->InitializeShader(vertexShader[1], fragmentShader[3]);
	tornado->initiateOutlineShader(vertexShader[1], fragmentOutlineShader[1]);
	tornado->resetEuler();

	tornado2->initiateBuffer();
	tornado2->initiateShader(vertexShader[1], fragmentShader[1]);
	tornado2->getChild(0)->getParent()->InitializeShader(vertexShader[1], fragmentShader[3]);
	tornado2->getChild(0)->getChild(0)->getParent()->InitializeShader(vertexShader[1], fragmentShader[3]);
	tornado2->initiateOutlineShader(vertexShader[1], fragmentOutlineShader[1]);
	tornado2->resetEuler();
}

void render() {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh.DrawPolygon();
		mesh2.DrawPolygon();
		mesh3.DrawPolygon();
		mesh2.Rotate(mesh.GetPosition(), Vertex(0, 1, 0), -1);

		tornado->drawPolygon();
		tornado->drawPolyline();
		tornado->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		tornado->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado->getChild(1)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		tornado->getChild(0)->getChild(0)->getParent()->Rotate(tornado->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);

		//coba->drawPolygon();
		//coba->drawPolyline();
		//coba->Rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		//coba->Rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);

		tornado2->drawPolygon();
		tornado2->drawPolyline();
		tornado2->rotate(tornado2->getParent()->GetPosition(), Vertex(0, 1, 0), 0.7);
		tornado2->rotate(tornado->getParent()->GetPosition(), Vertex(0, 1, 0), 0.5);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getChild(0)->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		//tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 0, 0), 0.5);
		tornado2->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		tornado2->getChild(0)->getChild(0)->getParent()->Rotate(tornado2->getParent()->GetPosition(), Vertex(1, 1, 0), 0.7);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		glDisableVertexAttribArray(0);

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

void cleanup() {
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
}

int main() {
	initializeGLFW();
	initializeWindow();
	initializeGLEW();
	initializeShapes();
	render();
	cleanup();
}
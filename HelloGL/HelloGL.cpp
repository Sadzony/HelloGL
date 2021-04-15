#include "HelloGL.h"




HelloGL::HelloGL(int argc, char* argv[]) {
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();
	InitLight();
	glutMainLoop();

}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;
	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	Mesh* monkeyMesh = MeshLoader::LoadOBJ((char*)"monkey.obj");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);
	for (int i = 0; i < 500; i++) {
		objects[i] = new Cube(monkeyMesh, texture, ((rand() % 400) / 7.5f) - 20.0f, ((rand() % 200) / 7.5f) - 15.0f, -(rand() % 1000), (rand() % 100) / 10.0f, (rand() % 2) - 1, (rand() % 2) - 1, (rand() % 2) - 1);
	}
	
	
}

void HelloGL::InitLight()
{
	lightPosition = new Vector4();
	lightPosition->x = 0.0f;
	lightPosition->y = 0.0f;
	lightPosition->z = 1.0f;
	lightPosition->w = 0.0f;

	lightData = new Lighting();
	lightData->ambient.x = 0.2f;
	lightData->ambient.y = 0.2f;
	lightData->ambient.z = 0.2f;
	lightData->ambient.w = 1.0f;

	lightData->diffuse.x = 0.8f;
	lightData->diffuse.y = 0.8f;
	lightData->diffuse.z = 0.8f;
	lightData->diffuse.w = 1.0f;

	lightData->specular.x = 0.2f;
	lightData->specular.y = 0.2f;
	lightData->specular.z = 0.2f;
	lightData->specular.w = 1.0f;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	
}

void HelloGL::Display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the scene
	for (int i = 0; i < 500; i++) {
		objects[i]->Draw();
	}
	glFlush(); //flush the scene drawn to the graphics card
	glutSwapBuffers();
}



void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightPosition->x));
	for (int i = 0; i < 500; i++) {
		objects[i]->Update();
	}
	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{

}
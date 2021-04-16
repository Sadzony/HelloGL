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
	camera->eye.y = 9.0f;
	camera->eye.z = -20.0f;
	camera->center.x = 0.0f;
	camera->center.y = 8.0f;
	camera->center.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	Mesh* roadMesh = MeshLoader::LoadOBJ((char*)"Road.obj");
	Mesh* lampMesh = MeshLoader::LoadOBJ((char*)"Lamp.obj");
	Mesh* carMesh = MeshLoader::LoadOBJ((char*)"Car.obj");
	Texture2D* roadTexture = new Texture2D();
	roadTexture->LoadBMP((char*)"road texture.bmp");
	Texture2D* lampTexture = new Texture2D();
	lampTexture->LoadBMP((char*)"lamp texture.bmp");
	Texture2D* carTexture = new Texture2D();
	carTexture->LoadBMP((char*)"car texture.bmp");
	roadObject = new StaticObject(roadMesh, roadTexture, 0, 0, 0, 0, 0, 0, 0);
	roadObject2 = new StaticObject(roadMesh, roadTexture, 20, 0, 0, 0, 0, 0, 0);
	roadObject3 = new StaticObject(roadMesh, roadTexture, -20, 0, 0, 0, 0, 0, 0);
	lampObject = new StaticObject(lampMesh, lampTexture, 7, 5.15, 5.3, 0, 1, 0, 180);
	lampObject2 = new StaticObject(lampMesh, lampTexture, -7, 5.15, 5.3, 0, 1, 0, 180);
	carObject = new Car(carMesh, carTexture, 0, 4.5, 0, 0, 1, 0, 180, 0.1);
	
	
}

void HelloGL::InitLight()
{
	lightPosition = new Vector4();
	lightPosition->x = 0.0f;
	lightPosition->y = 9.0f;
	lightPosition->z = 0.0f;
	lightPosition->w = 0.0f;

	lightData = new Lighting();
	lightData->ambient.x = 0.1f;
	lightData->ambient.y = 0.1f;
	lightData->ambient.z = 0.1f;
	lightData->ambient.w = 1.0f;

	lightData->diffuse.x = 1.0f;
	lightData->diffuse.y = 0.9f;
	lightData->diffuse.z = 0.2f;
	lightData->diffuse.w = 1.0f;

	lightData->specular.x = 1.0f;
	lightData->specular.y = 1.0f;
	lightData->specular.z = 1.0f;
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
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
}

void HelloGL::Display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the scene
	roadObject->Draw();
	roadObject2->Draw();
	roadObject3->Draw();
	lampObject->Draw();
	lampObject2->Draw();
	carObject->Draw();
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(sphereRotation, 0, 0, 1);
	glutWireSphere(50, 20, 20);
	glPopMatrix();
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
	roadObject->Update();
	lampObject->Update();
	lampObject2->Update();
	carObject->Update();
	camera->eye.x = carObject->GetPosition().x;
	camera->center.x = carObject->GetPosition().x;
	if (sphereRotation <= 360) {
		sphereRotation += 0.3f;
	}
	else {
		sphereRotation = 0;
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd') {
		carObject->moveDirection = -1;
	}
	else if (key == 'a') {
		carObject->moveDirection = 1;
	}
	else if (key != 'd' && key != 'a') {
		carObject->moveDirection = 0;
	}
}
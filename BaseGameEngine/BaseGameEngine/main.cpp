#include "Scene.h"

#define WIDTH 500
#define HEIGHT 500

void main()
{
	Screen screen(WIDTH, HEIGHT, "Test");
	screen.CreateWindow();
	Scene scene(&screen);
	Object cameraObj;
	Camera camera;
	cameraObj.AddComponent(&camera);
	scene.AddCamera(&camera);
	scene.UpdateLoop();

}
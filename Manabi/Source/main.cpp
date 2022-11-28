#include "Application.h"

#include <vld.h>

int main() {
	Application app;

	app.Init();
	app.Run();
	app.Exit();

	return 0;
}
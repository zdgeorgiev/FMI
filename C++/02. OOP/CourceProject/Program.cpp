#include <iostream>
#include "Engine.h"

using namespace std;

int main()
{
	Engine* e = new Engine();
	(*e).run();
	delete e;

	system("pause");
	return 0;
}
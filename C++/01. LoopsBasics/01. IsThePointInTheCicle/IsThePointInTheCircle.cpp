#include <iostream>
#include <math.h>

using namespace std;

static const int CircleRadius = 2;

int main()
{
	float x;
	float y;

	printf("x = ");
	cin >> x;
	printf("y = ");
	cin >> y;

	bool isInside = false;

	//If y is bigger than 0 then we have to check if the point its in the circle
	//else we will check for the rectangle.
	if (y > 0)
	{
		//To calc the distance to the center will use Euclidean distance forumla.
		float distanceToCenter = sqrt(pow(x - 0.0, 2) + pow(y - 0.0, 2));

		if (distanceToCenter <= CircleRadius)
		{
			isInside = true;
		}
	}
	else if (y == 0)
	{
		if (x >= -2 && x <= 2)
		{
			isInside = true;
		}
	}
	else
	{
		if (y >= -2)
		{
			if (x >= -1 && x <= 1)
			{
				isInside = true;
			}
		}
	}

	printf("Is the point with coords [%0.2f , %0.2f] is in the figure - %s \n", x, y, isInside ? "true" : "false");

	return 0;
}
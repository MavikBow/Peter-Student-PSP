//#include "collision.h"

void hello(void)
{
	printf("Hello, World!\n");
}

const float SCALE = 16.0f;

int bottom_collision_1(float x, float y) //0 - no collision; 1 - yes collision
{
	if(y <= 2 * SCALE)
	{
		return 1;
	}
	else if(y >= 12 * SCALE)
	{
		return 0;
	}
	else if(y >= 11 * SCALE)
	{
		if((x >= 25.5 * SCALE) || (x >= 12.5 * SCALE && x <= 15.5 * SCALE)) 
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if((y >= 5 * SCALE && y <= 6 * SCALE) && (x > 13.5 * SCALE && x < 17.5 * SCALE))//square 1
		{
			return 1;
		}
		else if((y >= 6 * SCALE && y <= 7 * SCALE) && (x > 18.5 * SCALE && x < 22.5 * SCALE))//square 2
		{
			return 1;
		}
		else if ((y >= 7 * SCALE && y <= 8 * SCALE) && (x > 24.5 * SCALE))//square 3
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
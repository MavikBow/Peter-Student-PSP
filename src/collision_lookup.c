//#include "collision.h"

void hello(void)
{
	printf("Hello, World!\n");
}

const float SCALE = 16.0f;
const float HEAD_OFFSET = 4.0f;
const float BODY_OFFSET = 8.0f;

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
		if((y > 5 * SCALE && y <= 6 * SCALE) && (x > 13.5 * SCALE && x < 17.5 * SCALE))//square 1
		{
			return 1;
		}
		else if((y > 6 * SCALE && y <= 7 * SCALE) && (x > 18.5 * SCALE && x < 22.5 * SCALE))//square 2
		{
			return 1;
		}
		else if ((y > 7 * SCALE && y <= 8 * SCALE) && (x > 24.5 * SCALE))//square 3
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int upper_collision_1(float x, float y) // 0 - no collision; 1 - yes collision
{
	if(y >= 15 * SCALE + HEAD_OFFSET)
	{
		return 1;
	}
	else if(y >= 10 * SCALE + HEAD_OFFSET)
	{
		return 0;
	}
	else if(y >= 9 * SCALE + HEAD_OFFSET)
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
		if((y >= 3 * SCALE + HEAD_OFFSET && y <= 5 * SCALE) && (x > 13.5 * SCALE && x < 17.5 * SCALE))//square 1
		{
			return 1;
		}
		else if((y >= 4 * SCALE + HEAD_OFFSET && y <= 5 * SCALE) && (x > 18.5 * SCALE && x < 22.5 * SCALE))//square 2
		{
			return 1;
		}
		else if ((y >= 5 * SCALE + HEAD_OFFSET && y <= 6 * SCALE) && (x > 24.5 * SCALE))//square 3
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int left_collision_1(float x, float y)
{
	if(x <= 1 * SCALE + BODY_OFFSET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int right_collision_1(float x, float y)
{
	if(x >= 29 * SCALE - BODY_OFFSET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int bottom_collision_2(float x, float y)
{
	if(y <= 2 * SCALE)
	{
		return 1;
	}
	else if (y > 12 * SCALE)
	{
		return 0;
	}
	else
	{
		if(x > 24.5f * SCALE && y >= 11 * SCALE)
		{
			return 1;
		}
		else if((x < 7.5 * SCALE) && (y >= 7 * SCALE && y <= 8 * SCALE))
		{
			return 1;
		}
		else if((x >= 7 * SCALE && x < 10.5 * SCALE) && (y >= 4 * SCALE && y <= 5 * SCALE))
		{
			return 1;
		}
		else if(((x > 21.5 * SCALE && x < 25.5 * SCALE) || (x > 14.5 * SCALE && x < 18.5 * SCALE)) && (y >= 5 * SCALE && y <= 6 * SCALE))
		{
			return 1;
		}
		else if((x >= 17.5 * SCALE && x < 21.5 * SCALE) && (y >= 8 * SCALE && y <= 9 * SCALE))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
}

int upper_collision_2(float x, float y)
{
	if(y >= 15 * SCALE + HEAD_OFFSET)
	{
		return 1;
	}
	else if(y >= 12 * SCALE + HEAD_OFFSET)
	{
		if(x > 21 * SCALE)
		{
			return 0;
		}
		else{
			return 1;
		}
	}
	else if(((x > 24.5f * SCALE) && (y >= 9 * SCALE + HEAD_OFFSET && y <= 10 * SCALE)))
	{
		return 1;
	}
	else if(((x > 21.5 * SCALE && x < 25.5 * SCALE) || (x > 14.5 * SCALE && x < 18.5 * SCALE)) && (y >= 3 * SCALE + HEAD_OFFSET && y <= 4 * SCALE))
	{
		return 1;
	}
	else if((x >= 17.5 * SCALE && x < 21.5 * SCALE) && (y >= 6 * SCALE + HEAD_OFFSET && y <= 7 * SCALE))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int left_collision_2(float x, float y)
{
	if(x <= 1 * SCALE + BODY_OFFSET)
	{
		return 1;
	}
	else
	{
		if((x >= 6 * SCALE + BODY_OFFSET && x <= 7 * SCALE + BODY_OFFSET) && (y < 8 * SCALE - 5))
		{
			return 1;
		}
		else if((x >= 9 * SCALE + BODY_OFFSET && x <= 10 * SCALE + BODY_OFFSET) && (y < 5 * SCALE - 5))
		{
			return 1;
		}
		else if((x >= 20 * SCALE + BODY_OFFSET && x <= 21 * SCALE + BODY_OFFSET) && (y > 12 * SCALE))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int right_collision_2(float x, float y)
{
	if(x >= 29 * SCALE - BODY_OFFSET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
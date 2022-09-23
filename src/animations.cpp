#include "animations.h"
#include <vector>
#include <iostream>

bool CompareFloats(float A, float B, float epsilon)
{
	return (fabs(A - B) < epsilon);
}

int currentFrame = 0;

int framesToBeShrunken = 100;
float lowerPlayerStep = 0.05f;
float shrinkStep = 0.1f;
float isGrowing = false;

void Shrink(SEntity &entity, bool &playerIsShrunken)
{
	if(entity.scale[1] > 0.5f && !isGrowing)
	{
		// shrink
		entity.scale[1] -= shrinkStep;
		// move down player
		entity.position[1] -= lowerPlayerStep;
	}
	else if(CompareFloats(entity.scale[1], 0.5f) && !isGrowing)
	{
		// stay small
		if (currentFrame < framesToBeShrunken)
		{
			currentFrame++;

			if (currentFrame == framesToBeShrunken - 1)
			{
				isGrowing = true;
			}
		}
	}
	else if(isGrowing)
	{
		// grow
		if(entity.scale[1] < 1.0f)
		{
			entity.scale[1] += shrinkStep;
			entity.position[1] += lowerPlayerStep;
		}
		else
		{
			currentFrame = 0;
			isGrowing = false;
			playerIsShrunken = false;
		}
	}
}

int framesToFly = 15;
float jumpStep = 0.11f;
bool isFalling = false;

void Jump(SEntity& entity, bool &playerIsJumping)
{
	if(entity.position[1] < 2.5f && !isFalling)
	{
		// jump up
		entity.position[1] += jumpStep;
	}
	else if(CompareFloats(entity.position[1], 2.54f) && !isFalling)
	{
		// stay top
		if (currentFrame < framesToFly)
		{
			currentFrame++;

			if (currentFrame == framesToFly - 1)
			{
				isFalling = true;
			}
		}
	}
	else if(isFalling)
	{
		// fall down
		if(entity.position[1] > 1.0f)
		{
			entity.position[1] -= jumpStep;
		}
		else
		{
			currentFrame = 0;
			isFalling = false;
			playerIsJumping = false;
		}
	}
}

float fallStep = 0.3f;
int dieFrameCounter = 0;

void Fall(SEntity& entity, bool& showGameOverScreen)
{
	entity.position[1] -= fallStep;

	if(entity.position[1] < -10.0f)
	{
		dieFrameCounter++;

		if(dieFrameCounter == 80)
		{
			showGameOverScreen = true;
			dieFrameCounter = 0;
		}
	}
}

void Die(SEntity& entity, bool &showGameOverScreen)
{
	if(entity.rotation[2] > -90.0f)
	{
		entity.rotation[2] -= 3.0f;
	}
	else
	{
		dieFrameCounter++;

		if(dieFrameCounter == 80)
		{
			showGameOverScreen = true;
			dieFrameCounter = 0;
		}
	}

	if(entity.position[1] > (entity.scale[1] / 2))
	{
		entity.position[1] -= 0.1f;
	}
}

float leftBorder = -1.9f;
float rightBorder = 1.9f;
float rollingStep = 1.0f;

void RollAround(SObstacleEntity &obstacle)
{
	if(obstacle.entity.position[0] < rightBorder && CompareFloats(obstacle.direction[0], 1.0f))
	{
		obstacle.entity.position[0] += 0.05f;
		obstacle.entity.rotation[2] += rollingStep;

		if(CompareFloats(obstacle.entity.position[0], rightBorder, 0.1f))
		{
			// once we reached the right end, we have to go left
			obstacle.direction[0] = -1.0f;
		}
	}
	else
	{
		obstacle.entity.position[0] -= 0.05f;
		obstacle.entity.rotation[2] -= rollingStep;

		if(CompareFloats(obstacle.entity.position[0], leftBorder, 0.1f))
		{
			// once we reached the left end, reverse the movement
			obstacle.direction[0] = 1.0f;
		}
	}
}

float leftJunkBorder = -30.9f;
float rightJunkBorder = 30.9f;
float rollingJunkStep = 2.0f;

void Fly(SObstacleEntity &obstacle)
{
	if(obstacle.entity.position[0] < rightJunkBorder && CompareFloats(obstacle.direction[0], 1.0f))
	{
		obstacle.entity.position[0] += 0.15f;
		obstacle.entity.rotation[2] += rollingJunkStep;

		if(CompareFloats(obstacle.entity.position[0], rightJunkBorder, 0.1f))
		{
			// once we reached the right end, we have to go left
			obstacle.direction[0] = -1.0f;
		}
	}
	else
	{
		obstacle.entity.position[0] -= 0.15f;
		obstacle.entity.rotation[2] -= rollingJunkStep;

		if(CompareFloats(obstacle.entity.position[0], leftJunkBorder, 0.1f))
		{
			// once we reached the left end, reverse the movement
			obstacle.direction[0] = 1.0f;
		}
	}
}
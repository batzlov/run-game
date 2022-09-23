#pragma once

#include "entity.h"

bool CompareFloats(float A, float B, float epsilon = 0.005f);

/*
	animations for the player
*/
void Jump(SEntity &entity, bool &playerIsJumping);

void Shrink(SEntity& entity, bool &playerIsShrunken);

void Fall(SEntity& entity, bool &showGameOverScreen);

void Die(SEntity& entity, bool &showGameOverScreen);

/*
	animations for the obstacle
*/
void RollAround(SObstacleEntity &obstacle);

void Fly(SObstacleEntity &obstacle);
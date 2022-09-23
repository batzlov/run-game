#pragma once

#include <string>

#include "../inc/yoshix.h"

using namespace gfx;

struct SEntity
{
	BHandle* mesh;
	float position[3];
	float scale[3];
	float rotation[3];
	float worldMatrix[16];
};

struct SObstacleEntity
{
	SEntity entity;
	float direction[3];
	bool isConquerableByJumping;
	bool isConquerableByShrinking;
	bool isVisible = true;
};

void TranslateEntityWorldMatrix(SEntity &entity);

void ScaleEntityWorldMatrix(SEntity &entity);

void RotateEntityWorldMatrix(SEntity &entity, int axis, float degrees);

void ScaleEntityWorldMatrix(SEntity &entity, float x, float y, float z);

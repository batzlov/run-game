#include "./entity.h"

void TranslateEntityWorldMatrix(SEntity &entity)
{
	float tmp[16];

	GetTranslationMatrix(entity.position[0], entity.position[1], entity.position[2], tmp);

	MulMatrix(entity.worldMatrix, tmp, entity.worldMatrix);
}

void ScaleEntityWorldMatrix(SEntity &entity)
{
	float tmp[16];

	GetScaleMatrix(entity.scale[0], entity.scale[1], entity.scale[2], tmp);

	MulMatrix(entity.worldMatrix, tmp, entity.worldMatrix);
}

void RotateEntityWorldMatrix(SEntity &entity, int axis, float degrees)
{
	float tmp[16];

	switch(axis)
	{
		case 0:
			GetRotationXMatrix(degrees, tmp);
		break;
		case 1:
			GetRotationYMatrix(degrees, tmp);
		break;
		case 2:
			GetRotationZMatrix(degrees, tmp);
		break;
		default:
			// do nothing
		break;
	}

	MulMatrix(entity.worldMatrix, tmp, entity.worldMatrix);
}

void ScaleEntityWorldMatrix(SEntity &entity, float x, float y, float z)
{
	float tmp[16];

	GetScaleMatrix(x, y, z, tmp);

	MulMatrix(entity.worldMatrix, tmp, entity.worldMatrix);
}
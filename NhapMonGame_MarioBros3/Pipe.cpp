#include "Pipe.h"


CPipe::CPipe(bool special, bool where, bool uses, int height)
{
	this->height = height;
	this->isSpecial = special;
	this->isInMainMap = where;
	this->isPullMario = uses;
	isActive = true;
	category = CATEGORY::GROUND;
}

void CPipe::Render()
{
	switch (height)
	{
	case TYPEPIPE::PIPE_SHORT:
			ani = 0;
			break;
	case TYPEPIPE::PIPE_MEDIUM:
		ani = 1;
		break;
	case TYPEPIPE::PIPE_LONG:
		ani = 2;
		break;
	case TYPEPIPE::PIPE_HIDENMAP:
		ani = 3;
		break;
	case TYPEPIPE::PIPE_BRICK:
		ani = 4;
	default:
		ani = 0;
		break;
	}
	if (height <= 4)
	animation_set->at(ani)->Render(x, y);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH * amountX;
	b = y + BRICK_BBOX_HEIGHT * amountY;
}
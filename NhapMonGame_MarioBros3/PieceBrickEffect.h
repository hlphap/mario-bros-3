#pragma once
#include "Effect.h"

#define PIECEBRICK_SPEED_DEFLECT_X		0.06f
#define PIECEBRICK_SPEED_DEFLECT_Y		-0.16f

#define PIECE_BRICK_GRAVITY				0.0009f		
#define BROKEN_BRICK_PIECE_WIDTH		8
#define BROKEN_BRICK_PIECE_HEIGHT		8

class CPieceBrickEffect : public CEffect
{
public:
	CPieceBrickEffect(float x, float y, int nx, int ny);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};


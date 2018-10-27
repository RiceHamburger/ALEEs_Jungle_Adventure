#ifndef SPRITEOBJ_H
#define SPRITEOBJ_H

#include <d3dx9.h>
#include "common.h"
#include "sprite.h"

class SpriteObj {
private:
	Vector2D position;
	Vector2D move;
	float width;
	float height;
	bool isLive;
	int TextureIndex;
	Circle g_CircleCollision;

	LPD3DXSPRITE sprite;
	D3DCOLOR color;
public:
	SpriteObj();
	~SpriteObj();
	void Update();
	void Draw();
	virtual void DrawCut();

	void SetObjectData(Vector2D pos, float width, float height);
	void SetPosition(Vector2D pos);
	void SetMoveX(float x);
	void SetMoveY(float y);
	void SetWidth(float wid);
	void SetHeight(float hei);
	void SetLiveFlag(bool flag);
	void SetTextureIndex(int index);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetCircleCollision(Circle objCollision);
	void SetCircleCollisionX(float x);
	void SetCircleCollisionY(float y);
	void InitSprite();

	Vector2D GetPosition();
	float GetWidth();
	float GetHeight();
	bool GetLiveFlag();
	int GetTextureIndex();
	Circle* GetCircleCollision();
};

#endif
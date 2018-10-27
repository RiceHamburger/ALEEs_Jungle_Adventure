#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "sprite.h"

class Object {
private:
	Vector2D position;
	Vector2D move;
	float width;
	float height;
	bool isLive;
	int TextureIndex;
	Circle g_CircleCollision;

	//camera
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
public:
	Object();
	~Object();
	void Update();
	void Draw();
	virtual void DrawCut();

	void DrawSprite();
	void DrawSprite(RECT* text_rec);

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
	void SetSpriteColor(D3DCOLOR Rgba);

	void InitSprite();
	void Sprite_Uninit();

	Vector2D GetPosition();
	float GetWidth();
	float GetHeight();
	bool GetLiveFlag();
	int GetTextureIndex();
	Circle* GetCircleCollision();
};

#endif
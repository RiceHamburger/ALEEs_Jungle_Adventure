
#include "background.h"
#include "sprite.h"
#include "texture.h"

BackGround::BackGround(int index, Vector2D pos)
{
	SetPosition(pos);
	SetTextureIndex(index);
	SetWidth(Texture_GetWidth(index));
	SetHeight(Texture_GetHeight(index));
}

BackGround::~BackGround()
{
}
#include "explosion.h"

Explosion::Explosion() {

}
Explosion::~Explosion() {

}

void Explosion::InitExplosion(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX,int tex_pic_numY) {
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(EXPLOSION_WIDTH);
	SetHeight(EXPLOSION_WIDTH);
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	textureX_NUM = tex_pic_numX;
	textureY_NUM = tex_pic_numY;
	aniTime = EXPLOSION_ANIMATION_TIME;
	this->SetLiveFlag(false);

	text_rec.left = textureX;
	text_rec.top = textureY;
	text_rec.right = text_rec.left + GetWidth();
	text_rec.bottom = text_rec.top + GetHeight();
}

void Explosion::ExplosionActive() {
	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= textureX_NUM) {
			textureX_index = 0;

			textureY_index++;
			if (textureY_index >= textureY_NUM) {
				ExplosionDestroy();
			}
		}

		textureX = GetWidth()*(textureX_index % textureX_NUM);
		textureY = GetHeight()*(textureY_index % textureY_NUM);
		aniTime = EXPLOSION_ANIMATION_TIME;

		text_rec.left = textureX;
		text_rec.top = textureY;
		text_rec.right = text_rec.left + GetWidth();
		text_rec.bottom = text_rec.top + GetHeight();
	}
}

void Explosion::ExplosionDestroy() {
	textureX_index = 0;
	textureY_index = 0;
	aniTime = EXPLOSION_ANIMATION_TIME;
	SetLiveFlag(false);
	text_rec = { 0 };
}

/*void Explosion::DrawCut() {
	Sprite_Draw(GetTextureIndex(), GetPosition().x, GetPosition().y, textureX, textureY, GetWidth(), GetHeight());
}*/

RECT* Explosion::GetRect() {
	return &text_rec;
}
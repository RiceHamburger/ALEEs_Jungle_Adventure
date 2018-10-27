#ifndef EXPLOSION_H_
#define EXPLOSION_H_
#include "texture.h"
#include "object.h"

#define EXPLOSION_MAX (6)
#define EXPLOSION_WIDTH (128)
#define EXPLOSION_ANIMATION_TIME (4)
#define EXPLOSION_PIC_NUM (4)

class Explosion :public Object {
private:
	RECT text_rec;
	int textureX;
	int textureY;
	int textureX_index;
	int textureY_index;
	int textureX_NUM;
	int textureY_NUM;
	int aniTime;
public:
	Explosion();
	~Explosion();
	void InitExplosion(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY);
	void ExplosionActive();
	void ExplosionDestroy();
	//void DrawCut();
	RECT *GetRect();
};

#endif //ENEMY_H_
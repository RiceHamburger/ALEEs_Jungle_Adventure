#include "enemy.h"
#include "direct3d_setup.h"
#include "bullet_Manager.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {

}

void Enemy::InitEnemy(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(ENEMY_WIDTH);
	SetHeight(ENEMY_HEIGHT);
	//”»’è‚Ì‰~‚ðÝ’è‚·‚é
	objCollision.cx = pos.x + GetHeight() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetHeight()*0.5f;
	SetCircleCollision(objCollision);
	this->SetLiveFlag(true);

	targetIndex = 0;
	bodydamage = ENEMY_BODYDAMAGE;
	SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	//sprite rect
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	textureX_NUM = tex_pic_numX;
	textureY_NUM = tex_pic_numY;
	aniTime = ENEMY_ANIMATION_TIME;
	text_rec.left = textureX;
	text_rec.top = textureY;
	text_rec.right = text_rec.left + GetHeight();
	text_rec.bottom = text_rec.top + GetHeight();

	health_percent = 1.0f;
	reSpawnTime = ENEMY_RETIME;

	//attack time
	attackTime = ENEMY_ATTACK_TIME;
	Effect = false;
	Effect_time = ENEMY_EFFECT_TIME;
}

void Enemy::SetTargetArr(Vector2D MtargetArr) {
	targetArr[targetIndex].x = MtargetArr.x;
	targetArr[targetIndex].y = MtargetArr.y;
	targetIndex++;
}

void Enemy::SetTargetIndex(int index) {
	targetIndex = index;
}

void Enemy::EnemyActive() {
	Vector2D position = GetPosition();

	if ((targetArr[targetIndex].x - position.x)*(targetArr[targetIndex].x - position.x) + (targetArr[targetIndex].y - position.y)*(targetArr[targetIndex].y - position.y) <= 10) {
		targetIndex++;
		if (targetIndex >= ENEMY_TARGET) {
			targetIndex = 0;
		}
	}

	float radian = getRadian(position.x, position.y, targetArr[targetIndex].x, targetArr[targetIndex].y);

	SetMoveX(cosf(radian) * speed);
	SetMoveY(sinf(radian) * speed);

	Update();

	SetCircleCollisionX(position.x + GetHeight() / 2);
	SetCircleCollisionY(position.y + GetHeight() / 2);

	//texture
	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= textureX_NUM) {
			textureX_index = 0;

			textureY_index++;
			if (textureY_index >= textureY_NUM) {
				textureY_index = 0;
			}
		}

		textureX = GetWidth()*(textureX_index % textureX_NUM);
		textureY = GetHeight()*(textureY_index % textureY_NUM);
		aniTime = ENEMY_ANIMATION_TIME;

		text_rec.left = textureX;
		text_rec.top = textureY;
		text_rec.right = text_rec.left + GetWidth();
		text_rec.bottom = text_rec.top + GetHeight();
	}

	//demage effect
	if (Effect) {
		SetSpriteColor(D3DCOLOR_ARGB((rand() % 155) + 1, 255, 255, 255));
		Effect_time--;
		if (Effect_time <= 0) {
			Effect = false;
			Effect_time = ENEMY_EFFECT_TIME;
			SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void Enemy::EnemyDestroy() {
	SetLiveFlag(false);
}

void Enemy::SetLife(int Life) {
	life = Life;
	if (life <= 0) {
		life = 0;
	}
}

void Enemy::SetScore(int Score) {
	score = Score;
}

void Enemy::SetSpeed(float Speed) {
	speed = Speed;
}

float Enemy::GetSpeed() {
	return speed;
}

int Enemy::GetScore() {
	return score;
}

RECT* Enemy::GetRect() {
	return &text_rec;
}

int Enemy::GetLife() {
	return life;
}

void Enemy::DeletTargetArr() {
	for (int i = 0;i < ENEMY_TARGET;i++) {
		targetArr[i] = { 0 };
	}
}

float Enemy::getRadian(float X1, float Y1, float X2, float Y2) {
	float w = X2 - X1; // cosƒÆ
	float h = Y2 - Y1; // sinƒÆ

	// atan2fŒÄ‚Ô‚¾‚¯‚Å‚¨‚µ‚Ü‚¢
	return atan2f(h, w);
}

int Enemy::GetEnemyBodyDamage() {
	return bodydamage;
}

void Enemy::InitBloodSprite() {
	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &health_sprite);
}

void Enemy::BloodSprite_Uninit() {
	health_sprite->Release();
}

void Enemy::DrawBloodSprite() {
	Vector2D Myposition = GetPosition();

	D3DXVECTOR3 Position;
	Position.x = Myposition.x + 5;
	Position.y = Myposition.y - ENEMY_HEALTHBAR_HEIGHT;
	Position.z = 0;

	health_percent = (float)life / ENEMY_HEALTHBAR_TOTAL;

	health_rec.left = 0;
	health_rec.top = 0;
	health_rec.right = health_rec.left + ENEMY_HEALTHBAR_WIDTH * health_percent;
	health_rec.bottom = health_rec.top + ENEMY_HEALTHBAR_HEIGHT;

	health_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	health_sprite->Draw(Texture_GetTexture(ENEMYBAR), &health_rec, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	health_sprite->End();
}

void Enemy::EnemyRespawn() {
	reSpawnTime--;
	if (reSpawnTime <= 0) {
		life = ENEMY_HEALTHBAR_TOTAL;
		health_percent = 1.0f;
		SetLiveFlag(true);
		reSpawnTime = ENEMY_RETIME;
		attackTime = ENEMY_ATTACK_TIME;
		Effect = false;
		Effect_time = ENEMY_EFFECT_TIME;
		SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Enemy::EnemyAttack() {
	attackTime--;
	if (attackTime <= 0) {
		EnemyBullet_Create(GetPosition().x + GetWidth() / 2 - BULLET_WIDTH/2, GetPosition().y + GetHeight() / 2);
		attackTime = ENEMY_ATTACK_TIME;
	}
	
}

void Enemy::SetDamageEffect(bool sw) {
	Effect = sw;
	Effect_time = ENEMY_EFFECT_TIME;
}
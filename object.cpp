#include "texture.h"
#include "object.h"

//�R���X�g���N�^
//==================================================
Object::Object()
{
	position = { 0.0f };
	move = { 0.0f };
	width = 0.0f;
	height = 0.0f;
	isLive = false;
	TextureIndex = 0;
	g_CircleCollision = { 0 };
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

// ����������
//==================================================
void Object::InitSprite() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

//�X�V����
//==================================================
void Object::Update()
{
	//�ړ��ʂ����Z
	position.x += move.x;
	position.y += move.y;
}

// �`�揈��
//==================================================
void Object::DrawSprite() {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), NULL, NULL, &Position, color);

	sprite->End();
}

// �`�揈���i�\���͈́j
//==================================================
void Object::DrawSprite(RECT* text_rec) {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), text_rec, NULL, &Position, color);

	sprite->End();
}

// �I�u�W�F�N�g�ݒ菈��
//==================================================
void Object::SetObjectData(Vector2D pos, float wid, float hei)
{
	position = pos;
	width = wid;
	height = hei;
	isLive = true;
}

// ���W�ݒ�
//==================================================
void Object::SetPosition(Vector2D pos)
{
	position = pos;
}

// X���ړ��x�N�g���X�V
//==================================================
void Object::SetMoveX(float x)
{
	move.x = x;
}

// Y���ړ��x�N�g���X�V
//==================================================
void Object::SetMoveY(float y)
{
	move.y = y;
}

// �L���ݒ�
//==================================================
void Object::SetWidth(float wid)
{
	width = wid;
}

// �����ݒ�
//==================================================
void Object::SetHeight(float hei)
{
	height = hei;
}

// ���s�`�F�b�N�p�t���O�ݒ�
//==================================================
void Object::SetLiveFlag(bool flag)
{
	isLive = flag;
}

// �e�N�X�`���C���f�b�N�X�ݒ�
//==================================================
void Object::SetTextureIndex(int index) {
	TextureIndex = index;
}

// X���W�ݒ�
//==================================================
void Object::SetPositionX(float x) {
	position.x = x;
}

// Y���W�ݒ�
//==================================================
void Object::SetPositionY(float y) {
	position.y = y;
}

// �~�R���W�����ݒ�
//==================================================
void Object::SetCircleCollision(Circle objCollision) {
	g_CircleCollision = objCollision;
}

// �~�R���W������X���W�ݒ�
//==================================================
void Object::SetCircleCollisionX(float x) {
	g_CircleCollision.cx = x;
}

// �~�R���W������Y���W�ݒ�
//==================================================
void Object::SetCircleCollisionY(float y) {
	g_CircleCollision.cy = y;
}

// ���W�����
//==================================================
Vector2D Object::GetPosition() {
	return position;
}

// �L�������
//==================================================
float Object::GetWidth() {
	return width;
}

// ���������
//==================================================
float Object::GetHeight() {
	return height;
}

// ���W�����
//==================================================
bool Object::GetLiveFlag() {
	return isLive;
}

// �e�N�X�`���C���f�b�N�X�����
//==================================================
int Object::GetTextureIndex() {
	return TextureIndex;
}

// �R���W���������
//==================================================
Circle* Object::GetCircleCollision() {
	return &g_CircleCollision;
}

//�f�X�g���N�^
//==================================================
Object::~Object()
{

}

//�I������
//==================================================
void Object::Sprite_Uninit() {
	sprite->Release();
}

// �X�v���C�g�F�����
//==================================================
void Object::SetSpriteColor(D3DCOLOR Rgba) {
	color = Rgba;
}
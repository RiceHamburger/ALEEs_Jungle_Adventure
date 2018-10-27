#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>

//���_�o�b�t�@
void Sprite_Initialize(void);
void Sprite_Finalize(void);

//�e�N�X�`���[�ƃT�C�Y���ꏏ�ɂ���֐�
void Sprite_Draw(int texture_index, float dx, float dy);
//�e�N�X�`���[�؂���
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void Sprite_SetColor(D3DCOLOR color);

#endif // SPRITE_H_
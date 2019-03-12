//==================================================
//  sprite�N���X [Sprite.h]        Autor:��
//==================================================

#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>

/*�\���̐錾*/
//creat 2D
typedef struct
{
	//float�ɂ��ĂS��1.0f���W�ϊ����_
	D3DXVECTOR4 position;
	//color
	D3DCOLOR color;
	//texture
	D3DXVECTOR2 texcoard;
}Vertex2D;

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

class Sprite {
public:
	Sprite();
	~Sprite();
	//���_�o�b�t�@
	void Sprite_Initialize(void);
	void Sprite_Finalize(void);

	//�e�N�X�`���[�ƃT�C�Y���ꏏ�ɂ���֐�
	void Sprite_Draw(int texture_index, float dx, float dy);

	//�e�N�X�`���[�؂���
	void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);

	void Sprite_SetColor(D3DCOLOR color);
private:
	static D3DCOLOR m_Color;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;

};

#endif // SPRITE_H_
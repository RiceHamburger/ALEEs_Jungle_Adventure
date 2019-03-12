//==================================================
//  spriteクラス [Sprite.h]        Autor:ロ
//==================================================

#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>

/*構造体宣言*/
//creat 2D
typedef struct
{
	//floatにして４つ目1.0f座標変換頂点
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
	//頂点バッファ
	void Sprite_Initialize(void);
	void Sprite_Finalize(void);

	//テクスチャーとサイズが一緒にする関数
	void Sprite_Draw(int texture_index, float dx, float dy);

	//テクスチャー切り取り
	void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);

	void Sprite_SetColor(D3DCOLOR color);
private:
	static D3DCOLOR m_Color;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;

};

#endif // SPRITE_H_
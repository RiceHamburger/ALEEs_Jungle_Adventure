#include <d3dx9.h>
#include "texture.h"
#include "direct3d_setup.h"

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

//#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

/**/
static D3DCOLOR g_Color = 0xffffffff;
//static D3DCOLOR g_Color = D3DCOLOR_RGBA(255,255,255,255);

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

void Sprite_SetColor(D3DCOLOR color) {
	g_Color = color;
}

//画像インデックス、X座標、Y座標
void Sprite_Draw(int texture_index, float dx, float dy) {

	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	float texture_width = (float)Texture_GetWidth(texture_index);
	float texture_height = (float)Texture_GetHeight(texture_index);

	float texture_Tx = dx - 0.5f;
	float texture_Ty = dy - 0.5f;
	float texture_Tw = dx + texture_width - 0.5f;
	float texture_Th = dy + texture_height - 0.5f;
	
	Vertex2D Square[] = {
		{ D3DXVECTOR4(texture_Tx, texture_Ty, 1.0f, 1.0f), g_Color,D3DXVECTOR2(0.0f,0.0f) },//0 0
		{ D3DXVECTOR4(texture_Tw, texture_Ty, 1.0f, 1.0f), g_Color,D3DXVECTOR2(1.0f,0.0f) },//1 1
		{ D3DXVECTOR4(texture_Tx, texture_Th, 1.0f, 1.0f), g_Color,D3DXVECTOR2(0.0f,1.0f) },//3 2
		{ D3DXVECTOR4(texture_Tw, texture_Th, 1.0f, 1.0f), g_Color,D3DXVECTOR2(1.0f,1.0f) }//2 4
	};


	//頂点インデックス
	WORD index[] = {
		0,1,2,
		1,3,2,
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	//Square
	g_pD3DDevice->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		4,
		2,
		index,
		D3DFMT_INDEX16,
		Square,
		sizeof(Vertex2D)
	);
}

//画像インデックス、X座標、Y座標、テクスチャの画像X座標、テクスチャの画像Y座標、画像の横サイズ、画像の立てサイズ
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th) {
	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	float texture_width = Texture_GetWidth(texture_index);
	float texture_height = Texture_GetHeight(texture_index);

	float texture_Tx = dx - 0.5f;
	float texture_Ty = dy - 0.5f;
	float texture_Tw = dx + texture_width - 0.5f;
	float texture_Th = dy + texture_height - 0.5f;

	float u0 = (float)tx / texture_width;
	float v0 = (float)ty / texture_height;
	float u1 = (float)(tx + tw) / texture_width;
	float v1 = (float)(ty + th) / texture_height;

	Vertex2D Square[] = {
		{ D3DXVECTOR4(texture_Tx, texture_Ty, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(tw + texture_Tx, texture_Ty, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(texture_Tx, texture_Ty +th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(tw + texture_Tx, texture_Ty + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1,v1) }
	};

	//仮想アドレス
	Vertex2D* pV;

	//頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, Square, sizeof(Square));
	g_pVertexBuffer->Unlock();

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));



	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	g_pD3DDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Square));

	//Square
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		Square,
		sizeof(Square[0])
		);

}

void Sprite_Initialize(void) {
	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();

	//頂点バッファの確保
	g_pD3DDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
}

void Sprite_Finalize(void) {
	//頂点バッファの解放
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

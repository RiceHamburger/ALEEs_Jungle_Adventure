#include "Effect.h"
#include "direct3d_setup.h"
#include "texture.h"

#define EFFECT_COUNT_MAX (2048)
//#define RAD90 (D3DX_PI*0.5f)
//#define RAD45 (D3DXToRadian(45))

typedef struct Effect_tag {
	float x, y;
	float radius;
	D3DCOLOR color;
	float alpha;
	int life;
	int birth;
}Effect;

//Texture
typedef struct EffectVertex_tag {
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}EffectVertex;

#define FVF_EFFECT (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

static int g_EffectframeCount = 0;
static Effect g_Effects[EFFECT_COUNT_MAX];
static LPDIRECT3DVERTEXBUFFER9 g_Effectvertexbuff = NULL;
static LPDIRECT3DINDEXBUFFER9 g_EffectIndexbuff = NULL;

static int g_EffectCount = 0;

void Effect_Initialize(void) {
	g_EffectframeCount = 0;
	g_EffectCount = 0;

	for (int i = 0;i < EFFECT_COUNT_MAX;i++) {
		g_Effects[i].life = -1;
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->CreateVertexBuffer(sizeof(EffectVertex) * 4 * EFFECT_COUNT_MAX, D3DUSAGE_WRITEONLY, FVF_EFFECT, D3DPOOL_MANAGED, &g_Effectvertexbuff, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6 * EFFECT_COUNT_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_EffectIndexbuff, NULL);
}

void Effect_Finalize(void) {
	if (g_Effectvertexbuff) {
		g_Effectvertexbuff->Release();
		g_Effectvertexbuff = NULL;
	}

	if (g_EffectIndexbuff) {
		g_EffectIndexbuff->Release();
		g_EffectIndexbuff = NULL;
	}
}

void Effect_Update(void) {

	g_EffectCount = 0;


	for (int i = 0;i < EFFECT_COUNT_MAX;i++) {
		if (g_Effects[i].life >= 0) {

			int age = g_EffectframeCount - g_Effects[i].birth;

			if (age >= g_Effects[i].life) {
				g_Effects[i].life = -1;
				continue;
			}
				
			g_Effects[i].alpha = 1.0f - age / g_Effects[i].life;
			g_Effects[i].radius *= 0.9f;
			
			g_EffectCount++;
		}
	}

	//四角の数
	int n = 0;

	EffectVertex* pV;
	g_Effectvertexbuff->Lock(0, 0, (void**)&pV, 0);

	WORD* pIndex;
	g_EffectIndexbuff->Lock(0, 0, (void**)&pIndex, 0);



	for (int i = 0;i < EFFECT_COUNT_MAX;i++) {

		//Iエフェクトのインデックス
		if (g_Effects[i].life >= 0) {

			D3DXCOLOR color = g_Effects[i].color;
			color.a = g_Effects[i].alpha;

			//static const float kakudo[4] = { D3DXToRadian(45 + 180),D3DXToRadian(45 + 180 + 90), D3DXToRadian(45 + 180 + 270), D3DXToRadian(45 + 180 + 180) };

			for (int j = 0;j < 4;j++) {
				//ｊ　四角の頂点カウント
				pV[n * 4 + j].position.x = cos(D3DXToRadian(45 + 90 * j))*g_Effects[i].radius + g_Effects[i].x;
				pV[n * 4 + j].position.y = sin(D3DXToRadian(45 + 90 * j))*g_Effects[i].radius + g_Effects[i].y;
				pV[n * 4 + j].position.z = 1.0f;
				pV[n * 4 + j].position.w = 1.0f;
				pV[n * 4 + j].color = color;
			}

			pV[n * 4 + 0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
			pV[n * 4 + 1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
			pV[n * 4 + 2].texcoord = D3DXVECTOR2(1.0f, 1.0f);
			pV[n * 4 + 3].texcoord = D3DXVECTOR2(0.0f, 1.0f);


			pIndex[n * 6 + 0] = n * 4 + 0;
			pIndex[n * 6 + 1] = n * 4 + 1;
			pIndex[n * 6 + 2] = n * 4 + 2;
			pIndex[n * 6 + 3] = n * 4 + 2;
			pIndex[n * 6 + 4] = n * 4 + 3;
			pIndex[n * 6 + 5] = n * 4 + 0;

			n++;

		}
	}

	g_Effectvertexbuff->Unlock();
	g_EffectIndexbuff->Unlock();

	//フレームの更新
	g_EffectframeCount++;
}

void Effect_Draw(void) {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetStreamSource(0, g_Effectvertexbuff, 0, sizeof(EffectVertex));
	pDevice->SetIndices(g_EffectIndexbuff);
	pDevice->SetFVF(FVF_EFFECT);
	pDevice->SetTexture(0, Texture_GetTexture(EFFECT));

	//加算合成
	//SrcRGB * Srca + DestRGB * 1.0f;
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	

	/*pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2 * g_EffectCount
	);*/

	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		4 * g_EffectCount,
		0,
		2 * g_EffectCount
	);

	//回歸
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//一般的合成 半透明
	//SrcRGB * Srca + DestRGB * (1.0f - Srca);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
}

void Effect_Creat(float x, float y,float radius, int life, D3DCOLOR color) {
	for (int i = 0;i < EFFECT_COUNT_MAX;i++) {
		if (g_Effects[i].life < 0) {
			g_Effects[i].alpha = 1.0f;
			g_Effects[i].birth = g_EffectframeCount;
			g_Effects[i].color = color;
			g_Effects[i].life = life;
			g_Effects[i].radius = radius;
			g_Effects[i].x = x;
			g_Effects[i].y = y;
			break;
		}
	}
}
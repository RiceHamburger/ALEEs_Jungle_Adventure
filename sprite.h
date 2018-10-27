#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>

//頂点バッファ
void Sprite_Initialize(void);
void Sprite_Finalize(void);

//テクスチャーとサイズが一緒にする関数
void Sprite_Draw(int texture_index, float dx, float dy);
//テクスチャー切り取り
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void Sprite_SetColor(D3DCOLOR color);

#endif // SPRITE_H_
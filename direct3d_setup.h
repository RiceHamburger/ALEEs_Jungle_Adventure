#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_

#include <Windows.h>
#include <d3dx9.h>
//Direct3D初期化
//
//戻り値：初期化に失敗したらfalse
//
//引数：hWnd..ウィンドウハンドル
//
bool MyDirect3D_Initialize(HWND hWnd);

//Direct3D終了処理
void MyDirect3D_Finallize(void);

//Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);

//個人
//GET　TEXTURE
//LPDIRECT3DTEXTURE9 GetDevice_pTexture(void);

#endif // MYDIRECT3D_H_
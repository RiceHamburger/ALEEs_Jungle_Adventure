#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_

#include <Windows.h>
#include <d3dx9.h>
//Direct3D������
//
//�߂�l�F�������Ɏ��s������false
//
//�����FhWnd..�E�B���h�E�n���h��
//
bool MyDirect3D_Initialize(HWND hWnd);

//Direct3D�I������
void MyDirect3D_Finallize(void);

//Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);

//�l
//GET�@TEXTURE
//LPDIRECT3DTEXTURE9 GetDevice_pTexture(void);

#endif // MYDIRECT3D_H_
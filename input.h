//=============================================================================
//
// キーボード入力処理 [input.h]
//
//=============================================================================
#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XInput.h>
#pragma comment (lib, "xinput.lib")

bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);
void Keyboard_Finalize(void);
void Keyboard_Update(void);

//xinput
bool Xinput_Initialize(HWND hWnd);
void Xinput_Update(void);
void Xinput_Finalize(void);
bool Xinput_IsTrigger(int nKey);

bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

#endif
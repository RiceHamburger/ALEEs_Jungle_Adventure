#include "texture.h"
#include "game.h"
#include "Title_Manager.h"
#include "Level1_Manager.h"
#include "End_Manager.h"

static Scene_Index scene = Scene_Title;

static int NewScore = 0;
static int OldScore = 0;

static void(*Init[])() = { TitleInit, Level_one_Init, EndInit };
static void(*Update[])() = { TitleUpdate, Level_one_Update, EndUpdate };
static void(*Draw[])() = { TitleDraw, Level_one_Draw, EndDraw };
static void(*Uninit[])() = { TitleUninit, Level_one_Uninit, EndUninit };

bool Game_Initialize(void) {
	if (Texture_Load() > 0) {
		return false;
	}
	GameSceneChange(Scene_Title);
	return true;
}
void Game_Finalize(void) {
	//テクスチャの解放
	Texture_Release();
}
void Game_Update(void) {
	Update[scene]();
}
void Game_Draw(void) {
	Draw[scene]();
}

void GameSceneChange(Scene_Index next) {
	//scene change
	Uninit[scene]();
	Init[next]();
	scene = next;
}

 void SetEndScore(int s) {
	NewScore = s;

	if (NewScore > OldScore) {
		OldScore = NewScore;
	}
}

int GetEndScore(void) {
	return NewScore;
}

int GetEndScoreBest(void) {
	return OldScore;
}
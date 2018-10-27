#ifndef GAME_H_
#define GAME_H_

typedef enum
{
	Scene_Title,
	Scene_Level_1,
	Scene_End
}Scene_Index;

bool Game_Initialize(void);
void Game_Finalize(void);
void Game_Update(void);
void Game_Draw(void);
void GameSceneChange(Scene_Index next);

void SetEndScore(int s);
int GetEndScore(void);
int GetEndScoreBest(void);

#endif // GAME_H_
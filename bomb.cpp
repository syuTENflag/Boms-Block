#include "game.h"

#pragma region 外部変数呼び出し
int BombX, BombY;	// 爆弾の位置
int bombCount;		// 使ったボムの数をカウント
bool bombFlg;		// ボムを置いているかどうかのフラグ
#pragma endregion

// 爆弾の配置
void ArrangementBomb() {
	if (px % SQUARES_SIZE >= SQUARES_SIZE / 2) {
		BombX = SQUARES_SIZE * (px / SQUARES_SIZE) + SQUARES_SIZE;
	}
	else
	{
		BombX = SQUARES_SIZE * (px / SQUARES_SIZE);
	}

	if (py % SQUARES_SIZE >= SQUARES_SIZE / 2) {
		BombY = SQUARES_SIZE * (py / SQUARES_SIZE) + SQUARES_SIZE;
	}
	else
	{
		BombY = SQUARES_SIZE * (py / SQUARES_SIZE);
	}
}
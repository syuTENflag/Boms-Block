/*
	タイトル画面処理のソース
*/
#pragma region main.hのインクルード

#include "game.h"

#pragma endregion
void TitleDraw() {
	// タイトル名のフォントサイズを指定し指定の座標に描画する
	SetFontSize(75);
	DrawFormatString(88, 150, Color_Yellow, "BLOCK PUZZLE");

	// 指示のフォントサイズを指定し指定の座標に描画する
	SetFontSize(40);
	DrawFormatString(100, 240, Color_Yellow, "PSコントローラーの\nタッチパッドを押して\n　　　スタート");

	
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) {// タッチパッド
		game_start = GAME_PLAYING;
		
		WaitTimer(100);

		
	}
}
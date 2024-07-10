#include "game.h"

#pragma region 外部変数呼び出し
int px, py;			// 主人公の位置
#pragma endregion

#pragma region プレイヤーの移動
/*
	各方向のforループ内のみの変数x、yはそのまま使うとマップデータの値になるため、
	プレイヤー座標に代入する場合はマス目のサイズをかける
	プレイヤー座標との条件文を作る場合はプレイヤー座標の値をマス目のサイズで割った値の整数値を使う
*/


// 右
void PlayerRightMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// 右の隣のマスが壁かどうか判定（座標変更も判定関数内で行う）
			if (((px + PLAYER_SIZE + 1) / SQUARES_SIZE == x) && (py / SQUARES_SIZE == y)) {
				RightHitWall(x, y);
			}
			//px、pyの位置を左上にしてキャラ画像（右移動）を描画
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[13], TRUE);
			
		}
	}
}

// 左
void PlayerLeftMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// 左の隣のマスが壁かどうか判定（座標変更も判定関数内で行う）
			if (((px - 1) / SQUARES_SIZE == x) && (py / SQUARES_SIZE == y)) {
				LeftHitWall(x, y);
			}
			//px、pyの位置を左上にしてキャラ画像（左移動）を描画
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[9], TRUE);
			
		}
	}
}

// 上
void PlayerUpMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// 上の隣のマスが壁かどうか判定（座標変更も判定関数内で行う）
			if ((px / SQUARES_SIZE == x) && ((py - 1) / SQUARES_SIZE == y)) {
				UpHitWall(x, y);
			}
			//px、pyの位置を左上にしてキャラ画像（上移動）を描画
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[1], TRUE);
			
		}
	}
}

// 下
void PlayerDownMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// 下の隣のマスが壁かどうか判定（座標変更も判定関数内で行う）
			if ((px / SQUARES_SIZE == x) && ((py + PLAYER_SIZE + 1) / SQUARES_SIZE == y)) {
				DownHitWall(x, y);
			}
			//px、pyの位置を左上にしてキャラ画像（下移動）を描画
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[5], TRUE);
			
		}
	}
}
#pragma endregion

#pragma region プレイヤーと壁の当たり判定
/*
	それぞれの移動したいマスのマス目の値が渡されてくるので、まずそのマスが壁かブロックかなにもないかを判定する
	もし壁かブロックであったら、プレイヤーのいる位置を調べ、
	移動したいマスの隣り合うマス（プレイヤーがいない方向）が何もなければその方向に移動させる

	移動したいマスが何もない場合は、移動したい方向ではない（xならy、yならx）の右（下）端の座標がy(x)+1か調べる
	もしそうであれば、移動したい方向ではない（xならy、yならx）に+1したマスが何もないか調べる
	もし何かあった場合は、先ほど足したところをもとに戻した値を調べて何もなければその方向に移動させ、
	何もなければ移動したいマスに向け移動させる

	上記の判定でなにもなければ移動したいマスには何もないのでそのまま移動させる
*/

// 右
void RightHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x - 1] == SQUARE_NONE) {
			py += 1;
		}
		else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
			py -= 1;
		}
	}
	else if ((py + PLAYER_SIZE) / SQUARES_SIZE == y + 1) {
		if (mapData[y + 1][x] != SQUARE_NONE) {
			if (mapData[y][x - 1] == SQUARE_NONE) {
				py -= 1;
			}
		}
		else {
			px += 1;
		}
	}
	else {
		px += 1;
	}
}

// 左
void LeftHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x + 1] == SQUARE_NONE) {
			py += 1;
		}
		else if (mapData[y - 1][x + 1] == SQUARE_NONE) {
			py -= 1;
		}
	}
	else if ((py + PLAYER_SIZE) / SQUARES_SIZE == y + 1) {
		if (mapData[y + 1][x] != SQUARE_NONE) {
			if (mapData[y][x + 1] == SQUARE_NONE) {
				py -= 1;
			}
		}
		else {
			px -= 1;
		}
	}
	else {
		px -= 1;
	}
}

// 上
void UpHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x + 1] == SQUARE_NONE) {
			px += 1;
		}
		else if (mapData[y + 1][x - 1] == SQUARE_NONE) {
			px -= 1;
		}
	}
	else if ((px + PLAYER_SIZE) / SQUARES_SIZE == x + 1) {
		if (mapData[y][x + 1] != SQUARE_NONE) {
			if (mapData[y + 1][x] == SQUARE_NONE) {
				px -= 1;
			}
		}
		else {
			py -= 1;
		}
	}
	else {
		py -= 1;
	}
}

// 下
void DownHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y - 1][x + 1] == SQUARE_NONE) {
			px += 1;
		}
		else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
			px -= 1;
		}
	}
	else if ((px + PLAYER_SIZE) / SQUARES_SIZE == x + 1) {
		if (mapData[y][x + 1] != SQUARE_NONE) {
			if (mapData[y - 1][x] == SQUARE_NONE) {
				px -= 1;
			}
		}
		else {
			py += 1;
		}
	}
	else {
		py += 1;
	}
}
#pragma endregion
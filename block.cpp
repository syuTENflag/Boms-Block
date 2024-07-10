#include "game.h"

int bx[], by[];  // ブロックの位置用
int blockCnt;    // ブロックの数
int clearCnt;    // クリアさせるためのカウンター

// ブロック生成
void BlockGenerate() {
    int rndX = 0, rndY = 0;
    int x = 0, y = 0;

    // 座標取得
    if (blockCnt < BLOCK_MAX) {
        //XとYの座標取得
        while (bx[blockCnt] == 0 || by[blockCnt] == 0) {
            //ランダムに取得
            rndX = GetRand(SQUARES_SIZE * 15 + 1);
            rndY = GetRand(SQUARES_SIZE * 13 + 1);

            // マス目に収まるときのみ被りがないかチェックする（収まらなかった時はまた取り直す）
            if ((rndX % SQUARES_SIZE == 0 && rndY % SQUARES_SIZE == 0) && mapData[rndY / SQUARES_SIZE][rndX / SQUARES_SIZE] == SQUARE_NONE) {
                // 被ってたら取り直す。被りがなかったらループから抜けカウントを増やし画像生成する
                if (BlockCheck(rndX, rndY) == true) {
                    // プレイヤーと同じ場所にはならないようにする
                    if (rndX == px && rndY == py) {
                        continue;
                    }
                    bx[blockCnt] = rndX;
                    by[blockCnt] = rndY;
                    break;
                }
                else {
                    continue;
                }
            }
        }

        //マップデータ変更
        x = bx[blockCnt] / SQUARES_SIZE;
        y = by[blockCnt] / SQUARES_SIZE;
        mapData[y][x] = SQUARE_BLOCK;

        // カウントを増やす
        blockCnt++;
        clearCnt++;
    }
}

// ブロックがダブってないかチェック
bool BlockCheck(int rx, int ry) {
    // 最初のブロックの場合はそのままtrueを返す
    // 2個目以降はforループで被りがないか調べ被ってたらfalseを返す
    if (blockCnt > 0) {
        for (int i = 0; i < blockCnt; i++) {
            // 被ってた時
            if (bx[i] == rx && by[i] == ry) {
                return false;
            }
            // 被ってなかった時
            else if (i == blockCnt - 1) {
                return true;
            }
        }
    }
    else {
        return true;
    }
    return false;
}

// 爆風に巻き込まれたブロックを消す処理
void DestroyBlocks() {
    for (int i = 0; i < blockCnt; i++) {
        if ((bx[i] == BombX && by[i] == BombY) ||
            (bx[i] == BombX - SQUARES_SIZE && by[i] == BombY) ||
            (bx[i] == BombX - SQUARES_SIZE * 2 && by[i] == BombY) ||
            (bx[i] == BombX + SQUARES_SIZE && by[i] == BombY) ||
            (bx[i] == BombX + SQUARES_SIZE * 2 && by[i] == BombY) ||
            (bx[i] == BombX && by[i] == BombY - SQUARES_SIZE) ||
            (bx[i] == BombX && by[i] == BombY - SQUARES_SIZE * 2) ||
            (bx[i] == BombX && by[i] == BombY + SQUARES_SIZE) ||
            (bx[i] == BombX && by[i] == BombY + SQUARES_SIZE * 2)) {

            // ブロックを消し、マップデータを何もない状態にする
            int y = by[i] / SQUARES_SIZE;
            int x = bx[i] / SQUARES_SIZE;

            if (BombX < bx[i]) {
                if (mapData[y][x - 1] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombX > bx[i]) {
                if (mapData[y][x + 1] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombY < by[i]) {
                if (mapData[y - 1][x] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombY > by[i]) {
                if (mapData[y + 1][x] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
        }
    }
}

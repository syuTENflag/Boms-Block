#pragma once

#pragma region ゲーム内で使うヘッダーファイルなどの定義
#include "DxLib.h"	// DXライブラリのヘッダー
#include <time.h>	// 時間関係のヘッダー
#include <string>	// stringstream を使うためにインポート
#include <sstream>	// ifstreamを使うためにインポート
#include <fstream>
//#include <stdlib.h>

using namespace std;
#pragma endregion

#pragma region ゲーム内で使う定数の定義
// ゲームの状態用の定数
#define GAME_INIT 0		// タイトル画面の時
#define GAME_RULE 1
#define GAME_PLAYING 2	// ゲームプレイ中
#define GAME_CLEAR 3    // ゲームクリア時

// ゲームプレイ用の定数
#define BLOCK_MAX 20	// ブロックの最大数
#define SQUARES_SIZE 32	// マスのサイズ
#define PLAYER_SIZE 30	// プレイヤーのサイズ
#define ENEMY_SIZE 30
#define STAGE_WIDTH 17	// ステージのマス目の数（横）
#define STAGE_HEIGHT 15	// ステージのマス目の数（縦）

// マスの状態用の定数
#define SQUARE_NONE 0	// 何もないマス（プレイヤーが動けるところ）
#define SQUARE_WALL 1	// 壁
#define SQUARE_BLOCK 2	// ブロック
#define SQUARE_ENEMY 3  // 敵

#pragma region 以下使わない定数（すべてコメント化）

// コントローラー用の定数（全てDxLib.hに定義済みのためコメント化）
#define PAD_INPUT_DOWN								(0x00000001)	// ↓チェックマスク
#define PAD_INPUT_LEFT								(0x00000002)	// ←チェックマスク
#define PAD_INPUT_RIGHT								(0x00000004)	// →チェックマスク
#define PAD_INPUT_UP								(0x00000008)	// ↑チェックマスク
#define PAD_INPUT_A									(0x00000010)	// Ａボタンチェックマスク
#define PAD_INPUT_B									(0x00000020)	// ?ボタンチェックマスク
#define PAD_INPUT_C									(0x00000040)	// 〇ボタンチェックマスク
#define PAD_INPUT_X									(0x00000080)	// Ｘボタンチェックマスク
#define PAD_INPUT_Y									(0x00000100)	// □ボタンチェックマスク
#define PAD_INPUT_Z									(0x00000200)
#define PAD_INPUT_L									(0x00000400)
#define PAD_INPUT_R									(0x00000800)
#define PAD_INPUT_START								(0x00001000)
#define PAD_INPUT_M									(0x00002000)	//オプション
#define PAD_INPUT_D									(0x00004000)    //L3
#define PAD_INPUT_F									(0x00008000)    //R3
#define PAD_INPUT_G									(0x00010000)    //ホームボタン
#define PAD_INPUT_H									(0x00020000)    //タッチパッド
#define PAD_INPUT_I									(0x00040000)    //マイク
#define PAD_INPUT_J									(0x00080000)
#define PAD_INPUT_K									(0x00100000)
#define PAD_INPUT_LL								(0x00200000)
#define PAD_INPUT_N									(0x00400000)
#define PAD_INPUT_O									(0x00800000)
#define PAD_INPUT_P									(0x01000000)
#define PAD_INPUT_RR								(0x02000000)
#define PAD_INPUT_S									(0x04000000)
#define PAD_INPUT_T									(0x08000000)
#define PAD_INPUT_U									(0x10000000)
#define PAD_INPUT_V									(0x20000000)
#define PAD_INPUT_W									(0x40000000)

#pragma endregion
#pragma endregion

#pragma region ゲーム内で使う関数の定義
// ゲーム進行や画面用の関数
void GameInit();											// ゲームの初期化関数
void LoadCSV();												// CSVファイル取り込み関数
void TitleScene();											// タイトル画面生成
void RuleScene();                                           // ルールの説明
void ClearScene();											// クリア画面生成
void DrawScore();											// スコア生成
int GetHitKeyStateAll_2(int GetHitKeyStateAll_InputKey[]);	// キー入力時の値取得
void InputGetAction();										// キーもしくはコントローラーの入力により処理を振り分け
void GameLoop();
void ChangeVolumeSoundMem();

// プレイヤー動作用の関数
void PlayerRightMove();				// プレイヤーの移動（右）
void PlayerLeftMove();				// プレイヤーの移動（左）
void PlayerUpMove();				// プレイヤーの移動（上）
void PlayerDownMove();				// プレイヤーの移動（下）
void RightHitWall(int x, int y);	// プレイヤーと壁の当たり判定（右）
void LeftHitWall(int x, int y);		// プレイヤーと壁の当たり判定（左）
void UpHitWall(int x, int y);		// プレイヤーと壁の当たり判定（上）
void DownHitWall(int x, int y);		// プレイヤーと壁の当たり判定（下）

//敵用の関数
void UpdateEnemy();
void DrawEnemy();
void RightHitWall_ENEMY(int x, int y);
void LeftHitWall_ENEMY(int x, int y);
void UpHitWall_ENEMY(int x, int y);
void DownHitWall_ENEMY(int x, int y);

// ブロック用の関数
void BlockGenerate();				// ブロック生成
void DestroyBlocks();				// ブロック破壊
bool BlockCheck(int rx, int ry);	// ブロックがあるかどうかチェック

// 爆弾用の関数
void ArrangementBomb();	// 爆弾の配置
#pragma endregion

#pragma region ゲーム内で使う外部変数の定義
// ゲーム進行や画面用の外部変数
extern int game_State;							// ゲームの状態を定義
extern int clearCnt;							// クリアさせるためのカウンター
extern int mapData[STAGE_HEIGHT][STAGE_WIDTH];	// マップデータを2次元配列に格納
extern int frameCount;							// フレームカウント
extern int score;								// スコア
extern bool firstInitFlg;						// 初回起動かどうかのフラグ

// キー入力関係の外部変数
extern int Key[256];		// キーボードの入力内容取り込み
extern bool spacePressed;	// スペースキーが押されているか判定

// 画像、音素材用の外部変数
extern int img00, img01[16], img02[20], img03[56], img04[24], img05[30];	// 画像ロード用（プレイヤー等）
extern int fnt01[30], fnt03[40];											// 画像ロード用（フォント）
extern int gamesound;														// プレイ中のBGM
extern int titlesound;														// タイトル画面のBGM
extern int clearsound;														// クリア画面のBGM
extern int bombSound;														// ボムを置いた時に流す効果音
extern int bombExSound;														// ボムが爆発したときに流す効果音
extern bool imageVisible;													// 画像が見えるかどうか判定

// プレイヤー用の外部変数
extern int px, py;	// 主人公の位置

// 敵用の外部変数
extern int ex, ey;	// 敵の位置

// ブロック用の外部変数
extern int bx[BLOCK_MAX], by[BLOCK_MAX];	// ブロックの位置（複数あるので配列）
extern int blockCnt;						// ブロックの数

// 爆弾用の外部変数
extern int bombCount;		// 使ったボムの数をカウント
extern int BombX, BombY;	// 爆弾の位置
extern bool bombFlg;		// ボムを置いているかどうかのフラグ
#pragma endregion
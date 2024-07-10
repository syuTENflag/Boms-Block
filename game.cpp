#include "game.h"

int game_State;	// ゲームの状態を定義する変数
int img00, img01[16], img02[20], img03[56], img04[24], img05[30];//画像ロード用
int fnt01[30], fnt03[40];//画像ロード用
int Key[256]; //キーボードの入力内容
int Color_White;
int Color_Black;
int score; // スコア
int gamesound;
int titlesound;
int clearsound;
int bombSound;
int bombExSound;
int startTime = GetNowCount();
bool spacePressed;	// スペースキーが押されているか判定
int frameCount;			// フレームカウント
bool imageVisible;	// 画像が見えるかどうか判定

int mapData[STAGE_HEIGHT][STAGE_WIDTH];

bool firstInitFlg;	// 初回起動かどうかのフラグ

int GetHitKeyStateAll_2(int GetHitKeyStateAll_InputKey[]) {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i < 256; i++) {
		if (GetHitKeyStateAll_Key[i] == 1)
			GetHitKeyStateAll_InputKey[i]++;
		else
			GetHitKeyStateAll_InputKey[i] = 0;
	}
	return 0;
}//キーボードの押されてる時間の長さ判定


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {//決まり文句
	ChangeWindowMode(false);//全画面からウィンドウモードへ切り替え
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//DXライブラリ初期化と絵を画面の裏側に描写

	gamesound = LoadSoundMem("./resorces/PerituneMaterial.mp3");
	titlesound = LoadSoundMem("./resorces/title.mp3");
	clearsound = LoadSoundMem("./resorces/clear.mp3");

	// 起動時のゲーム初期化処理
	firstInitFlg = true;
	GameInit();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll_2(Key) == 0 && Key[KEY_INPUT_ESCAPE] == 0) {
		//こっから下が繰り返し処理される(メインループ)



		switch (game_State) {
		case GAME_INIT:
			TitleScene();
			break;
		case GAME_RULE:
			RuleScene();
			break;
		case GAME_PLAYING:
			//PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
			DrawGraph(0, 0, img00, TRUE);//背景画像表示

			// スコア生成
			DrawScore();
			
			/*
			GameLoop();

			SetFontSize(10);
			DrawFormatString(550, 50, Color_Black, "%d秒", (GetNowCount() - startTime) / 1000);
			*/

			// ブロック生成
			BlockGenerate();

			// 敵の更新処理
			UpdateEnemy();

			// 敵の描画処理D
			DrawEnemy();

			// キー入力判定し、値に応じて処理を振り分ける
			InputGetAction();
			//px、pyの位置を左上にしてキャラ画像（停止）を描画
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[4], TRUE);
			// ゲームをクリアさせる
			if (clearCnt == 0 && blockCnt == BLOCK_MAX) {
				game_State = GAME_CLEAR;
				clearsound = LoadSoundMem("./resorces/clear.mp3");
				ChangeVolumeSoundMem(128, clearsound); // ここで音量設定を行う
				PlaySoundMem(clearsound, DX_PLAYTYPE_LOOP);
			}
			break;
		case GAME_CLEAR:

			ClearScene();
			break;
		default:
			break;
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

// ゲーム初期化処理
void GameInit() {

	// プレイヤー座標
	px = 32;
	py = 32;

	// ブロック座標
	for (int i = 0; i < BLOCK_MAX; i++) {
		bx[i] = 0;
		by[i] = 0;
	}

	blockCnt = 0;
	clearCnt = 0;
	bombCount = BLOCK_MAX;
	frameCount = 240;

	bombFlg = false;
	spacePressed = false;
	imageVisible = false;

	game_State = GAME_INIT;

	score = 0;

	LoadCSV();

	// 初回起動時のみ初期化するもの
	if (firstInitFlg == true) {
		//↓画像のロード
		img00 = LoadGraph("./resorces/01back.png"); // 背景画像
		LoadDivGraph("./resorces/01stage.png", 16, 4, 4, 32, 32, img01); //マップチップ画像
		LoadDivGraph("./resorces/01char.png", 20, 4, 5, 32, 32, img02); //戦闘時主人公画像
		LoadDivGraph("./resorces/01bomb.png", 56, 7, 8, 32, 32, img03); //戦闘時ボム画像
		LoadDivGraph("./resorces/01enemy.png", 24, 4, 6, 32, 32, img04); //戦闘時敵画像
		LoadDivGraph("./resorces/01item.png", 30, 10, 3, 32, 32, img05); //戦闘時アイテム画像
		LoadDivGraph("./resorces/01font.png", 30, 10, 3, 7, 10, fnt01); //フォント画像
		LoadDivGraph("./resorces/03font.png", 40, 10, 4, 6, 9, fnt03); //フォント画像

		// 色の取得
		Color_White = GetColor(255, 255, 255);
		Color_Black = GetColor(0, 0, 0);

		// BGM
		gamesound = LoadSoundMem("./resorces/PerituneMaterial.mp3");
		bombSound = LoadSoundMem("./resorces/e6a9c4be24d80e52.mp3");
		bombExSound = LoadSoundMem("./resorces/game_explosion1.mp3");
		titlesound = LoadSoundMem("./resorces/title.mp3");
		clearsound = LoadSoundMem("./resorces/clear.mp3");

		// すべてのBGMを停止
		//StopSoundMem(gamesound);
		//StopSoundMem(clearsound);
		//StopSoundMem(titlesound);

		// 音量の設定（0～255の範囲で設定）
		ChangeVolumeSoundMem(128, gamesound);
		ChangeVolumeSoundMem(128, bombSound);
		ChangeVolumeSoundMem(128, bombExSound);
		ChangeVolumeSoundMem(128, titlesound);
		ChangeVolumeSoundMem(128, clearsound);

		PlaySoundMem(titlesound, DX_PLAYTYPE_LOOP);
	}
}

// CSVファイルからステージデータを読み込む関数
void LoadCSV() {
	// getlineによって読み込まれた文字列を取り込むローカル変数
	string str;

	// strに取り込まれた文字列を読み込み配列へ格納させるローカル変数
	stringstream ss;

	// 以下のifstreamによって、ステージデータが入ったCSVファイルを開く
	ifstream csvFile("./resorces/Stage.csv");

	// 配列の値を初期化
	mapData[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	/*
		2重ループによりステージのマス分の数値を取り込む
	*/

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// 横は最後は改行コードまで読みこむので一つ手前まで読み込む
		for (int j = 0; j < STAGE_WIDTH - 1; j++)
		{
			/*
				getlineの第1引数は読み出し開始位置を表す
				(このコードでは現在位置を表す)
				第2引数は読み出し先を指定
				第3引数は終端とする文字を指定
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstreamに読みだしたstringを流す
			ss.str(str);

			/*
				stringstreamから配列に流す
				この時にstring型からint型の変換が暗黙的に行われる
			*/
			ss >> mapData[i][j];

			/*
				前の文字が残って想定通りの数値が配列に格納できないため
				stringstreamを以下の２行のコードでクリアする
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// 横の最後の数値は改行コードまで読み込み次の行へ移動させる
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// STAGE_WIDTHの値をそのまま使うと配列外になってしまうため-1する
		ss >> mapData[i][STAGE_WIDTH - 1];

		/*
			ここでも前の文字が残って想定通りの数値が配列に格納できないため
			stringstreamを以下の２行のコードでクリアする
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSVファイルを閉じてファイルへのアクセス権を開放する。
	csvFile.close();
}

void TitleScene() {

	StopSoundMem(clearsound);
	StopSoundMem(gamesound);

	SetFontSize(75);
	DrawFormatString(105, 150, Color_White, "BOMB PUZZLE");

	SetFontSize(35);
	DrawFormatString(60, 300, Color_White, "SPACEを押してルール説明へ\nPAD操作方法\n×でルール説明へ");

	DrawGraph(10, 400, img02[4], TRUE);//キャラ画像表示
	DrawGraph(600, 400, img02[4], TRUE);//キャラ画像表示

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_SPACE) == 1) {
		game_State = GAME_RULE;
		//PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
		//StopSoundMem(titlesound);

	}
}

void RuleScene() {

	SetFontSize(35);
	DrawFormatString(30, 50, Color_White, "20個の障害物をどれだけ少ない\n爆弾で破壊できるかでスコアが\n変動するので高得点を取れるように\nよく考えよう。");
	SetFontSize(35);
	DrawFormatString(60, 300, Color_White, "エンターキーを押してスタート\nPAD操作方法\n〇でスタート\n□orSPACEで爆弾設置");

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C || CheckHitKey(KEY_INPUT_RETURN) == 1) {
		game_State = GAME_PLAYING;
		PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
		StopSoundMem(titlesound);

	}
}

void ClearScene() {

	// クリアBGMが再生されていない場合のみ再生する
	if (CheckSoundMem(clearsound) == 0) {
		PlaySoundMem(clearsound, DX_PLAYTYPE_LOOP);
	}

	SetFontSize(75);
	DrawFormatString(140, 100, Color_White, "Result");

	StopSoundMem(gamesound);

	SetFontSize(35);
	DrawFormatString(220, 220, Color_White, "スコア：%d", score * bombCount);
	DrawFormatString(45, 300, Color_White, "エンターキーを押してタイトルへ\n〇でタイトルへ");

	DrawGraph(10, 400, img02[4], TRUE);//キャラ画像表示
	DrawGraph(200, 400, img02[4], TRUE);//キャラ画像表示
	DrawGraph(400, 400, img02[4], TRUE);//キャラ画像表示
	DrawGraph(600, 400, img02[4], TRUE);//キャラ画像表示

	

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C || CheckHitKey(KEY_INPUT_RETURN) == 1) {
		// すべてのBGMを停止
		StopSoundMem(gamesound);
		StopSoundMem(clearsound);
		StopSoundMem(titlesound);
		GameInit();
	}
}

//背景の描画
void DrawScore() {

	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (mapData[y][x] == SQUARE_WALL) {
				DrawGraph(x * SQUARES_SIZE, y * SQUARES_SIZE, img01[9], TRUE);
			}
			else if (mapData[y][x] == SQUARE_BLOCK) {
				DrawGraph(x * SQUARES_SIZE, y * SQUARES_SIZE, img01[4], TRUE);
			}
			else {
				DrawGraph(x * SQUARES_SIZE, y * SQUARES_SIZE, img01[1], TRUE);
			}
		}
	}


	SetFontSize(10);
	DrawFormatString(550, 10, Color_Black, "スコア:%d", score * bombCount);
	DrawFormatString(550, 30, Color_Black, "置いたボム数:%d", BLOCK_MAX - bombCount);
	DrawFormatString(550, 50, Color_Black, "残ブロック数:%d", clearCnt);
}

// ゲームのメインループ
void GameLoop() {
	// ゲームの更新処理などをここに記述

	// 経過時間の計測
	static int startTime = GetNowCount();
	int currentTime = GetNowCount();
	int elapsedTime = currentTime - startTime;

	// startTimeを現在の時間に更新
	startTime = currentTime;


}

void InputGetAction() {
	// Dキーか→キーか→チェックマスク
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT || Key[KEY_INPUT_RIGHT] || Key[KEY_INPUT_D] >= 1)
	{
		PlayerRightMove();
	}

	// Aキーか←キーか←チェックマスク
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT || Key[KEY_INPUT_LEFT] || Key[KEY_INPUT_A] >= 1)
	{
		PlayerLeftMove();
	}

	// Wキーか↑キーか↑チェックマスク
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP || Key[KEY_INPUT_UP] || Key[KEY_INPUT_W] >= 1)
	{
		PlayerUpMove();
	}

	// Sキーか↓キーか↓チェックマスク
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN || Key[KEY_INPUT_DOWN] || Key[KEY_INPUT_S] >= 1)
	{
		PlayerDownMove();
	}

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A || CheckHitKey(KEY_INPUT_SPACE) == 1) && bombFlg == false) {
		// Spacebar key is pressed, show the image
		spacePressed = true;
		bombFlg = true;
		frameCount = 0;

		ArrangementBomb();
	}

	if (spacePressed) {
		// If the spacebar is pressed, show the image for a few seconds
		if (frameCount < 180) { // Display the image for 60 frames (change as needed)
			if (frameCount == 1) {
				PlaySoundMem(bombSound, DX_PLAYTYPE_BACK);
				if (bombCount > 1) {
					bombCount--;
				}
			}
			DrawGraph(BombX, BombY, img03[0], TRUE);

		}
		else if (frameCount < 240) {
			DrawGraph(BombX, BombY, img03[7], TRUE);
			if (mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE - 1] == SQUARE_NONE) {
				DrawGraph(BombX - SQUARES_SIZE, BombY, img03[14], TRUE);
			}

			if ((mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE - 2] == SQUARE_NONE) &&
				(mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE - 1] == SQUARE_NONE)) {
				DrawGraph(BombX - SQUARES_SIZE * 2, BombY, img03[28], TRUE);
			}

			if (mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE + 1] == SQUARE_NONE) {
				DrawGraph(BombX + SQUARES_SIZE, BombY, img03[14], TRUE);
			}

			if ((mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE + 2] == SQUARE_NONE) &&
				(mapData[BombY / SQUARES_SIZE][BombX / SQUARES_SIZE + 1] == SQUARE_NONE)) {
				DrawGraph(BombX + SQUARES_SIZE * 2, BombY, img03[42], TRUE);
			}

			if (mapData[BombY / SQUARES_SIZE - 1][BombX / SQUARES_SIZE] == SQUARE_NONE) {
				DrawGraph(BombX, BombY - SQUARES_SIZE, img03[21], TRUE);
			}

			if ((mapData[BombY / SQUARES_SIZE - 2][BombX / SQUARES_SIZE] == SQUARE_NONE) &&
				(mapData[BombY / SQUARES_SIZE - 1][BombX / SQUARES_SIZE] == SQUARE_NONE)) {
				DrawGraph(BombX, BombY - SQUARES_SIZE * 2, img03[35], TRUE);
			}

			if (mapData[BombY / SQUARES_SIZE + 1][BombX / SQUARES_SIZE] == SQUARE_NONE) {
				DrawGraph(BombX, BombY + SQUARES_SIZE, img03[21], TRUE);
			}

			if ((mapData[BombY / SQUARES_SIZE + 2][BombX / SQUARES_SIZE] == SQUARE_NONE) &&
				(mapData[BombY / SQUARES_SIZE + 1][BombX / SQUARES_SIZE] == SQUARE_NONE)) {
				DrawGraph(BombX, BombY + SQUARES_SIZE * 2, img03[49], TRUE);
			}

			if (frameCount == 180) {
				StopSoundMem(bombSound);
				PlaySoundMem(bombExSound, DX_PLAYTYPE_BACK);
			}

			if (frameCount == 190) {
				DestroyBlocks();
			}
		}

		else {
			spacePressed = false; // Reset the state
			imageVisible = false;
			bombFlg = false;
		}

		frameCount++;
	}
}
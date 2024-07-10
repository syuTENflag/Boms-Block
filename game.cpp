#include "game.h"

int game_State;	// �Q�[���̏�Ԃ��`����ϐ�
int img00, img01[16], img02[20], img03[56], img04[24], img05[30];//�摜���[�h�p
int fnt01[30], fnt03[40];//�摜���[�h�p
int Key[256]; //�L�[�{�[�h�̓��͓��e
int Color_White;
int Color_Black;
int score; // �X�R�A
int gamesound;
int titlesound;
int clearsound;
int bombSound;
int bombExSound;
int startTime = GetNowCount();
bool spacePressed;	// �X�y�[�X�L�[��������Ă��邩����
int frameCount;			// �t���[���J�E���g
bool imageVisible;	// �摜�������邩�ǂ�������

int mapData[STAGE_HEIGHT][STAGE_WIDTH];

bool firstInitFlg;	// ����N�����ǂ����̃t���O

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
}//�L�[�{�[�h�̉�����Ă鎞�Ԃ̒�������


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {//���܂蕶��
	ChangeWindowMode(false);//�S��ʂ���E�B���h�E���[�h�֐؂�ւ�
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//DX���C�u�����������ƊG����ʂ̗����ɕ`��

	gamesound = LoadSoundMem("./resorces/PerituneMaterial.mp3");
	titlesound = LoadSoundMem("./resorces/title.mp3");
	clearsound = LoadSoundMem("./resorces/clear.mp3");

	// �N�����̃Q�[������������
	firstInitFlg = true;
	GameInit();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll_2(Key) == 0 && Key[KEY_INPUT_ESCAPE] == 0) {
		//�������牺���J��Ԃ����������(���C�����[�v)



		switch (game_State) {
		case GAME_INIT:
			TitleScene();
			break;
		case GAME_RULE:
			RuleScene();
			break;
		case GAME_PLAYING:
			//PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
			DrawGraph(0, 0, img00, TRUE);//�w�i�摜�\��

			// �X�R�A����
			DrawScore();
			
			/*
			GameLoop();

			SetFontSize(10);
			DrawFormatString(550, 50, Color_Black, "%d�b", (GetNowCount() - startTime) / 1000);
			*/

			// �u���b�N����
			BlockGenerate();

			// �G�̍X�V����
			UpdateEnemy();

			// �G�̕`�揈��D
			DrawEnemy();

			// �L�[���͔��肵�A�l�ɉ����ď�����U�蕪����
			InputGetAction();
			//px�Apy�̈ʒu������ɂ��ăL�����摜�i��~�j��`��
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[4], TRUE);
			// �Q�[�����N���A������
			if (clearCnt == 0 && blockCnt == BLOCK_MAX) {
				game_State = GAME_CLEAR;
				clearsound = LoadSoundMem("./resorces/clear.mp3");
				ChangeVolumeSoundMem(128, clearsound); // �����ŉ��ʐݒ���s��
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

// �Q�[������������
void GameInit() {

	// �v���C���[���W
	px = 32;
	py = 32;

	// �u���b�N���W
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

	// ����N�����̂ݏ������������
	if (firstInitFlg == true) {
		//���摜�̃��[�h
		img00 = LoadGraph("./resorces/01back.png"); // �w�i�摜
		LoadDivGraph("./resorces/01stage.png", 16, 4, 4, 32, 32, img01); //�}�b�v�`�b�v�摜
		LoadDivGraph("./resorces/01char.png", 20, 4, 5, 32, 32, img02); //�퓬����l���摜
		LoadDivGraph("./resorces/01bomb.png", 56, 7, 8, 32, 32, img03); //�퓬���{���摜
		LoadDivGraph("./resorces/01enemy.png", 24, 4, 6, 32, 32, img04); //�퓬���G�摜
		LoadDivGraph("./resorces/01item.png", 30, 10, 3, 32, 32, img05); //�퓬���A�C�e���摜
		LoadDivGraph("./resorces/01font.png", 30, 10, 3, 7, 10, fnt01); //�t�H���g�摜
		LoadDivGraph("./resorces/03font.png", 40, 10, 4, 6, 9, fnt03); //�t�H���g�摜

		// �F�̎擾
		Color_White = GetColor(255, 255, 255);
		Color_Black = GetColor(0, 0, 0);

		// BGM
		gamesound = LoadSoundMem("./resorces/PerituneMaterial.mp3");
		bombSound = LoadSoundMem("./resorces/e6a9c4be24d80e52.mp3");
		bombExSound = LoadSoundMem("./resorces/game_explosion1.mp3");
		titlesound = LoadSoundMem("./resorces/title.mp3");
		clearsound = LoadSoundMem("./resorces/clear.mp3");

		// ���ׂĂ�BGM���~
		//StopSoundMem(gamesound);
		//StopSoundMem(clearsound);
		//StopSoundMem(titlesound);

		// ���ʂ̐ݒ�i0�`255�͈̔͂Őݒ�j
		ChangeVolumeSoundMem(128, gamesound);
		ChangeVolumeSoundMem(128, bombSound);
		ChangeVolumeSoundMem(128, bombExSound);
		ChangeVolumeSoundMem(128, titlesound);
		ChangeVolumeSoundMem(128, clearsound);

		PlaySoundMem(titlesound, DX_PLAYTYPE_LOOP);
	}
}

// CSV�t�@�C������X�e�[�W�f�[�^��ǂݍ��ފ֐�
void LoadCSV() {
	// getline�ɂ���ēǂݍ��܂ꂽ���������荞�ރ��[�J���ϐ�
	string str;

	// str�Ɏ�荞�܂ꂽ�������ǂݍ��ݔz��֊i�[�����郍�[�J���ϐ�
	stringstream ss;

	// �ȉ���ifstream�ɂ���āA�X�e�[�W�f�[�^��������CSV�t�@�C�����J��
	ifstream csvFile("./resorces/Stage.csv");

	// �z��̒l��������
	mapData[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	/*
		2�d���[�v�ɂ��X�e�[�W�̃}�X���̐��l����荞��
	*/

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// ���͍Ō�͉��s�R�[�h�܂œǂ݂��ނ̂ň��O�܂œǂݍ���
		for (int j = 0; j < STAGE_WIDTH - 1; j++)
		{
			/*
				getline�̑�1�����͓ǂݏo���J�n�ʒu��\��
				(���̃R�[�h�ł͌��݈ʒu��\��)
				��2�����͓ǂݏo������w��
				��3�����͏I�[�Ƃ��镶�����w��
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstream�ɓǂ݂�����string�𗬂�
			ss.str(str);

			/*
				stringstream����z��ɗ���
				���̎���string�^����int�^�̕ϊ����ÖٓI�ɍs����
			*/
			ss >> mapData[i][j];

			/*
				�O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
				stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// ���̍Ō�̐��l�͉��s�R�[�h�܂œǂݍ��ݎ��̍s�ֈړ�������
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// STAGE_WIDTH�̒l�����̂܂܎g���Ɣz��O�ɂȂ��Ă��܂�����-1����
		ss >> mapData[i][STAGE_WIDTH - 1];

		/*
			�����ł��O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
			stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSV�t�@�C������ăt�@�C���ւ̃A�N�Z�X�����J������B
	csvFile.close();
}

void TitleScene() {

	StopSoundMem(clearsound);
	StopSoundMem(gamesound);

	SetFontSize(75);
	DrawFormatString(105, 150, Color_White, "BOMB PUZZLE");

	SetFontSize(35);
	DrawFormatString(60, 300, Color_White, "SPACE�������ă��[��������\nPAD������@\n�~�Ń��[��������");

	DrawGraph(10, 400, img02[4], TRUE);//�L�����摜�\��
	DrawGraph(600, 400, img02[4], TRUE);//�L�����摜�\��

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B || CheckHitKey(KEY_INPUT_SPACE) == 1) {
		game_State = GAME_RULE;
		//PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
		//StopSoundMem(titlesound);

	}
}

void RuleScene() {

	SetFontSize(35);
	DrawFormatString(30, 50, Color_White, "20�̏�Q�����ǂꂾ�����Ȃ�\n���e�Ŕj��ł��邩�ŃX�R�A��\n�ϓ�����̂ō����_������悤��\n�悭�l���悤�B");
	SetFontSize(35);
	DrawFormatString(60, 300, Color_White, "�G���^�[�L�[�������ăX�^�[�g\nPAD������@\n�Z�ŃX�^�[�g\n��orSPACE�Ŕ��e�ݒu");

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C || CheckHitKey(KEY_INPUT_RETURN) == 1) {
		game_State = GAME_PLAYING;
		PlaySoundMem(gamesound, DX_PLAYTYPE_LOOP);
		StopSoundMem(titlesound);

	}
}

void ClearScene() {

	// �N���ABGM���Đ�����Ă��Ȃ��ꍇ�̂ݍĐ�����
	if (CheckSoundMem(clearsound) == 0) {
		PlaySoundMem(clearsound, DX_PLAYTYPE_LOOP);
	}

	SetFontSize(75);
	DrawFormatString(140, 100, Color_White, "Result");

	StopSoundMem(gamesound);

	SetFontSize(35);
	DrawFormatString(220, 220, Color_White, "�X�R�A�F%d", score * bombCount);
	DrawFormatString(45, 300, Color_White, "�G���^�[�L�[�������ă^�C�g����\n�Z�Ń^�C�g����");

	DrawGraph(10, 400, img02[4], TRUE);//�L�����摜�\��
	DrawGraph(200, 400, img02[4], TRUE);//�L�����摜�\��
	DrawGraph(400, 400, img02[4], TRUE);//�L�����摜�\��
	DrawGraph(600, 400, img02[4], TRUE);//�L�����摜�\��

	

	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C || CheckHitKey(KEY_INPUT_RETURN) == 1) {
		// ���ׂĂ�BGM���~
		StopSoundMem(gamesound);
		StopSoundMem(clearsound);
		StopSoundMem(titlesound);
		GameInit();
	}
}

//�w�i�̕`��
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
	DrawFormatString(550, 10, Color_Black, "�X�R�A:%d", score * bombCount);
	DrawFormatString(550, 30, Color_Black, "�u�����{����:%d", BLOCK_MAX - bombCount);
	DrawFormatString(550, 50, Color_Black, "�c�u���b�N��:%d", clearCnt);
}

// �Q�[���̃��C�����[�v
void GameLoop() {
	// �Q�[���̍X�V�����Ȃǂ������ɋL�q

	// �o�ߎ��Ԃ̌v��
	static int startTime = GetNowCount();
	int currentTime = GetNowCount();
	int elapsedTime = currentTime - startTime;

	// startTime�����݂̎��ԂɍX�V
	startTime = currentTime;


}

void InputGetAction() {
	// D�L�[�����L�[�����`�F�b�N�}�X�N
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT || Key[KEY_INPUT_RIGHT] || Key[KEY_INPUT_D] >= 1)
	{
		PlayerRightMove();
	}

	// A�L�[�����L�[�����`�F�b�N�}�X�N
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT || Key[KEY_INPUT_LEFT] || Key[KEY_INPUT_A] >= 1)
	{
		PlayerLeftMove();
	}

	// W�L�[�����L�[�����`�F�b�N�}�X�N
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP || Key[KEY_INPUT_UP] || Key[KEY_INPUT_W] >= 1)
	{
		PlayerUpMove();
	}

	// S�L�[�����L�[�����`�F�b�N�}�X�N
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
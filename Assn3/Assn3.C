// 20220778 표승현
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // GetConsoleMode () 등의 사용을 위해 포함

void set_vt_mode() {
	DWORD l_mode;
	GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &l_mode);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), l_mode | 0x0004 | 0x0008);
}
void set_color(int code) {
	printf("\033[%dm", code);
}
void reset_color() {
	printf("\033[0m");
}


void generate_ladder(int** board, int num_player, int num_height, int num_line); // 사다리를 생성하는 함수
void save_ladder(char filename[], int** board, int num_player, int num_height, int num_line); // 생성된 사다리를 txt파일로 저장
int** load_ladder(char filename[], int* player, int* height, int* line); // txt 파일을 읽고 배열에 저장하여 사다리 불러오기
void print_ladder(int** board, int num_player, int num_height, int num_line); // 사다리를 출력하는 함수
int** board_change(int** board, int num_player, int num_height, int player, int* x, int* y,int*g); // 사다리 타며 배열의 값을 바꾸는 함수
void board_color(int** board, int num_player, int num_height,int*x,int*y); // 배열 값에 따라 다른 색으로 사다리를 출력하는 함수

int main()
{
	srand(time(NULL));
	set_vt_mode();
	int i, j;
	int num;
	int select, num_player, num_height, num_line;
	char filename[20];
	int** board;
	char c;

	while (1) {
		printf("[사다리 게임]\n");
		printf("=================================\n");
		printf("1. 사다리 보드 생성\n");
		printf("2. 사다리 타기 시작\n");
		printf("3. 종료\n");
		printf("=================================\n");
		printf("선택: ");
		scanf("%d", &num);

		if (num == 3) break; // 3을 입력 받으면 프로그램 종료

		switch (num) {
		case 1: // 1을 입력했을 때
			printf("\n");
			printf("참여 인원수: ");
			scanf("%d", &num_player);
			printf("사다리 높이: ");
			scanf("%d", &num_height);
			printf("가로줄 개수: ");
			scanf("%d", &num_line);
			printf("파일이름: ");
			scanf("%s", filename);

			// 입력받은 정보를 바탕으로 배열 동적 할당
			board = (int**)malloc((num_height) * sizeof(int*));
			for (i = 0; i < num_height; i++)
				board[i] = (int*)malloc((num_player) * sizeof(int));

			generate_ladder(board, num_player, num_height, num_line); // 게임판 생성
			save_ladder(filename, board, num_player, num_height, num_line); // 파일 생성

			for (i = 0; i < num_height; i++) // 배열 할당 해제
				free(board[i]);
			free(board);

			printf("\n");
			break;
		case 2: // 2를 입력했을 때
			printf("\n파일 이름: ");
			scanf("%s", filename); // 파일 이름을 입력받는다
			board = load_ladder(filename, &num_player, &num_height, &num_line); //사다리 불러오기
			print_ladder(board, num_player, num_height, num_line); // 불러온 사다리를 출력

			int player; //사용자가 선택한 플레이어
			int x, y, g, alp; // 좌표와 사다리 타기의 보조 변수, 알파벳 표현 변수
			int round = num_player; // 총 진행할 라운드 수
			char c; // 엔터를 입력받기 위한 변수

			while (1) {
				printf(">> ");
				scanf("%d", &player); // 플레이어 번호를 받는다

				if (player == 0) break; //0을 누르면 탈출
				if (player == -1) { //사다리 타기에서 -1을 입력했을 때
					for (player = 1; player < num_player + 1; player++) { //1번부터 차례대로 모든 플레이어의 사다리 타기를 진행
						x = (player - 1) * 2;
						y = num_height - 1;
						board[y][x] = player * 10;
						system("cls"); //화면 초기화
						board_color(board, num_player, num_height, &x, &y); //사다리 출력
						g = 0;
						system("cls");
						while (1) {
							if (g == 0) board = board_change(board, num_player, num_height, player, &x, &y, &g); //다음 칸의 사다리 배열 변경
							else { //g가 1(가로줄로 이동한 직후)라면 무조건적으로 위로 한 칸 이동한다.
								board[y - 1][x] = player * 10;
								y--; //위로 한 칸 이동
								g--; //다시 0으로 바꾼다
							}
							board_color(board, num_player, num_height, &x, &y); // 출력
							if (y == 0) break; //끝에 이르면 탈출한다.
							system("cls");
						}
						round--; // 사다리 타기가 진행될 때마다 줄인다
						if (round < 0) break; // 모든 라운드가 진행되면 탈출한다.
					}
					for (player = 1; player < num_player + 1; player++) { //플레이어 사다리의 종착점 배열값을 통해 어느 알파벳에 도착했는지 출력
						for (i = 0; i < (num_player - 1) * 2 + 1; i++) {
							if (board[0][i] == player * 10) {
								alp = i / 2;
								break;
							}
						}
						printf("\nresult: %d -> %c", player, alp + 65);
					}
					printf("\n");
					break;
				}
				// 플레이어 번호를 선택했을 때
				x = (player - 1) * 2;
				y = num_height - 1;
				board[y][x] = player * 10;
				system("cls");
				board_color(board, num_player, num_height, &x, &y); //보드 출력
				scanf("%c", &c);
				scanf("%c", &c);
				g = 0;
				system("cls");
				while (1) {
					if (g == 0) board = board_change(board, num_player, num_height, player, &x, &y, &g); //다음 사다리 칸의 배열값을 변경
					else { //가로줄을 이동한 직후에는 바로 위로 이동
						board[y - 1][x] = player * 10;
						y--;
						g--;
					}
					board_color(board, num_player, num_height, &x, &y); //출력
					if (y == 0) break;
					scanf("%c", &c);
					system("cls");
				}
				for (i = 0; i < (num_player - 1) * 2 + 1; i++) {
					if (board[0][i] == player * 10) {
						alp = i / 2;
						break;
					}
				}
				printf("\nresult: %d -> %c\n\n", player, alp + 65);
				round--;
				if (round == 1) break;
			}
			for (i = 0; i < num_height; i++)
				free(board[i]);
			free(board);
			break;
		}
		printf("\n");
	}

	return 0;
}

void board_color(int** board, int num_player, int num_height,int*x,int*y)
{
	int i, j, c=65;
	int color;

	printf("%d %d\n", *x, *y);

	for (i = 0; i < num_player; i++) {
		printf("%c   ", c + i);
	}
	printf("\n");
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < (num_player - 1) * 2 + 1; j++) {
			if (board[i][j] != 0 && board[i][j] != 1) {//색상 바꾸기
				if ((board[i][j] / 10) % 5 == 0) color = 95; //배열에 저장된 값에 따라 색상 변경
				else color = (board[i][j] / 10) % 5 + 90;
				set_color(color); //색 설정
			}

			if (j % 2 == 0) printf("+");
			else if (j % 2) {
				if (board[i][j]) printf("---");
				else printf("   ");
			}
			reset_color();//색 초기화
		}
		printf("\n");
	}

	for (i = 0; i < num_player; i++) {
		printf("%d   ", i + 1);
	}
	printf("\n");
}

int** board_change(int** board, int num_player, int num_height, int player, int* x, int* y,int*g)
{
	if (*x == 0 && !board[*y][*x+1]) { //가장 왼쪽이고 오른쪽에 사다리가 없을때
		board[*y-1][*x] = player * 10;
		(*y)--;
	}
	else if (*x == (num_player-1)*2 && !board[*y][*x-1]) { //가장 오른쪽이고 왼쪽에 사다리가 없을때
		board[*y-1][*x] = player * 10;
		(*y)--;
	}
	else if (!board[*y][*x + 1] && !board[*y][*x - 1]) { //옆에 사다리가 없을때
		board[*y - 1][*x] = player * 10;
		(*y)--;
	}
	else {
		if (*x != (num_player - 1) * 2 && board[*y][*x + 1]) { //오른쪽에 사다리가 있을때
			board[*y][*x] = player * 10;
			board[*y][*x + 1] = player * 10;
			board[*y][*x + 2] = player * 10;
			(*x) += 2;
			(*g)++;
		}
		else if (board[*y][*x - 1]) { //왼쪽에 사다리가 있을때
			board[*y][*x] = player * 10;
			board[*y][*x - 1] = player * 10;
			board[*y][*x - 2] = player * 10;
			(*x) -= 2;
			(*g)++;
		}
	}
	return board;
}

void generate_ladder(int** board, int num_player, int num_height, int num_line)
{
	int i, j;
	//0으로 가득 찬 사다리 배열 생성
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < num_player; j++) {
			board[i][j] = 0;
		}
	}

	int k;
	for (i = 0; i < num_line; i++) { // 입력받은 가로줄 개수만큼 좌표 생성
		j = rand() % (num_height - 2) + 1; 
		k = rand() % (num_player);
		if (k != 0) { 
			if (board[j][k] == 0 && board[j][k - 1] == 0 && board[j][k + 1] == 0) { //비어있는 칸이고 양 옆에 다리가 없으면 1 저장
				board[j][k] = 1;
			}
			else { //가로줄을 생성 못하면 i 다시 감소
				i--;
			}
		}
		else if (k == 0) { //가장 왼쪽이면 오른쪽만 검사
			if (board[j][k] == 0 && board[j][k + 1] == 0) {
				board[j][k] = 1;
			}
			else {
				i--;
			}
		}
	}
}

void save_ladder(char filename[], int** board, int num_player, int num_height, int num_line)
{
	int i, j;
	FILE* fp;
	fp = fopen(filename, "w"); //파일 생성

	fprintf(fp, "%d %d %d \n", num_player, num_height, num_line); //정보 저장
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < num_player; j++) {
			if (board[i][j]) fprintf(fp, "%d %d\n", i, j + 1);
		}
	}

	fclose(fp);
}

int** load_ladder(char filename[], int* player, int* height, int* line)
{
	int i, j;
	int num_player, num_height, num_line;
	int a, b; // 파일의 값들을 일시적으로 저장할 변수
	int** board;

	FILE* fp;
	fp = fopen(filename, "r");
	//파일 읽기
	fscanf(fp, "%d %d %d\n", &num_player, &num_height, &num_line);
	*player = num_player;
	*height = num_height;
	*line = num_line;
	// 파일 정보를 바탕으로 배열 동적 할당
	board = (int**)malloc(num_height * sizeof(int*));
	for (i = 0; i < num_height; i++)
		board[i] = (int*)malloc((num_player * 2 - 1) * sizeof(int));

	// 세로줄 생성 >> 경로는 1을 저장하여 나타낸다
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < num_player * 2 - 1; j++) {
			if (j % 2 == 0)
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}

	for (i = 0; i < num_line; i++) { //좌표 출력
		fscanf(fp, "%d %d\n", &a, &b);
		board[a][b * 2 - 1] = 1;
	}
	return board;
}

void print_ladder(int** board, int num_player, int num_height, int num_line)
{
	int i, j;
	// Player 출력
	i = 0;
	printf(" ");
	while (1) { //알파벳 출력
		printf("%c", i + 65);
		i++;
		if (i == num_player) break;
		printf("   ");
	}
	printf("\n");

	for (i = 0; i < num_height; i++) {  //사다리 출력
		printf(" ");
		for (j = 0; j < num_player * 2 - 1; j++) {
			if (board[i][j] == 1) {
				if (j % 2 == 0) printf("+");
				else printf("---");
			}
			else printf("   ");
		}
		printf("\n");
	}

	i = 0;
	while (1) { //플레이어 번호 출력
		printf("%2d", i + 1);
		i++;
		if (i == num_player) break;
		printf("  ");
	}
	printf("\n");
}

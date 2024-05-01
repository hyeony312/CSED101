// 20220778 ǥ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // GetConsoleMode () ���� ����� ���� ����

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


void generate_ladder(int** board, int num_player, int num_height, int num_line); // ��ٸ��� �����ϴ� �Լ�
void save_ladder(char filename[], int** board, int num_player, int num_height, int num_line); // ������ ��ٸ��� txt���Ϸ� ����
int** load_ladder(char filename[], int* player, int* height, int* line); // txt ������ �а� �迭�� �����Ͽ� ��ٸ� �ҷ�����
void print_ladder(int** board, int num_player, int num_height, int num_line); // ��ٸ��� ����ϴ� �Լ�
int** board_change(int** board, int num_player, int num_height, int player, int* x, int* y,int*g); // ��ٸ� Ÿ�� �迭�� ���� �ٲٴ� �Լ�
void board_color(int** board, int num_player, int num_height,int*x,int*y); // �迭 ���� ���� �ٸ� ������ ��ٸ��� ����ϴ� �Լ�

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
		printf("[��ٸ� ����]\n");
		printf("=================================\n");
		printf("1. ��ٸ� ���� ����\n");
		printf("2. ��ٸ� Ÿ�� ����\n");
		printf("3. ����\n");
		printf("=================================\n");
		printf("����: ");
		scanf("%d", &num);

		if (num == 3) break; // 3�� �Է� ������ ���α׷� ����

		switch (num) {
		case 1: // 1�� �Է����� ��
			printf("\n");
			printf("���� �ο���: ");
			scanf("%d", &num_player);
			printf("��ٸ� ����: ");
			scanf("%d", &num_height);
			printf("������ ����: ");
			scanf("%d", &num_line);
			printf("�����̸�: ");
			scanf("%s", filename);

			// �Է¹��� ������ �������� �迭 ���� �Ҵ�
			board = (int**)malloc((num_height) * sizeof(int*));
			for (i = 0; i < num_height; i++)
				board[i] = (int*)malloc((num_player) * sizeof(int));

			generate_ladder(board, num_player, num_height, num_line); // ������ ����
			save_ladder(filename, board, num_player, num_height, num_line); // ���� ����

			for (i = 0; i < num_height; i++) // �迭 �Ҵ� ����
				free(board[i]);
			free(board);

			printf("\n");
			break;
		case 2: // 2�� �Է����� ��
			printf("\n���� �̸�: ");
			scanf("%s", filename); // ���� �̸��� �Է¹޴´�
			board = load_ladder(filename, &num_player, &num_height, &num_line); //��ٸ� �ҷ�����
			print_ladder(board, num_player, num_height, num_line); // �ҷ��� ��ٸ��� ���

			int player; //����ڰ� ������ �÷��̾�
			int x, y, g, alp; // ��ǥ�� ��ٸ� Ÿ���� ���� ����, ���ĺ� ǥ�� ����
			int round = num_player; // �� ������ ���� ��
			char c; // ���͸� �Է¹ޱ� ���� ����

			while (1) {
				printf(">> ");
				scanf("%d", &player); // �÷��̾� ��ȣ�� �޴´�

				if (player == 0) break; //0�� ������ Ż��
				if (player == -1) { //��ٸ� Ÿ�⿡�� -1�� �Է����� ��
					for (player = 1; player < num_player + 1; player++) { //1������ ���ʴ�� ��� �÷��̾��� ��ٸ� Ÿ�⸦ ����
						x = (player - 1) * 2;
						y = num_height - 1;
						board[y][x] = player * 10;
						system("cls"); //ȭ�� �ʱ�ȭ
						board_color(board, num_player, num_height, &x, &y); //��ٸ� ���
						g = 0;
						system("cls");
						while (1) {
							if (g == 0) board = board_change(board, num_player, num_height, player, &x, &y, &g); //���� ĭ�� ��ٸ� �迭 ����
							else { //g�� 1(�����ٷ� �̵��� ����)��� ������������ ���� �� ĭ �̵��Ѵ�.
								board[y - 1][x] = player * 10;
								y--; //���� �� ĭ �̵�
								g--; //�ٽ� 0���� �ٲ۴�
							}
							board_color(board, num_player, num_height, &x, &y); // ���
							if (y == 0) break; //���� �̸��� Ż���Ѵ�.
							system("cls");
						}
						round--; // ��ٸ� Ÿ�Ⱑ ����� ������ ���δ�
						if (round < 0) break; // ��� ���尡 ����Ǹ� Ż���Ѵ�.
					}
					for (player = 1; player < num_player + 1; player++) { //�÷��̾� ��ٸ��� ������ �迭���� ���� ��� ���ĺ��� �����ߴ��� ���
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
				// �÷��̾� ��ȣ�� �������� ��
				x = (player - 1) * 2;
				y = num_height - 1;
				board[y][x] = player * 10;
				system("cls");
				board_color(board, num_player, num_height, &x, &y); //���� ���
				scanf("%c", &c);
				scanf("%c", &c);
				g = 0;
				system("cls");
				while (1) {
					if (g == 0) board = board_change(board, num_player, num_height, player, &x, &y, &g); //���� ��ٸ� ĭ�� �迭���� ����
					else { //�������� �̵��� ���Ŀ��� �ٷ� ���� �̵�
						board[y - 1][x] = player * 10;
						y--;
						g--;
					}
					board_color(board, num_player, num_height, &x, &y); //���
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
			if (board[i][j] != 0 && board[i][j] != 1) {//���� �ٲٱ�
				if ((board[i][j] / 10) % 5 == 0) color = 95; //�迭�� ����� ���� ���� ���� ����
				else color = (board[i][j] / 10) % 5 + 90;
				set_color(color); //�� ����
			}

			if (j % 2 == 0) printf("+");
			else if (j % 2) {
				if (board[i][j]) printf("---");
				else printf("   ");
			}
			reset_color();//�� �ʱ�ȭ
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
	if (*x == 0 && !board[*y][*x+1]) { //���� �����̰� �����ʿ� ��ٸ��� ������
		board[*y-1][*x] = player * 10;
		(*y)--;
	}
	else if (*x == (num_player-1)*2 && !board[*y][*x-1]) { //���� �������̰� ���ʿ� ��ٸ��� ������
		board[*y-1][*x] = player * 10;
		(*y)--;
	}
	else if (!board[*y][*x + 1] && !board[*y][*x - 1]) { //���� ��ٸ��� ������
		board[*y - 1][*x] = player * 10;
		(*y)--;
	}
	else {
		if (*x != (num_player - 1) * 2 && board[*y][*x + 1]) { //�����ʿ� ��ٸ��� ������
			board[*y][*x] = player * 10;
			board[*y][*x + 1] = player * 10;
			board[*y][*x + 2] = player * 10;
			(*x) += 2;
			(*g)++;
		}
		else if (board[*y][*x - 1]) { //���ʿ� ��ٸ��� ������
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
	//0���� ���� �� ��ٸ� �迭 ����
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < num_player; j++) {
			board[i][j] = 0;
		}
	}

	int k;
	for (i = 0; i < num_line; i++) { // �Է¹��� ������ ������ŭ ��ǥ ����
		j = rand() % (num_height - 2) + 1; 
		k = rand() % (num_player);
		if (k != 0) { 
			if (board[j][k] == 0 && board[j][k - 1] == 0 && board[j][k + 1] == 0) { //����ִ� ĭ�̰� �� ���� �ٸ��� ������ 1 ����
				board[j][k] = 1;
			}
			else { //�������� ���� ���ϸ� i �ٽ� ����
				i--;
			}
		}
		else if (k == 0) { //���� �����̸� �����ʸ� �˻�
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
	fp = fopen(filename, "w"); //���� ����

	fprintf(fp, "%d %d %d \n", num_player, num_height, num_line); //���� ����
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
	int a, b; // ������ ������ �Ͻ������� ������ ����
	int** board;

	FILE* fp;
	fp = fopen(filename, "r");
	//���� �б�
	fscanf(fp, "%d %d %d\n", &num_player, &num_height, &num_line);
	*player = num_player;
	*height = num_height;
	*line = num_line;
	// ���� ������ �������� �迭 ���� �Ҵ�
	board = (int**)malloc(num_height * sizeof(int*));
	for (i = 0; i < num_height; i++)
		board[i] = (int*)malloc((num_player * 2 - 1) * sizeof(int));

	// ������ ���� >> ��δ� 1�� �����Ͽ� ��Ÿ����
	for (i = 0; i < num_height; i++) {
		for (j = 0; j < num_player * 2 - 1; j++) {
			if (j % 2 == 0)
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}

	for (i = 0; i < num_line; i++) { //��ǥ ���
		fscanf(fp, "%d %d\n", &a, &b);
		board[a][b * 2 - 1] = 1;
	}
	return board;
}

void print_ladder(int** board, int num_player, int num_height, int num_line)
{
	int i, j;
	// Player ���
	i = 0;
	printf(" ");
	while (1) { //���ĺ� ���
		printf("%c", i + 65);
		i++;
		if (i == num_player) break;
		printf("   ");
	}
	printf("\n");

	for (i = 0; i < num_height; i++) {  //��ٸ� ���
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
	while (1) { //�÷��̾� ��ȣ ���
		printf("%2d", i + 1);
		i++;
		if (i == num_player) break;
		printf("  ");
	}
	printf("\n");
}
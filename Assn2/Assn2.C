// 20220778 ǥ����

#define _CRT_SECURE_NO_WARNINGS
#define max_size 75
#define ERROR 0.00001
#include <stdio.h>
#include <math.h>
#include <windows.h> // GetConsoleMode () ���� ����� ���� ����

int set_vt_mode() {
	DWORD l_mode;
	GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &l_mode);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), l_mode | 0x0004 | 0x0008);
}

void set_color_rgb(int r, int g, int b) {
	printf("\033[38;2;%d;%d;%dm", r, g, b);
}
void reset_color() {
	printf("\033[0m");
}

int load_image(const char* filename, int image_rgb[][max_size][max_size],float image_hsv[][max_size][max_size], int* width, int* height); //�̹��� ���� �޾Ƽ� rgb, hsv �迭�� ���� �����ϱ�
void print_image(int image_rgb[][max_size][max_size], int width, int height); //rgb �ȼ� �����͸� �̹����� ����ϴ� �Լ�
float C_max(float R, float G, float B,int* color); // ���� ū ���� ��ȯ�ϴ� �Լ� + ���� ū ���� ���� ���� �������� ����
float C_min(float R, float G, float B); // ���� ���� ���� ��ȯ�ϴ� �Լ�
void print_histogram(float image_hsv[][max_size][max_size], int width, int height); // hsv �����͸� �м��Ͽ� ������׷��� ����ϴ� �Լ�
int histogram_color(int* r, int* g, int* b, float H); // ������׷��� HSV -> RGB ����ȯ
void change_color(float image_hsv[][max_size][max_size], int width, int height, int source, int target); // �ҽ�, Ÿ�� ������ �޾� ��ȯ�Ͽ� �ٽ� �����ϴ� �Լ�
int valid_num(int a, int b, int num); // a�� b ������ �������� �Ǵ��Ͽ� ��ȿ ���θ� �Ǵ��ϴ� �Լ�
void save_image(int image_rgb[][max_size][max_size], int width, int height); // rgb �����Ͱ� ����� �迭�� ppm ���Ϸ� �����ϴ� �Լ�
void HSV2RGB(float image_hsv[][max_size][max_size], int image_rgb[][max_size][max_size], int width, int height); // hsv �����͸� rgb �����ͷ� ��ȯ�Ͽ� �����ϴ� �Լ�

int main()
{
	set_vt_mode();

	int i, j, k;
	int  width, height; // �ʺ�� ����
	int source, target; //change color �Լ����� �̿�

	// ���� ����
	char filename[max_size]; // �ִ� 74�� ���� ���� ����
	int num; // �޴� �Է°�
	int image_rgb[3][max_size][max_size]; // ä�� �ʺ� ����
	float image_hsv[3][max_size][max_size]; // h s v
	int program_end = 1; // �� ���� 0�� �Ǹ� ���α׷��� ����ȴ�.

	if(load_image(filename, image_rgb, image_hsv, &width, &height)) // �迭�� ������ �Է��ϱ�
		return 0; // ���� �ҷ����⿡ ������ ��� ���α׷� ����

	while (program_end) {
		//�޴� ���
		printf("\n=================\n");
		printf("IMAGE COLOR CHANGER\n");
		printf("=================\n");

		printf(" 1. Image Histogram\n");
		printf(" 2. Change Color\n");
		printf(" 3. Print Image\n");
		printf(" 4. Save Image\n");
		printf(" 5. Exit\n");

		printf("Loaded file:");
		printf("%s\n\n", filename); // �Է� ���� ���ڿ��� ȭ�鿡 ���
		
		while (1) { // ��ȿ�� ���� ���� ������ �ݺ�
			// �޴����� �Է¹޴´�.
			printf("Choose menu number >> "); 
			scanf("%d", &num);
			if (valid_num(1, 5, num)) // ��ȿ�� �������� �Ǵ�
				break;
			printf("Wrong input!\n");
		}

		switch (num) { //�Է��� ���� ���� ��� ����
		case 1:
			print_histogram(image_hsv, width, height); // ������׷��� ����Ѵ�.
			break;
		case 2:
			print_histogram(image_hsv, width, height); // ������׷� ���
			while(1) { // source �� �ޱ�
				printf("Choose source color >> ");
				scanf("%d", &source);
				if (valid_num(0, 11, source)) //��ȿ�� ������ �Ǵ�
					break;
				printf("Wrong input!\n");
			}
			while (1) { // target �� �ޱ�
				printf("Choose target color >> ");
				scanf("%d", &target);
				if (valid_num(0, 11, target)) // ��ȿ�� ������ �Ǵ�
					break;
				printf("Wrong input!\n");
			}
			change_color(image_hsv, width, height, source, target); // �ҽ��� Ÿ�� ���� ���� ������ ����
			break;
		case 3:
			print_image(image_rgb, width, height); // �̹��� ���� ���
			break;
		case 4:
			HSV2RGB(image_hsv, image_rgb, height, width); // �ٲ� HSV�� RGB�� ����
			save_image(image_rgb, width, height); // rgb �����͸� �̿��Ͽ� ppm ���� ����
			break;
		case 5:
			program_end = 0; // ���α׷� ����
			break;
		default:
			printf("Wrong input!"); // ������ �� �̿��� ���� �Է¹޾��� ��
			break;
		}
	}

}
int valid_num(int a, int b, int num) {
	if (a <= num && b >= num)
		return 1;
	else
		return 0;
}

int load_image(const char* filename, int image_rgb[][max_size][max_size], float image_hsv[][max_size][max_size], int* width, int* height)
{
	// ������ �а� RGB �迭�� ����
	int i, j, k;

	//���� �б�
	FILE* fp;
	printf("Enter input filename: ");
	scanf("%s", filename); // ���� �� ������ ����
	fp = fopen(filename, "r"); // �Է� ���� ������ �б� ���� ����

	if (fp == NULL) { // ������ �ҷ����µ� ������ ��� 1 ��ȯ
		printf("File not found: %s", filename);
		return 1;
	}

	fscanf(fp, "%*s %d %d %*d", width, height);

	for (k = 0; k < *height; k++) {
		for (j = 0; j < *width; j++) {
			for (i = 0; i < 3; i++) { // 3���� ������ ���� ���� r, g, b ä�ο� ����
				fscanf(fp, "%d ", &image_rgb[i][k][j]);
			}
		}
	}

	// RGB���� HSV ������ ��ȯ
	float R, G, B;
	float Cmax, Cmin, delta;
	int color;

	for (k = 0; k < *height; k++) {
		for (j = 0; j < *width; j++) {
			R = ((float)image_rgb[0][k][j]) / 255;
			G = ((float)image_rgb[1][k][j]) / 255;
			B = ((float)image_rgb[2][k][j]) / 255;

			Cmax = C_max(R, G, B, &color);
			Cmin = C_min(R, G, B);
			delta = Cmax - Cmin;

			//H �� ä�� �ֱ�
			if (delta == 0) {
				image_hsv[0][k][j] = 0;
			}
			else if (color == 1) {
				image_hsv[0][k][j] = 60 * ((G - B) / delta);
			}
			else if (color == 2) {
				image_hsv[0][k][j] = 60 * (((B - R) / delta) + 2);
			}
			else {
				image_hsv[0][k][j] = 60 * (((R - G) / delta) + 4);
			}

			//S �� ä�� �ֱ�
			if (Cmax == 0) {
				image_hsv[1][k][j] = 0;
			}
			else {
				image_hsv[1][k][j] = delta / Cmax;
			}

			//V �� ä�� �ֱ�
			image_hsv[2][k][j] = Cmax;

			//H �� ����
			if (image_hsv[0][k][j] < 0) {
				image_hsv[0][k][j] = image_hsv[0][k][j] + 360;
			}
		}
	}


	fclose(fp); //���� �ݱ�
	return 0;
}

void print_image(int image_rgb[][max_size][max_size], int width, int height)
{
	int r, g, b;
	int i, j = 0, k = 0;
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			// rgb ä�ο��� ���� ���� �ҷ���
			r = image_rgb[0][k][j];
			g = image_rgb[1][k][j];
			b = image_rgb[2][k][j];

			set_color_rgb(r, g, b); // ���� ����, r g b
			printf("��");
			reset_color();
		}
		printf("\n");
	}
}

float C_max(float R, float G, float B,int* color)
{// R, G, B�� Max�� �� color�� ���� 1, 2, 3�� ���� �����ϰ� �ȴ�.
	float max;
	if (R >= G) {
		max = R;
		*color = 1;
	}
	else {
		max = G;
		*color = 2;
	}
	// B�� ��
	if (max >= B) {
		return max;
	}
	else {
		max = B;
		*color = 3;
	}

	return max;
}
float C_min(float R, float G, float B)
{
	float min;
	if (R < G) {
		min = R;
	}
	else {
		min = G;
	}
	// B�� ��
	if (min < B) {
		return min;
	}
	else {
		min = B;
	}

	return min;
}

int histogram_color(int* r, int* g, int* b, float H)
{
	float x;
	int m = 0;
	int C = 1;
	int H1 = H;
	x = 1 - fabs(fmod((H / 60), 2) - 1);
	float r1 = 0, g1 = 0, b1 = 0;
	switch (H1 / 60) {
	case 0:
		r1 = C;
		g1 = x;
		b1 = 0;
		break;
	case 1:
		r1 = x;
		g1 = C;
		b1 = 0;
		break;
	case 2:
		r1 = 0;
		g1 = C;
		b1 = x;
		break;
	case 3:
		r1 = 0;
		g1 = x;
		b1 = C;
		break;
	case 4:
		r1 = x;
		g1 = 0;
		b1 = C;
		break;
	case 5:
		r1 = C;
		g1 = 0;
		b1 = x;
		break;
	}
	*r = ((r1 + m) * 255);
	*g = ((g1 + m) * 255);
	*b = ((b1 + m) * 255);

}

void print_histogram(float image_hsv[][max_size][max_size], int width, int height)
{
	int color[12] = { 0 }; // ��޺� ����� �ȼ� ����
	int i, k, j, h;
	int check=0; // ���� ���� ���� Ȯ�� ����

	// ���� ����
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			if (image_hsv[1][k][j] == 0) { // S�� 0�϶� �ѱ��
				continue;
			}
			else {
				for (i = 0; i < 12; i++) { 
					if (fabsf(i * 30 - (image_hsv[0][k][j])) < ERROR) { // float ���� ���� ����
						color[i]++;
						check = 1;
					}
				}
				if (check > 0) {
					check = 0; // float ���� ���� ���� �������� ������ ����Ǿ��ٸ� �߰��� ���� �ʴ´�
					continue;
				}
				h = image_hsv[0][k][j] / 30;
				color[h]++; // ��޿� ������ �߰��Ѵ�
			}
		}
	}

	int num;
	int r, g, b;

	for (i = 0; i < 12; i++) {
		printf("[%2d]", i);
		num = color[i] / 10; // �м��� �ȼ��� ������ 0.1��

		histogram_color(&r, &g, &b, i * 30);
		set_color_rgb(r, g, b); // ���� ��ȯ
		for (j = 0; j < num; j++) {
			printf("��");
		}
		reset_color(); // �� �ʱ�ȭ
		printf("%d\n", color[i]); // ���� ���
	}
}

void change_color(float image_hsv[][max_size][max_size], int width, int height, int source, int target)
{
	int k, j;
	// ���� ����
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			image_hsv[0][k][j] = image_hsv[0][k][j] + (target - source) * 30;

			if (image_hsv[0][k][j] < 0) { // ���� ������ ��� 360�� �����ش�
				image_hsv[0][k][j] += 360;
			}
			else if (image_hsv[0][k][j] >= 360) { // ���� 360�� �Ѵ� ��� 360�� ���ش�
				image_hsv[0][k][j] -= 360;
			}
		}
	}
}

void HSV2RGB(float image_hsv[][max_size][max_size], int image_rgb[][max_size][max_size], int height, int width)
{
	int i, j, k;
	float r1 = 0, g1 = 0, b1 = 0;

	// HSV �����͸� RGB �����ͷ� ��ȯ�Ͽ� �迭�� ����
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			float H = image_hsv[0][k][j];
			float S = image_hsv[1][k][j];
			float V = image_hsv[2][k][j];

			float C = V * S;
			float x = C * (1 - fabs(fmod((H / 60), 2) - 1));
			float m = V - C;

			if (H < 60) {
				r1 = C;
				g1 = x;
				b1 = 0;
			}
			else if (H < 120) {
				r1 = x;
				g1 = C;
				b1 = 0;
			}
			else if (H < 180) {
				r1 = 0;
				g1 = C;
				b1 = x;
			}
			else if (H < 240) {
				r1 = 0;
				g1 = x;
				b1 = C;
			}
			else if (H < 300) {
				r1 = x;
				g1 = 0;
				b1 = C;
			}
			else {
				r1 = C;
				g1 = 0;
				b1 = x;
			}
			image_rgb[0][k][j] = ((r1 + m) * 255);
			image_rgb[1][k][j] = ((g1 + m) * 255);
			image_rgb[2][k][j] = ((b1 + m) * 255);
		}
	}
}

void save_image(int image_rgb[][max_size][max_size], int width, int height)
{
	int j, k;
	FILE* fp;
	fp = fopen("output.ppm", "w");

	fprintf(fp, "P3 %d %d 255\n",width, height); // ppm ������ ������ ����
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) { //rgb �迭�� ����� ���� ������� ���Ͽ� ������� ����
			fprintf(fp, "%d %d %d ", image_rgb[0][k][j], image_rgb[1][k][j], image_rgb[2][k][j]);
		}
	}
	fclose(fp);
}
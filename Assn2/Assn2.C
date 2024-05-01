// 20220778 표승현

#define _CRT_SECURE_NO_WARNINGS
#define max_size 75
#define ERROR 0.00001
#include <stdio.h>
#include <math.h>
#include <windows.h> // GetConsoleMode () 등의 사용을 위해 포함

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

int load_image(const char* filename, int image_rgb[][max_size][max_size],float image_hsv[][max_size][max_size], int* width, int* height); //이미지 파일 받아서 rgb, hsv 배열에 각각 저장하기
void print_image(int image_rgb[][max_size][max_size], int width, int height); //rgb 픽셀 데이터를 이미지로 출력하는 함수
float C_max(float R, float G, float B,int* color); // 가장 큰 값을 반환하는 함수 + 가장 큰 값을 가진 색이 무엇인지 구별
float C_min(float R, float G, float B); // 가장 작은 값을 반환하는 함수
void print_histogram(float image_hsv[][max_size][max_size], int width, int height); // hsv 데이터를 분석하여 히스토그램을 출력하는 함수
int histogram_color(int* r, int* g, int* b, float H); // 히스토그램용 HSV -> RGB 색변환
void change_color(float image_hsv[][max_size][max_size], int width, int height, int source, int target); // 소스, 타겟 색상을 받아 변환하여 다시 저장하는 함수
int valid_num(int a, int b, int num); // a와 b 사이의 값인지를 판단하여 유효 여부를 판단하는 함수
void save_image(int image_rgb[][max_size][max_size], int width, int height); // rgb 데이터가 저장된 배열을 ppm 파일로 저장하는 함수
void HSV2RGB(float image_hsv[][max_size][max_size], int image_rgb[][max_size][max_size], int width, int height); // hsv 데이터를 rgb 데이터로 변환하여 저장하는 함수

int main()
{
	set_vt_mode();

	int i, j, k;
	int  width, height; // 너비와 높이
	int source, target; //change color 함수에서 이용

	// 변수 선언
	char filename[max_size]; // 최대 74자 까지 저장 가능
	int num; // 메뉴 입력값
	int image_rgb[3][max_size][max_size]; // 채널 너비 높이
	float image_hsv[3][max_size][max_size]; // h s v
	int program_end = 1; // 이 값이 0이 되면 프로그램은 종료된다.

	if(load_image(filename, image_rgb, image_hsv, &width, &height)) // 배열에 데이터 입력하기
		return 0; // 파일 불러오기에 실패한 경우 프로그램 종료

	while (program_end) {
		//메뉴 출력
		printf("\n=================\n");
		printf("IMAGE COLOR CHANGER\n");
		printf("=================\n");

		printf(" 1. Image Histogram\n");
		printf(" 2. Change Color\n");
		printf(" 3. Print Image\n");
		printf(" 4. Save Image\n");
		printf(" 5. Exit\n");

		printf("Loaded file:");
		printf("%s\n\n", filename); // 입력 받은 문자열을 화면에 출력
		
		while (1) { // 유효한 값이 들어올 때까지 반복
			// 메뉴값을 입력받는다.
			printf("Choose menu number >> "); 
			scanf("%d", &num);
			if (valid_num(1, 5, num)) // 유효한 값인지를 판단
				break;
			printf("Wrong input!\n");
		}

		switch (num) { //입력한 값에 따라 기능 실행
		case 1:
			print_histogram(image_hsv, width, height); // 히스토그램을 출력한다.
			break;
		case 2:
			print_histogram(image_hsv, width, height); // 히스토그램 출력
			while(1) { // source 값 받기
				printf("Choose source color >> ");
				scanf("%d", &source);
				if (valid_num(0, 11, source)) //유효한 값인지 판단
					break;
				printf("Wrong input!\n");
			}
			while (1) { // target 값 받기
				printf("Choose target color >> ");
				scanf("%d", &target);
				if (valid_num(0, 11, target)) // 유효한 값인지 판단
					break;
				printf("Wrong input!\n");
			}
			change_color(image_hsv, width, height, source, target); // 소스와 타겟 색상에 따라 색조를 변경
			break;
		case 3:
			print_image(image_rgb, width, height); // 이미지 파일 출력
			break;
		case 4:
			HSV2RGB(image_hsv, image_rgb, height, width); // 바뀐 HSV를 RGB에 저장
			save_image(image_rgb, width, height); // rgb 데이터를 이용하여 ppm 파일 생성
			break;
		case 5:
			program_end = 0; // 프로그램 종료
			break;
		default:
			printf("Wrong input!"); // 지정된 값 이외의 것을 입력받았을 때
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
	// 파일을 읽고 RGB 배열에 저장
	int i, j, k;

	//파일 읽기
	FILE* fp;
	printf("Enter input filename: ");
	scanf("%s", filename); // 공백 전 까지만 읽음
	fp = fopen(filename, "r"); // 입력 받은 파일을 읽기 모드로 열기

	if (fp == NULL) { // 파일을 불러오는데 실패한 경우 1 반환
		printf("File not found: %s", filename);
		return 1;
	}

	fscanf(fp, "%*s %d %d %*d", width, height);

	for (k = 0; k < *height; k++) {
		for (j = 0; j < *width; j++) {
			for (i = 0; i < 3; i++) { // 3개의 정수씩 묶어 각각 r, g, b 채널에 저장
				fscanf(fp, "%d ", &image_rgb[i][k][j]);
			}
		}
	}

	// RGB값을 HSV 값으로 변환
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

			//H 값 채워 넣기
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

			//S 값 채워 넣기
			if (Cmax == 0) {
				image_hsv[1][k][j] = 0;
			}
			else {
				image_hsv[1][k][j] = delta / Cmax;
			}

			//V 값 채워 넣기
			image_hsv[2][k][j] = Cmax;

			//H 값 보정
			if (image_hsv[0][k][j] < 0) {
				image_hsv[0][k][j] = image_hsv[0][k][j] + 360;
			}
		}
	}


	fclose(fp); //파일 닫기
	return 0;
}

void print_image(int image_rgb[][max_size][max_size], int width, int height)
{
	int r, g, b;
	int i, j = 0, k = 0;
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			// rgb 채널에서 각각 값을 불러옴
			r = image_rgb[0][k][j];
			g = image_rgb[1][k][j];
			b = image_rgb[2][k][j];

			set_color_rgb(r, g, b); // 색깔 설정, r g b
			printf("■");
			reset_color();
		}
		printf("\n");
	}
}

float C_max(float R, float G, float B,int* color)
{// R, G, B가 Max일 때 color는 각각 1, 2, 3의 값을 저장하게 된다.
	float max;
	if (R >= G) {
		max = R;
		*color = 1;
	}
	else {
		max = G;
		*color = 2;
	}
	// B랑 비교
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
	// B랑 비교
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
	int color[12] = { 0 }; // 계급별 조사된 픽셀 개수
	int i, k, j, h;
	int check=0; // 연산 오차 보정 확인 변수

	// 개수 세기
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			if (image_hsv[1][k][j] == 0) { // S가 0일때 넘기기
				continue;
			}
			else {
				for (i = 0; i < 12; i++) { 
					if (fabsf(i * 30 - (image_hsv[0][k][j])) < ERROR) { // float 연산 오차 보정
						color[i]++;
						check = 1;
					}
				}
				if (check > 0) {
					check = 0; // float 연산 오차 보정 과정에서 개수가 집계되었다면 추가로 세지 않는다
					continue;
				}
				h = image_hsv[0][k][j] / 30;
				color[h]++; // 계급에 개수를 추가한다
			}
		}
	}

	int num;
	int r, g, b;

	for (i = 0; i < 12; i++) {
		printf("[%2d]", i);
		num = color[i] / 10; // 분석한 픽셀의 개수의 0.1배

		histogram_color(&r, &g, &b, i * 30);
		set_color_rgb(r, g, b); // 색을 변환
		for (j = 0; j < num; j++) {
			printf("■");
		}
		reset_color(); // 색 초기화
		printf("%d\n", color[i]); // 개수 출력
	}
}

void change_color(float image_hsv[][max_size][max_size], int width, int height, int source, int target)
{
	int k, j;
	// 개수 세기
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			image_hsv[0][k][j] = image_hsv[0][k][j] + (target - source) * 30;

			if (image_hsv[0][k][j] < 0) { // 값이 음수인 경우 360을 더해준다
				image_hsv[0][k][j] += 360;
			}
			else if (image_hsv[0][k][j] >= 360) { // 값이 360을 넘는 경우 360을 빼준다
				image_hsv[0][k][j] -= 360;
			}
		}
	}
}

void HSV2RGB(float image_hsv[][max_size][max_size], int image_rgb[][max_size][max_size], int height, int width)
{
	int i, j, k;
	float r1 = 0, g1 = 0, b1 = 0;

	// HSV 데이터를 RGB 데이터로 변환하여 배열에 저장
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

	fprintf(fp, "P3 %d %d 255\n",width, height); // ppm 파일의 정보를 저장
	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) { //rgb 배열에 저장된 값을 기반으로 파일에 순서대로 저장
			fprintf(fp, "%d %d %d ", image_rgb[0][k][j], image_rgb[1][k][j], image_rgb[2][k][j]);
		}
	}
	fclose(fp);
}
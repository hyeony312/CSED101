#define _CRT_SECURE_NO_WARNINGS 
#include "functions.h"

int main()
{
    char filename[30]; // 읽는 파일 이름
    Head* head; 
    head = (Head*)calloc(1, sizeof(Head));
    readfile(filename, head); // 초기에 파일 읽는 함수
    char command[10]; // 사용자 입력을 저장
    while (1) {
        printf("명령어를 입력해주세요. >> ");
        scanf("%s", command); // 사용자 입력 받음
        if (!strcmp(command, "add")) {
            addSong(head);
        }
        else if (!strcmp(command, "show")) {
            printList(head);
        }
        else if (!strcmp(command, "delete")) {
            deleteList(head);
        }
        else if (!strcmp(command, "show_favorites")) {
            int n;
            printf("상위 몇 개의 음악을 추출할까요? >> ");
            scanf("%d", &n);
            show_fav(head, n);
        }
        else if (!strcmp(command, "exit")) {
            char newfile[30];
            printf("저장할 파일명을 입력해주세요. >>");
            scanf("%s", newfile);
            myexit(head, newfile);
            break;
        }
        else {
            printf("유효하지 않은 명령어입니다.\n\n");
        }
    }
}

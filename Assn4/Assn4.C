#define _CRT_SECURE_NO_WARNINGS 
#include "functions.h"

int main()
{
    char filename[30]; // �д� ���� �̸�
    Head* head; 
    head = (Head*)calloc(1, sizeof(Head));
    readfile(filename, head); // �ʱ⿡ ���� �д� �Լ�
    char command[10]; // ����� �Է��� ����
    while (1) {
        printf("���ɾ �Է����ּ���. >> ");
        scanf("%s", command); // ����� �Է� ����
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
            printf("���� �� ���� ������ �����ұ��? >> ");
            scanf("%d", &n);
            show_fav(head, n);
        }
        else if (!strcmp(command, "exit")) {
            char newfile[30];
            printf("������ ���ϸ��� �Է����ּ���. >>");
            scanf("%s", newfile);
            myexit(head, newfile);
            break;
        }
        else {
            printf("��ȿ���� ���� ���ɾ��Դϴ�.\n\n");
        }
    }
}
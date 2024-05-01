#define _CRT_SECURE_NO_WARNINGS 
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void sortList(Head* head) {
    int i;
    Node* curr;
    curr = head->first;
    for (i = 0; i < head->num-1; i++) { // 음악 개수만큼
        if (strcmp(curr->title, curr->next->title) > 0) { // 사전 순으로 버블 소트
            Node tmp; // 일시적으로 바꿀 데이터 저장
            strcpy(tmp.name, curr->name);
            strcpy(tmp.title, curr->title);
            tmp.prefer = curr->prefer;
            tmp.volume = curr->volume;
            // 데이터 교환
            strcpy(curr->name, curr->next->name);
            strcpy(curr->title, curr->next->title);
            curr->prefer = curr->next->prefer;
            curr->volume = curr->next->volume;

            strcpy(curr->next->name, tmp.name);
            strcpy(curr->next->title, tmp.title);
            curr->next->volume = tmp.volume;
            curr->next->prefer = tmp.prefer;
            i = 0;
            curr = head->first;
        }
        else {
            curr = curr->next; // 커서를 다음으로 옮김
        }
    }
}
void readfile(char filename[30], Head* head)
{
    FILE* fo = NULL;
    int i = 0;
    printf("음악 리스트 파일 이름을 입력해주세요. >>");
    scanf("%s", filename); // 파일 이름을 입력받는다
    fo = fopen(filename, "r"); // 파일 생성
    while (fo == NULL) // 파일 열기에 실패했을 시
    {
        printf("유효하지 않은 파일입니다. 음악 리스트 파일을 다시 입력해주세요. >>");
        scanf("%s", filename);
        fo = fopen(filename, "r");
    }
    Node* tmp = NULL;
    while (1)
    {
        Node* new_node;// 새로운 노드 생성
        new_node = (Node*)calloc(1, sizeof(Node));

        fscanf(fo, "%s %s %f %f \n", new_node->title, new_node->name, &new_node->volume, &new_node->prefer); //음악 정보를 읽는다
        if (new_node->volume == 0)
        {
            break;
        }
        if (head->total_vol + new_node->volume <= 50) // 크기가 50이 넘어가지 않으면 추가한다
        {
            new_node->index = ++i;
            head->total_vol += new_node->volume;
            if (head->num == 0)
            {
                head->num++;
                head->first = new_node;
                tmp = new_node;
            }
            else
            {
                head->num++;
                tmp->next = new_node;
                tmp = new_node;
            }
        }
        else
        {
            printf("용량 초과! 음악(%s)는 추가되지 않았습니다.\n", new_node->title);
        }
    }
    sortList(head);
}

void printList(Head* head)
{
    int i;
    Node* tmp;
    printf(" PLAYLIST\n");
    printf("====================================================================================\n");
    if (head->num == 0) {
        printf("Empty Playlist!\n");
        printf("------------------------------------------------------------------------------------\n");
        printf("Total number of songs: 0\n");
        printf("Storage: 0.00 MB\n");
        printf("====================================================================================\n");
        return;

    }
    printf("No. Title Artist Volume Preference\n");
    printf("------------------------------------------------------------------------------------\n");
    for (i = 0, tmp = head->first; i < head->num; i++, tmp = tmp->next)
    {
        printf("#%2d  |  %14s   |   %14s   |   %.2f   |   %.2f\n", tmp->index, tmp->title, tmp->name, tmp->volume, tmp->prefer);
    }
    printf("------------------------------------------------------------------------------------\n");
    printf("Total number of songs: %d\n", i);
    printf("Storage: %.2f\n", head->total_vol);
}

int find(Head* head, char title[14], int* index)
{// 찾고자 하는 음악의 유무를 판별한다. 성공하면 1을 반환하고 실패하면 0을 반환한다.
    Node* cur;
    cur = head->first;
    int i;
    for (i = 0; i < head->num; i++)
    {
        if (!strcmp(cur->title, title))
        {
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}

int findindex(Head* head, char title[14], int* index)
{ //찾고자 하는 음악의 인덱스를 반환한다
    Node* cur;
    cur = head->first;
    int i;
    for (i = 0; i < head->num; i++)
    {
        if (!strcmp(cur->title, title))
        {
            return i;
        }
        cur = cur->next;
    }

    return i;
}

Node* findLast(Head* head)
{
    int i;
    Node* tmp;
    tmp = head->first;
    for (i = 0; i < head->num - 1; i++)
    {
        tmp = tmp->next;
    }
    return tmp;
}

void deleteList(Head* head) {
    char title[14];
    int index;

    printf("삭제할 음악의 타이틀을 입력해주세요. >> ");
    scanf("%s", title);
    if (find(head, title, 0) == 0) { // find함수를 이용해 해당 곡이 있는지를 판단한다
        printf("플레이리스트에 해당 음악(%s)이 없습니다.", title);
    }
    else {
        index = findindex(head, title, &index);
        int i;
        Node* tmp;
        tmp = head->first;
        for (i = 0; i < index - 2; i++) {
            tmp = tmp->next;
        }


        if (index == 0 && index == head->num - 1) { // 하나만 남았을 때
            head->num--;
            head->total_vol -= tmp->volume;
            tmp = head->first;
            free(tmp);

        }
        else if (index == 0) { // 첫번째 삭제
            head->total_vol -= head->first->volume;
            head->first = head->first->next;
            head->num--;

            free(tmp);
            int j;
            for (j = 0, tmp = head->first; j < head->num; j++, tmp = tmp->next) {
                tmp->index--;
            }
        }
        else if (index == head->num - 1) { // 마지막 삭제
            Node* cur;
            Node* last;
            head->num--;
            last = findLast(head);
            head->total_vol -= last->next->volume;
            cur = head->first;
            int j;
            for (j = 0; j < index - 1; j++) {
                cur = cur->next;
            }

            cur->next = NULL;
            free(last->next);
        }
        else { // 그 외의 위치

            Node* cur;
            Node* next;
            Node* del;
            head->num--;
            cur = head->first;
            int j;
            for (j = 0; j < index - 1; j++) {
                cur = cur->next;
            }
            del = cur->next;
            head->total_vol -= del->volume;
            next = cur->next->next;

            cur->next = next;
            free(del);


            tmp = head->first;
            for (j = 0; j < index; j++) {
                if (cur->next == NULL) {
                    break;
                }
                cur = cur->next;
            }

            for (j = index; j < head->num; j++, cur = cur->next) { //삭제된 곡 뒤의 곡들의 인덱스를 1 줄인다
                cur->index--;
            }
        }
    }

}

void addSong(Head* head)
{
    char title[14];
    char name[14];
    float vol;
    float prefer;
    int nulln = 0;
    printf("추가할 음악의 타이틀을 입력해주세요. >> ");
    scanf("%s", title);
    printf("추가할 음악의 아티스트를 입력해주세요. >> ");
    scanf("%s", name);
    printf("추가할 음악의 용량을 입력해주세요. >> ");
    scanf("%f", &vol);
    printf("추가할 음악의 선호도를 입력해주세요. >> ");
    scanf("%f", &prefer);

    if (find(head, title, &nulln) == 0) // title일치하는게 있는지 찾고 없으면 0리턴 있으면 1리턴
    {
        if (vol + head->total_vol > 50)  // 50 넘어가면 곡을 추가하지 않는다
        {
            printf("용량 초과! 음악(%s)는 추가되지 않았습니다.\n", title);
            return;
        }
        else
        {
            if (head->num == 0) { // 리스트에 곡이 없을 때
                Node* new_node;
                new_node = (Node*)calloc(1, sizeof(Node));
                strcpy(new_node->title, title);
                strcpy(new_node->name, name);
                new_node->volume = vol;
                new_node->prefer = prefer;
                head->first = new_node;
                new_node->index = 1;
                head->total_vol += new_node->volume;
                head->num = 1;
            }
            else {
                Node* new_node;
                new_node = (Node*)calloc(1, sizeof(Node));
                strcpy(new_node->title, title);
                strcpy(new_node->name, name);
                new_node->volume = vol;
                new_node->prefer = prefer;
                new_node->next = NULL;
                Node* last = findLast(head);
                last->next = new_node;
                head->num++;
                head->total_vol += new_node->volume;
                new_node->index = last->index + 1;
            }
        }
    }
    else
    {
        printf("해당 음악이 이미 플레이리스트 내에 존재합니다.\n");
        return;
    }
    sortList(head); // 사전순으로 소트
}


void show_fav(Head* head, int n) {

    if (head->num < n) { // 음악 수보다 큰 수를 입력한 경우
        printf("추출하고자 하는 음악의 수가 전체 음악의 수보다 많습니다.\n");
        return;
    }

    if (n <= 0) { // 유효하지 않는 입력값
        printf("추출하고자 하는 음악의 수는 1 이상이어야 합니다.\n");
        return;
    }
    int i;
    Node* curr;
    curr = head->first;
    for (i = 0; i < head->num; i++) {
        if (curr->prefer < curr->next->prefer) { //다음 곡이 선호도가 높은 경우, 순서를 바꾼다
            Node tmp;
            strcpy(tmp.name, curr->name);
            strcpy(tmp.title, curr->title);
            tmp.prefer = curr->prefer;
            tmp.volume = curr->volume;

            strcpy(curr->name, curr->next->name);
            strcpy(curr->title, curr->next->title);
            curr->prefer = curr->next->prefer;
            curr->volume = curr->next->volume;

            strcpy(curr->next->name, tmp.name);
            strcpy(curr->next->title, tmp.title);
            curr->next->volume = tmp.volume;
            curr->next->prefer = tmp.prefer;
            i = 0;
            curr = head->first;
        }
        else {
            curr = curr->next;
        }
    }



    Node* tmp;
    printf("                                    FAVORITES\n");
    printf("====================================================================================\n");
    if (head->num == 0) {
        printf("Empty Playlist!\n");
        printf("------------------------------------------------------------------------------------\n");
        printf("Total number of songs: 0\n");
        printf("Storage: 0.00 MB\n");
        printf("====================================================================================\n");
        return;

    }
    printf("No. Title Artist Volume Preference\n");
    printf("------------------------------------------------------------------------------------\n");
    float strage = 0;
    for (i = 0, tmp = head->first; i < n; i++, tmp = tmp->next)
    {
        printf("#%2d  |  %14s   |   %14s   |   %.2f   |   %.2f\n", i + 1, tmp->title, tmp->name, tmp->volume, tmp->prefer);
        strage += tmp->volume;
    }
    printf("------------------------------------------------------------------------------------\n");
    printf("Total number of songs: %d\n", n);


    printf("Storage: %.2f\n", strage);
    printf("====================================================================================\n");
    sortList(head);
}

void myexit(Head* head, char myfile[30]) {
    printf("프로그램을 종료합니다.\n");
    FILE* fo = NULL;
    Node* curr;
    curr = head->first;
    int i, j;
    fo = fopen(myfile, "w"); // 입력받은 이름으로 파일 생성
    for (i = 0; i < head->num; i++) {
        fprintf(fo, "%14s %14s %.2f %.2f \n", curr->title, curr->name, curr->volume, curr->prefer);
        fflush(fo);
        curr = curr->next;
    }

    for (i = head->num - 1; i >= 0; i--) {
        curr = head->first;
        for (j = 0; j < i; j++) {
            curr = curr->next;

        }
        free(curr); //할당 해제
    }
    free(head);
    fclose(fo);

}

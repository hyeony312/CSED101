#pragma once

struct node // 첫번째를 제외한 곡들 정보
{
    int index;
    char title[14];
    char name[14];
    float volume;
    float prefer;
    struct node* next;
};
typedef struct node Node;

struct head // 리스트의 정보 저장(제일 처음에 위치)
{
    int num;
    float total_vol;
    Node* first;
};
typedef struct head Head;

void sortList(Head* head); // 버블 소트를 이용하여 사전순으로 음악 정렬
void readfile(char filename[30], Head* head); //텍스트 파일을 읽고 리스트 생성

void printList(Head* head); // 리스트를 출력
int find(Head* head, char title[14], int* index); // 찾고자 하는 음악이 존재하는지 판단
int findindex(Head* head, char title[14], int* index); //찾고자 하는 음악의 인덱스를 반환

Node* findLast(Head* head); // 리스트의 마지막 노드를 찾는 함수

void deleteList(Head* head); // 입력 받은 음악을 삭제
void addSong(Head* head); // 음악을 추가


void show_fav(Head* head, int n); // 선호도 순으로 노래 출력

void myexit(Head* head, char myfile[30]); // 파일을 저장하고 프로그램 종료
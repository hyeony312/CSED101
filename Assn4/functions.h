#pragma once

struct node // ù��°�� ������ ��� ����
{
    int index;
    char title[14];
    char name[14];
    float volume;
    float prefer;
    struct node* next;
};
typedef struct node Node;

struct head // ����Ʈ�� ���� ����(���� ó���� ��ġ)
{
    int num;
    float total_vol;
    Node* first;
};
typedef struct head Head;

void sortList(Head* head); // ���� ��Ʈ�� �̿��Ͽ� ���������� ���� ����
void readfile(char filename[30], Head* head); //�ؽ�Ʈ ������ �а� ����Ʈ ����

void printList(Head* head); // ����Ʈ�� ���
int find(Head* head, char title[14], int* index); // ã���� �ϴ� ������ �����ϴ��� �Ǵ�
int findindex(Head* head, char title[14], int* index); //ã���� �ϴ� ������ �ε����� ��ȯ

Node* findLast(Head* head); // ����Ʈ�� ������ ��带 ã�� �Լ�

void deleteList(Head* head); // �Է� ���� ������ ����
void addSong(Head* head); // ������ �߰�


void show_fav(Head* head, int n); // ��ȣ�� ������ �뷡 ���

void myexit(Head* head, char myfile[30]); // ������ �����ϰ� ���α׷� ����
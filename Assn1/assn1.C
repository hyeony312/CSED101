#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

#define NOPAIR 0
#define STRAIGHT 1
#define DOUBLE 2
#define TRIPLE 3

void card_shuffle(int* shared_card1, int* shared_card2, int* user_card, int* computer_card);
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card);

int calc_hand(int card, int shard_card1, int shard_card2);

int is_valid_num(int a, int b, int num);
int user_turn(int user_chips, int* user_betting_chips, int betted_chips, int turn);
int computer_turn(int user_hand, int com_chips, int* com_betting_chips, int betted_chips, int turn);

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card);


int main()
{
	srand(time(NULL));
	int round = 1; // ���� ��
	int shared_card1;
	int shared_card2;
	int user_card;
	int computer_card;
	int user_hand, computer_hand; // ī�� ����
	int user_chips = 50, com_chips = 50; // �ܿ� Ĩ ����
	int user_end, com_end;
	int winner = 0; // ���� ����
	int con; // ��� ���� ����

	while (1) {
		int num = 0; // ����ڿ��� �Է� ���� �ൿ��
		int user_betting_chips = 1, com_betting_chips = 1; // ������ Ĩ ��
		int turn = 0; // ���ü���, ¦�� >> ���� ��, Ȧ�� >> ��ǻ�� ��

		// 2. ���� ����
		printf("��������������������������������������\n");
		printf("�� %2d Game Starts! ��\n", round);
		printf("��������������������������������������\n");

		printf("\n Chips remaining:\n");
		printf("����������������������������������������������\n");
		printf("��  User        ��  %2d  ��\n", user_chips);
		printf("��  Computer    ��  %2d  ��\n", com_chips);
		printf("����������������������������������������������\n");

		//ī�弼��
		card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);
		print_card_info(shared_card1, shared_card2, user_card, computer_card);

		user_hand = calc_hand(user_card, shared_card1, shared_card2); // ����ī�� �� ��� ����ī�� �� ���� ��
		computer_hand = calc_hand(computer_card, shared_card1, shared_card2); // ��ǻ��ī�� �� ��� ����ī�� �� ���� ��

		// 3. ����
		while (1) {
			if (user_chips == 1)
				break;
			else if (com_chips == 1)
				break;

			if (winner == 1) { // ���� ������ �¸��ߴٸ�
				turn++;
			}
			winner = 0;

			printf("������������������������������������\n");
			printf("��     Betting    ��\n");
			printf("������������������������������������\n");

			printf("������������������������������������������������\n");
			printf("��  User:  1 ��  Com:  1 ��\n");
			printf("������������������������������������������������\n\n");

			do {
				user_end = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
				com_end = computer_turn(user_hand, com_chips, &com_betting_chips, user_betting_chips, turn);

				printf("\n������������������������������������������������\n");
				printf("��  User: %2d ��  Com: %2d ��\n", user_betting_chips, com_betting_chips);
				printf("������������������������������������������������\n\n");

				turn++;
			} while (user_end > 0 && com_end > 0); // �� �� �ϳ��� Call �Ǵ� Fold�� ������ ������ ���� ����

			winner = 0;//���� �ʱ�ȭ
			break;
		}

		// ���� ����
		printf("������������������������������������������������������������������������������������������������������������������������\n\n");
		printf("Betting Finished\n\n");
		printf("����������������������������������������������������������������������������������������������������������������������������������\n");
		printf("��    Computer   ��         Shared Cards          ��      User     ��\n");
		printf("����������������������������������������������������������������������������������������������������������������������������������\n");
		printf("�� �������������������������� �� �������������������������� �� �������������������������� �� �������������������������� ��\n");
		printf("�� �� ��        �� �� �� ��        �� �� �� ��        �� �� �� ��        �� ��\n");
		printf("�� ��           �� �� ��           �� �� ��           �� �� ��           �� ��\n");
		printf("�� ��     %2d    �� �� ��     %2d    �� �� ��     %2d    �� �� ��     %2d    �� ��\n", computer_card, shared_card1, shared_card2, user_card);
		printf("�� ��           �� �� ��           �� �� ��           �� �� ��           �� ��\n");
		printf("�� ��         ���� �� ��         ���� �� ��         ���� �� ��         ���� ��\n");
		printf("�� �������������������������� �� �������������������������� �� �������������������������� �� �������������������������� ��\n");
		printf("����������������������������������������������������������������������������������������������������������������������������������\n\n");


		winner = calc_winner(shared_card1, shared_card2, user_card, computer_card);

		if (user_end == -1 || winner == 2) { // ������ �й��� ��� 
			printf("������������������������������������������\n");
			printf("��   Computer win!   ��\n");
			printf("������������������������������������������\n");

			com_chips = com_chips + user_betting_chips;
			user_chips = user_chips - user_betting_chips;
		}
		else { // ��ǻ�Ͱ� �й��� ���
			printf("������������������������������������\n");
			printf("��    User Win!   ��\n");
			printf("������������������������������������\n");

			com_chips = com_chips - com_betting_chips;
			user_chips = user_chips + com_betting_chips;
		}

		printf("\n����������������������������������������������\n");
		printf("��  User       ��  %3d  ��\n", user_chips);
		printf("��  Computer   ��  %3d  ��\n", com_chips);
		printf("����������������������������������������������\n\n");

		round++;// ���� �� 1ȸ �߰�

		if (round > 10 || com_chips <= 0 || user_chips <= 0) { // ���� ���� �� ��� ���
			printf("������������������������������������������������������������������������������������������������������������������������\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("����������������������������������������������\n");
			printf("��  User       ��  %3d  ��\n", user_chips);
			printf("��  Computer   ��  %3d  ��\n", com_chips);
			printf("����������������������������������������������\n\n\n");

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}

		printf("Proceed or Not? [Go: 1, End: -1]:"); //���� ���� ���� Ȯ��
		scanf_s("%d", &con);
		if (con == -1) { // ���� ���� �� ��� ���
			printf("������������������������������������������������������������������������������������������������������������������������\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("����������������������������������������������\n");
			printf("��  User       ��  %3d  ��\n", user_chips);
			printf("��  Computer   ��  %3d  ��\n", com_chips);
			printf("����������������������������������������������\n\n\n");
			con = 0;

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}
		else if (con == 1) { // ���� ��� ����
			system("cls");
			con = 0;
		}
	}
}

void card_shuffle(int* shared_card1, int* shared_card2, int* user_card, int* computer_card)
{
	*shared_card1 = rand() % 10 + 1;
	*shared_card2 = rand() % 10 + 1;
	*user_card = rand() % 10 + 1;
	*computer_card = rand() % 10 + 1;
}

void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card)
{
	printf("\n����������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��    Computer   ��         Shared Cards          ��      User     ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������\n");
	printf("�� �������������������������� �� �������������������������� �� �������������������������� �� �������������������������� ��\n");
	printf("�� �� ��        �� �� �� ��        �� �� �� ��        �� �� �� ��        �� ��\n");
	printf("�� ��           �� �� ��           �� �� ��           �� �� ��           �� ��\n");
	printf("�� ��     %2d    �� �� ��     %2d    �� �� ��     %2d    �� �� ��      ?    �� ��\n", computer_card, shared_card1, shared_card2);
	printf("�� ��           �� �� ��           �� �� ��           �� �� ��           �� ��\n");
	printf("�� ��         ���� �� ��         ���� �� ��         ���� �� ��         ���� ��\n");
	printf("�� �������������������������� �� �������������������������� �� �������������������������� �� �������������������������� ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������\n\n");
}

int calc_hand(int card, int shard_card1, int shard_card2)
{
	int i,j;
	int large;

	for (i = 10; i; i--) { //�� ���� ī�� �� ���ڰ� ���� ū ī�� ���� >> STRAIGHT ���� �Ǵܿ� Ȱ��
		if (i == card) { //ù ��° ī�尡 ���� ū ���
			large = card;
			j = 1;
			break;
		}
		else if (i == shard_card1) {//�� ��° ī�尡 ���� ū ���
			large = shard_card1;
			j = 2;
			break;
		}
		else if (i == shard_card2) {//�� ��° ī�尡 ���� ū ���
			large = shard_card2;
			j = 3;
			break;
		}
	}

	switch (j) { //large���� 1 ���� ��, 2 ���� ���� ��� �ִٸ� STRAiGHT��� �Ǵ�(j=4)
	case 1: if (large - 1 == shard_card1 || large - 1 == shard_card2) {
		if (large - 2 == shard_card1 || large - 2 == shard_card2)
			j = 4;
		break;
	}
		  else break;
	case 2: if (large - 1 == card || large - 1 == shard_card2) {
		if (large - 2 == card || large - 2 == shard_card2)
			j = 4;
		break;
	}
		  else break;
	case 3: if (large - 1 == shard_card1 || large - 1 == card) {
		if (large - 2 == shard_card1 || large - 2 == card)
			j = 4;
		break;
	}
		  else break;
	}


	if (card == shard_card1 && card == shard_card2 && shard_card1 == shard_card2) //�� ���� ī�尡 ��� ���� ��� >> TRIPLE
		return TRIPLE;

	else if (card == shard_card1 || shard_card1 == shard_card2 || card == shard_card2) //�� ���� ī�尡 ���� ��� >> DOUBLE
		return DOUBLE;

	else if (j > 3) // j=4��� STRAIGHT��� �Ǵ� (�� for, switch�� ����)
		return STRAIGHT;

	else //�� ���ǿ� �ش���� �ʴ´ٸ� NOPAIR��� �Ǵ�
		return NOPAIR;

}

int is_valid_num(int a, int b, int num) // num���� ��ȿ�� ������ �Ǵ� >> 1�̸� ��ȿ
{
	if (a <= num && num <= b)
		return 1;
	else
		return 0;
}

int user_turn(int user_chips, int* user_betting_chips, int betted_chips, int turn)
{
	int select; // �ൿ��
	int betting; // ���Ӱ� ������ Ĩ

	if (turn % 2 == 0) {
		do {
			printf("USER �� [Call: 1 | Raise: 2 | Fold: 3]: ");
			scanf_s("%d", &select);
			printf("\n");

			if (turn == 0 && select == 1) { //ù �Ͽ� call�� ����� ��
				printf("\nUSER �� [Invalid input]\n");
			}
			else if (is_valid_num(1,3,select)) {
				break;
			}
			else { //��ȿ���� ���� ���ڸ� �������� ��
				printf("\nUSER �� [Invalid input]\n");
			}
		} while (1);


		switch (select) {
		case 1:
			if (betted_chips > user_chips) { // ������ Ĩ�� ���� Ĩ�� ������ ���� ���
				*user_betting_chips = user_chips;
				return 0;
			}
			else { // Call ����
				if (betted_chips >= user_chips) { // ��ǻ�Ͱ� ������ Ĩ�� ������ ���� Ĩ���� ���� ���
					*user_betting_chips = user_chips;
					return 0;
				}
				*user_betting_chips = betted_chips;
				return 0;
			}
		case 2: // Raise ����
			printf("\nUSER �� [Input number of chips for Raise]: ");
			scanf_s("%d", &betting);
			printf("\n");
			*user_betting_chips = *user_betting_chips + betting;

			return *user_betting_chips;
		case 3: // Fold ����
			return -1;
		}
	}
	else {
		return 1;
	}
	
}

int computer_turn(int user_hand, int com_chips, int* com_betting_chips, int betted_chips, int turn)
{
	if (turn % 2 == 1) {
		int select = rand() % 10 + 1;
		int betting;

		if (user_hand > 0) {
			if (select <= 7) {
				if (turn == 1) { // [���1] ù ���� ��� 1�� Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // ������ Ĩ�� ���� Ĩ���� ���� ���, Call
						*com_betting_chips = com_chips;
						printf("\nCOM �� Call\n");
						return 0;
					}

					printf("\nCOM �� Raise, +1\n");
					return 1;
				}
				else { // Fold ����
					printf("\nCOM �� Fold\n");
					return -1;
				}
			}
			else { // Call ����
				if (turn == 1) { // [���1] ù ���� ��� 1�� Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // ������ Ĩ�� ���� Ĩ���� ���� ���, Call
						*com_betting_chips = com_chips;
						printf("\nCOM �� Call\n");
						return 0;
					}

					printf("\nCOM �� Raise, +1\n");
					return 1;
				}

				if (betted_chips >= com_chips) { // Call�� �ߴµ� Ĩ ���� ���ڶ� ���
					*com_betting_chips = com_chips;
					printf("\nCOM �� Call\n");
					return 0;
				}
				*com_betting_chips = betted_chips;
				printf("\nCOM �� Call\n");
				return 0;
			}
		}

		else {
			if (turn == 1) { // [���2] ù ���� ��� 1�� Raise
				*com_betting_chips = betted_chips + 1;

				if (*com_betting_chips > com_chips) { // ������ Ĩ�� ���� Ĩ���� ���� ���, Call
					*com_betting_chips = com_chips;
					printf("\nCOM �� Call\n");
					return 0;
				}

				printf("\nCOM �� Raise, +1\n");
				return 1;
			}
			else if (select <= 5) { // Call ����
				if (betted_chips >= com_chips) { // Call�� �ߴµ� Ĩ ���� ���ڶ� ���
					*com_betting_chips = com_chips;
					printf("\nCOM �� Call\n");
					return 0;
				}

				*com_betting_chips = betted_chips;
				printf("\nCOM �� Call\n");

				return 0;
			}
			else{ // Raise ����
				betting = rand() % 5 + 1; // ���Ӱ� ������ ��
				*com_betting_chips = betted_chips + betting;

				if (*com_betting_chips > com_chips) { // ������ Ĩ�� ���� Ĩ���� ���� ���, Call
					*com_betting_chips = com_chips;
					printf("\nCOM �� Call\n");
					return 0;
				}

				printf("\nCOM �� Raise, +%d\n", betting);
				return *com_betting_chips;
		}
		}
	}
	return 1;
}

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card)
{
	// ������ �¸��� ��� 1��, ��ǻ�Ͱ� �¸��� ��� 2�� ��ȯ
	int user = calc_hand(user_card, shared_card1, shared_card2);
	int com = calc_hand(computer_card, shared_card1, shared_card2);

	if (user > com) {
		return 1;
	}
	else if (user < com){
		return 2;
	}
	else {
		// �ڵ尡 ���� ���
		if (user_card > computer_card) {
			return 1;
		}
		else if (user_card < computer_card) {
			return 2;
		}
		// ���� ī���� ���ڰ� ���� ���
		else {
			return 1;
		}
	}
}
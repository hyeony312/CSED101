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
	int round = 1; // ¶ó¿îµå ¼ö
	int shared_card1;
	int shared_card2;
	int user_card;
	int computer_card;
	int user_hand, computer_hand; // Ä«µå Á¶ÇÕ
	int user_chips = 50, com_chips = 50; // ÀÜ¿© Ä¨ °³¼ö
	int user_end, com_end;
	int winner = 0; // ½ÂÀÚ ±¸ºÐ
	int con; // °è¼Ó ÁøÇà ¿©ºÎ

	while (1) {
		int num = 0; // »ç¿ëÀÚ¿¡°Ô ÀÔ·Â ¹ÞÀº Çàµ¿°ª
		int user_betting_chips = 1, com_betting_chips = 1; // º£ÆÃÇÑ Ä¨ ¼ö
		int turn = 0; // º£ÆÃ¼ø¼­, Â¦¼ö >> À¯Àú ÅÏ, È¦¼ö >> ÄÄÇ»ÅÍ ÅÏ

		// 2. °ÔÀÓ ¼¼ÆÃ
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
		printf("¦­ %2d Game Starts! ¦­\n", round);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");

		printf("\n Chips remaining:\n");
		printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
		printf("¦­  User        ¦­  %2d  ¦­\n", user_chips);
		printf("¦­  Computer    ¦­  %2d  ¦­\n", com_chips);
		printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦°\n");

		//Ä«µå¼¼ÆÃ
		card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);
		print_card_info(shared_card1, shared_card2, user_card, computer_card);

		user_hand = calc_hand(user_card, shared_card1, shared_card2); // À¯ÀúÄ«µå ÇÑ Àå°ú °øÀ¯Ä«µå µÎ ÀåÀ» ºñ±³
		computer_hand = calc_hand(computer_card, shared_card1, shared_card2); // ÄÄÇ»ÅÍÄ«µå ÇÑ Àå°ú °øÀ¯Ä«µå µÎ ÀåÀ» ºñ±³

		// 3. º£ÆÃ
		while (1) {
			if (user_chips == 1)
				break;
			else if (com_chips == 1)
				break;

			if (winner == 1) { // ÀüÆÇ À¯Àú°¡ ½Â¸®Çß´Ù¸é
				turn++;
			}
			winner = 0;

			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­     Betting    ¦­\n");
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");

			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­  User:  1 ¦­  Com:  1 ¦­\n");
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");

			do {
				user_end = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
				com_end = computer_turn(user_hand, com_chips, &com_betting_chips, user_betting_chips, turn);

				printf("\n¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
				printf("¦­  User: %2d ¦­  Com: %2d ¦­\n", user_betting_chips, com_betting_chips);
				printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");

				turn++;
			} while (user_end > 0 && com_end > 0); // µÑ Áß ÇÏ³ª°¡ Call ¶Ç´Â Fold¸¦ ¼±ÅÃÇÒ ¶§±îÁö º£ÆÃ ÁøÇà

			winner = 0;//½ÂÀÚ ÃÊ±âÈ­
			break;
		}

		// º£ÆÃ Á¾·á
		printf("¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n\n");
		printf("Betting Finished\n\n");
		printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
		printf("¦­    Computer   ¦­         Shared Cards          ¦­      User     ¦­\n");
		printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´\n");
		printf("¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­\n");
		printf("¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­\n");
		printf("¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­\n");
		printf("¦­ ¦­     %2d    ¦­ ¦­ ¦­     %2d    ¦­ ¦­ ¦­     %2d    ¦­ ¦­ ¦­     %2d    ¦­ ¦­\n", computer_card, shared_card1, shared_card2, user_card);
		printf("¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­\n");
		printf("¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­\n");
		printf("¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­\n");
		printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n\n");


		winner = calc_winner(shared_card1, shared_card2, user_card, computer_card);

		if (user_end == -1 || winner == 2) { // À¯Àú°¡ ÆÐ¹èÇÑ °æ¿ì 
			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­   Computer win!   ¦­\n");
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");

			com_chips = com_chips + user_betting_chips;
			user_chips = user_chips - user_betting_chips;
		}
		else { // ÄÄÇ»ÅÍ°¡ ÆÐ¹èÇÑ °æ¿ì
			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­    User Win!   ¦­\n");
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");

			com_chips = com_chips - com_betting_chips;
			user_chips = user_chips + com_betting_chips;
		}

		printf("\n¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
		printf("¦­  User       ¦­  %3d  ¦­\n", user_chips);
		printf("¦­  Computer   ¦­  %3d  ¦­\n", com_chips);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");

		round++;// ¶ó¿îµå ¼ö 1È¸ Ãß°¡

		if (round > 10 || com_chips <= 0 || user_chips <= 0) { // °ÔÀÓ Á¾·á ¹× °á°ú Ãâ·Â
			printf("¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­  User       ¦­  %3d  ¦­\n", user_chips);
			printf("¦­  Computer   ¦­  %3d  ¦­\n", com_chips);
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n\n");

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}

		printf("Proceed or Not? [Go: 1, End: -1]:"); //°ÔÀÓ ÁøÇà ¿©ºÎ È®ÀÎ
		scanf_s("%d", &con);
		if (con == -1) { // °ÔÀÓ Á¾·á ¹× °á°ú Ãâ·Â
			printf("¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
			printf("¦­  User       ¦­  %3d  ¦­\n", user_chips);
			printf("¦­  Computer   ¦­  %3d  ¦­\n", com_chips);
			printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n\n");
			con = 0;

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}
		else if (con == 1) { // °ÔÀÓ °è¼Ó ÁøÇà
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
	printf("\n¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
	printf("¦­    Computer   ¦­         Shared Cards          ¦­      User     ¦­\n");
	printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´\n");
	printf("¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­ ¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯ ¦­\n");
	printf("¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­ ¦­ ¢¼        ¦­ ¦­\n");
	printf("¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­\n");
	printf("¦­ ¦­     %2d    ¦­ ¦­ ¦­     %2d    ¦­ ¦­ ¦­     %2d    ¦­ ¦­ ¦­      ?    ¦­ ¦­\n", computer_card, shared_card1, shared_card2);
	printf("¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­ ¦­           ¦­ ¦­\n");
	printf("¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­ ¦­         ¢¼¦­ ¦­\n");
	printf("¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­ ¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦° ¦­\n");
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n\n");
}

int calc_hand(int card, int shard_card1, int shard_card2)
{
	int i,j;
	int large;

	for (i = 10; i; i--) { //¼¼ ÀåÀÇ Ä«µå Áß ¼ýÀÚ°¡ °¡Àå Å« Ä«µå ¼±º° >> STRAIGHT ¿©ºÎ ÆÇ´Ü¿¡ È°¿ë
		if (i == card) { //Ã¹ ¹øÂ° Ä«µå°¡ °¡Àå Å« °æ¿ì
			large = card;
			j = 1;
			break;
		}
		else if (i == shard_card1) {//µÎ ¹øÂ° Ä«µå°¡ °¡Àå Å« °æ¿ì
			large = shard_card1;
			j = 2;
			break;
		}
		else if (i == shard_card2) {//¼¼ ¹øÂ° Ä«µå°¡ °¡Àå Å« °æ¿ì
			large = shard_card2;
			j = 3;
			break;
		}
	}

	switch (j) { //largeº¸´Ù 1 ÀÛÀº ¼ö, 2 ÀÛÀº ¼ö°¡ ¸ðµÎ ÀÖ´Ù¸é STRAiGHT¶ó°í ÆÇ´Ü(j=4)
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


	if (card == shard_card1 && card == shard_card2 && shard_card1 == shard_card2) //¼¼ ÀåÀÇ Ä«µå°¡ ¸ðµÎ °°À» °æ¿ì >> TRIPLE
		return TRIPLE;

	else if (card == shard_card1 || shard_card1 == shard_card2 || card == shard_card2) //µÎ ÀåÀÇ Ä«µå°¡ °°À» °æ¿ì >> DOUBLE
		return DOUBLE;

	else if (j > 3) // j=4¶ó¸é STRAIGHT¶ó°í ÆÇ´Ü (À§ for, switch¹® ÂüÁ¶)
		return STRAIGHT;

	else //À§ Á¶°Ç¿¡ ÇØ´çµÇÁö ¾Ê´Â´Ù¸é NOPAIR¶ó°í ÆÇ´Ü
		return NOPAIR;

}

int is_valid_num(int a, int b, int num) // num°ªÀÌ À¯È¿ÇÑ °ªÀÎÁö ÆÇ´Ü >> 1ÀÌ¸é À¯È¿
{
	if (a <= num && num <= b)
		return 1;
	else
		return 0;
}

int user_turn(int user_chips, int* user_betting_chips, int betted_chips, int turn)
{
	int select; // Çàµ¿°ª
	int betting; // »õ·Ó°Ô º£ÆÃÇÑ Ä¨

	if (turn % 2 == 0) {
		do {
			printf("USER ¦­ [Call: 1 | Raise: 2 | Fold: 3]: ");
			scanf_s("%d", &select);
			printf("\n");

			if (turn == 0 && select == 1) { //Ã¹ ÅÏ¿¡ callÀ» °ñ¶úÀ» ¶§
				printf("\nUSER ¦­ [Invalid input]\n");
			}
			else if (is_valid_num(1,3,select)) {
				break;
			}
			else { //À¯È¿ÇÏÁö ¾ÊÀº ¼ýÀÚ¸¦ ¼±ÅÃÇßÀ» ¶§
				printf("\nUSER ¦­ [Invalid input]\n");
			}
		} while (1);


		switch (select) {
		case 1:
			if (betted_chips > user_chips) { // º£ÆÃÇÒ Ä¨ÀÌ °¡Áø Ä¨ÀÇ ¼öº¸´Ù ¸¹À» °æ¿ì
				*user_betting_chips = user_chips;
				return 0;
			}
			else { // Call ¼±ÅÃ
				if (betted_chips >= user_chips) { // ÄÄÇ»ÅÍ°¡ º£ÆÃÇÑ Ä¨ÀÌ À¯Àú°¡ °¡Áø Ä¨º¸´Ù ¸¹Àº °æ¿ì
					*user_betting_chips = user_chips;
					return 0;
				}
				*user_betting_chips = betted_chips;
				return 0;
			}
		case 2: // Raise ¼±ÅÃ
			printf("\nUSER ¦­ [Input number of chips for Raise]: ");
			scanf_s("%d", &betting);
			printf("\n");
			*user_betting_chips = *user_betting_chips + betting;

			return *user_betting_chips;
		case 3: // Fold ¼±ÅÃ
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
				if (turn == 1) { // [°æ¿ì1] Ã¹ ÅÏÀÏ °æ¿ì 1°³ Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // º£ÆÃÇÒ Ä¨ÀÌ °¡Áø Ä¨º¸´Ù ¸¹À» °æ¿ì, Call
						*com_betting_chips = com_chips;
						printf("\nCOM ¦­ Call\n");
						return 0;
					}

					printf("\nCOM ¦­ Raise, +1\n");
					return 1;
				}
				else { // Fold ¼±ÅÃ
					printf("\nCOM ¦­ Fold\n");
					return -1;
				}
			}
			else { // Call ¼±ÅÃ
				if (turn == 1) { // [°æ¿ì1] Ã¹ ÅÏÀÏ °æ¿ì 1°³ Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // º£ÆÃÇÒ Ä¨ÀÌ °¡Áø Ä¨º¸´Ù ¸¹À» °æ¿ì, Call
						*com_betting_chips = com_chips;
						printf("\nCOM ¦­ Call\n");
						return 0;
					}

					printf("\nCOM ¦­ Raise, +1\n");
					return 1;
				}

				if (betted_chips >= com_chips) { // CallÀ» Çß´Âµ¥ Ä¨ ¼ö°¡ ¸ðÀÚ¶õ °æ¿ì
					*com_betting_chips = com_chips;
					printf("\nCOM ¦­ Call\n");
					return 0;
				}
				*com_betting_chips = betted_chips;
				printf("\nCOM ¦­ Call\n");
				return 0;
			}
		}

		else {
			if (turn == 1) { // [°æ¿ì2] Ã¹ ÅÏÀÏ °æ¿ì 1°³ Raise
				*com_betting_chips = betted_chips + 1;

				if (*com_betting_chips > com_chips) { // º£ÆÃÇÒ Ä¨ÀÌ °¡Áø Ä¨º¸´Ù ¸¹À» °æ¿ì, Call
					*com_betting_chips = com_chips;
					printf("\nCOM ¦­ Call\n");
					return 0;
				}

				printf("\nCOM ¦­ Raise, +1\n");
				return 1;
			}
			else if (select <= 5) { // Call ¼±ÅÃ
				if (betted_chips >= com_chips) { // CallÀ» Çß´Âµ¥ Ä¨ ¼ö°¡ ¸ðÀÚ¶õ °æ¿ì
					*com_betting_chips = com_chips;
					printf("\nCOM ¦­ Call\n");
					return 0;
				}

				*com_betting_chips = betted_chips;
				printf("\nCOM ¦­ Call\n");

				return 0;
			}
			else{ // Raise ¼±ÅÃ
				betting = rand() % 5 + 1; // »õ·Ó°Ô º£ÆÃÇÑ ¼ö
				*com_betting_chips = betted_chips + betting;

				if (*com_betting_chips > com_chips) { // º£ÆÃÇÒ Ä¨ÀÌ °¡Áø Ä¨º¸´Ù ¸¹À» °æ¿ì, Call
					*com_betting_chips = com_chips;
					printf("\nCOM ¦­ Call\n");
					return 0;
				}

				printf("\nCOM ¦­ Raise, +%d\n", betting);
				return *com_betting_chips;
		}
		}
	}
	return 1;
}

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card)
{
	// À¯Àú°¡ ½Â¸®ÇÑ °æ¿ì 1À», ÄÄÇ»ÅÍ°¡ ½Â¸®ÇÑ °æ¿ì 2¸¦ ¹ÝÈ¯
	int user = calc_hand(user_card, shared_card1, shared_card2);
	int com = calc_hand(computer_card, shared_card1, shared_card2);

	if (user > com) {
		return 1;
	}
	else if (user < com){
		return 2;
	}
	else {
		// ÇÚµå°¡ °°Àº °æ¿ì
		if (user_card > computer_card) {
			return 1;
		}
		else if (user_card < computer_card) {
			return 2;
		}
		// °³ÀÎ Ä«µåÀÇ ¼ýÀÚ°¡ °°Àº °æ¿ì
		else {
			return 1;
		}
	}
}
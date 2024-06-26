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
	int round = 1; // 塭遴萄 熱
	int shared_card1;
	int shared_card2;
	int user_card;
	int computer_card;
	int user_hand, computer_hand; // 蘋萄 褻м
	int user_chips = 50, com_chips = 50; // 濤罹 蘑 偃熱
	int user_end, com_end;
	int winner = 0; // 蝓濠 掘碟
	int con; // 啗樓 霞ч 罹睡

	while (1) {
		int num = 0; // 餌辨濠縑啪 殮溘 嫡擎 ч翕高
		int user_betting_chips = 1, com_betting_chips = 1; // 漆たи 蘑 熱
		int turn = 0; // 漆た牖憮, 礎熱 >> 嶸盪 欐, �汝� >> 闡У攪 欐

		// 2. 啪歜 撮た
		printf("忙式式式式式式式式式式式式式式式式式忖\n");
		printf("早 %2d Game Starts! 早\n", round);
		printf("戌式式式式式式式式式式式式式式式式式戎\n");

		printf("\n Chips remaining:\n");
		printf("旨收收收收收收收收收收收收收收有收收收收收收旬\n");
		printf("早  User        早  %2d  早\n", user_chips);
		printf("早  Computer    早  %2d  早\n", com_chips);
		printf("曲收收收收收收收收收收收收收收朴收收收收收收旭\n");

		//蘋萄撮た
		card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);
		print_card_info(shared_card1, shared_card2, user_card, computer_card);

		user_hand = calc_hand(user_card, shared_card1, shared_card2); // 嶸盪蘋萄 и 濰婁 奢嶸蘋萄 舒 濰擊 綠掖
		computer_hand = calc_hand(computer_card, shared_card1, shared_card2); // 闡У攪蘋萄 и 濰婁 奢嶸蘋萄 舒 濰擊 綠掖

		// 3. 漆た
		while (1) {
			if (user_chips == 1)
				break;
			else if (com_chips == 1)
				break;

			if (winner == 1) { // 瞪っ 嶸盪陛 蝓葬ц棻賊
				turn++;
			}
			winner = 0;

			printf("忙式式式式式式式式式式式式式式式式忖\n");
			printf("早     Betting    早\n");
			printf("戌式式式式式式式式式式式式式式式式戎\n");

			printf("忙式式式式式式式式式式式式式式式式式式式式式式忖\n");
			printf("早  User:  1 早  Com:  1 早\n");
			printf("戌式式式式式式式式式式式式式式式式式式式式式式戎\n\n");

			do {
				user_end = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
				com_end = computer_turn(user_hand, com_chips, &com_betting_chips, user_betting_chips, turn);

				printf("\n忙式式式式式式式式式式式式式式式式式式式式式式忖\n");
				printf("早  User: %2d 早  Com: %2d 早\n", user_betting_chips, com_betting_chips);
				printf("戌式式式式式式式式式式式式式式式式式式式式式式戎\n\n");

				turn++;
			} while (user_end > 0 && com_end > 0); // 萃 醞 ж釭陛 Call 傳朝 Fold蒂 摹鷗й 陽梱雖 漆た 霞ч

			winner = 0;//蝓濠 蟾晦��
			break;
		}

		// 漆た 謙猿
		printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n\n");
		printf("Betting Finished\n\n");
		printf("旨收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
		printf("早    Computer   早         Shared Cards          早      User     早\n");
		printf("曳收收收收收收收收收收收收收收收朱收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收朱收收收收收收收收收收收收收收收朽\n");
		printf("早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早\n");
		printf("早 早 Ⅳ        早 早 早 Ⅳ        早 早 早 Ⅳ        早 早 早 Ⅳ        早 早\n");
		printf("早 早           早 早 早           早 早 早           早 早 早           早 早\n");
		printf("早 早     %2d    早 早 早     %2d    早 早 早     %2d    早 早 早     %2d    早 早\n", computer_card, shared_card1, shared_card2, user_card);
		printf("早 早           早 早 早           早 早 早           早 早 早           早 早\n");
		printf("早 早         Ⅳ早 早 早         Ⅳ早 早 早         Ⅳ早 早 早         Ⅳ早 早\n");
		printf("早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早\n");
		printf("曲收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收旭\n\n");


		winner = calc_winner(shared_card1, shared_card2, user_card, computer_card);

		if (user_end == -1 || winner == 2) { // 嶸盪陛 ぬ寡и 唳辦 
			printf("忙式式式式式式式式式式式式式式式式式式式忖\n");
			printf("早   Computer win!   早\n");
			printf("戌式式式式式式式式式式式式式式式式式式式戎\n");

			com_chips = com_chips + user_betting_chips;
			user_chips = user_chips - user_betting_chips;
		}
		else { // 闡У攪陛 ぬ寡и 唳辦
			printf("忙式式式式式式式式式式式式式式式式忖\n");
			printf("早    User Win!   早\n");
			printf("戌式式式式式式式式式式式式式式式式戎\n");

			com_chips = com_chips - com_betting_chips;
			user_chips = user_chips + com_betting_chips;
		}

		printf("\n忙式式式式式式式式式式式式式式式式式式式式式忖\n");
		printf("早  User       早  %3d  早\n", user_chips);
		printf("早  Computer   早  %3d  早\n", com_chips);
		printf("戌式式式式式式式式式式式式式式式式式式式式式戎\n\n");

		round++;// 塭遴萄 熱 1�� 蹺陛

		if (round > 10 || com_chips <= 0 || user_chips <= 0) { // 啪歜 謙猿 塽 唸婁 轎溘
			printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("忙式式式式式式式式式式式式式式式式式式式式式忖\n");
			printf("早  User       早  %3d  早\n", user_chips);
			printf("早  Computer   早  %3d  早\n", com_chips);
			printf("戌式式式式式式式式式式式式式式式式式式式式式戎\n\n\n");

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}

		printf("Proceed or Not? [Go: 1, End: -1]:"); //啪歜 霞ч 罹睡 �挫�
		scanf_s("%d", &con);
		if (con == -1) { // 啪歜 謙猿 塽 唸婁 轎溘
			printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n\n");
			printf("Number of Games: %d\n", round - 1);
			printf("Chips remaining:\n");
			printf("忙式式式式式式式式式式式式式式式式式式式式式忖\n");
			printf("早  User       早  %3d  早\n", user_chips);
			printf("早  Computer   早  %3d  早\n", com_chips);
			printf("戌式式式式式式式式式式式式式式式式式式式式式戎\n\n\n");
			con = 0;

			if (user_chips > com_chips) {
				printf("User Win!\n");
			}
			else {
				printf("Computer Win!\n");
			}
			break;
		}
		else if (con == 1) { // 啪歜 啗樓 霞ч
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
	printf("\n旨收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早    Computer   早         Shared Cards          早      User     早\n");
	printf("曳收收收收收收收收收收收收收收收朱收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收朱收收收收收收收收收收收收收收收朽\n");
	printf("早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早 旨收收收收收收收收收收收旬 早\n");
	printf("早 早 Ⅳ        早 早 早 Ⅳ        早 早 早 Ⅳ        早 早 早 Ⅳ        早 早\n");
	printf("早 早           早 早 早           早 早 早           早 早 早           早 早\n");
	printf("早 早     %2d    早 早 早     %2d    早 早 早     %2d    早 早 早      ?    早 早\n", computer_card, shared_card1, shared_card2);
	printf("早 早           早 早 早           早 早 早           早 早 早           早 早\n");
	printf("早 早         Ⅳ早 早 早         Ⅳ早 早 早         Ⅳ早 早 早         Ⅳ早 早\n");
	printf("早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早 曲收收收收收收收收收收收旭 早\n");
	printf("曲收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收收旭\n\n");
}

int calc_hand(int card, int shard_card1, int shard_card2)
{
	int i,j;
	int large;

	for (i = 10; i; i--) { //撮 濰曖 蘋萄 醞 璋濠陛 陛濰 贖 蘋萄 摹滌 >> STRAIGHT 罹睡 っ欽縑 �倏�
		if (i == card) { //羅 廓簞 蘋萄陛 陛濰 贖 唳辦
			large = card;
			j = 1;
			break;
		}
		else if (i == shard_card1) {//舒 廓簞 蘋萄陛 陛濰 贖 唳辦
			large = shard_card1;
			j = 2;
			break;
		}
		else if (i == shard_card2) {//撮 廓簞 蘋萄陛 陛濰 贖 唳辦
			large = shard_card2;
			j = 3;
			break;
		}
	}

	switch (j) { //large爾棻 1 濛擎 熱, 2 濛擎 熱陛 賅舒 氈棻賊 STRAiGHT塭堅 っ欽(j=4)
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


	if (card == shard_card1 && card == shard_card2 && shard_card1 == shard_card2) //撮 濰曖 蘋萄陛 賅舒 偽擊 唳辦 >> TRIPLE
		return TRIPLE;

	else if (card == shard_card1 || shard_card1 == shard_card2 || card == shard_card2) //舒 濰曖 蘋萄陛 偽擊 唳辦 >> DOUBLE
		return DOUBLE;

	else if (j > 3) // j=4塭賊 STRAIGHT塭堅 っ欽 (嬪 for, switch僥 霤褻)
		return STRAIGHT;

	else //嬪 褻勒縑 п渡腎雖 彊朝棻賊 NOPAIR塭堅 っ欽
		return NOPAIR;

}

int is_valid_num(int a, int b, int num) // num高檜 嶸�褲� 高檣雖 っ欽 >> 1檜賊 嶸��
{
	if (a <= num && num <= b)
		return 1;
	else
		return 0;
}

int user_turn(int user_chips, int* user_betting_chips, int betted_chips, int turn)
{
	int select; // ч翕高
	int betting; // 億照啪 漆たи 蘑

	if (turn % 2 == 0) {
		do {
			printf("USER 早 [Call: 1 | Raise: 2 | Fold: 3]: ");
			scanf_s("%d", &select);
			printf("\n");

			if (turn == 0 && select == 1) { //羅 欐縑 call擊 埤嫉擊 陽
				printf("\nUSER 早 [Invalid input]\n");
			}
			else if (is_valid_num(1,3,select)) {
				break;
			}
			else { //嶸�褲狫� 彊擎 璋濠蒂 摹鷗ц擊 陽
				printf("\nUSER 早 [Invalid input]\n");
			}
		} while (1);


		switch (select) {
		case 1:
			if (betted_chips > user_chips) { // 漆たй 蘑檜 陛霞 蘑曖 熱爾棻 號擊 唳辦
				*user_betting_chips = user_chips;
				return 0;
			}
			else { // Call 摹鷗
				if (betted_chips >= user_chips) { // 闡У攪陛 漆たи 蘑檜 嶸盪陛 陛霞 蘑爾棻 號擎 唳辦
					*user_betting_chips = user_chips;
					return 0;
				}
				*user_betting_chips = betted_chips;
				return 0;
			}
		case 2: // Raise 摹鷗
			printf("\nUSER 早 [Input number of chips for Raise]: ");
			scanf_s("%d", &betting);
			printf("\n");
			*user_betting_chips = *user_betting_chips + betting;

			return *user_betting_chips;
		case 3: // Fold 摹鷗
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
				if (turn == 1) { // [唳辦1] 羅 欐橾 唳辦 1偃 Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // 漆たй 蘑檜 陛霞 蘑爾棻 號擊 唳辦, Call
						*com_betting_chips = com_chips;
						printf("\nCOM 早 Call\n");
						return 0;
					}

					printf("\nCOM 早 Raise, +1\n");
					return 1;
				}
				else { // Fold 摹鷗
					printf("\nCOM 早 Fold\n");
					return -1;
				}
			}
			else { // Call 摹鷗
				if (turn == 1) { // [唳辦1] 羅 欐橾 唳辦 1偃 Raise
					*com_betting_chips = betted_chips + 1;

					if (*com_betting_chips > com_chips) { // 漆たй 蘑檜 陛霞 蘑爾棻 號擊 唳辦, Call
						*com_betting_chips = com_chips;
						printf("\nCOM 早 Call\n");
						return 0;
					}

					printf("\nCOM 早 Raise, +1\n");
					return 1;
				}

				if (betted_chips >= com_chips) { // Call擊 ц朝等 蘑 熱陛 賅濠塢 唳辦
					*com_betting_chips = com_chips;
					printf("\nCOM 早 Call\n");
					return 0;
				}
				*com_betting_chips = betted_chips;
				printf("\nCOM 早 Call\n");
				return 0;
			}
		}

		else {
			if (turn == 1) { // [唳辦2] 羅 欐橾 唳辦 1偃 Raise
				*com_betting_chips = betted_chips + 1;

				if (*com_betting_chips > com_chips) { // 漆たй 蘑檜 陛霞 蘑爾棻 號擊 唳辦, Call
					*com_betting_chips = com_chips;
					printf("\nCOM 早 Call\n");
					return 0;
				}

				printf("\nCOM 早 Raise, +1\n");
				return 1;
			}
			else if (select <= 5) { // Call 摹鷗
				if (betted_chips >= com_chips) { // Call擊 ц朝等 蘑 熱陛 賅濠塢 唳辦
					*com_betting_chips = com_chips;
					printf("\nCOM 早 Call\n");
					return 0;
				}

				*com_betting_chips = betted_chips;
				printf("\nCOM 早 Call\n");

				return 0;
			}
			else{ // Raise 摹鷗
				betting = rand() % 5 + 1; // 億照啪 漆たи 熱
				*com_betting_chips = betted_chips + betting;

				if (*com_betting_chips > com_chips) { // 漆たй 蘑檜 陛霞 蘑爾棻 號擊 唳辦, Call
					*com_betting_chips = com_chips;
					printf("\nCOM 早 Call\n");
					return 0;
				}

				printf("\nCOM 早 Raise, +%d\n", betting);
				return *com_betting_chips;
		}
		}
	}
	return 1;
}

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card)
{
	// 嶸盪陛 蝓葬и 唳辦 1擊, 闡У攪陛 蝓葬и 唳辦 2蒂 奩��
	int user = calc_hand(user_card, shared_card1, shared_card2);
	int com = calc_hand(computer_card, shared_card1, shared_card2);

	if (user > com) {
		return 1;
	}
	else if (user < com){
		return 2;
	}
	else {
		// с萄陛 偽擎 唳辦
		if (user_card > computer_card) {
			return 1;
		}
		else if (user_card < computer_card) {
			return 2;
		}
		// 偃檣 蘋萄曖 璋濠陛 偽擎 唳辦
		else {
			return 1;
		}
	}
}
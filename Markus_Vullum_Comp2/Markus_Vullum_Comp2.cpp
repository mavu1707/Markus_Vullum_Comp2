#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <vector>

struct Player {
	std::string userName = "";
	unsigned int score = 0;
	unsigned int hand = 0;
	unsigned int bet = 0;
};

void menu(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount, int PlayerCardCount, int x, Player users[]);
void gameComputer(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount, int PlayerCardCount, int x, Player users[]);
void scores(int x, Player users[]);
void shuffle(bool CardDealt[]);
void displayCard(int Card);
void displayHand(int Hand[], const int CardCount);
void displayScoresAndHands(int HouseHand[], const int HouseCardCount, int PlayerHand[], const int  PlayerCardCount);
int nextCard(bool CardsDealt[]);
int scoreHand(int Hand[], const int CardCount);

//******************************
//                             *
//			Main()             *
//                             *
//******************************
int main() {

	time_t qTime;
	time(&qTime);
	srand(qTime);

	int count = 0;
	bool CardsDealt[52];
	int HouseCardCount = 0;
	int HouseHand[12];
	int PlayerCardCount = 0;
	int PlayerHand[12];
	int x = 0;
	const int PLAYERS = 3;
	Player users[PLAYERS];

	menu(CardsDealt, HouseHand, PlayerHand, HouseCardCount, PlayerCardCount, x, users);

	system("pause");
	return 0;
}

//******************************
//                             *
//   Intro to play the game    *
//                             *
//******************************
void menu(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount, int PlayerCardCount, int x, Player users[])
{
	std::cout << "\n\n";
	std::cout << "\\$$                        $$/ / $$$$$$$$$$|  | $$           /$$$$$$$$$     /$$$$$$$$$$\\    |$$$$\\     /$$$$  / $$$$$$$$$$|\n";
	std::cout << " \\$$                      $$/  |  $$_______/  | $$          / $$____  $$   | $$       $$|   |$$ $$\\   /$$ $$| |  $$_______/\n";
	std::cout << "  \\$$                    $$/   |  $$          | $$         | $$      \\__/  | $$       $$|   |$$   $$$$$   $$| |  \n";
	std::cout << "   \\$$                  $$/    |  $$$$$$$|    | $$         | $$            | $$       $$|   |$$    $$     $$| |  $$$$$$$|\n";
	std::cout << "    \\$$     $$$$$$     $$/     |  $$_____/    | $$         | $$            | $$       $$|   |$$           $$| |  $$_____/\n";
	std::cout << "     \\$$   $$/  \\$$   $$/      |  $$          | $$         | $$       $$   | $$       $$|   |$$           $$| |   \n";
	std::cout << "      \\$$$$$/    \\$$$$$/       |  $$$$$$$$$|  | $$$$$$$$$| | $$$$$$$$$$/   | $$$$$$$$$$$|   |$$           $$| |  $$$$$$$$$\n";
	std::cout << "       \\___/      \\___/        |__________/   |__________/  \\__________/    \\__________/    |__|         |__| |__________/\n";
	std::cout << "\n\n\n";

	std::cout << "                                                |$$$$$$$$|  /$$$$$$$$\\\n";
	std::cout << "                                                   |$$|    |$$      $$|\n";
	std::cout << "                                                   |$$|    |$$      $$|\n";
	std::cout << "                                                   |$$|    |$$      $$|\n";
	std::cout << "                                                   |$$|     \\$$$$$$$$/\n";

	std::cout << "\n\n\n";
	std::cout << "            /$$$$$$$   /$$        /$$$$$$    /$$$$$$    /$$   /$$    /$$$$$   /$$$$$$    /$$$$$$   /$$   /$$\n";
	std::cout << "           | $$__  $$ | $$       / $$__  $  / $$__  $$ | $$  /$$/   |__  $$  / $$__ $$  / $$__  $$| $$  /$$/\n";
	std::cout << "           | $$   \\$$ | $$      | $$   \\ $$| $$   \\__/ | $$  $$/       | $$ | $$   \\ $$| $$   \\__/| $$ /$$/\n";
	std::cout << "           | $$$$$$$$ | $$      | $$$$$$$$ | $$        | $$$$$/        | $$ | $$$$$$$$ | $$       | $$$$$/ \n";
	std::cout << "           | $$__  $$ | $$      | $$__  $$ | $$        | $$  $$    $$  | $$ | $$__  $$ | $$       | $$  $$\n";
	std::cout << "           | $$   \\$$ | $$      | $$  | $$ | $$    $$  | $$\  $$  | $$  | $$ | $$  | $$ |  $$    $$| $$   $$\n";
	std::cout << "           | $$$$$$$/ | $$$$$$$$| $$  | $$ | $$$$$$ /  | $$ \  $$ | $$$$$$$/ | $$  | $$ |  $$$$$$/ | $$    $$\n";
	std::cout << "           | ______/  |________/|__/  |__ / \\______/   |__ / __/  \\______/  |__/  |__ / \\______/  |__ /  __/\n";


	std::cout << "\n\n";
	std::cout << "Please press ENTER to start the game " << std::endl;
	std::cin.get();

	for (int a = 1; a < 8; a++)
	{
		std::cout << "*";
		Sleep(500);
	}
	system("cls");
	gameComputer(CardsDealt, HouseHand, PlayerHand, HouseCardCount, PlayerCardCount, x, users);

}

//******************************
//                             *
//			Game PC            *
//                             *
//******************************
void gameComputer(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount, int PlayerCardCount, int x, Player users[])
{
	bool playAgain = true;
	char choice;
	int bets;
	int playerMoney = 100;

	while (playAgain == true) {

		shuffle(CardsDealt);

		PlayerHand[0] = nextCard(CardsDealt);
		HouseHand[0] = nextCard(CardsDealt);
		PlayerHand[1] = nextCard(CardsDealt);
		HouseHand[1] = nextCard(CardsDealt);
		HouseCardCount = 2;
		PlayerCardCount = 2;

		char PlayerChoice;
		bool PlayerHits = true;
		int PlayerScore = scoreHand(PlayerHand, PlayerCardCount);

		std::cout << "You have: " << playerMoney << " to your disposal" << std::endl;
		std::cout << "Place your bets!" << std::endl;
		std::cout << "Bet: ";
		std::cin >> bets;
		system("cls");



		system("cls");

		do {
			std::cout << "House's hand" << std::endl;
			std::cout << " ** ";
			displayCard(HouseHand[1]);
			std::cout << std::endl;
			std::cout << "\n\nPlayer's hand: Score = " << scoreHand(PlayerHand, PlayerCardCount) << std::endl;
			displayHand(PlayerHand, PlayerCardCount);

			if (users[x].score > users[x].bet) {
				std::cout << "\n\nHit(h) or Stay(s): ";
				std::cin >> PlayerChoice;
			}
			else {
				std::cout << "\n\nHit(h) or Stay(s): ";
				std::cin >> PlayerChoice;
			}
			if (PlayerChoice == 'h') {
				PlayerHand[PlayerCardCount] = nextCard(CardsDealt);
				++PlayerCardCount;
			}
			else if (PlayerChoice == 's') {
				PlayerHits = false;
				displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
			}
			else {
				std::cout << "Error, please try again" << std::endl;
			}
			PlayerScore = scoreHand(PlayerHand, PlayerCardCount);



			if (PlayerScore > 21) {
				system("cls");
				scores(x, users);
				std::cout << "House Wins!" << std::endl;
				std::cout << "You lost " << bets << std::endl;
				std::cout << "You have: " << playerMoney - bets << std::endl;
				displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
			}
			else {
				int HouseScore = scoreHand(HouseHand, HouseCardCount);
				while (HouseScore < 17) {
					HouseHand[HouseCardCount] = nextCard(CardsDealt);
					++HouseCardCount;
					HouseScore = scoreHand(HouseHand, HouseCardCount);
				}

				bool HouseBusts = (HouseScore > 21);
				if (HouseBusts) {
					system("cls");
					scores(x, users);
					std::cout << "You win!" << std::endl;
					bets = bets * 2;
					std::cout << "You've won: " << bets << std::endl;
					std::cout << "You have: " << playerMoney + bets << std::endl;
					displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
				}
			}



		} while (PlayerHits && PlayerScore < 22);

		//system("pause");
		std::cout << "\n\nDo you want to play again? yes(y) or no(n)" << std::endl;
		std::cin >> choice;
		system("cls");

		if (choice == 'n') {
			playAgain = false;
		}
		else {
			playAgain = true;
			system("cls");
		}
	}

}

//******************************
//                             *
//			Shuffle            *
//                             *
//******************************
void shuffle(bool CardsDealt[])
{
	for (int Index = 0; Index < 52; ++Index) {
		CardsDealt[Index] = false;
	}
}

//******************************
//                             *
//			 Cards             *
//                             *
//******************************
void displayCard(int Card) {

	const int Rank = (Card % 13);

	if (Rank == 0) {
		std::cout << "ACE of ";
	}
	else if (Rank < 9) {
		std::cout << (Rank + 1);
	}
	else if (Rank == 9) {
		std::cout << "TEN of ";
	}
	else if (Rank == 10) {
		std::cout << "JACK of ";
	}
	else if (Rank == 11) {
		std::cout << "QUEEN of ";
	}
	else {
		std::cout << "KING of ";
	}

	const int Suit = (Card / 13);

	if (Suit == 0) {
		std::cout << "Clubs";
	}
	else if (Suit == 1) {
		std::cout << "Diamonds";
	}
	else if (Suit == 2) {
		std::cout << "Hearts";
	}
	else {
		std::cout << "Spades";
	}
}

//******************************
//                             *
//      Display the hand       *
//                             *
//******************************
void displayHand(int Hand[], const int CardCount)
{
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		displayCard(NextCard);
		std::cout << " ";
	}

}

//******************************
//                             *
//         Next card           *
//                             *
//******************************
int nextCard(bool CardsDealt[])
{
	bool CardDealt = true;
	int NewCard = -1;
	do {
		NewCard = (rand() % 52);
		if (!CardsDealt[NewCard]) {
			CardDealt = false;
			CardsDealt[NewCard] = true;
		}
	} while (CardDealt);
	return NewCard;
}

//******************************
//                             *
//         Score hand          *
//                             *
//******************************
int scoreHand(int Hand[], const int CardCount)
{
	int AceCount = 0;
	int Score = 0;
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		const int Rank = (NextCard % 13);
		if (Rank == 0) {
			++AceCount;
			++Score;
		}
		else if (Rank < 9) {
			Score = Score + (Rank + 1);
		}
		else {
			Score = Score + 10;
		}

	}
	while (AceCount > 0 && Score < 12) {
		--AceCount;
		Score = Score + 10;
	}
	return Score;
}

//******************************
//                             *
//  Display scores and hands   *
//                             *
//******************************
void displayScoresAndHands(int HouseHand[], const int HouseCardCount, int PlayerHand[], int PlayerCardCount)
{
	std::cout << "Houses's Hand: Score = " << scoreHand(HouseHand, HouseCardCount) << std::endl;
	std::cout << "Player's Hand: Score = " << scoreHand(PlayerHand, PlayerCardCount) << std::endl;
	displayHand(PlayerHand, PlayerCardCount);

}

void scores(int x, Player users[])
{

}
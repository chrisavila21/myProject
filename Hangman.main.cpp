//*****************
//Program Name:
//Author: Chris Avila
//        Patrick DeMers
//        Nathan Jaggers
//IDE Used: cloud9 , Visual studio, code blocks
//Cloud9 username: nathanj8
//Cloud9 workspace name: happy_fun_coding_time
//Cloud9 folder: 
//Cloud9 C++ file: 
//******************************************************************************
#include "Design.cpp"
#include "Player.cpp"
#include "PlayerLinkedList.cpp"
using namespace std;

//Function Prototypes    
void welcome();
void goodbye();
char YorN(char&);


int main()
{
	//declarations
	char repeat, samePlayer, letter; //repeat, samePlayer - holds decision, letter - holds guess letter

	string firstPlayer, newPlayer, currentPlayer, guesses, wordToGuess;

	int tries = 0;
	bool win = false;
	srand(time(0));

	Design game;
	PlayerList PlayerRecords; // keeps track of players and their stats
//welcome
	welcome();

	//set first player
	cout << "Please enter the name of the first Player : ";
	getline(cin, firstPlayer);
	PlayerRecords.insertNode(firstPlayer);
	currentPlayer = firstPlayer;
	//cin.ignore() ;    Troubleshooting

//game
	do
	{
		//Game reset
		tries = 0;
		guesses = "";
		win = false;

		wordToGuess = game.LoadRandomWord("BigWordFile.txt");
		if (wordToGuess == "-1")
		{
			cin.get();
			return -1;
		}
		do
		{
			//initiate game
			game.PrintMessage("Hangman");
			game.DrawHangman(tries);
			game.PrintAvailableLetters(guesses);
			game.PrintMessage("Guess the word");
			win = game.PrintWordAndCheckWin(wordToGuess, guesses);

			if (win)
				break;

			cout << "guess a letter >> "; cin >> letter;

			if (guesses.find(letter) == string::npos)
				guesses += letter;

			tries = game.TriesLeft(wordToGuess, guesses);

		} while (tries < 10);

		//increment games played
		PlayerRecords.incrementGamesPlayed(currentPlayer);
		//results
		if (win)
		{
			game.PrintMessage("YOU WON!");
			PlayerRecords.incrementWins(currentPlayer);
		}
		else
		{
			game.PrintMessage("GAME OVER");
			PlayerRecords.incrementLosses(currentPlayer);

			cout << "\nThe word was : " << wordToGuess << endl << endl;

		}
		
		PlayerRecords.displayPlayer(currentPlayer);

		//play again? same player?
		cout << "\n***************************************************************"
			<< "\nWould you like to play again? (Y/N) --> : ";
		YorN(repeat);
		if (repeat == 'Y')
		{
			cout << "Same player? (Y/N) : ";
			YorN(samePlayer);
			if (samePlayer == 'N')
			{
				cout << "\nEnter name of new Player : ";
				getline(cin, newPlayer);

				PlayerRecords.insertNode(newPlayer);
				currentPlayer = newPlayer;
			}
		}
		cout << "***************************************************************\n";

	} while (repeat == 'Y');

	//goodbye
	cout << "\n"
		<< "***************************************************************"
		<< "\nHere are the stats of the players for this session : \n\n";
	PlayerRecords.displayAllPlayers();

	goodbye();
	return 0;
}
void welcome()
{
	cout << "Hello and Welcome to \"Hangman\"!\n"
		<< "This is a hangman program where you can test your knowlege on words!\n"
		<< "First you will be asked to make a player profile by entering a player name.\n"
		<< "Then you are free to play the game to your hearts content. At the end \n"
		<< "of each game you will be asked two questions. You will first be asked if \n"
		<< "you want to play again. If you choose no, next you will be asked if a \n"
		<< "new player would like to play. If there is a new player they will be able\n"
		<< "to create a player profile as well. Once everyone is finished with the \n"
		<< "program, you can end the program by resonding \"N\" to the two prompts \n"
		<< "at the end of the game.\n"
		<< "At the end of the program, all player stats will be printed.\n"
		<< "Have fun!\n\n"
		<< "***************************************************************"
		<< "\n\n";
}
void goodbye()
{
	cout << "***************************************************************"
		<< "\n\n"
		<< "Thank you for using our program and have a great day!\n";
	cin.get();
}
char YorN(char& tchoice)
{
	cin >> tchoice;
	tchoice = toupper(tchoice);
	while (tchoice != 'Y' and tchoice != 'N')
	{
		cout << "Error! : Y or N only --> :";
		cin >> tchoice;
		tchoice = toupper(tchoice);
	}
	cin.ignore();
	return tchoice;
}



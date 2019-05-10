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
#include <iostream>
#include <string>       
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

//Design Declaration
class Design
{
public:

	int TriesLeft(string word, string guessed);
	string LoadRandomWord(string path);
	void PrintAvailableLetters(string taken);
	void PrintMessage(string, bool, bool);
	void DrawHangman(int g);
	void PrintLetters(string input, char from, char to);
	bool PrintWordAndCheckWin(string word, string guessed);

};

//Design Class definitions
void Design::PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
	if (printTop)
	{
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}
	bool front = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}
	cout << message.c_str();

	if (printBottom)
	{
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}
void Design::DrawHangman(int guessCount = 0)
{
	if (guessCount >= 1)
		PrintMessage("|", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount >= 2)
		PrintMessage("|", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount >= 3)
		PrintMessage("O", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount == 4)
		PrintMessage("/  ", false, false);

	if (guessCount == 5)
		PrintMessage("/| ", false, false);

	if (guessCount >= 6)
		PrintMessage("/|\\", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount >= 7)
		PrintMessage("|", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount == 8)
		PrintMessage("/  ", false, false);

	if (guessCount >= 9)
		PrintMessage("/ \\", false, false);
	else
		PrintMessage("", false, false);
}
void Design::PrintLetters(string input, char from, char to)
{
	//takes input string and makes all char uppercase
	for (int i = 0; i < input.length(); i++)
	{
		input[i] = toupper(input[i]);
	}
	//prints string
	string s;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i) == string::npos)
		{
			s += i;
			s += " ";
		}
		else
			s += "  ";
	}
	PrintMessage(s, false, false);
}
void Design::PrintAvailableLetters(string taken)
{
	PrintMessage("Available letters");
	PrintLetters(taken, 'A', 'M');
	PrintLetters(taken, 'N', 'Z');
}
bool Design::PrintWordAndCheckWin(string word, string guessed)
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	PrintMessage(s, false);
	return won;
}
string Design::LoadRandomWord(string path)
{
	int lineCount = 0;
	string word;
	vector<string> v;

	//get random word from external file
	ifstream reader(path);
	if (reader.is_open())
	{
		while (std::getline(reader, word))
			v.push_back(word);

		int randomLine = rand() % v.size();

		word = v.at(randomLine);
		reader.close();
	}
	else
	{
		cout << "There was an error opening the file.\n"
			<< "Please check the name sent to LoadRandomWord and try again\n";
		return "-1";
	}

	return word;
}
int Design::TriesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
			error++;
	}
	return error;
}


//Player and PlayerList Class Declarations
class Player
{
private:
	string playerName;
	int gamesPlayed;
	int gamesWon;
	int gamesLost;

public:
	//Mutator Functions
	void setPlayerName(string);    // set player name
	void addGamesPlayed();         // update games played
	void addWins();                // update wins
	void addLosses();              // update losses

	//Accessor 
	string getPlayerName();
	int getWins();
	int getLosses();
	int getGamesPlayed();
	int getWinRate();
	void getAll();

	Player() :Player("{Empty}")
	{ }
	Player(string pName)
	{
		playerName = pName;
		gamesPlayed = 0;
		gamesWon = 0;
		gamesLost = 0;
	}

	~Player() {}

};
class PlayerList
{
private:
	struct PlayerNode
	{
		Player pInfo;
		PlayerNode *next;
	};

	PlayerNode *head;

public:
	//Mutators
	void insertNode(string);
	void incrementWins(string);
	void incrementLosses(string);
	void incrementGamesPlayed(string);

	//Accessors
	void displayPlayer(string);
	void displayAllPlayers();


	//Constructor 
	PlayerList()
	{
		head = nullptr;
	}




};

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

			cout << "\nThe word was : " << wordToGuess;
		}
		getchar();

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


//Player Class
//Mutator Functions
void Player::setPlayerName(string pName)
{
	playerName = pName;
}
void Player::addGamesPlayed()
{
	gamesPlayed++;
}
void Player::addWins()
{
	gamesWon++;
}
void Player::addLosses()
{
	gamesLost++;
}

//Accessor 
string Player::getPlayerName()
{
	return playerName;
}
int Player::getWins()
{
	return gamesWon;
}
int Player::getLosses()
{
	return gamesLost;
}
int Player::getGamesPlayed()
{
	return gamesPlayed;
}
int Player::getWinRate()
{
	float wins, games;
	wins = getWins();
	games = getGamesPlayed();

	if (wins == 0)
	{
		return 0;
	}
	else
	{
		return (wins / games) * 100;
	}
}
void Player::getAll()
{
	cout << "Player : " << playerName
		<< "\nTotal games played : " << gamesPlayed << "\tGames Won: " << gamesWon << "\tGames Lost:" << gamesLost
		<< "\nYour win rate is : " << getWinRate() << "%\n";
}

//PlayerList Class    
//Mutators
void PlayerList::insertNode(string tempPName)
{
	//declarations
	PlayerNode *insNode;
	PlayerNode *nodePtr;
	PlayerNode *previousNode = nullptr;

	// Allocate a new node and store num there.
	insNode = new PlayerNode;
	insNode->pInfo.setPlayerName(tempPName);

	// If there are no nodes in the list
	// make insNode the first node
	// cout << head << endl ;
	if (!head)
	{
		head = insNode;
		insNode->next = nullptr;
		//insNode.cInfo.getAll();
	}
	else // Otherwise, insert insNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose value is less than num.
		while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() < insNode->pInfo.getPlayerName())
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr)
		{
			head = insNode;
			insNode->next = nodePtr;
		}
		else // Otherwise insert after the previous node.
		{
			previousNode->next = insNode;
			insNode->next = nodePtr;
		}
	}


}
void PlayerList::incrementWins(string findName)
{
	PlayerNode *nodePtr;        // To traverse the list
	PlayerNode *previousNode;   // To point to the previous node

// If the list is empty, do nothing.
	if (!head)
	{
		cout << "No players : List is empty \n";
		return;
	}

	// Determine if the first node is the one.
	if (head->pInfo.getPlayerName() == findName)
	{
		head->pInfo.addWins();
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is
		// not equal.
		while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() != findName)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			nodePtr->pInfo.addWins();
		}
	}
}
void PlayerList::incrementLosses(string findName)
{
	PlayerNode *nodePtr;        // To traverse the list
	PlayerNode *previousNode;   // To point to the previous node

// If the list is empty, do nothing.
	if (!head)
	{
		cout << "No players : List is empty \n";
		return;
	}

	// Determine if the first node is the one.
	if (head->pInfo.getPlayerName() == findName)
	{
		head->pInfo.addLosses();
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is
		// not equal.
		while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() != findName)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			nodePtr->pInfo.addLosses();
		}
	}
}
void PlayerList::incrementGamesPlayed(string findName)
{
	PlayerNode *nodePtr;        // To traverse the list
	PlayerNode *previousNode;   // To point to the previous node

// If the list is empty, do nothing.
	if (!head)
	{
		cout << "No players : List is empty \n";
		return;
	}

	// Determine if the first node is the one.
	if (head->pInfo.getPlayerName() == findName)
	{
		head->pInfo.addGamesPlayed();
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is
		// not equal.
		while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() != findName)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			nodePtr->pInfo.addGamesPlayed();
		}
	}
}
//Accessors
void PlayerList::displayPlayer(string findName)
{
	PlayerNode *nodePtr;        // To traverse the list
	PlayerNode *previousNode;   // To point to the previous node

// If the list is empty, do nothing.
	if (!head)
	{
		cout << "No players : List is empty \n";
		return;
	}

	// Determine if the first node is the one.
	if (head->pInfo.getPlayerName() == findName)
	{
		head->pInfo.getAll();
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is
		// not equal.
		while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() != findName)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (nodePtr)
		{
			nodePtr->pInfo.getAll();
		}
	}
}
void PlayerList::displayAllPlayers()
{
	PlayerNode *nodePtr; // To move through the list

// Position nodePtr at the head of the list.
	nodePtr = head;

	//is list empty?
	if (nodePtr == nullptr)
	{
		cout << "No Players\n";
	}
	//if not, print
	else
	{
		// While nodePtr points to a node, traverse
		// the list.
		while (nodePtr)
		{
			// Display the value in this node.
			nodePtr->pInfo.getAll();

			// Move to the next node.
			nodePtr = nodePtr->next;
		}
	}

}

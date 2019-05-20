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
void Design::PrintMessage(string message, bool printTop = true, bool printBottom = true)//Important function that centers all of the strings and makes it look nice
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
cout << message;

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
void Design::DrawHangman(int guessCount = 0)// This will build the hangman as the player guesses
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
PrintMessage("|", false, false);

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
void Design::PrintLetters(string input, char from, char to) //Will check to see if guessed letter(s) from A-M  or N-Z
{
string s;
for (char i = from; i <= to; i++)
{
if (input.find(i) == string::npos)//if guessed letter is not found then it will remain on the board 
{
s += i;
s += " "; 
}
else //else if the letter is found it will be taken off the board.
s += "  ";
}
PrintMessage(s, false, false);
}
void Design::PrintAvailableLetters(string taken)//This will print out the available letters
{
PrintMessage("Available Letters");
PrintLetters(taken, 'A', 'M');
PrintLetters(taken, 'N', 'Z');
}
bool Design::PrintWordAndCheckWin(string word, string guessed)// Checking the guesses for a match with the word
{
bool won = true;
string s;
for (int i = 0; i < word.length(); i++)
{
if (guessed.find(word[i]) == string::npos)//compares guess to random word, if guess doesnt match it will just show the place holders along with any guessed letter.
{
won = false;
s += "_ ";
}
else//else when guess correctly the place holder will be replaced with the letter
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
while (getline(reader, word))//This will create a vector of strings 
v.push_back(word);

int randomLine = rand() % v.size();//generates a random number between 0 and the  max size of the vector

word = v[randomLine];//word to guess is selected
reader.close();
}

return word;
}
int Design::TriesLeft(string word, string guessed)//This will determine how many letters they get wrong
{
int error = 0;
for (int i = 0; i < guessed.length(); i++)
{
if (word.find(guessed[i]) == string::npos)//if word doesn't find a match with the guess the error count will increment by one
error++;
}
return error;
}

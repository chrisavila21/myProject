 //*****************
//Program Name:
//Author: Nathan Jaggers
//IDE Used: cloud9 (change if necessary)
//Cloud9 username: nathanj8
//Cloud9 workspace name: happy_fun_coding_time
//Cloud9 folder: 
//Cloud9 C++ file: 
//Program description: one-sentence summary of what your program does
//******************************************************************************
#include <iostream>
#include "Player.h"
using namespace std;

//Mutator Functions
void Player:: setPlayerName(string pName)
    {
        playerName = pName ;
    }
void Player:: addGamesPlayed()   
    {
        gamesPlayed++ ;
    }
void Player:: addWins()
    {
        gamesWon++ ;
    }
void Player:: addLosses()
    {
        gamesLost++;
    }
    
//Accessor 
string Player:: getPlayerName()  
    {
        return playerName ;
    }
int Player:: getWins()   
    {
        return gamesWon ;
    }
int Player:: getLosses()   
    {
        return gamesLost ;
    }
int Player:: getGamesPlayed()  
    {
        return gamesPlayed ;
    }
int Player:: getWinRate() 
    {
        float wins, games ;
        wins = getWins() ;
        games = getGamesPlayed() ;
        
        if (wins == 0)
            {
                return 0 ;
            }
        else
            {
                return (wins/games)*100 ;
            }
    }
void Player :: getAll() 
    {
        cout << "Player : " << playerName 
             << "\nTotal games played : " << gamesPlayed << "\tGames Won: " << gamesWon << "\tGames Lost:" << gamesLost 
             << "\nYour win rate is : " << getWinRate() << "%\n" ;
    }

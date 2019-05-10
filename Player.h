#ifndef PLAYER_H 
#define PLAYER_H

#include <string>       
#include <cctype>  

using namespace std;

class Player
    {
        private:
            string playerName ;
            int gamesPlayed ;
            int gamesWon ;
            int gamesLost ;
        
        public:
            //Mutator Functions
            void setPlayerName(string) ;    // set player name
            void addGamesPlayed() ;         // update games played
            void addWins() ;                // update wins
            void addLosses() ;              // update losses
            
            //Accessor 
            string getPlayerName() ; 
            int getWins() ;                
            int getLosses() ;              
            int getGamesPlayed() ;
            int getWinRate() ;
            void getAll()  ;

            Player():Player("{Empty}") 
                { } 
            Player(string pName) 
                {
                    playerName = pName ;
                    gamesPlayed  = 0;
                    gamesWon = 0 ; 
                    gamesLost = 0 ;
                }
            
            ~Player() {}
                
    };



#endif

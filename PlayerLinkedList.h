#ifndef PLAYERLINKEDLIST_H 
#define PLAYERLINKEDLIST_H 

#include <string>
#include "Player.h"

class PlayerList 
{
    private:
        struct PlayerNode 
            {
                Player pInfo ;
                PlayerNode *next ;
            };
        
        PlayerNode *head ;
        
    public:
        //Mutators
            void insertNode(string) ;
            void incrementWins(string);
            void incrementLosses(string);
            void incrementGamesPlayed(string);
            
        //Accessors
            void displayPlayer(string) ;
            void displayAllPlayers() ;
            
            
        //Constructor 
            PlayerList()
                {
                    head = nullptr ;
                }
        
        
        

};

#endif

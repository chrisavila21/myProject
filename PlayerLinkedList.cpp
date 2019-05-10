#include <iostream>
#include "PlayerLinkedList.h"

using namespace std;

//Mutators
    void PlayerList :: insertNode(string tempPName) 
        {
            //declarations
            PlayerNode *insNode ;
            PlayerNode *nodePtr ;
            PlayerNode *previousNode = nullptr;
                    
            // Allocate a new node and store num there.
                insNode = new PlayerNode;
                insNode ->pInfo.setPlayerName(tempPName);
                
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
                    while (nodePtr != nullptr && nodePtr->pInfo.getPlayerName() < insNode->pInfo.getPlayerName() )
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
    void PlayerList :: incrementWins(string findName)
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
    void PlayerList :: incrementLosses(string findName)
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
    void PlayerList :: incrementGamesPlayed(string findName)
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
    void PlayerList :: displayPlayer(string findName)
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
    void PlayerList :: displayAllPlayers() 
        {
            PlayerNode *nodePtr; // To move through the list
        
        // Position nodePtr at the head of the list.
            nodePtr = head;
        
        //is list empty?
            if (nodePtr == nullptr)
                {
                    cout << "No Players\n" ;
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

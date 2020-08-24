#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>

class Player {
    std::string name; //player's full name
    char piece; //player's piece on boarc
    int balance; //stores player's cash
    int pos; //player's current positon
    int turnsInLine; //counts turns a player has been stuck in line (max 3)
    int timsCups; //a player's timsCups count (max 4)
    bool withdraw; //false if a play is still in auction, or there is not an auction currently happening

    public:
        Player(std::string name, char piece, int balance, int pos, int turnsInLine, int timsCups);
        ~Player();
        
        int getBalance();
        std::string getName();
        char getPiece();
        int getPos();
        int getTurnsInLine();
        int getTimsCups();
        bool getWithdraw();
        void setBalance(int setTo);
        void setPos(int setTo);
        void setTurnsInLine(int setTo);
        void setTimsCups(int setTo);
        void setWithdraw(bool setTo);

        void addBalance(int add);
        void subtractBalance(int subtract);
        void addPos(int roll);
        void incrementTurnsInLine();
        void incrementTimsCups();
        void decrementTimsCups();

};

#endif

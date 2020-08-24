#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream> // not sure if we need this
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
#include "subject.h"
#include "player.h"
#include "square.h"
#include "academic.h"
#include "nonacademic.h"
#include "nonproperty.h"



class Game: public Subject{
	std::vector<std::shared_ptr<Square>> board;
	std::vector<std::shared_ptr<Player>> players;
	int currPlayer;
	int doublesRolled; 
	int thirdRoll;
	bool rolled;
	int forAuctionIdx;
	int auctionTurn;
	int currentBid;
	int countActiveBidders;
	int timsCups;
	std::string message;
	bool testing;
	int idxUnmortgage;
	int playerUnmortgageIdx;
	bool movePlayer(int steps);
	bool landedOn();
	bool landedOnProperty();
	bool landedOnNonProperty();
	bool landedOnTuition();
	bool landedOnGoToTims();
	bool oneInAHundred();
	void subtractTenPercent(int idx, int amount);
	void addFunds(std::string playerName, int amount);
	void resetAuction();
	int getWinningBidder();
	void setNextBidder();
	bool subtractCurrentPlayerBalance(int amount);
//	bool valid(char piece);
	void setUpProperties(std::ifstream &myfile);
	bool canImprove(std::vector<int> monopolyBlock);
	bool payGymTuition();
 	bool payResTuition();
	int checkMonopolyOwners(std::string & o, std::vector<int> monopolyBlock);
	bool bankruptAuctionProperty();
	std::shared_ptr<Academic> setAcademic(std::ifstream & file, int cost, std::string m, int i0, int i1, int i2, int i3, int i4, int i5);
	std::shared_ptr<NonAcademic> setNonAcademic(std::ifstream & file, int cost, std::string m);
	std::shared_ptr<NonProperty> setNonProperty(std::string name);
	public: 
		// initialize an empty game 
		Game();
		
		// Contructor that initializes with given values 
		Game(std::vector<std::shared_ptr<Square>> b, std::vector<std::shared_ptr<Player>> p, bool test); 

		~Game();

		// executes a single turn for the current player only if they haven't
		// rolled yet
		void turn(int dice1, int dice2);
		
		// This function is called when the current player is in the tims line
		// has decided to try rolling doubles to get out of the tims line
		// If the player rolls doubles then the player will move forward that many
		// spaces if not, the player will remain in the tims line 
		void rollTims(int dice1, int dice2);
		
		// This function handles the user input "response" for a player currently 
		// in the tims line who has entered the "pay" or "cup" command. It appropriately  out their 
		// command or re-prompts the user  if the response is invalid.
		void leaveTims(std::string & response); 
		
		// returns the name of the property that the player whose turn it currently is, 
		// is on.
		std::string getCurrentPropertyName();

		// returns the pruchase price of the property that the player whose turn it currently is, 
		// is on
		int getCurrentPropertyPrice();

		// The current player purchases the property they're currently on 
		//
		// requires: the current players balnace must be greater or equal to the 
		// purchase price of the current property
		void buy();

		// starts an auction, specifically for the case where the 
		// auction was initiated by the current player landing on a 
		// property and not buying it
		// This funcitons either runs an auction on the property
		// the current player is on if it is not passed a propertyIdx
		// if not, it will run an auction on the property at the specified index
		void startAuction(int propertyIdx = -1);

		// withdrawCurrentBidder() withdraws the current bidder from 
		// the auction
		//
		// requires: an auction must be in action
		void withdrawCurrentBidder();

		// makeBid(int bidAmount) updates the current bid with the bid amount 
		// if the current bidder has sufficient funds and the bid being made
		// is larger than the current bid
		// Otherwise this function will re-prompt
		void makeBid(int bidAmount);
		
		// returns the name of the current bidder in an auction
		std::string getCurrentBidder();

		// accessor to the currentBid field
		int getCurrentBid();
		void improve(int numImprovements, std::string &propertyName);
		// gives control to the next player
		// only works if the current player has finished his/her turn
		void next();

		void landedOnNeedlesHall(int random);

		void landedOnSLC(int r);


		// accessor to the board field 
		std::vector<std::shared_ptr<Square>> getBoard();

		// accessor to the players field
		std::vector<std::shared_ptr<Player>> getPlayers();
		
		std::vector<std::shared_ptr<Square>> setUp(std::ifstream &myfile);
		
		//void newGame(bool testingMode);
		// saves the current state of the game to the given file
		void saveGame(std::string & fileName);

		// sets the state of the current game to that of 
		// the game that was saved in the file with the same 
		// name as the input string of "fileName"
		void loadGame(std::string & fileName, bool testingMode);

		// returns the name the name of the current player
		std::string getCurrentPlayerName();

		// returns the balance in the current players account
		int getCurrentPlayerBalance();
		int getCurrentPlayer(); 	
		bool getRolled(); // why?

		int getPlayerBalance(std::string name);

		std::string getPropertyName(int num);

		int getPropertyPrice(int num);

		int getPlayerBalance(int num);

		std::string getPlayerName(int num);

		std::string getPlayerPropertyInfo(int num);

		void Mortgage(int pos);
		void Unmortgage(int pos, int playerIdx);
		int getPlayerTimsCups(int num);
		int getPropertyIdx(std::string playerName, std::string propertyName);
		void PropertyForProperty(std::string &p1, std::string &p2, std::string &recipient);

		void MoneyForProperty(int price, std::string &p, std::string &currPlyr, std::string &recipient);
		void PropertyForMoney(std::string &p, int price, std::string &currPlyr, std::string &recipient);

		bool NotImproved(std::string &property);

		// returns a string containing all the information of the 
		// properties the current player owns
		std::string getCurrentPlayerPropertyInfo();

		// returns the number of tims cups that the current player has
		int getCurrentPlayerTimsCups();

		// accessor to the message field 
		std::string getMessage();

		// sets message to the empty string 
		void eraseMessage();
		
		//calculates 10% of the players total worth, including balance, prices of buildings owned, and improvements
		int get10PercentWorth();

		void payTuition(bool i); //send true if paying 300, false if paying 10% worth
		
		// removes the player at the given index from the game 
		// Should only be called when the current players balance 
		// is the less than the amount they owe 
		void removeCurrentPlayer();

		// inTimsLine returns true if the player is currently in the 
		// tims tims line and false otherwise (visiting tims line does 
		// not count and thus returns false)
		bool inTimsLine();
	
		// finds the index of the player with the
		// same as the one given for input 
		// if it cannot find a player with a matching name
		// then it returns -1
		int findPlayerIdx(std::string &name);

		// accessor to the idxUnmortgage field
		int getIdxUnmortgage();

		// accessor to the playerUnmortgageIdx field
		int getPlayerUnmortgageIdx();
};


#endif

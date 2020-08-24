#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "observer.h"
#include <memory>
#include <vector>

class Game;

class Display: public Observer{
	std::istream & in;
	std::ostream & out;
	std::shared_ptr<Game> game;
	bool testing;
    std::vector<std::string> line2; 
    std::vector<std::string> line3;
    std::vector<std::string> line4;
	void help();
	int roll();
	void nextCommand();
	void printBoard();
	void promptBuy();
	void promptImprove();
	void promptTrade();
	void promptSLC();
	void promptNEEDLESHALL();
	void promptAuction();
	void promptMortgage();
	void promptUnmortgage();
	void promptLeaveTims();
	void promptBankrupt();
	void promptTuition();
	void promptRaiseFunds();
	void promptBankruptUnmortgage();
	void rollTesting();
	void callFunction(std::string & functionName);
        void printBlank(int i); //prints a string of spaces the length of i
        void printLine1(bool allDashes); //prints all dashes if true, -------- or --------|
        void printLine2(int i); //prints improvements for property square, or line 1 of name if non-property
        void printLine3(int i); //line if property square or line 2 of name if non-property (or blank if n/a) for square i
        void printLine4(int i); //prints name if property or blank line if non-property for square i
        void printLine5(int i); //prints the players on square i
	void printAssets(int num); // prints out all the assets of the current player
	void all();
	public:
		Display(std::istream & in, std::ostream & out, std::shared_ptr<Game> g, bool testing);
		virtual ~Display();
		virtual void update(const std::string & s) override;
};

#endif

#include <iostream>
#include <string>
#include <sstream>
#include "display.h"
#include "game.h"
#include <climits>


Display::Display(std::istream & in, std::ostream & out, std::shared_ptr<Game> game, bool testing): in{in}, out{out}, 
	game{game}, testing{testing}{
	out << "Welcome to Watopoly!" << std::endl;

	game->subscribe(this);

    	for (int i = 0; i <= 39; i++) {
    		std::string name = game->getBoard()[i]->getName();
        	if (name == "GOOSE NESTING") {
	            line2.emplace_back("GOOSE");
        	    line3.emplace_back("NESTING");
	            line4.emplace_back("");
        	} else if (name == "NEEDLES HALL") {
	            line2.emplace_back("NEEDLES");
        	    line3.emplace_back("HALL");
	            line4.emplace_back("");
        	} else if (name == "GO TO TIMS") {
	            line2.emplace_back("GO TO");
        	    line3.emplace_back("TIMS");
	            line4.emplace_back("");
        	} else if (name == "COLLECT OSAP") {
	            line2.emplace_back("COLLECT");
	            line3.emplace_back("OSAP");
        	    line4.emplace_back("");
	        } else if (name == "DC TIMS LINE") {
        	    line2.emplace_back("DC TIMS");
	            line3.emplace_back("LINE");
		    line4.emplace_back("");
        	} else if (name == "V1" || name == "CIF" || name == "REV" || name == "COOP FEE" || name == "SLC" 
				|| name == "TUITION" || name == "MKV" || name == "PAC" || name == "UWP") {
                line2.emplace_back(name);
                line3.emplace_back("");
            	line4.emplace_back("");
        	} else { //is an academic building
           	    line2.emplace_back("");
            	line3.emplace_back("--------");
            	line4.emplace_back(name);
        	}
    	}

	printBoard();
}

void Display::printBoard() {

    //each square is made up of 5 lines
    /*
    1. --------     OR    --------
    2. GOOSE              III
    3. NESTING            --------
    4.                    EV1
    5. $                  $
    */

    //*******TOP ROW*********
    //line1
    out << std::string(100, '_') << std::endl;
    //line 2
    out << "|";
    for (int i = 20; i < 31; i++) { //improvements for properties, first name line for non-properties
        printLine2(i);
    }
    out << std::endl;
    //line3
    out << "|";
    for (int i = 20; i < 31; i++) { //dashes for properties, second name line for non-properties
        printLine3(i);
    }
    out << std::endl;
    //line4
    out << "|";
    for (int i = 20; i < 31; i++) { //building name for properties, blank for non-properties
        printLine4(i);
    }
    out << std::endl;
    //line5
    out << "|";
    for (int i = 20; i < 31; i++) { //players
        printLine5(i);
    }
    out << std::endl;

    //****MIDDLE OF BOARD******
    int i = 19;
    int j = 31;
    while(i >= 11 && j <= 39){
        //19 prints on same line as 31, so while 11<=i<=19, 39<=j<=31

        //line1
        out << "|";
        //special case for 19 & 31 
        if (i == 19) {
            for (int k = i; k < j - 1; k++) {
                printLine1(false); //want --------|
            }
        }
        else {
            printLine1(false);
            printBlank(80);
            out << "|";
            printLine1(false);
        }
        out << std::endl;

        //line2
        out << "|";
        printLine2(i);
        printBlank(80);
        out << "|";
        printLine2(j);
        out << std::endl;

        //line3
        out << "|";
        printLine3(i);
        printBlank(80);
        out << "|";
        printLine3(j);
        out << std::endl;

        //line4
        out << "|";
        printLine4(i);
        printBlank(80);
        out << "|";
        printLine4(j);
        out << std::endl;

        //line5
        out << "|";
        printLine5(i);
        printBlank(80);
        out << "|";
        printLine5(j);
        out << std::endl;
        
        --i;
        ++j;
    }

    //*****BOTTOM ROW*******
    //line1
    out << "|";
    printLine1(false); //10
    for (int i = 9; i >= 0; i--) {
        printLine1(true);
    }
    out << "|";
    printLine1(false); //0
    out << std::endl;

    //line 2
    out << "|";
    for (int i = 10; i >= 0; i--) { //improvements for properties, first name line for non-properties
        printLine2(i);
    }
    out << std::endl;

    //line3
    out << "|";
    for (int i = 10; i >= 0; i--) { //dashes for properties, second name line for non-properties
        printLine3(i);
    }
    out << std::endl;

    //line4
    out << "|";
    for (int i = 10; i >= 0; i--) { //building name for properties, blank for non-properties
        printLine4(i);
    }
    out << std::endl;

    //line5
    out << "|";
    for (int i = 10; i >= 0; i--) { //players
        printLine5(i);
    }
    out << std::endl;

    //bottom line
    out << "|";
    for (int i = 10; i >= 0; i--) { //players
        printLine1(false);
    }
    out << std::endl;

	if(game->getMessage() != ""){
		out << game->getMessage() << std::endl;
		game->eraseMessage();
	} 
    nextCommand();
}

void Display::printBlank(int i) {
    out << std::string(i, ' ');
}

void Display::printLine1(bool allDashes) {
    //either want --------- or ---------|
    if (allDashes) { //----------
        out << std::string(8, '_');
    }
    else {
        out << std::string(8, '_') << "|";
    }
}

void Display::printLine2(int i) {
    int long numI = game->getBoard()[i]->getImprovementCount();
	if (line2[i] == "" && numI != -1) { //need to get improvements if it's a property square
        out << std::string(numI, 'I') << std::string(8 - numI, ' ');
    }
    else { //non-property square
        int length = line2[i].length();
        out << line2[i] << std::string(8 - length, ' ');
    }
    out << "|";
}

void Display::printLine3(int i) {
    int length = line3[i].length();
    out << line3[i] << std::string(8 - length, ' ') << "|";
}

void Display::printLine4(int i) {
    int length = line4[i].length();
    out << line4[i] << std::string(8 - length, ' ') << "|";
}

void Display::printLine5(int i) { //players
    int counter = 0;

    for (unsigned j = 0; j < game->getPlayers().size(); j++) {
        if (game->getPlayers()[j]->getPos() == i) { //if player is on this square
            out << game->getPlayers()[j]->getPiece();
            counter++;
        }
    }
    //after it prints all the players on that square, we need to fill the rest of the line
    out << std::string(8 - counter, ' ') << "|";
}

void Display::update(const std::string &s){
	if(s == "printBoard"){ 
		printBoard();
		return;
	}
	if(game->getMessage() != ""){
		out << game->getMessage() << std::endl;
		game->eraseMessage();
	} 

	if(s == "promptLeaveTims"){
		promptLeaveTims(); 
	} else if(s == "promptBuy"){
		promptBuy();
	} else if(s == "promptAuction"){
		promptAuction();
	} else if(s == "promptBankrupt"){
		promptBankrupt();		
	} else if(s == "promptTrade"){ // might not be necessary
		promptTrade();
	} else if(s == "promptTuition"){
		promptTuition();
	} else if (s == "forcedAuction"){
		game->startAuction();
	} else if(s == "nextCommand"){
		nextCommand();
	} else if(s == "endOfGame") {
		//end game
	} else if(s == "promptSLC") {
		promptSLC();
	} else if(s == "promptNEEDLESHALL") {
		promptNEEDLESHALL();
	} else if(s == "promptRaiseFunds"){
		promptRaiseFunds();
	} else if(s == "returnToRemoveCurrentPlayer"){
		game->removeCurrentPlayer();		
	} else if(s == "promptBankruptUnmortgage"){
		promptBankruptUnmortgage();
	}
}


Display::~Display(){}

int Display::roll(){
	return (rand() % 6) + 1;	
}

void Display::rollTesting(){
	std::string line;
	std::getline(in, line);
	std::stringstream ss{line};
	int dice1;
	int dice2;
	
	if(ss >> dice1 && ss >> dice2){
		if(dice1 >= 0 && dice2 >= 0 && !game->inTimsLine()){
			game->turn(dice1, dice2);
		} else if(dice1 >= 0 && dice2 >= 0){
			game->rollTims(dice1, dice2);
		} else{
			out << "Error, the number of the dice cannot be negative" << std::endl;
			nextCommand();		
		}
	} else if(game->inTimsLine()){
		game->rollTims(roll(), roll());
	} else{
		game->turn(roll(), roll());
	}
}


void Display::nextCommand(){
	out << game->getCurrentPlayerName() << " please enter one of the following commands:" << std::endl;
	if (!game->getRolled() && testing) { out << "roll <number> <number>\t" << std::endl; }
	else if (!game->getRolled()) { out << "roll\t\t" << std::endl; }
	out << "next\t\t\t"  << "improve <property name> buy\t\t" << "mortgage <property name>\t" << "printBoard" << std::endl;
	out << "assets\t\t\t" << "improve <property name> sell\t\t" << "unmortgage <property name>\t" << "all\t\t"  << std::endl;
	out << "save <filename>\t\t" << "trade <player name> <give> <receive>\t" << "help\t" << "quit" << std::endl; 

	if(game->inTimsLine() && !game->getRolled()){
		out << "Enter \"pay\" to pay $50 to get out of the Tim's Line" << std::endl;
		out << "Enter \"cup\" to use a Roll up the Rim cup to get out of the Tim's Line" << std::endl;
	}
	out << std::endl;
	std::string cmd; // should reset failbit then read
	if(!(in >> cmd)){
		return;
	} // is it possible that we hit the eof here?
	if(cmd == "roll" && testing){
		rollTesting();
	} else if(cmd == "roll" && !game->inTimsLine()){
		game->turn(roll(), roll());
	} else if(cmd == "roll"){
		game->rollTims(roll(), roll());	
	} else if(cmd == "next"){
		game->next();	
	} else if(cmd == "trade"){
		promptTrade();	
	} else if(cmd == "improve"){
		promptImprove();	
	} else if(cmd == "mortgage"){
		promptMortgage();
	} else if(cmd == "unmortgage"){
		promptUnmortgage();
	} else if(cmd == "assets"){
		printAssets(game->getCurrentPlayer());	
		nextCommand();
	} else if(cmd == "all"){
		all();	
	} else if(cmd == "save"){
		std::string fileName;
		in >> fileName;
		game->saveGame(fileName);	
	} else if(cmd == "pay" && game->inTimsLine() && !game->getRolled()){
		game->leaveTims(cmd);
	} else if(cmd == "cup" && game->inTimsLine() && !game->getRolled()){
		game->leaveTims(cmd);
	} else if(cmd == "printBoard"){
		printBoard();	
	}
	else if (cmd == "quit") {
		// do nothing, which will then subsequently terminate the program
	}
	else if (cmd == "help") {
		help();
	} else {
		out << "Invalid command, please try again" << std::endl;
		nextCommand();
	}
} 

void Display::promptSLC() {
	if(!testing){
		game->landedOnSLC(rand() % 24);
		return;
	}
	std::string random;
	out << "You have landed on SLC" << std::endl;
	out << "Please enter a random number between 0 and 23" << std::endl;
	out << "Enter:\t 0-2 to move back 3 steps" << std::endl;
     	out << "\t 3-6 to move back 2 steps" << std::endl;
	out << "\t 7-10 to move back 1 step" << std::endl;
	out << "\t 11-13 to move forward 1 step" << std::endl;
	out << "\t 14-17 to move forward 2 steps" << std::endl;
	out << "\t 18-21 to move forward 3 steps" << std::endl;
	out << "\t 22 to get sent to the DC Tims Line" << std::endl;
	out << "\t 23 advance to collect OSAP" << std::endl;	
	in >> random;
	int r;
	try {	
		r = std::stoi(random);
	} catch(...) {
		out << "Invalid input, try again." << std::endl;
		promptSLC();
		return;
	}
	if(r < 0 || r > 23) {
		out << "Invalid input" << std::endl;
		promptSLC();
		return;
	}
	game->landedOnSLC(r);
}

void Display::promptNEEDLESHALL() {
	if(!testing){
		game->landedOnNeedlesHall(rand() % 18);
		return;
	}
	std::string random;
	out << "You have landed on Needles Hall" << std::endl;
	out << "Please enter a random number between 0 and 17" << std::endl;
	out << "Enter:\t 0 to subtract $200 from your balance" << std::endl;
	out << "\t 1-2 to subtract $100 from your balance" << std::endl;
	out << "\t 3-5 to subtract $50 from your balance" << std::endl;
	out << "\t 6-11 to add $25 to your balance" << std::endl;
	out << "\t 12-14 to add $50 to your balance" << std::endl;
	out << "\t 15-16 to add $100 to your balance" << std::endl;
	out << "\t 17 to add $200 to your balance" << std::endl;
	in >> random;
	int r;
	try {
		r = std::stoi(random);
	} catch(...) {
		out << "Invalid input, try again." << std::endl;
		promptNEEDLESHALL();
		return;
	}
		if(r < 0 || r > 17) {
			out << "Invalid input" << std::endl;
			promptNEEDLESHALL();
			return;
	}
	
	game->landedOnNeedlesHall(r);
}


void Display::promptImprove() {
	std::string response = "";
	std::string pName;
	in >> pName;
	in >> response;
	if((response != "buy" && response != "sell") || game->getPropertyIdx(game->getCurrentPlayerName(), pName) == -1) {
		out << "Invalid input, please try the command again" << std::endl;
		nextCommand();
		return; 
	}
	if(response == "buy") {
		game->improve(1, pName);
	} else if(response == "sell") {
		game->improve(-1, pName);
	}
}

void Display::promptMortgage() {
	std::string propertyName;
	in >> propertyName;
	int propIndex = game->getPropertyIdx(game->getCurrentPlayerName(), propertyName);
	if(propIndex != -1) {
		game->Mortgage(propIndex);
	} else {
		out << "Not a valid property to mortgage" << std::endl;
		if(game->getCurrentPlayerBalance() >= 0){
			nextCommand();	
		} else{
			promptRaiseFunds();	
		}
	}
}

void Display::promptUnmortgage() {
	std::string propertyName;
	in >> propertyName;
	int propIndex = game->getPropertyIdx(game->getCurrentPlayerName(), propertyName);
	if(propIndex != -1) {
		game->Unmortgage(propIndex, game->getCurrentPlayer());
	} else {
		out << "Not a valid property to unmortgage." << std::endl;
		nextCommand();
	}	
}


// This function takes is specifically called when a user that is 
// in jail has failed to roll doubles on their third attmept. It will
// prompt the user to enter one of the commands and will then call the
// appropriate method in the controller.
void Display::promptLeaveTims(){
	out << "Please enter the command:" << std::endl;
	out << "1.\"pay\" to pay $50 to get out of the Tim's Line" << std::endl;
	out << "2.\"cup\" to use a Roll up the Rim cup to get out of the Tim's Line" << std::endl;
	std::string cmd;
	in >> cmd;
	if(cmd == "pay" || cmd == "cup"){
		game->leaveTims(cmd);
	} else{
		promptLeaveTims();
	}
}



void Display::promptBuy(){
	out << "Would you like to purchase " << game->getCurrentPropertyName();
	out << " for $" << game->getCurrentPropertyPrice() << '?' << std::endl;
	out << "Enter \"yes\" to purchase and \"no\" to decline:" << std::endl;
	std::string response;
	in >> response;
	if(response == "yes"){
		game->buy();
	} else if(response == "no"){
		game->startAuction(); 
	} else{
		out << "Inavalid response, your command did not match either ";
		out << "of \"yes\" or \"no\", please try again." << std::endl;
		promptBuy();
	}
}

// takes in input of either nextCommand or promptRaiseFunds
// and calls the correct function
void Display::callFunction(std::string & functionName){
	if(functionName == "nextCommand"){
		nextCommand();
	} else if(functionName == "promptRaiseFunds"){
		promptRaiseFunds();
	} else{
		out << "Invalid function call to the \"returnFunction\"" << std::endl;
	}
}

//Still needs to check to see that there are no improvements before doing its job.
void Display::promptTrade() {
	std::string functionName;
	if(game->getCurrentPlayerBalance() >= 0){
		functionName = "nextCommand";	
	} else{
		functionName = "promptRaiseFunds";
	}
	std::string recipient;
	std::string tradeItem1;
	std::string tradeItem2;
	int TI1 = -1;
	int TI2 = -1;
	in >> recipient;
	in >> tradeItem1;
	in >> tradeItem2;
	std::string currentPlayer = game->getCurrentPlayerName();
	if(currentPlayer == recipient){
		out << "Sorry, you cannot make a trade with yourself" << std::endl;
		nextCommand();
		return;
	}
	int playerBal = game->getPlayerBalance(currentPlayer);
	int player2Bal = game->getPlayerBalance(recipient); 
	if(player2Bal == INT_MIN){  
		out << "Error: the recipient for this trade does not exist" << std::endl;
		callFunction(functionName);
		return;
	} 
	
	try {
		TI1 = std::stoi(tradeItem1);
		if(TI1 <= 0) {
			out << "You cannot trade negative amounts of money" << std::endl;
			callFunction(functionName);
			return;
		}
	} catch (...) {
	}try {
		TI2 = std::stoi(tradeItem2);
		if(TI2 <= 0) {
			out << "You cannot trade negative amounts of money" << std::endl;
			callFunction(functionName);
			return;
		}
	} catch (...) {
	}
	
	int otherPlayer = game->findPlayerIdx(recipient);
	int id1 = game->getPropertyIdx(game->getCurrentPlayerName(), tradeItem1);
	int id2 = game->getPropertyIdx(game->getPlayers()[otherPlayer]->getName(), tradeItem2);
	if(TI1 == -1 && id1 == -1) {
		out << "Error: either property 1 in this trade does not exist";
		out << " and/or the player does not own the given property" << std::endl;
		callFunction(functionName);
		return;
	} else if(TI2 == -1 && id2 == -1) {
		out << "Error: either property 2 in this trade does not exist";
		out << " and/or the player does not own the given property" << std::endl;
		callFunction(functionName);
		return;
	} else if(TI1 != -1 && TI2 != -1){
		out << "Invalid trade, you cannot trade money for money" << std::endl;	
		callFunction(functionName);
		return;
	} else if(TI1 != -1 && TI1 > playerBal){
		out << "Sorry, " << game->getCurrentPlayerName() << " you do not have the funds to execute this trade" << std::endl;
		callFunction(functionName);
		return;
	} else if(TI2 != -1 && TI2 > player2Bal){
		out << "Invalid trade, the recipient does not have sufficient funds to make this trade" << std::endl;
		callFunction(functionName);
		return;
	} else if(TI1 == -1 && !game->NotImproved(tradeItem1)) {
		out << "Error: at least 1 property in the same monopoly block as property 1 still has improvements" << std::endl;	
		callFunction(functionName);
		return;
	} else if(TI2 ==  -1 && !game->NotImproved(tradeItem2)){
		out << "Error: at least 1 property in the same monopoly block as property 2 still has improvements" << std::endl;	
		callFunction(functionName);
		return;
	}
	bool invalidResponse = true;
	while(invalidResponse){
		out << recipient << " would you like to make the trade? type \"accept\" to accept or \"decline\" to decline" << std::endl;
		std::string response;
		in >> response;
		if(response == "decline"){
			invalidResponse = false;
			out << "Sorry, " << game->getCurrentPlayerName() << " your trade has been declined" << std::endl;
			callFunction(functionName); 
		} else if(response != "accept"){
			out << "Your command does not match any of the valid commands, please try again" << std::endl;
		} else if(TI1 == -1 && TI2 == -1){
			invalidResponse = false;
			game->PropertyForProperty(tradeItem1, tradeItem2, recipient);
		} else if(TI1 == -1 && TI2 != -1) {
			invalidResponse = false;
			game->PropertyForMoney(tradeItem1, TI2, currentPlayer, recipient);
		} else if(TI1 != -1 && TI2 == -1) {
			invalidResponse = false;
			game->MoneyForProperty(TI1, tradeItem2, currentPlayer, recipient);
		} else {
			out << "uh oh... it looks like there was an unanticipated case in our program" << std::endl;	
			callFunction(functionName);
		}
	}
}

void Display::promptAuction(){	
	out << game->getCurrentBidder() << " please enter a number higher than the current leading bid of $";
	out << game->getCurrentBid() << " or withdraw from the auction using the command \"withdraw\":" << std::endl;
	std::string response;
	in >> response;
	
	bool conversion = true;
	int bidAmount;
	try{
		bidAmount = std::stoi(response);
	} catch(...){
		conversion = false;
	} // try to convert it to an int

	if(conversion){
		game->makeBid(bidAmount);
	} else if(response == "withdraw"){
		game->withdrawCurrentBidder();
	} else{
		out << "Invalid input, please try again" << std::endl;
		promptAuction();
	}

}

void Display::promptTuition() {
    out << "Enter the command \"300\" to pay $300 or the command \"10\" to pay 10% of your total worth which is: $";
	out << game->get10PercentWorth() << "." << std::endl;
    std::string response;
    in >> response;

    if (response == "300") {
        game->payTuition(true);
    } else if (response == "10") {
        game->payTuition(false);
    } else {
		out << "Not a valid command." << std::endl;
        promptTuition();
    }
}


// prints out the assets of the current player
void Display::printAssets(int num){
	out << std::endl;
	out << game->getPlayerName(num) << " assets:" << std::endl;
	out << "Balance: $" << game->getPlayerBalance(num) << std::endl;
	std::string temp {game->getPlayerPropertyInfo(num)};
	if(temp == ""){
		out << "No properties" << std::endl;
	} else{
		out << temp;	
	}
	out << "Tims cups: " << game->getPlayerTimsCups(num) << std::endl;
}
void Display::all() {
	for(unsigned i = 0; i < game->getPlayers().size(); ++i) {
		printAssets(i);
	}
	nextCommand();
}

void Display::promptBankrupt(){
	out << "Sorry " << game->getCurrentPlayerName() << " your current balance is $" << game->getCurrentPlayerBalance() << std::endl;
	out << "Enter the command \"bankrupt\" to drop out" << std::endl;
        out << "or" << std::endl;
	out << "Enter the command \"raiseFunds\" to attempt to raise the necessary funds (ie. balance must get back to zero at the very least) to remain in the game" << std::endl;	
	std::string response; 
	in >> response;
	if(response == "bankrupt"){
		game->removeCurrentPlayer();	
	} else if(response == "raiseFunds"){
		promptRaiseFunds();
	} else{
		out << "Invalid command, the command you entered does not match either";
		out << " of \"bankrupt\" or \"raiseFunds\", please try again" << std::endl;
		promptBankrupt();
	}
}

void Display::promptRaiseFunds(){
	out << "List of Available Commands:" << std::endl;
	out << "trade <name> <give> <receive>\tmortgage <property>\timprove <property> sell\nbankrupt" << std::endl;
	printAssets(game->getCurrentPlayer());	
	std::string response;
	in >> response;
	if(response == "trade"){
		promptTrade();				
	} else if(response == "mortgage"){
		promptMortgage();	
	} else if(response == "improve"){
		promptImprove(); // should probably review how the improve funciton works to see if it's appropriate		
	} else if(response == "bankrupt"){
		game->removeCurrentPlayer();	
	} else{
		out << "Invalid command, please try again" << std::endl;	
		promptRaiseFunds();
	}
}

void Display::promptBankruptUnmortgage(){
	out << "Would you like to unmortgage this property for an";
	out <<" additional 50% of its purchase price?" << std::endl;
	out << "Enter \"yes\" or \"no\"" << std::endl;
	std::string response;
	in >> response;

	if(response == "yes"){
		game->Unmortgage(game->getIdxUnmortgage(), game->getPlayerUnmortgageIdx());
	} else if(response == "no"){
		game->removeCurrentPlayer();
	} else{
		out << "Invalid input, please try again" << std::endl;
		promptBankruptUnmortgage();
	}

}

void Display::help() {
	out << std::endl << "Please enter the command you would like clarification on, your options are:" << std::endl;
	out << "roll" << std::endl;
	out << "next" << std::endl;
	out << "improve" << std::endl;
	out << "assets" << std::endl;
	out << "all" << std::endl;
	out << "mortgage" << std::endl;
	out << "unmortgage" << std::endl;
	out << "printBoard" << std::endl;
	out << "save" << std::endl;
	out << "trade" << std::endl;
	out << "quit" << std::endl << std::endl;
	out << "Enter \"return\" to return to regular gameplay." << std::endl;
	std::string cmd;
	in >> cmd;

	if (cmd == "return") {
	nextCommand();
	return;
	}
	else if (cmd == "roll") {
		out << "The roll command executes the action of the current player rolling the dice." << std::endl;
		out << "If testing mode is on then you may enter the two number you wish to roll, note that you are"; 
		out << " not limited to numbers between 1-6, as you may enter any non-negative number." << std::endl;
	}
	else if (cmd == "next") {
		out << "The next command hands over control of the turn from the current player to the next player ";
		out << "if the current player has already finished rolling." << std::endl;
	}
	else if (cmd == "improve") {
		out << "The improve command allows you to buy or sell a single improvement (ie. house or hotel) on the";
		out << " specified property given that it is a valid move." << std::endl;
	}
	else if (cmd == "assets") {
		out << "The assets command displays the assets of the current player." << std::endl;
		out << "Your assets include: your current balance, your properties/improvements and your Tims Cups." << std::endl;
	}
	else if (cmd == "all") {
		out << "The all command displays the assets of all the players in the game." << std::endl;
		out << "A players assets include: their current balance, their properties/improvements and their Tims Cups." << std::endl;
	}
	else if (cmd == "mortgage") {
		out << "The mortgage command attempts to mortgage the specified property." << std::endl;
		out << "If the move is valid then it will mortgage the property, otherwise it will print an error message." << std::endl;
	}
	else if (cmd == "unmortgage") {
		out << "The unmortgage command attempts to unmortgage the specified property." << std::endl;
		out << "If the move is valid then it will unmortgage the property, otherwise it will print an error message." << std::endl;
	}
	else if (cmd == "printBoard") {
		out << "The command printBoard simply prints out the board." << std::endl;
		out << "This command is mostly used for when the screen is filled with text and the user would";
		out << " like to see the state of the board before making a move." << std::endl;
	}
	else if (cmd == "save") {
		out << "The save command saves the game to the specified file, and quits the game." << std::endl;
	}
	else if (cmd == "trade") {
		out << "The command trade, makes a trade proposal to the specified player in which you ";
		out << "are offering the item specified in the \"<give>\" position and are receiving the item ";
		out << "specified in the \"<receive>\" position." << std::endl;
	}
	else if (cmd == "quit") {
		out << "The quit command quits the game without saving." << std::endl;
	}
	else {
		out << "Sorry you're does not match any of the specified commands, please try again." << std::endl;
	}
	help();
}

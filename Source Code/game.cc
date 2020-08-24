#include "game.h"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <string>
#include <climits>

const std::string printBoard {"printBoard"};
const std::string promptLeaveTims {"promptLeaveTims"};
const std::string promptBuy {"promptBuy"};
const std::string promptAuction {"promptAuction"};
const std::string promptBankrupt {"promptBankrupt"};
const std::string promptTrade {"promptTrade"};
const std::string promptTuition {"promptTuition"};
const std::string promptRaiseFunds {"promptRaiseFunds"};
const std::string nextCommand {"nextCommand"};
const std::string forcedAuction {"forcedAuction"};
const std::string endOfGame {"endOfGame"};
const std::string promptSLC {"promptSLC"};
const std::string promptNEEDLESHALL {"promptNEEDLESHALL"};

Game::Game(){
	currPlayer = 0;
	doublesRolled = 0;
	rolled = false;
	thirdRoll = 0;
	forAuctionIdx = 0;
	idxUnmortgage = 0;
	playerUnmortgageIdx = 0;
	auctionTurn = 0;
	timsCups = 4;
	currentBid = 0;
	message = "";
}

//constructor for new game
Game::Game(std::vector<std::shared_ptr<Square>> b, std::vector<std::shared_ptr<Player>> p, bool t) : board{b}, players{p}, testing{t} {
	currPlayer = 0;
	doublesRolled = 0;
	rolled = false;
	thirdRoll = 0;
	forAuctionIdx = 0;
	auctionTurn = 0;
	currentBid = 0;
	timsCups = 4;
	message = "";
	idxUnmortgage = 0;
	playerUnmortgageIdx = 0;
	//board gets set to default in main
}

Game::~Game() {}

// accessor to the board field
std::vector<std::shared_ptr<Square>> Game::getBoard(){
	return board;
}

// accessor to the players field
std::vector<std::shared_ptr<Player>> Game::getPlayers(){
	return players;
}

void Game::saveGame(std::string & fileName) {
	std::ofstream myfile;
	myfile.open(fileName);
	myfile << players.size() << std::endl;
	int n;
	for (unsigned i = 0; i < players.size(); ++i) {
		if (!players[i]->getTurnsInLine()) {
			myfile << players[i]->getName() << " " << players[i]->getPiece() << " " << players[i]->getTimsCups() << " " << players[i]->getBalance() << " " << players[i]->getPos() << " " << 0 << " " << std::endl;
		}
		else {
			n = players[i]->getTurnsInLine() - 1;
			myfile << players[i]->getName() << " " << players[i]->getPiece() << " " << players[i]->getTimsCups() << " " << players[i]->getBalance() << " " << players[i]->getPos() << " " << 1 << " " << n << std::endl;
		}
	}
	for (unsigned i = 0; i < board.size(); ++i) {
		if (board[i]->property()) {
			myfile << board[i]->getName() << " " << board[i]->getOwner() << " " << board[i]->getImprovementCount() << std::endl;
		}
	}

	myfile.close();
}

std::shared_ptr<Academic> Game::setAcademic(std::ifstream& file, int cost, std::string m, int i0, int i1, int i2, int i3, int i4, int i5) {
	std::string sName;
	int icost;
	if (m == "Arts1" || m == "Arts2") {
		icost = 50;
	}
	else if (m == "Eng" || m == "Health") {
		icost = 100;
	}
	else if (m == "Env" || m == "Sci1") {
		icost = 150;
	}
	else if (m == "Sci2" || m == "Math") {
		icost = 200;
	}
	std::string own;
	int improve;
	file >> sName;
	file >> own;
	file >> improve;
	auto p = std::make_shared<Academic>(sName, own,  cost, m, icost, i0, i1, i2, i3, i4, i5, improve);
	return p;
}
// Creates a shared pointer to a nonAcademic building
std::shared_ptr<NonAcademic> Game::setNonAcademic(std::ifstream& file, int cost, std::string m) {
	std::string sName;
	std::string own;
	int improvement;
	file >> sName;
	file >> own;
	file >> improvement;
		auto p = std::make_shared<NonAcademic>(sName, own, cost, m, improvement);
	return p;
}
//Creates a shared pointer to a NonProperty sqyare
std::shared_ptr<NonProperty> Game::setNonProperty(std::string name) {
	auto np = std::make_shared<NonProperty>(name);
	return np;
}

std::vector<std::shared_ptr<Square>> Game::setUp(std::ifstream & myfile) {
	std::vector<std::shared_ptr<Square>> b;
	b.emplace_back(setNonProperty("COLLECT OSAP"));
	b.emplace_back(setAcademic(myfile, 40, "Arts1", 2, 10, 30, 90, 160, 250));
	b.emplace_back(setNonProperty("SLC"));
	b.emplace_back(setAcademic(myfile, 60, "Arts1", 4, 20, 60, 180, 320, 450));
	b.emplace_back(setNonProperty("TUITION"));
	b.emplace_back(setNonAcademic(myfile, 200, "RES"));
	b.emplace_back(setAcademic(myfile, 100, "Arts2", 6, 30, 90, 270, 400, 550));
	b.emplace_back(setNonProperty("NEEDLES HALL"));
	b.emplace_back(setAcademic(myfile, 100, "Arts2", 6, 30, 90, 270, 400, 550));
	b.emplace_back(setAcademic(myfile, 120, "Arts2", 8, 40, 100, 300, 450, 600));
	b.emplace_back(setNonProperty("DC TIMS LINE"));
	b.emplace_back(setAcademic(myfile, 140, "Eng", 10, 50, 150, 450, 625, 750));
	b.emplace_back(setNonAcademic(myfile, 150, "GYM"));
	b.emplace_back(setAcademic(myfile, 140, "Eng", 10, 50, 150, 450, 625, 750));
	b.emplace_back(setAcademic(myfile, 160, "Eng", 12, 60, 180, 500, 700, 900));
	b.emplace_back(setNonAcademic(myfile, 200, "RES"));
	b.emplace_back(setAcademic(myfile, 180, "Health", 14, 70, 200, 550, 750, 950));
	b.emplace_back(setNonProperty("SLC"));
	b.emplace_back(setAcademic(myfile, 180, "Health", 14, 70, 200, 550, 750, 950));
	b.emplace_back(setAcademic(myfile, 200, "Health", 16, 80, 220, 600, 800, 1000));
	b.emplace_back(setNonProperty("GOOSE NESTING"));
	b.emplace_back(setAcademic(myfile, 220, "Env", 18, 90, 250, 700, 875, 1050));
	b.emplace_back(setNonProperty("NEEDLES HALL"));
	b.emplace_back(setAcademic(myfile, 220, "Env", 18, 90, 250, 700, 875, 1050));
	b.emplace_back(setAcademic(myfile, 240, "Env", 20, 100, 300, 750, 925, 1100));
	b.emplace_back(setNonAcademic(myfile, 200, "RES"));
	b.emplace_back(setAcademic(myfile, 260, "Sci1", 22, 110, 330, 800, 975, 1150));
	b.emplace_back(setAcademic(myfile, 260, "Sci1", 22, 110, 330, 800, 975, 1150));
	b.emplace_back(setNonAcademic(myfile, 150, "GYM"));
	b.emplace_back(setAcademic(myfile, 280, "Sci1", 24, 120, 360, 850, 1025, 1200));
	b.emplace_back(setNonProperty("GO TO TIMS"));
	b.emplace_back(setAcademic(myfile, 300, "Sci2", 26, 130, 390, 900, 1100, 1275));
	b.emplace_back(setAcademic(myfile, 300, "Sci2", 26, 130, 390, 900, 1100, 1275));
	b.emplace_back(setNonProperty("SLC"));
	b.emplace_back(setAcademic(myfile, 320, "Sci2", 28, 150, 450, 1000, 1200, 1400));
	b.emplace_back(setNonAcademic(myfile, 200, "RES"));
	b.emplace_back(setNonProperty("NEEDLES HALL"));
	b.emplace_back(setAcademic(myfile, 350, "Math", 35, 175, 500, 1100, 1300, 1500));
	b.emplace_back(setNonProperty("COOP FEE"));
	b.emplace_back(setAcademic(myfile, 400, "Math", 50, 200, 600, 1400, 1700, 2000));
	return b;
}

void Game::setUpProperties(std::ifstream & myfile) {
	board.emplace_back(setNonProperty("COLLECT OSAP"));
	board.emplace_back(setAcademic(myfile, 40, "Arts1", 2, 10, 30, 90, 160, 250));
	board.emplace_back(setNonProperty("SLC"));
	board.emplace_back(setAcademic(myfile, 60, "Arts1", 4, 20, 60, 180, 320, 450));
	board.emplace_back(setNonProperty("TUITION"));
	board.emplace_back(setNonAcademic(myfile, 200, "RES"));
	board.emplace_back(setAcademic(myfile, 100, "Arts2", 6, 30, 90, 270, 400, 550));
	board.emplace_back(setNonProperty("NEEDLES HALL"));
	board.emplace_back(setAcademic(myfile, 100, "Arts2", 6, 30, 90, 270, 400, 550));
	board.emplace_back(setAcademic(myfile, 120, "Arts2", 8, 40, 100, 300, 450, 600));
	board.emplace_back(setNonProperty("DC TIMS LINE"));
	board.emplace_back(setAcademic(myfile, 140, "Eng", 10, 50, 150, 450, 625, 750));
	board.emplace_back(setNonAcademic(myfile, 150, "GYM"));
	board.emplace_back(setAcademic(myfile, 140, "Eng", 10, 50, 150, 450, 625, 750));
	board.emplace_back(setAcademic(myfile, 160, "Eng", 12, 60, 180, 500, 700, 900));
	board.emplace_back(setNonAcademic(myfile, 200, "RES"));
	board.emplace_back(setAcademic(myfile, 180, "Health", 14, 70, 200, 550, 750, 950));
	board.emplace_back(setNonProperty("SLC"));
	board.emplace_back(setAcademic(myfile, 180, "Health", 14, 70, 200, 550, 750, 950));
	board.emplace_back(setAcademic(myfile, 200, "Health", 16, 80, 220, 600, 800, 1000));
	board.emplace_back(setNonProperty("GOOSE NESTING"));
	board.emplace_back(setAcademic(myfile, 220, "Env", 18, 90, 250, 700, 875, 1050));
	board.emplace_back(setNonProperty("NEEDLES HALL"));
	board.emplace_back(setAcademic(myfile, 220, "Env", 18, 90, 250, 700, 875, 1050));
	board.emplace_back(setAcademic(myfile, 240, "Env", 20, 100, 300, 750, 925, 1100));
	board.emplace_back(setNonAcademic(myfile, 200, "RES"));
	board.emplace_back(setAcademic(myfile, 260, "Sci1", 22, 110, 330, 800, 975, 1150));
	board.emplace_back(setAcademic(myfile, 260, "Sci1", 22, 110, 330, 800, 975, 1150));
	board.emplace_back(setNonAcademic(myfile, 150, "GYM"));
	board.emplace_back(setAcademic(myfile, 280, "Sci1", 24, 120, 360, 850, 1025, 1200));
	board.emplace_back(setNonProperty("GO TO TIMS"));
	board.emplace_back(setAcademic(myfile, 300, "Sci2", 26, 130, 390, 900, 1100, 1275));
	board.emplace_back(setAcademic(myfile, 300, "Sci2", 26, 130, 390, 900, 1100, 1275));
	board.emplace_back(setNonProperty("SLC"));
	board.emplace_back(setAcademic(myfile, 320, "Sci2", 28, 150, 450, 1000, 1200, 1400));
	board.emplace_back(setNonAcademic(myfile, 200, "RES"));
	board.emplace_back(setNonProperty("NEEDLES HALL"));
	board.emplace_back(setAcademic(myfile, 350, "Math", 35, 175, 500, 1100, 1300, 1500));
	board.emplace_back(setNonProperty("COOP FEE"));
	board.emplace_back(setAcademic(myfile, 400, "Math", 50, 200, 600, 1400, 1700, 2000));
}

void Game::loadGame(std::string & fileName, bool testingMode) {
	testing = testingMode;
	std::ifstream myfile;
	myfile.open(fileName);
	int num;
	myfile >> num;
	std::string name;
	char char_piece;
	int cups;
	int bal;
	int posn;
	int inJail;
	int turns;
	std::string line;
	for (int i = 0; i < num; ++i) {
		myfile >> name;
		myfile >> char_piece;
		myfile >> cups;
		timsCups -= cups;
		myfile >> bal;
		myfile >> posn;
		myfile >> inJail;
		if (inJail) {
			myfile >> turns;
			players.emplace_back(std::make_shared<Player>(name,char_piece, bal, posn, turns + 1, cups));
		}
		else {
			players.emplace_back(std::make_shared<Player>(name, char_piece, bal, posn, 0, cups));
		}
	}
	setUpProperties(myfile);
	myfile.close();
}

// This funciton is called when the current player is in the tims line
// has decided to try rolling doubles to get out of the tims line
// If the player rolls doubles then the player will move forward that many
// spaces if not, the player will remain in the tims line 
void Game::rollTims(int dice1, int dice2){
	if(rolled){
		message = "Sorry, " + players[currPlayer]->getName() + " it looks like you have already rolled";	
		notify(nextCommand);
		return;
	}

	message = "You have rolled a " + std::to_string(dice1) +
		" and a " + std::to_string(dice2) + '\n';
	if(dice1 == dice2){
		players[currPlayer]->setTurnsInLine(0);
		rolled = true;
		if(movePlayer(dice1 + dice1)){
			return;
		}
		notify(printBoard);
	} else if(players[currPlayer]->getTurnsInLine() == 3){
		players[currPlayer]->incrementTurnsInLine(); // this line can be deleted
		thirdRoll = dice1 + dice2;
		message += "You have spent 3 turns in the DC Tims Line, you must now leave by paying or using a tims cup";
		notify(promptLeaveTims);
	} else{
		players[currPlayer]->incrementTurnsInLine(); 
		rolled = true;
		message += "Sorry, " + players[currPlayer]->getName() + " it looks like you did not roll doubles";
		notify(nextCommand);
	}
}

int Game::getPropertyIdx(std::string playerName, std::string propertyName ) {
	for(int i = 0; i < 40; ++i) {
		if(propertyName == board[i]->getName() && board[i]->getOwner() == playerName) {
			return i;
		}
	}
	return -1;
}

void Game::PropertyForProperty(std::string &p1, std::string &p2, std::string &recipient) {
	std::string functionName;
	if(players[currPlayer]->getBalance() >= 0) {
		functionName = "nextCommand";
	} else {
		functionName = "promptRaiseFunds";
	}

	int id1 = getPropertyIdx( players[currPlayer]->getName(), p1);
	if(id1 == -1) {
		message = "Error: either the first property in this trade does not exist or ";
		message += players[currPlayer]->getName() + " does not own the given property";  
		notify(functionName);
		return;
	}
	int id2 = getPropertyIdx(recipient, p2);
	if(id2 == -1) {
		message = "Error: either the second property in this trade does not exist or ";
		message += recipient + " does not own the given property";  
		notify(functionName);
		return;
	}
	board[id1]->setOwner(recipient);
	board[id2]->setOwner(players[currPlayer]->getName());
	message = "Trade was successful!";

	notify(functionName);
}

int Game::findPlayerIdx(std::string & name) {
	for(unsigned i = 0; i < players.size(); ++i) {
		if(players[i]->getName() == name) {
			return i;
		}
	}
	return -1;
}

int Game::getPlayerBalance(std::string name) {
	for(unsigned i = 0; i < players.size(); ++i) {
		if(players[i]->getName() == name) {
			return players[i]->getBalance();
		}
	}
	return INT_MIN;
}

bool Game::NotImproved(std::string &property) {
	int idx = 0;
	for(unsigned i = 0; i < board.size(); ++i) {
		if(board[i]->getName() == property) {
			idx = i;
			break;
		}
	}
	
	for(unsigned i = 0; i < board[idx]->getMonopolyBlock().size(); ++i) {
		if(board[board[idx]->getMonopolyBlock()[i]]->getImprovementCount() > 0) {
			return false;
		}
	}
	return true;
}

void Game::MoneyForProperty(int price, std::string &p, std::string &currPlyr, std::string &recipient) {
	int currentPlayer = findPlayerIdx(currPlyr);
	int otherPlayer = findPlayerIdx(recipient);
	int id = getPropertyIdx( players[otherPlayer]->getName(), p);
	players[currentPlayer]->subtractBalance(price);
	players[otherPlayer]->addBalance(price);
	board[id]->setOwner(currPlyr);
	message = "The trade was successfully made"; 
	
	if(players[currPlayer]->getBalance() >= 0){
		notify(nextCommand);
	} else{
		notify(promptRaiseFunds);
	}
}

void Game::PropertyForMoney(std::string &p, int price, std::string &currPlyr, std::string &recipient) {
	MoneyForProperty(price, p, recipient, currPlyr);
}

// This funciton handles the user input "response" for a player currently 
// in the tims line who has entered the "pay" or "cup" command. It appropriately  out their 
// command or re-prompts the user  if the response is invalid.
void Game::leaveTims(std::string & response){ // thirdRoll should be equal to 0 by default
	const int FEE = 50;
	if(response == "pay" && thirdRoll){
		message = "Since it was your third attempt rolling doubles, you shall move the sum ";
		message += "of your last roll, which is " + std::to_string(thirdRoll) + " spots forward\n";
		if (subtractCurrentPlayerBalance(FEE)) {
			return;
		}
		players[currPlayer]->setTurnsInLine(0);
		rolled = true;
		if(movePlayer(thirdRoll)){
			return;
		}
		notify(printBoard);
	} else if(response == "pay" && players[currPlayer]->getBalance() >= FEE){
		if (subtractCurrentPlayerBalance(FEE)) {
			return;
		}
		players[currPlayer]->setTurnsInLine(0);
		message = "Payment received, you now have your coffee/donuts and have left the tims line!";
		notify(nextCommand);
	} else if(response == "pay" && !thirdRoll){
		message = "Sorry, " + players[currPlayer]->getName() + " you do not currently have the funds to pay the $50 fee";
		notify(nextCommand);
	} else if(response == "cup" &&  players[currPlayer]->getTimsCups() > 0 && thirdRoll){
		message = "Since it was your third attempt rolling doubles, you shall move the sum ";
		message += "of your last roll, which is " + std::to_string(thirdRoll) + " spots forward\n";
		players[currPlayer]->decrementTimsCups();
		++timsCups;
		players[currPlayer]->setTurnsInLine(0);
		rolled = true;
		if(movePlayer(thirdRoll)){
			return;
		}
		notify(printBoard);
	} else if(response == "cup" && players[currPlayer]->getTimsCups() > 0){
		players[currPlayer]->decrementTimsCups();
		++timsCups;
		players[currPlayer]->setTurnsInLine(0);
		message = "Roll up the rim cup was successfully used, you now have your coffee/donuts and have left the tims line!";
		notify(nextCommand);
	} else if(response == "cup" && !thirdRoll){
		message = "Sorry, " + players[currPlayer]->getName() + " you do not currently own any Roll up the Rim cups";
		notify(nextCommand);
	} else if(response == "cup"){
		message = "Sorry, " + players[currPlayer]->getName() + " you do not currently own any Roll up the Rim cups";
		notify(promptLeaveTims);
	} else if(thirdRoll){
		message = "uh oh, there's seems to be an unanticipated case we did not consider"; 
		notify(promptLeaveTims);
	} else{
		message = "uh oh, there's seems to be an unanticipated case we did not consider"; 
		notify(nextCommand);
	}
}

bool Game::canImprove(std::vector<int> monopolyBlock) {
	std::string currName = players[currPlayer]->getName();
	for(unsigned int i = 0; i < monopolyBlock.size(); ++i) {
		if(board[monopolyBlock[i]]->getOwner() != currName) {
			return false;
		}
	}
	return true;
}

void Game::improve(int numImprovements, std::string &propertyName) {
	std::string functionName;
	if(players[currPlayer]->getBalance() < 0){
		functionName = "promptRaiseFunds";
	} else{
		functionName = "printBoard";
	}

	int space = getPropertyIdx(players[currPlayer]->getName(), propertyName);
	if(space == -1) {
		message = "Property name is not found or not owned by current player";
		notify(functionName);
		return;
	} else if(!board[space]->property()){
		message = "Error: cannot buy or sell improvements on a non-property square";
		notify(functionName);
		return;	
	} else if(!board[space]->isAcademic()){
		message = "Error: cannot buy or sell improvements on a gym or residence";
		notify(functionName);
		return;
	} else if(board[space]->getImprovementCount() < 0){
		message = "Cannot buy or sell improvements on a property that is mortagaged";
		notify(functionName);
		return;	
	} 

	if(players[currPlayer]->getBalance() < 0 && numImprovements > 0) {
		message = "Error: current player does not have enough money and must raise funds.";
		notify(promptRaiseFunds);
		return;
	} 

	std::vector<int> mBlock = board[space]->getMonopolyBlock();
	int currImprovements = board[space]->getImprovementCount();
	int desiredImprovements = numImprovements + currImprovements;
	if(desiredImprovements <= 5 && desiredImprovements >= 0 && canImprove(mBlock)) {
		if(numImprovements > 0 && players[currPlayer]->getBalance() >= board[space]->getImprovementCost()) {
			for(int i = currImprovements + 1; i <= desiredImprovements; ++i) {
				players[currPlayer]->subtractBalance(board[space]->getImprovementCost());
			}
		} else if(numImprovements < 0){
			for(int i = currImprovements; i > desiredImprovements; --i) {
				players[currPlayer]->addBalance(board[space]->getImprovementCost() / 2);
			}
		} else if(players[currPlayer]->getBalance() < board[space]->getImprovementCost()) {
			message = "Error: insufficient funds";	
			notify(functionName);
			return;
		} else {
			message = "Sorry, it looks like there has been an unanticipated case in our program...";
			notify(functionName);
			return;
		}
		board[space]->setImprovementCount(desiredImprovements);
	} else if(canImprove(mBlock)) {
		message = "Error: ensure the desired number of improvements is between 0 and 5";
		notify(functionName);
		return;
	} else {
		message = "Error: ensure that the monopoly block is completely owned by the current player";
		notify(functionName);
		return;
	}

	if(players[currPlayer]->getBalance() < 0){
		notify(promptRaiseFunds);	
		return;
	} else if(numImprovements > 0){
		message = "Improvement successfully purchased.";
	} else if(numImprovements < 0) {
		message = "Improvement successfully sold.";
	}
	notify(printBoard);
}

void Game::Mortgage(int pos) {
	if (!board[pos]->property()) {
		message = "Error: You cannot mortage a non-property square";
	}
	else if (board[pos]->isAcademic() && players[currPlayer]->getName() == board[pos]->getOwner() && board[pos]->getImprovementCount() == 0) {
		int price = board[pos]->getPurchaseCost();
		players[currPlayer]->addBalance(price / 2);
		board[pos]->setImprovementCount(-1);
		message = "Property successfully mortgaged";
	}
	else if (!board[pos]->isAcademic()) {
		message = "Error: You cannot mortage a gym or a residence";
	}
	else if (players[currPlayer]->getName() != board[pos]->getOwner()) {
		message = "Error: You cannot mortagage a property you do not own";
	}
	else if (board[pos]->getImprovementCount() == -1) {
		message = "Error: " + board[pos]->getName() + " is already mortgaged";
	}
	else if (board[pos]->getImprovementCount() > 0) {
		message = "Error: You cannot mortgage a property that still has improvements on it";
	}
	else {
		message = "Uh oh... it looks like there may have been a case we did not account for";
	}

	if (players[currPlayer]->getBalance() >= 0) {
		notify(nextCommand);
	}
	else {
		notify(promptRaiseFunds);
	}
}

void Game::Unmortgage(int pos, int playerIdx) {
	const bool BANKRUPT = players[currPlayer]->getBalance() < 0;
	if(BANKRUPT){ players[playerIdx]->addBalance(board[pos]->getPurchaseCost() * 0.1); }
	int price = board[pos]->getPurchaseCost();
	price *= 0.6;
	if(!board[pos]->property()){
		message = "Error: cannot unmortgage a non-property";
	} else if(!board[pos]->isAcademic()){
		message = "Error: cannot unmortage a gym or a residence";
	} else if(board[pos]->getImprovementCount() != -1){
		message = "Error: this property is not mortgaged.";
	} else if(players[playerIdx]->getBalance() >= price && 
			getPlayerName(playerIdx) == board[pos]->getOwner()) {
		players[playerIdx]->subtractBalance(price);
		board[pos]->setImprovementCount(0);
		message = "Property successfully unmortgaged.";
	} else if (players[playerIdx]->getBalance() < price) {
		message = "Error: you do not have enough money to unmortgage this property.";
	}
	
	if(!BANKRUPT){
		notify(nextCommand);
	} else{
		notify("returnToRemoveCurrentPlayer");	
	}
}

bool Game::movePlayer(int steps){
	unsigned newPosition = players[currPlayer]->getPos() + steps;
	if(newPosition > board.size() - 1){
		const int AMOUNT = (newPosition / board.size()) * 200;
		newPosition %= board.size();
		message += "You have passed Collect OSAP, and have collected $200\n";
		players[currPlayer]->addBalance(AMOUNT); 
	} else if(newPosition == 0){
		players[currPlayer]->addBalance(200);
	} else if(newPosition < 0) {
		newPosition +=  board.size(); // see if this works with SLC
	}
	players[currPlayer]->setPos(newPosition);
	return landedOn();
	 // take the appropriate aciton for landing on this spot
}

bool Game::landedOn(){
	if(board[players[currPlayer]->getPos()]->property()){
		return landedOnProperty();
	} else{
		return landedOnNonProperty();	
	}
}

bool Game::landedOnProperty(){
    // academic 
    const bool ERROR = true;
	const int curr = players[currPlayer]->getPos();
	const std::string building = board[players[currPlayer]->getPos()]->getName();
	const std::string player = players[currPlayer]->getName();
    if(board[curr]->getOwner() == "BANK" && 
            players[currPlayer]->getBalance() >= getCurrentPropertyPrice()){
        notify(promptBuy);
        return true;
    } else if(board[curr]->getOwner() == "BANK"){
		message += "You do not have enough funds to purchase " + board[players[currPlayer]->getPos()]->getName();
	 	message += ", the property will be auctioned.";
        notify(forcedAuction);
        return true;
    } else if(board[curr]->getImprovementCount() == -1){	   
	message += "You have landed on a mortgaged property and therefore do not have to pay rent";
	return false;
    } else if((building == "PAC" || building == "CIF") && board[curr]->getOwner() != player) { //first need to check if it's a non-academic
        return payGymTuition();
    } else if ((building == "MKV" || building == "UWP" || building == "V1" || building  == "REV") && board[curr]->getOwner() != player) {
        return payResTuition();
    } else if(board[curr]->getOwner() == player){
    	message += "You have landed on your own property";
		return false;
    } else { //they owe tuition
	    //first need to check if the owner owns all the properties in the monopoly
	    std::string owner = board[curr]->getOwner();
	    unsigned numOwned = checkMonopolyOwners(owner, board[curr]->getMonopolyBlock());
	    int owe = board[curr]->getTuition();
	    if(board[curr]->getImprovementCount() == 0 && numOwned == board[curr]->getMonopolyBlock().size()){
	    	// doubled on all properties when all the properties in the monopoly are owned by the same owner
		owe *= 2;
	    }
		addFunds(board[curr]->getOwner(), owe);  
		message += "Transferring $" + std::to_string(owe) + " from " + players[currPlayer]->getName() + " to " + board[players[currPlayer]->getPos()]->getOwner() + '\n';
		return subtractCurrentPlayerBalance(owe); //true if bankrupt, false if not
	}
    return ERROR;
}

int Game::checkMonopolyOwners(std::string & o, std::vector<int> monopolyBlock) {
    int counter = 0;

	for(unsigned int i = 0; i < monopolyBlock.size(); ++i) {
		if(board[monopolyBlock[i]]->getOwner() == o) {
			++counter;
		}
	}
    return counter;
}

bool Game::payGymTuition() {
    std::string owner = board[players[currPlayer]->getPos()]->getOwner();
    int gymsOwned = checkMonopolyOwners(owner, board[players[currPlayer]->getPos()]->getMonopolyBlock());
    int roll1 = (rand() % 6) + 1;
    int roll2 = (rand() % 6) + 1;
    int G1 = 4;
    int G2 = 10;
    int owe = roll1 + roll2;

    if (gymsOwned == 1) {
        owe *= G1;
    } else if (gymsOwned == 2) {
        owe *= G2;
    }
    addFunds(board[players[currPlayer]->getPos()]->getOwner(), owe);
	message += "Transferring $" + std::to_string(owe) + " from " + players[currPlayer]->getName() + " to " + board[players[currPlayer]->getPos()]->getOwner() + '\n';
    if (subtractCurrentPlayerBalance(owe)) {
		return true;
	}
	if (gymsOwned == 1) {
		message += "Successfully paid tuition. " + owner + " owns " + std::to_string(gymsOwned) + " gym, and the dice were ";
		message += std::to_string(roll1) + " & " + std::to_string(roll2) + " so your tuition was $" + std::to_string(owe) + ". ";
	} else {
		message += "Successfully paid tuition. " + owner + " owns " + std::to_string(gymsOwned) + " gyms, and the dice were ";
		message += std::to_string(roll1) + " & " + std::to_string(roll2) + ", so your tuition was $" + std::to_string(owe) + ". ";
	}
	notify(printBoard);
	return true;
}

bool Game::payResTuition() {
	std::string owner = board[players[currPlayer]->getPos()]->getOwner();
    int resOwned = checkMonopolyOwners(owner, board[players[currPlayer]->getPos()]->getMonopolyBlock());
    const int R1 = 25;
    const int R2 = 50;
    const int R3 = 100;
    const int R4 = 200;
    int owe = 0;

    if (resOwned == 1) {
        owe = R1;
    } else if (resOwned == 2) {
        owe = R2;
    } else if (resOwned == 3) {
        owe = R3;
    } else if (resOwned == 4) {
        owe = R4;
    }
    addFunds(board[players[currPlayer]->getPos()]->getOwner(), owe);
    message += "Transferring $" + std::to_string(owe) + " from " + players[currPlayer]->getName() + " to " + board[players[currPlayer]->getPos()]->getOwner() + '\n';
	if (subtractCurrentPlayerBalance(owe)) {
		return true;
	}

	if (resOwned == 1) {
		message += "Successfully paid tuition. " + owner + " owns " + std::to_string(resOwned) + " residence, so tuition was $" + std::to_string(owe) + ". ";
	} else{
		message += "Successfully paid tuition. " + owner + " owns " + std::to_string(resOwned) + " residences, so tuition was $" + std::to_string(owe) + ". ";
	}
	
	notify(printBoard);
	return true;
}

// The current player purchases the property they're currently on 
//
// requires: the current players balance must be greater or equal to the 
// purchase price of the current property
void Game::buy(){ // make sure that the only time someone can call this function is during their turn
	players[currPlayer]->subtractBalance(getCurrentPropertyPrice());
	board[players[currPlayer]->getPos()]->setOwner(players[currPlayer]->getName());
	message = players[currPlayer]->getName() + " has successfully bought " + board[players[currPlayer]->getPos()]->getName() + " for $" + std::to_string(getCurrentPropertyPrice());
	notify(printBoard);
}

void Game::resetAuction(){
	for(auto p: players){
		p->setWithdraw(false);
	}
	auctionTurn = 0;
	currentBid = 0;
	forAuctionIdx = -1;
}

// getActiveBidder returns the index at which the only active bidder is stored
//
// requires: there may only be one acitive bidder at the time
// this function is called 
int Game::getWinningBidder(){
	const int NO_ACTIVE_BIDDERS = -1;
	for(unsigned i = 0; i < players.size(); ++i){
		if( !players[i]->getWithdraw() ){
			return i;	
		}
	}	
	return NO_ACTIVE_BIDDERS;
}

// returns the index of the next active bidder
//
// requires: must have at least one active bidder
void Game::setNextBidder(){
	const int NUM_PLAYERS = players.size();
	auctionTurn = (auctionTurn + 1) % NUM_PLAYERS;
	for(int i = 0; i < NUM_PLAYERS; ++i){
		if( !players[auctionTurn % NUM_PLAYERS]->getWithdraw() ){
			auctionTurn = auctionTurn % NUM_PLAYERS;
			return;
		}
		++auctionTurn;
	}
	
	// this line should never be reached
}


void Game::startAuction(int propertyIdx){
	if(propertyIdx == -1){
		forAuctionIdx = players[currPlayer]->getPos();
	} else{
		forAuctionIdx = propertyIdx;
	}
	if(players[currPlayer]->getBalance() >= 0){
		auctionTurn = currPlayer;
		countActiveBidders = players.size();
	} else{
		players[currPlayer]->setWithdraw(true);
		auctionTurn = (currPlayer + 1) % players.size();
		countActiveBidders = players.size() - 1;
	}
	message += "An auction for the property " + board[forAuctionIdx]->getName() + " has started";
	notify(promptAuction);
}

void Game::withdrawCurrentBidder(){
	players[auctionTurn]->setWithdraw(true); // withdraw current player
	--countActiveBidders;
	std::string functionName;
	if(players[currPlayer]->getBalance() >= 0){
		functionName = "nextCommand";
	} else{
		functionName = "returnToRemoveCurrentPlayer";
	}

	if(countActiveBidders == 0){ // no bidders left
		message = "Since there are no bidders for " + board[forAuctionIdx]->getName() + " it will remain a property of the bank";
		resetAuction();
		notify(functionName);	
	} else if(countActiveBidders == 1 && currentBid > 0){
		const int bidderIdx = getWinningBidder();
		players[bidderIdx]->subtractBalance(currentBid);
		board[forAuctionIdx]->setOwner(players[bidderIdx]->getName());
		message = "Congratulations, " + players[bidderIdx]->getName() + " you have won the auction for " + board[forAuctionIdx]->getName();
		message += " at the price of $" + std::to_string(currentBid);
		resetAuction();
		notify(functionName);
	} else{
		setNextBidder();
		notify(promptAuction);
	}	
}

void Game::makeBid(int bidAmount){
	std::string functionName;
	if(players[currPlayer]->getBalance() >= 0){
		functionName = "nextCommand";	
	} else {
		functionName = "returnToRemoveCurrentPlayer";
	}
	if(players[auctionTurn]->getBalance() >= bidAmount && bidAmount > currentBid && countActiveBidders == 1){
		players[auctionTurn]->subtractBalance(bidAmount);
		board[forAuctionIdx]->setOwner(players[auctionTurn]->getName());
		message = "Congratulations, " + players[auctionTurn]->getName() + " you have won the auction for " + 
			board[forAuctionIdx]->getName() + " at the price of $" + std::to_string(bidAmount);
		resetAuction();
		notify(functionName);
	} else if(players[auctionTurn]->getBalance() >= bidAmount && bidAmount > currentBid){
		currentBid = bidAmount;
		setNextBidder();
		notify(promptAuction);
	} else if(players[auctionTurn]->getBalance() < bidAmount){
		message = "Sorry " + players[auctionTurn]->getName() + " your bid of $" + std::to_string(bidAmount) + 
			" exceeds your current balance of $" + std::to_string(players[auctionTurn]->getBalance());
		notify(promptAuction);
	} else if(bidAmount <= currentBid){
		message = "Invalid bid, your bid amount must exceed that of the current leading bid";	
		notify(promptAuction);
	} else{
		message = "Sorry it looks like there has been an unanticipated case in our program...";
		notify(promptAuction);
	}
}

// returns the name of the current bidder in an auction
std::string Game::getCurrentBidder(){
	return players[auctionTurn]->getName();	
}

// accessor to the currentBid field 
int Game::getCurrentBid(){
	return currentBid;
}


/*
// required definition of this operator so that we can use 
// std::find in Game::addFunds(std::string & playerName)
bool operator==(std::unique_ptr<Player> p, std::string & playerName){
	return p->getName() == playerName;
}
*/

// Game::addFunds(std::string & playerName) adds the amount to the balance of the 
// player with the name that matches that of the parameter playerName
void Game::addFunds(std::string playerName, int amount){
	for(unsigned i = 0; i < players.size(); ++i){
		if(players[i]->getName() == playerName){
			players[i]->addBalance(amount);
			return;
		}
	}
}

bool Game::landedOnGoToTims(){
	const int TIMS_LINE = 10;
	players[currPlayer]->setPos(TIMS_LINE);
	players[currPlayer]->setTurnsInLine(1);
	rolled = true;
	message += "You have landed on go to Tims, you're now stuck in the DC Tims Line";
	return false;
}

bool Game::subtractCurrentPlayerBalance(int amount){
	players[currPlayer]->subtractBalance(amount);
	
	if (players[currPlayer]->getBalance() < 0) {
		//call 
		notify(promptBankrupt);
		return true;
	}
	return false;
}

bool Game::oneInAHundred() {
	unsigned r = rand() % 100;
	if(r == 0 && timsCups > 0) {
		players[currPlayer]->incrementTimsCups();
		--timsCups;
		return true;
	} return false;
}

void Game::landedOnSLC(int r) {
	if(oneInAHundred()) {
		message = "You have won a Roll up the Rim cup";
		notify(printBoard);
		return;
	} 
		int steps;
		//int r = rand() % 24;
		if(r >= 0 && r <= 2) {
			steps = -3;
		} else if(r >= 3 && r <= 6) {
			steps = -2;
		} else if(r >= 7 && r <= 10) {
			steps = -1;
		} else if(r >= 11 && r <= 13) {
			steps = 1;
		} else if(r >= 14 && r <= 17) {
			steps = 2;
		} else if(r >= 18 && r <= 21) {
			steps = 3;
		} else if(r == 22) {
			message = players[currPlayer]->getName() + " has been sent to the DC Tims Line";
			const int TIMS_LINE = 10;
			players[currPlayer]->setPos(TIMS_LINE);
			players[currPlayer]->setTurnsInLine(1);
			rolled = true;
			notify(printBoard);
			return;
		}else {
			steps = 40 - players[currPlayer]->getPos();
		}
		if(steps < 0) {
			message += "You have landed on SLC and moved back ";
		} else {
			message += "You have landed on SLC and moved forward ";
		}
		std::string s = std::to_string(abs(steps));
	if(players[currPlayer]->getPos() + steps < 0) {
		message += s + " space(s).\n";
		if(movePlayer(steps + board.size())){
			return;	
		}
	} else {
		message += s + " space(s).\n";
		if(movePlayer(steps)){
			return;
		}
	}
	notify(printBoard);
	//rolled = true; // be careful where you put the "rolled = true" statement high chance that it's incorrect
	//return false;
}

void Game::landedOnNeedlesHall(int random) {
		if(random >= 0 && random <=5) {
		message += "You have landed on Needles Hall and now have to pay ";
		} else {
		message += "You have landed on Needles Hall and now gained ";
		}
		if(oneInAHundred()) {
			message = "You have won a Roll up the Rim cup";
			notify(printBoard);
			return;
		}
		if(random == 0) {
			message += "$200\n";
			if(subtractCurrentPlayerBalance(200)){
				return;
			}
		} else if(random == 1 || random == 2) {
			message += "$100\n";
			if(subtractCurrentPlayerBalance(100)){
				return;
			}
		} else if(random >= 3 && random <= 5) {
			message += "$50\n";
			if(subtractCurrentPlayerBalance(50)){
				return;
			}
		} else if(random >= 6 && random <= 11) {
			message += "$25\n";
			players[currPlayer]->addBalance(25);
		} else if(random >= 12 && random <= 14) {
			message += "$50\n";
			players[currPlayer]->addBalance(50);
		} else if(random >= 15 && random <= 16) {
			message += "$100\n";
			players[currPlayer]->addBalance(100);
		} else {
			message += "$200\n";
			players[currPlayer]->addBalance(200);
		}
		notify(printBoard);
}

bool Game::landedOnTuition(){
	notify(promptTuition);
	return true;	
}

void Game::payTuition(bool i) {
    if (i) { //player chose to pay $300
        if (subtractCurrentPlayerBalance(300)) { //returns true if it bankrupts them
			return;
		}
    } else { 
        //find 10% worth
        int worth = get10PercentWorth();
        if (subtractCurrentPlayerBalance(worth)) {
			return;
		}
    }
	message = players[currPlayer]->getName() + " has successfully paid tuition.";
	notify(printBoard);
}

int Game::get10PercentWorth() {
	int worth = players[currPlayer]->getBalance();
    //loop through buildings and add their prices and cost of improvements
    for(unsigned i = 1; i < board.size(); ++i){
		//if it's an ownable property and the currPlayer owns it
        if(board[i]->property() && players[currPlayer]->getName() == board[i]->getOwner()){
			//add the purchase price
            worth += board[i]->getPurchaseCost();
			//if it has improvements, add the cost of them
			int numImprovements = board[i]->getImprovementCount();
            if (numImprovements > 0) {
                worth += (board[i]->getImprovementCost() * numImprovements);
            }
        }
    }
	worth *= 0.1;
	return worth;
}


bool Game::landedOnNonProperty(){
	const bool ERROR = true;
	const std::string SQUARE_NAME{board[players[currPlayer]->getPos()]->getName()};
	if(SQUARE_NAME == "TUITION"){
		return landedOnTuition();
	} else if(SQUARE_NAME == "SLC") {
		notify(promptSLC);
		return true;
	} else if(SQUARE_NAME == "COOP FEE"){
		message += "You have landed on COOP FEE and now have to pay $150\n";
		return subtractCurrentPlayerBalance(150);
	} else if(SQUARE_NAME == "GO TO TIMS"){
		return landedOnGoToTims();
	} else if(SQUARE_NAME == "NEEDLES HALL"){
		notify(promptNEEDLESHALL);
		return true;
	} else if(SQUARE_NAME == "COLLECT OSAP"){
		message += "You have landed on " + SQUARE_NAME + ", collect $200";
		return false;
	} else if(SQUARE_NAME == "GOOSE NESTING"){
		message += "You have been attacked by a flock of nesting geese!";
		return false;
	} else if(SQUARE_NAME == "DC TIMS LINE"){
		message += "You have landed on and are visiting " + SQUARE_NAME;
		return false;
	}
	return ERROR;
}


// This function takes in the a counter to the number of times in a row that 
// the current player has rolled doubles. This function will execute a single turn for a 
// player.
void Game::turn(int dice1, int dice2){ 
	if(rolled){
		message = "Sorry, " + players[currPlayer]->getName() + " it looks like you have already rolled"; // should edit to say something like your turn is over
		notify(nextCommand);
		return;
	} // the player has already rolled we re-prompt them for a new command 

	if(players[currPlayer]->getTurnsInLine()){
		message = "Error: A player in jail should never be able to access the \"turn\" funciton";
		notify(nextCommand);
		return;
	} // should never be used, can be deleted after thorough testing 

	message = "You have rolled a " + std::to_string(dice1) + " and a " + std::to_string(dice2) + '\n';

	if(doublesRolled == 2 && dice1 == dice2 ){
		const int TIMSLINE = 10;
		players[currPlayer]->setPos(TIMSLINE);
		players[currPlayer]->setTurnsInLine(1);
		rolled = true;
		message += players[currPlayer]->getName() + " has been sent to the DC Tims Line for rolling 3 doubles in a row";
		notify(printBoard);	
		return;
	} // need to store doubles rolled as a field

	if(dice1 != dice2){
		rolled = true;
	} else{
		++doublesRolled;
		message += "Since you have rolled doubles you get to roll again!\n";
		if (doublesRolled != 1) {
			message += "You have now rolled " + std::to_string(doublesRolled) + " doubles in a row\n";
		} 
	} 
	
	if(movePlayer(dice1 + dice2)){
		return;
	}
	//draw the board without moving onto the next turn
		
	notify(printBoard);	
}

// moves ownership of the turn from the current player to the next
// if the current players turn has been completed
// Otherwise it sends an error message to the display classs
void Game::next(){
	if(rolled){
		currPlayer = (currPlayer + 1) % players.size();
		doublesRolled = 0;
		thirdRoll = 0;
		rolled = false;
		message = players[currPlayer]->getName() + " it looks like it's your turn";
	} else{
		message = "Sorry, " + players[currPlayer]->getName() + " you still have a roll left.";
	} 
	notify(nextCommand);
}

// returns true if the current player has already rolled
bool Game::getRolled() { return rolled;}

int Game::getCurrentPlayer() { // should delete unless if not being used
	return currPlayer;
}

std::string Game::getCurrentPropertyName(){
	return board[players[currPlayer]->getPos()]->getName();
}

int Game::getCurrentPropertyPrice(){
	return board[players[currPlayer]->getPos()]->getPurchaseCost();
}

std::string Game::getCurrentPlayerName(){
	return players[currPlayer]->getName();
}

int Game::getCurrentPlayerBalance(){
	return players[currPlayer]->getBalance();
}

std::string Game::getPropertyName(int num) {
	return board[players[num]->getPos()]->getName();
}

// returns the purchase price of the property
// that the player at index "num" is current on
int Game::getPropertyPrice(int num) {
	return board[players[num]->getPos()]->getPurchaseCost();
}

// returns the name of the player stored at the 
// index "num"
std::string Game::getPlayerName(int num) {
	return players[num]->getName();
}

// returns the balance of the current player
int Game::getPlayerBalance(int num) {
	return players[num]->getBalance();
}

// accessor to the timsCups field of the 
// player being stored at the "num" index
int Game::getPlayerTimsCups(int num) {
	return players[num]->getTimsCups();
}

// returns a string containing a list of all
// the properties the player stored at the index
// "num" owns
std::string Game::getPlayerPropertyInfo(int num){
	std::string info;
	std::string currPlayerName{players[num]->getName()};
	for(unsigned i = 1; i < board.size(); ++i){
		if(board[i]->property() && currPlayerName == board[i]->getOwner()){
			info += board[i]->getName() + ' ';
			const int improvementCount = board[i]->getImprovementCount();
			if(improvementCount == -1){
				info += "mortgaged";
			} else{
				info += "unmortgaged";
			}

			if(improvementCount > 0 ){
				info += " improvementCount " + std::to_string(improvementCount);
			}

			info += '\n';
		}
	}	
	return info;
}

// accessor to the timsCups count of the current player
int Game::getCurrentPlayerTimsCups(){
	return players[currPlayer]->getTimsCups();
}

// accessor to the message class 
std::string Game::getMessage(){
	return message;
}

// sets the value of the message to the empty string
void Game::eraseMessage(){
	message = "";
}

bool Game::bankruptAuctionProperty(){
	for(unsigned i = 0; i < board.size(); ++i){
		if(board[i]->getOwner() == players[currPlayer]->getName()){
			board[i]->setOwner("BANK");
			board[i]->setImprovementCount(0);
			startAuction(i);
			return true;
		}
	}
	return false;
}

void Game::subtractTenPercent(int idx, int amount){
	if(players[idx]->getBalance() >= (amount * 0.1)){
		players[idx]->subtractBalance(amount * 0.1);
	} else{
		players[idx]->setBalance(0);
	}
}

// Transfers all remaining assets from the player who has went bankrupt 
void Game::removeCurrentPlayer(){
	if(players[currPlayer]->getBalance() >= 0){
		message = "Error: player has sufficient funds and therefore should not be removed";
		notify(nextCommand);	
		return;
	} // check to make sure that it is a valid call to the function

	if(players.size() == 2){
		message = "Congratulations, " + players[(currPlayer + 1) % 2]->getName() + " you have won!";
		notify(endOfGame);	
		return;
	}
	if(board[players[currPlayer]->getPos()]->property()){ // transfer all assets to the player they owe
		std::string receivingPlayerName = board[players[currPlayer]->getPos()]->getOwner();
		const int RECEIVING_PLAYER = findPlayerIdx(receivingPlayerName);
		for(unsigned i = 0; i < board.size(); ++i){
			if(board[i]->getOwner() == players[currPlayer]->getName()){
				if(board[i]->getImprovementCount() == -1 && players[RECEIVING_PLAYER]->getBalance() 
						>= board[i]->getPurchaseCost() * 0.6){
					message += players[RECEIVING_PLAYER]->getName() + " you have received the";
					message += " mortgaged property " + board[i]->getName();
					message += " for which a 10% fee of the original price has been deducted";
					message += " from your balance";
					board[i]->setOwner(receivingPlayerName);
					subtractTenPercent(RECEIVING_PLAYER, board[i]->getPurchaseCost());
					idxUnmortgage = i; 
					playerUnmortgageIdx = RECEIVING_PLAYER;
					notify("promptBankruptUnmortgage");
					return;
				} else if(board[i]->getImprovementCount() == -1){
					subtractTenPercent(RECEIVING_PLAYER, board[i]->getPurchaseCost());
					board[i]->setOwner(receivingPlayerName);
				} else{
					board[i]->setOwner(receivingPlayerName); // transfer ownership	
				}
			} 
		}
		players[RECEIVING_PLAYER]->addBalance(players[currPlayer]->getBalance()); // transfer current balance, could be negative
		players[RECEIVING_PLAYER]->setTimsCups(players[currPlayer]->getTimsCups() + players[RECEIVING_PLAYER]->getTimsCups()); // transfer tims cups	
	} else{ // transfer assets to the bank
		if(bankruptAuctionProperty()){
			return;	
		}
	} 

	message += players[currPlayer]->getName() + " has been removed from the game";
	players.erase(players.begin() + currPlayer);
	if(players.size() == unsigned(currPlayer)){ currPlayer = 0; }
	doublesRolled = 0;
	thirdRoll = 0;
	rolled = false;
	if (players.size() == 1) {
		message += "\nCongratulations, " + players[0]->getName() + " you have won!";
		notify(endOfGame);
	} else {
		notify(printBoard);
	}
}

bool Game::inTimsLine(){
	return players[currPlayer]->getTurnsInLine();
}

int Game::getIdxUnmortgage(){
	return idxUnmortgage;
}

int Game::getPlayerUnmortgageIdx(){
	return playerUnmortgageIdx;
}

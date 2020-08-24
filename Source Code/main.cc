#include <cstring>
#include "game.h"
#include "display.h"
#include <algorithm>
bool valid(char char_piece) {
	return char_piece == 'G' || char_piece == 'B' || char_piece == 'D' || char_piece == 'P' || char_piece == 'S' || char_piece == '$' || char_piece == 'L' || char_piece == 'T';
}

std::vector<std::shared_ptr<Square>> defaultBoard() {
	std::vector<std::shared_ptr<Square>> b;
	b.emplace_back(std::make_shared<NonProperty>("COLLECT OSAP"));
	b.emplace_back(std::make_shared<Academic>("AL", "BANK", 40, "Arts1", 50, 2, 10, 30, 90, 160, 250, 0));
	b.emplace_back(std::make_shared<NonProperty>("SLC"));
	b.emplace_back(std::make_shared<Academic>("ML", "BANK", 60, "Arts1", 50, 4, 20, 60, 180, 320, 450, 0));
	b.emplace_back(std::make_shared<NonProperty>("TUITION"));
	b.emplace_back(std::make_shared<NonAcademic>("MKV", "BANK", 200, "RES", 0));
	b.emplace_back(std::make_shared<Academic>("ECH", "BANK", 100, "Arts2", 50, 6, 30, 90, 270, 400, 550, 0));
	b.emplace_back(std::make_shared<NonProperty>("NEEDLES HALL"));
	b.emplace_back(std::make_shared<Academic>("PAS", "BANK", 100, "Arts2", 50, 6, 30, 90, 270, 400, 550, 0));
	b.emplace_back(std::make_shared<Academic>("HH", "BANK", 120, "Arts2", 50, 8, 40, 100, 300, 450, 600, 0));
	b.emplace_back(std::make_shared<NonProperty>("DC TIMS LINE"));
	b.emplace_back(std::make_shared<Academic>("RCH", "BANK", 140, "Eng", 100, 10, 50, 150, 450, 625, 750, 0));
	b.emplace_back(std::make_shared<NonAcademic>("PAC", "BANK", 150, "GYM", 0));
	b.emplace_back(std::make_shared<Academic>("DWE", "BANK", 140, "Eng", 100, 10, 50, 150, 450, 625, 750, 0));
	b.emplace_back(std::make_shared<Academic>("CPH", "BANK", 160, "Eng", 100, 12, 60, 180, 500, 700, 900, 0));
	b.emplace_back(std::make_shared<NonAcademic>("UWP", "BANK", 200, "RES", 0));
	b.emplace_back(std::make_shared<Academic>("LHI", "BANK", 180, "Health", 100, 14, 70, 200, 550, 750, 950, 0));
	b.emplace_back(std::make_shared<NonProperty>("SLC"));
	b.emplace_back(std::make_shared<Academic>("BMH", "BANK", 180, "Health", 100, 14, 70, 200, 550, 750, 950, 0));
	b.emplace_back(std::make_shared<Academic>("OPT", "BANK", 200, "Health", 100, 16, 80, 220, 600, 800, 1000, 0));
	b.emplace_back(std::make_shared<NonProperty>("GOOSE NESTING"));
	b.emplace_back(std::make_shared<Academic>("EV1", "BANK", 220, "Env", 150, 18, 90, 250, 700, 875, 1050, 0));
	b.emplace_back(std::make_shared<NonProperty>("NEEDLES HALL"));
	b.emplace_back(std::make_shared<Academic>("EV2", "BANK", 220, "Env", 150, 18, 90, 250, 700, 875, 1050, 0));
	b.emplace_back(std::make_shared<Academic>("EV3", "BANK", 240, "Env", 150, 20, 100, 300, 750, 925, 1100, 0));
	b.emplace_back(std::make_shared<NonAcademic>("V1", "BANK", 200, "RES", 0));
	b.emplace_back(std::make_shared<Academic>("PHYS", "BANK", 260, "Sci1", 150, 22, 110, 330, 800, 975, 1150, 0));
	b.emplace_back(std::make_shared<Academic>("B1", "BANK", 260, "Sci1", 150, 22, 110, 330, 800, 975, 1150, 0));
	b.emplace_back(std::make_shared<NonAcademic>("CIF", "BANK", 150, "GYM", 0));
	b.emplace_back(std::make_shared<Academic>("B2", "BANK", 280, "Sci1", 150, 24, 120, 360, 850, 1025, 1200, 0));
	b.emplace_back(std::make_shared<NonProperty>("GO TO TIMS"));
	b.emplace_back(std::make_shared<Academic>("EIT", "BANK", 300, "Sci2", 200, 26, 130, 390, 900, 1100, 1275, 0));
	b.emplace_back(std::make_shared<Academic>("ESC", "BANK", 300, "Sci2", 200, 26, 130, 390, 900, 1100, 1275, 0));
	b.emplace_back(std::make_shared<NonProperty>("SLC"));
	b.emplace_back(std::make_shared<Academic>("C2", "BANK", 320, "Sci2", 200, 28, 150, 450, 1000, 1200, 1400, 0));
	b.emplace_back(std::make_shared<NonAcademic>("REV", "BANK", 200, "RES", 0));
	b.emplace_back(std::make_shared<NonProperty>("NEEDLES HALL"));
	b.emplace_back(std::make_shared<Academic>("MC", "BANK", 350, "Math", 200, 35, 175, 500, 1100, 1300, 1500, 0));
	b.emplace_back(std::make_shared<NonProperty>("COOP FEE"));
	b.emplace_back(std::make_shared<Academic>("DC", "BANK", 400, "Math", 200, 50, 200, 600, 1400, 1700, 2000, 0));
	return b;
}

std::shared_ptr<Game> newGameHelper(bool testMode, Game temp) {
	std::string n;
	int num;
	std::cout << "Enter the number of players between (inclusive) 2 and 8" << std::endl;
	std::cin >> n;
	try {
	 num = std::stoi(n);
	 if(num > 8 || num <= 1) {
		std::cout << "Make sure the number is between 2 and 8" << std::endl;
		return newGameHelper(testMode, temp);
	 }
	} catch (...) {
		std::cout << "Invalid input, please try again" << std::endl;
		return newGameHelper(testMode, temp);

	}std::string name;
	char char_piece;
	int i = 0;
	std::vector<std::string> nameVector;
	std::vector<char> charVector;
	while(i < num) {
		std::cout << "Enter the name of player " << i + 1 << std::endl;
		std::cin >> name;
		while(std::find(nameVector.begin(), nameVector.end(), name) != nameVector.end()) {
			std::cout << "Invalid input, please try again" << std::endl;
			std::cin >> name;
		}
		nameVector.emplace_back(name);
		std::cout << "Enter the piece you would like to play as" << std::endl;
		std::cout << "The list of valid pieces are G B D P S $ L T" << std::endl;
		std::cin >> char_piece;
		while(std::find(charVector.begin(), charVector.end(), char_piece) != charVector.end() || !valid(char_piece)) {
			std::cout << "Invalid input, please try again" << std::endl;
			std::cin >> char_piece;
		}
		charVector.emplace_back(char_piece);
		++i;

	}
	std::vector<std::shared_ptr<Player>> playerVector;
	for(unsigned i = 0; i < charVector.size(); ++i) {
		playerVector.emplace_back(std::make_shared<Player>(nameVector[i], charVector[i], 1500, 0, 0, 0));
	}
	std::vector<std::shared_ptr<Square>> sqrVector = defaultBoard();
	auto g = std::make_shared<Game>(sqrVector, playerVector, testMode);
	return g;
}

int main(int argc, char * argv[]){
	// do we have to handle when the command line argument isn't one or the other
	bool testingMode = false;
	Game temp;
	std::shared_ptr<Game> model; // make empty game

	if(argc == 1){
		model = newGameHelper(false, temp);
		// no command line arguments
	} else if(argc == 2 && strcmp(argv[1], "-testing") == 0){
		testingMode = true;
		model = newGameHelper(testingMode, temp);
		// -testing, initialize the "testing" field in display as true
	} else if(argc == 3 && strcmp(argv[1], "-load") == 0){
		std::string file{argv[2]};
		model = std::make_shared<Game>();
		model->loadGame(file, false);
		// -load <file>
	} else if(argc == 4 && strcmp(argv[1], "-load") == 0 && strcmp(argv[3], "-testing") == 0){
		std::string file{argv[2]};
		model = std::make_shared<Game>();
		model->loadGame(file, true);
		testingMode = true;
		// -load <file> -testing
	} else if(argc == 2 && strcmp(argv[1], "-load") == 0) {
		//model = newGameHelper(false, temp);
	} else {
		std::cout << "Invalid commnad line arguments, starting new game" << std::endl;
		model = newGameHelper(false, temp);
	}

	Display view(std::cin, std::cout, model, testingMode);	
	
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
#include<stdlib.h>
#include "iGraphics.h"
#include<string>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <deque>
#include <algorithm>
#include "Level.h"

#define SCREEN_WIDTH  1500
#define SCREEN_HEIGHT  900

enum MenuScreen {

    MENU_GAMEPOSTER,
    MENU_STORYLINE,
	MENU_SHOW_MENU,
    MENU_OPTIONS,
    MENU_ABOUT,
    MENU_ORIGINATORS,
	MENU_INSTRUCTION,
	MENU_SCORE,
    MENU_NEW_GAME,
	LEVEL_1, 
	LEVEL_2,
	LEVEL_3,
	LEVEL_2_BG,
	LEVEL_3_BG,
	MENU_LEVEL1_COMPLETE, // New menu screen for level completion
	MENU_LEVEL2_COMPLETE,
	MENU_LEVEL3_COMPLETE
};

int bg_game_poster, bg_storyline, bg_newgame,bg_menu, bg_originators, bg_about, instruc,bgscore ,enter_name;
int blue_coin,gold_coin,red_coin,stone ,diamond;
int play_button,about_button,score_button,originators_button,instruction_button,main_menu_button,playoption_button,new_game_button,resume_button ;

int congrats ,bg_level1poster,bg_l2poster,bg_l3poster;
int opp_sub_bullet,my_sub_bullet;

MenuScreen currentMenu = MENU_GAMEPOSTER;
bool isNewGameSelected = false;
//bool isEnterPressedOnMainMenu = false;

int scoreLimit = 60 ,scoreLimit2 = 60, scoreLimit3 = 60;

int grass ,space;
int grassX = 0;
int grassY = 0;

// my tank, opp tank, bullet, opp bullet
// coin, life count, time
int my_tank;
int my_submarine;
int my_spaceship;
int my_tankX = SCREEN_WIDTH / 2 - 50;
int my_tankY = 0;

int opp_tank;
int opp_submarine;
int opp_spaceship;

int opp_tankX = SCREEN_HEIGHT / 4 - 50 ;
int	opp_tank2X = 2 * SCREEN_WIDTH / 3  - 50;

//int opp_tankY = SCREEN_HEIGHT -100;
int opp_tankY = SCREEN_HEIGHT /4 -50;
int opp_tank2Y = 2 * SCREEN_WIDTH/3  - 50;

int my_bullet_image;
int bullet_swing_step = 10;
int my_bullet_speed = 25;

int opp_bullet;

int opp_bulletX = opp_tankX;
int opp_bullet2X = opp_tank2X;

//int opp_bulletY = opp_tankY;
int opp_bulletY = opp_tankY;
int opp_bullet2Y = opp_tank2Y;

int initial_opp_bullet_speed = 30;
int opp_bullet_speed = initial_opp_bullet_speed;

int opp_tankMoveStep = +15;
int my_tank_move_step = +10;

int collectingCoins;
int collectingCoinsGOLD;
int collectingCoinsRED ;
int collectingDIAMOND;

int playerLifeCount = 3;

int start_time_for_new_Game;
int time_toFinish_level ,time_exit;
int previous_time_Last_Paused;
int level_exit ;

bool isGamePaused = false;
bool isGameOngoing = false;

bool enterPressedOnL2Poster = false;
bool enterPressedOnL3Poster = false;

bool musicOn = true;

//if change, change at 3 positions
//remember to change bguwxx()
int uw_graphics = 45;
int underwater_photos[45];

//int space_graphics = 10;
//int space_photos[10];

int menu_graphics = 100;
int menu_animation[100];

int frame_count = 0;
int totalScore;

int isEnteringName = 0;

std::string playerName ;
std::string playerName_LowestTime;

int prevTankX = my_tankX;
int prevTankY = my_tankY;

int i,j;

// Global variables
int l1_CompletionTime = 0;
int l2_CompletionTime = 0;
int l3_CompletionTime = 0;
int Total_Time_Game_Finish;

struct Coin {
    struct Blue {
        int x, y;
        bool state;
    };

    struct Gold {
        int x, y;
        bool state;
    };

	struct Red {
        int x, y;
        bool state;
    };

	struct Diamond {
        int x, y;
        bool state;
    };

	struct stone {
        int x, y;
        bool state;
    };
};

struct my_bullet_structure {
    int x, y;
    bool state;
};

const int MAX_BLUE_COINS = 10;
std::vector<Coin::Blue> blue_coins(MAX_BLUE_COINS);

const int MAX_GOLD_COINS = 7;
std::vector<Coin::Gold> gold_coins(MAX_GOLD_COINS);

const int MAX_RED_COINS = 2;
std::vector<Coin::Red> red_coins(MAX_RED_COINS);

const int MAX_DIAMOND = 3;
std::vector<Coin::Diamond> diamond_coins(MAX_DIAMOND);

const int MAX_STONE = 4;
std::vector<Coin::stone> stone_coins(MAX_STONE);

const int MAX_MY_BULLET = 10;
std::vector<my_bullet_structure> my_bullet(MAX_MY_BULLET);

int randomPositionX() {
    return rand() % (SCREEN_WIDTH - 200);
}

int randomPositionY() {
    return rand() % (SCREEN_HEIGHT- 200);
}

void my_all_bullet_reset(){
	for (int i = 0; i < MAX_MY_BULLET; i++){
		my_bullet[i].state = false;
		my_bullet[i].x = 0;
		my_bullet[i].y = 0;
	}
}

void my_nth_bullet_reset(int i){
	my_bullet[i].state = false;
	my_bullet[i].x = 0;
	my_bullet[i].y = 0;
}

void opp_bullet_reset(){

	opp_bulletY = opp_tankY;
	opp_bullet2Y = opp_tank2Y;

	opp_bulletX = opp_tankX;
	opp_bullet2X = opp_tank2X;
}

void initialize_level_1(){
	my_tankX = SCREEN_WIDTH / 2 - 50;
    my_tankY = 0;

    opp_tankX = SCREEN_WIDTH / 4 - 50;
	opp_tank2X = 2*SCREEN_WIDTH/3  - 50;

    opp_tankY = SCREEN_HEIGHT - 100;
}

void Level1_CompletePage() {

    iClear();
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,congrats);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+70, "!!!  CONGRATULATIONS  !!!", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+10, "BATTLEFIELD Completed !!!", GLUT_BITMAP_TIMES_ROMAN_24);
}

void initialize_level_2(){
	my_tankX = 0;
    my_tankY = SCREEN_HEIGHT / 2 - 50;

    opp_tankX = SCREEN_WIDTH - 100;

    opp_tankY = SCREEN_HEIGHT / 4 - 50;
	opp_tank2Y = 2*SCREEN_HEIGHT / 3 - 50;
}

void Level2_CompletePage() {

    iClear();
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,congrats);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+70, "!!!  CONGRATULATIONS  !!!", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+10, "CORAL KINGDOM Completed !!!", GLUT_BITMAP_TIMES_ROMAN_24);
}

void initialize_level_3(){
	my_tankX = 0;
    my_tankY = SCREEN_HEIGHT / 2 - 50;

    opp_tankX = SCREEN_WIDTH - 100;

    opp_tankY = SCREEN_HEIGHT / 4 - 50;
	opp_tank2Y = 2*SCREEN_HEIGHT / 3 - 50;
}

void Level3_CompletePage() {

    iClear();
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,congrats);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+70, "!!!  CONGRATULATIONS  !!!", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2+10, "STELLER VOYAGE Completed !!!", GLUT_BITMAP_TIMES_ROMAN_24);
}

void coin_initialize(){
	
	// Generate random positions for each COIN during the new game initialization
	for (int i = 0; i < MAX_BLUE_COINS; ++i) {
        blue_coins[i].x = randomPositionX();
        blue_coins[i].y = randomPositionY();
        blue_coins[i].state = true;
    }
	for (int i = 0; i < MAX_RED_COINS; ++i) {
		red_coins[i].x = randomPositionX();
		red_coins[i].y = randomPositionY();
		red_coins[i].state = true;
	}

	if (currentMenu == LEVEL_2 ){
		for (int i = 0; i < MAX_GOLD_COINS; ++i) {
			gold_coins[i].x = randomPositionX();
			gold_coins[i].y = randomPositionY();
			gold_coins[i].state = true;
		}
	}

	if (currentMenu == LEVEL_3) {
		for (int i = 0; i < MAX_GOLD_COINS; ++i) {
			gold_coins[i].x = randomPositionX();
			gold_coins[i].y = randomPositionY();
			gold_coins[i].state = true;
		}
	}
}

void saveTotalTimeToFile() {
	
	Total_Time_Game_Finish = l1_CompletionTime + l2_CompletionTime + l3_CompletionTime;

	FILE* saveFile = fopen("Total_Time_Game_Finish.txt", "a"); 
	if (saveFile) {
		fprintf(saveFile, "Name: %s\n", playerName.c_str()); // Save player name
		fprintf(saveFile, "Total Time : %d sec\n", Total_Time_Game_Finish);
		fclose(saveFile); // Close the file

	}
}

// Function to save completion time to a file
void saveCompletionTimeToFile(const std::string& filename, int timeInSeconds) {

	FILE* saveFile = fopen(filename.c_str(), "w"); // Open the file in append mode
    if (saveFile) {
        if (currentMenu == LEVEL_1) {
            fprintf(saveFile, "Level 1 completed in = %d sec\n", timeInSeconds);
        }
		if (currentMenu == LEVEL_2) {
            fprintf(saveFile, "Level 2 completed in = %d sec\n", timeInSeconds);
        }
		if (currentMenu == LEVEL_3) {
            fprintf(saveFile, "Level 3 completed in = %d sec\n", timeInSeconds);
        }
		fclose(saveFile);
    }
	
	if (currentMenu == LEVEL_3 && totalScore >= scoreLimit3){
		saveTotalTimeToFile();
	}
}

void initializeNewGame() {

	if (currentMenu == LEVEL_1){ 
		isEnteringName = 0;
		initialize_level_1();
	}

	if (currentMenu == LEVEL_2 ){
		initialize_level_2();
	}

	if (currentMenu == LEVEL_3 ){
		initialize_level_3();

		for (int i = 0; i <MAX_DIAMOND; ++i) {
			diamond_coins[i].x = randomPositionX();
			diamond_coins[i].y = randomPositionY();
			diamond_coins[i].state = true;
		}
	}

	my_all_bullet_reset();
	opp_bullet_reset();
    
	collectingCoins = 0;
	collectingCoinsGOLD = 0;
	collectingDIAMOND = 0;
	collectingCoinsRED = 0;
    
	// Generate random positions for each STONE during the new game initialization
    for (int i = 0; i < MAX_STONE; ++i) {
        stone_coins[i].x = randomPositionX();
        stone_coins[i].y = randomPositionY();
        stone_coins[i].state = true;
    }

	playerLifeCount = 3;

    int this_time = static_cast<long int> (time(NULL));
	start_time_for_new_Game = this_time; // Reset the start time for a new game
}

void l2_poster() {
    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_l2poster);
	iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to continue...", GLUT_BITMAP_HELVETICA_18);

	initializeNewGame();
}

void l3_poster() {
    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_l3poster);
	iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to continue...", GLUT_BITMAP_HELVETICA_18);

	initializeNewGame();
}

void drawGameStartPage() {
    iClear();
    iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT  / 2, "GAME START", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void saveGameStateAndTime() {

    FILE* saveFile = fopen("Save_Game_State.txt", "w");
    if (saveFile) {
        fprintf(saveFile, "Game ongoing = %d\n\n", isGameOngoing);
		
        fprintf(saveFile, "Player Name = %s\n", playerName.c_str());
        fprintf(saveFile, "Life Count = %d\n", playerLifeCount);
		fprintf(saveFile, "Time was played = %ld\n", time_exit);
        fprintf(saveFile, "Total Score = %d\n\n", totalScore);
		
        fprintf(saveFile, "Level  = %d\n\n", level_exit );

		if (level_exit == 2 ){
			fprintf(saveFile, "Level 1 completed in = %d\n", l1_CompletionTime);
		}
		if (level_exit == 3 ){
			fprintf(saveFile, "Level 2 completed in = %d\n\n", l2_CompletionTime);
		}

        fclose(saveFile);
    }
}

void handleExit() {

	saveGameStateAndTime();
    exit(0);
}

void loadSavedGame() {

    std::ifstream loadFile("Game_State_Save.txt");

    if (loadFile) {

        std::string line;
        std::getline(loadFile, line);
        isGameOngoing = (line == "1");

		// Load the player's name from the save file
        // std::getline(loadFile, playerName);

        // Load the player's life count and coins collected from the save file
        std::getline(loadFile, line);
        playerLifeCount = std::stoi(line);
       

		// Load the game time
        std::getline(loadFile, line);
        time_exit = std::stod(line);

        loadFile.close();
    }
}

void drawAboutText() {
    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT , bg_about);
    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void drawStorylineText() {
    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_storyline);
    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to continue...", GLUT_BITMAP_HELVETICA_18);
}

void drawPlayOptions() {

    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_newgame);

	iShowImage(250, 650 , 300, 150, playoption_button);
	iShowImage(250, 500 , 150, 100, new_game_button);
	iShowImage(250, 380 , 150, 100, resume_button);

	iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void drawOptions() {

    iClear();
	//iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_menu);
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menu_animation[frame_count % menu_graphics]);

	iSetColor(255, 255, 255);
	
	iShowImage(600, 650 , 350, 200, main_menu_button);

	iText(370, 400, "1", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(650, 400, "2", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(930, 400, "3", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(510, 220, "4", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(790, 220, "5", GLUT_BITMAP_TIMES_ROMAN_24);

	iShowImage(370, 390, 200, 100, play_button);
	iShowImage(650, 390 , 200, 100, about_button);
	iShowImage(930, 390, 200, 100, score_button);

	iShowImage(510, 210, 200, 100, originators_button);
	iShowImage(790, 210 , 200, 100,instruction_button );
   
	iText(SCREEN_WIDTH / 2 - 10, 30, "Press 'Enter' to play...", GLUT_BITMAP_HELVETICA_18);
}

void drawMenu() {
    iClear();

    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_game_poster);
    iSetColor(255, 255, 255);
	
	iText(SCREEN_WIDTH / 2 - 10, 30, "Press 'Enter' to continue...", GLUT_BITMAP_HELVETICA_18);
}

void drawOriginators() {
    iClear();

    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_originators); // Show your background picture here

    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void instruction() {
    iClear();

    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, instruc );

    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void score() {

    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgscore);

    FILE* timeFile = fopen("Total_Time_Game_Finish.txt", "r");
    if (timeFile) {

        int minTime = INT_MAX;
        char totalGameTime[100];
		int latestTime = 0;
		// std::string playerName
		//std::string playerName_LowestTime;

        while (fgets(totalGameTime, sizeof(totalGameTime), timeFile)) {
            int currentTime;
            if (sscanf(totalGameTime, "Total Time : %d sec", &currentTime) == 1) {
				latestTime = currentTime;
                if (currentTime < minTime) {
                    minTime = currentTime;
					playerName_LowestTime = playerName;
                }
            }
			else if (strstr(totalGameTime, "Name: ") == totalGameTime) {
				playerName = totalGameTime + strlen("Name: "); // Extract player name
				playerName = playerName.substr(0, playerName.find_first_of("\n")); // Remove newline character
			}
        }
        fclose(timeFile);

        char minTimeStr[100];
        sprintf_s(minTimeStr, sizeof(minTimeStr), "Best Time : %d sec", minTime);
        iText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 +150, minTimeStr, GLUT_BITMAP_HELVETICA_18);

		std::string playerName_LowestTimeStr = "Best Player Name: " + playerName_LowestTime;
        char playerName_LowestTimeBuffer[100];
        strcpy_s(playerName_LowestTimeBuffer, playerName_LowestTimeStr.c_str());
        iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 100, playerName_LowestTimeBuffer, GLUT_BITMAP_HELVETICA_18);


		char latestTimeStr[100];
        sprintf_s(latestTimeStr, sizeof(latestTimeStr), "Current Player Time : %d sec", latestTime);
        iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 -50, latestTimeStr, GLUT_BITMAP_HELVETICA_18);

        std::string playerNameStr = "Current Player Name: " + playerName;
        char playerNameBuffer[100];
        strcpy_s(playerNameBuffer, playerNameStr.c_str());
        iText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 100, playerNameBuffer, GLUT_BITMAP_HELVETICA_18);
    }

    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to go back...", GLUT_BITMAP_HELVETICA_18);
}

void delay(float secs){
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

bool hit(int x1, int y1, int x2, int y2) {
    if (abs(x1 - x2) < 50 && abs(y1 - y2) < 50)
        return true;
    else
        return false;
}

bool outside_screen(int x, int y){
	if (x > grassX || y> grassY)
        return true;
    else
        return false;
}

void checkAndReappearNewCoin() {
    for (int i = 0; i < MAX_BLUE_COINS; ++i) {
			if (!blue_coins[i].state) {
				blue_coins[i].x = randomPositionX();
				blue_coins[i].y = randomPositionY();
				blue_coins[i].state = true;
			}
    }

	for (int i = 0; i < MAX_GOLD_COINS; ++i) {
        if (!gold_coins[i].state) {
            gold_coins[i].x = randomPositionX();
            gold_coins[i].y = randomPositionY();
            gold_coins[i].state = true;
        }
    }

	for (int i = 0; i < MAX_RED_COINS; ++i) {
        if (!red_coins[i].state) {
            red_coins[i].x = randomPositionX();
            red_coins[i].y = randomPositionY();
            red_coins[i].state = true;
        }
    }
}

void show_game_data(){

	char nameText[20];
	strcpy_s(nameText, playerName.c_str()); // Convert playerName to a C-string
	std::string nameStr = "Name: " + std::string(nameText);
	iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 40, &nameStr[0], GLUT_BITMAP_HELVETICA_18);

	char livesText[20];
    _itoa_s(playerLifeCount, livesText, sizeof(livesText), 10);
    std::string livesStr = "Lives: " + std::string(livesText);
    iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 80, &livesStr[0], GLUT_BITMAP_HELVETICA_18);

	char timeText[20];
    _itoa_s(time_toFinish_level, timeText, sizeof(timeText), 10);
    std::string timeStr = "Game time: " + std::string(timeText)+" sec";
    iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 120, &timeStr[0], GLUT_BITMAP_HELVETICA_18);

	
	// Level 1 completion time to show on level 2 screen
	if (currentMenu == LEVEL_2 || currentMenu == LEVEL_3 ){
		std::ifstream timeFile("l1_complete_time.txt");
		std::string totalGameTime;
		if (timeFile.is_open()) {
			std::getline(timeFile, totalGameTime);
			timeFile.close();
		}

		// Convert the completion time to a C-string
		char gameTimeStr[100];
		strcpy(gameTimeStr, totalGameTime.c_str());

		iText(SCREEN_WIDTH - 1400, SCREEN_HEIGHT - 40, gameTimeStr, GLUT_BITMAP_HELVETICA_18);
	}

	// Level 1 ,2 completion time to show on level 3 screen
	if (currentMenu == LEVEL_3 ){
		std::ifstream timeFile("l2_complete_time.txt");
		std::string totalGameTime;
		if (timeFile.is_open()) {
			std::getline(timeFile, totalGameTime);
			timeFile.close();
		}

		// Convert the completion time to a C-string
		char gameTimeStr[100];
		strcpy(gameTimeStr, totalGameTime.c_str());

		iText(SCREEN_WIDTH - 1400, SCREEN_HEIGHT - 80, gameTimeStr, GLUT_BITMAP_HELVETICA_18);
	}
}

void show_level_1_gtbcd(){

	level_exit = 1 ;
	// show grass, tank, bullet, coin, data
	iShowImage(grassX, grassY, SCREEN_WIDTH, SCREEN_HEIGHT, grass);
    iShowImage(my_tankX, my_tankY, 100, 100, my_tank);

    iShowImage(opp_tankX, opp_tankY, 100, 100, opp_tank);
	iShowImage(opp_tank2X, opp_tankY, 100, 100, opp_tank);

    iShowImage(opp_bulletX, opp_bulletY, 50, 50, opp_bullet);
	iShowImage(opp_bullet2X, opp_bulletY, 50, 50, opp_bullet);

	for (int i = 0; i < MAX_MY_BULLET; i++){
	    if (my_bullet[i].state)
			iShowImage(my_bullet[i].x, my_bullet[i].y, 50, 50, my_bullet_image);
	}

    for (int i = 0; i < MAX_BLUE_COINS; ++i) {
        if (blue_coins[i].state) {
            iShowImage(blue_coins[i].x, blue_coins[i].y, 50, 50, blue_coin);
        }
    }

	 for (int i = 0; i < MAX_RED_COINS; ++i) {
        if (red_coins[i].state) {
            iShowImage(red_coins[i].x, red_coins[i].y, 50, 50, red_coin);
        }
    }

	for (int i = 0; i < MAX_STONE; ++i) {
        if (stone_coins[i].state) {
            iShowImage(stone_coins[i].x, stone_coins[i].y, 35, 35, stone);
        }
    }

	show_game_data();
    totalScore = collectingCoins*20 - collectingCoinsRED*10 ; // Calculate total score

	char totalScoreText[20];
    _itoa_s(totalScore, totalScoreText, sizeof(totalScoreText), 10);

    std::string totalScoreStr = "Total Score: " + std::string(totalScoreText);
    iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 160, &totalScoreStr[0], GLUT_BITMAP_HELVETICA_18);


	if (currentMenu == LEVEL_1 ) {
		l1_CompletionTime = time_toFinish_level;
	//	l1_CompletionTime = time_toFinish_level - previous_time_Last_Paused ;
		saveCompletionTimeToFile("l1_complete_time.txt", l1_CompletionTime);
	}
}

void show_level_2_gtbcd(){

	level_exit = 2 ;

	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, underwater_photos[frame_count % uw_graphics]);

	iShowImage(my_tankX, my_tankY, 100, 100, my_submarine);

    iShowImage(opp_tankX, opp_tankY, 100, 100, opp_submarine);
	iShowImage(opp_tankX, opp_tank2Y, 100, 100, opp_submarine);

    iShowImage(opp_bulletX, opp_bulletY, 50, 50, opp_sub_bullet);
	iShowImage(opp_bulletX, opp_bullet2Y, 50, 50, opp_sub_bullet);

    for (int i = 0; i < MAX_MY_BULLET; i++){
	    if (my_bullet[i].state)
			iShowImage(my_bullet[i].x, my_bullet[i].y, 50, 50, my_sub_bullet);
	}

	 for (int i = 0; i < MAX_BLUE_COINS; ++i) {
        if (blue_coins[i].state) {
            iShowImage(blue_coins[i].x, blue_coins[i].y, 50, 50, blue_coin);
        }
    }

    for (int i = 0; i < MAX_GOLD_COINS; ++i) {
        if (gold_coins[i].state) {
            iShowImage(gold_coins[i].x, gold_coins[i].y, 50, 50, gold_coin);
        }
    }

	 for (int i = 0; i < MAX_RED_COINS; ++i) {
        if (red_coins[i].state) {
            iShowImage(red_coins[i].x, red_coins[i].y, 50, 50, red_coin);
        }
    }

	 for (int i = 0; i < MAX_STONE; ++i) {
        if (stone_coins[i].state) {
            iShowImage(stone_coins[i].x, stone_coins[i].y, 35, 35, stone);
        }
    }

	show_game_data();
	totalScore = collectingCoins*20 + collectingCoinsGOLD*30 - collectingCoinsRED*10; // Calculate total score

    char totalScoreText[20];
    _itoa_s(totalScore, totalScoreText, sizeof(totalScoreText), 10);
    std::string totalScoreStr = "Total Score: " + std::string(totalScoreText);
    iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 160, &totalScoreStr[0], GLUT_BITMAP_HELVETICA_18);


	if (currentMenu == LEVEL_2 && enterPressedOnL2Poster) {
		l2_CompletionTime = time_toFinish_level ;
		//	l2_CompletionTime = time_toFinish_level - previous_time_Last_Paused ;
		saveCompletionTimeToFile("l2_complete_time.txt", l2_CompletionTime);
	}

}

void show_level_3_gtbcd(){

	level_exit = 3 ;

	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, space);
	//iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, space_photos[frame_count % space_graphics]);

	iShowImage(my_tankX, my_tankY, 100, 100, my_spaceship);

    iShowImage(opp_tankX, opp_tankY, 100, 100, opp_spaceship);
	iShowImage(opp_tankX, opp_tank2Y, 100, 100, opp_spaceship);

    iShowImage(opp_bulletX, opp_bulletY, 50, 50, opp_sub_bullet);
	iShowImage(opp_bulletX, opp_bullet2Y, 50, 50, opp_sub_bullet);

    for (int i = 0; i < MAX_MY_BULLET; i++){
	    if (my_bullet[i].state)
			iShowImage(my_bullet[i].x, my_bullet[i].y, 50, 50, my_sub_bullet);
	}

	 for (int i = 0; i < MAX_BLUE_COINS; ++i) {
        if (blue_coins[i].state) {
            iShowImage(blue_coins[i].x, blue_coins[i].y, 50, 50, blue_coin);
        }
    }

    for (int i = 0; i < MAX_GOLD_COINS; ++i) {
        if (gold_coins[i].state) {
            iShowImage(gold_coins[i].x, gold_coins[i].y, 50, 50, gold_coin);
        }
    }

	 for (int i = 0; i < MAX_RED_COINS; ++i) {
        if (red_coins[i].state) {
            iShowImage(red_coins[i].x, red_coins[i].y, 50, 50, red_coin);
        }
    }
	  for (int i = 0; i < MAX_DIAMOND; ++i) {
        if (diamond_coins[i].state) {
            iShowImage(diamond_coins[i].x, diamond_coins[i].y, 50, 50, diamond);
        }
    }

	 for (int i = 0; i < MAX_STONE; ++i) {
        if (stone_coins[i].state) {
            iShowImage(stone_coins[i].x, stone_coins[i].y, 35, 35, stone);
        }
    }

	show_game_data();

	totalScore = collectingCoins*20 + collectingCoinsGOLD*30 - collectingCoinsRED*10; // Calculate total score

    char totalScoreText[20];
    _itoa_s(totalScore, totalScoreText, sizeof(totalScoreText), 10);
    std::string totalScoreStr = "Total Score: " + std::string(totalScoreText);
    iText(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 160, &totalScoreStr[0], GLUT_BITMAP_HELVETICA_18);
           

	if (currentMenu == LEVEL_3 && enterPressedOnL3Poster) {
		l3_CompletionTime = time_toFinish_level;
		//	l3_CompletionTime = time_toFinish_level - previous_time_Last_Paused ;
		saveCompletionTimeToFile("l3_complete_time.txt", l3_CompletionTime);
	}
}

void drawLevel_1() {
	iClear();

    show_level_1_gtbcd();

    if (totalScore >= scoreLimit) {
		// play sound when level completed
        PlaySound("music\\level_complete.wav", NULL, SND_ASYNC | SND_FILENAME);	
		PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        currentMenu = MENU_LEVEL1_COMPLETE; // Transition to the level complete page
        return;
    }

	if (isGamePaused) {
        iText(700, 400, "The Game is paused.", GLUT_BITMAP_TIMES_ROMAN_24);
    }

	checkAndReappearNewCoin(); // function to check and appear a new coin
}

void drawLevel_2(){

	iClear();

    show_level_2_gtbcd();

    if ( totalScore >= scoreLimit2 ) {
		// play sound when level completed
        PlaySound("music\\level_complete.wav", NULL, SND_ASYNC | SND_FILENAME);
		PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

       currentMenu = MENU_LEVEL2_COMPLETE; // Transition to the level complete page
        return;
    }

	if (isGamePaused) {
        iText(700, 400, "The Game is paused.", GLUT_BITMAP_TIMES_ROMAN_24);
    }

	checkAndReappearNewCoin(); // function to check and appear a new coin
}

void drawLevel_3(){

	iClear();

    show_level_3_gtbcd();

    if ( totalScore >= scoreLimit3 ) {
		// play sound when level completed
        PlaySound("music\\level_complete.wav", NULL, SND_ASYNC | SND_FILENAME);
		PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
       currentMenu = MENU_LEVEL3_COMPLETE; // Transition to the level complete page 
        return;
    }

	if (isGamePaused) {
        iText(700, 400, "The Game is paused.", GLUT_BITMAP_TIMES_ROMAN_24);
    }

	checkAndReappearNewCoin(); // function to check and appear a new coin
}

void i_got_hit(){

	if (  (opp_bulletY <= my_tankY + 75  && opp_bulletY + 50 >= my_tankY &&
          opp_bulletX <= my_tankX + 75 && opp_bulletX + 50 >= my_tankX) ||

         (opp_bullet2Y <= my_tankY + 75 && opp_bullet2Y + 50 >= my_tankY &&
          opp_bullet2X <= my_tankX + 75 && opp_bullet2X + 50 >= my_tankX)  )
	{
		PlaySound("music\\life_deduct.wav", NULL, SND_ASYNC | SND_FILENAME);
		playerLifeCount--;
		
		PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

		if (playerLifeCount == 0) {
			currentMenu = MENU_OPTIONS;
			playerLifeCount = 3;
		}
		opp_bullet_reset();
    }
}

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

void update_position_my_tank(){

	// Bounce the player's tank back when it hits the right or left edge of the screen
    if (my_tankX <= 0) {
        my_tankX = 0;
    }
	else if (my_tankX >= SCREEN_WIDTH - 100) {
        my_tankX = SCREEN_WIDTH - 100;
    }

    if (my_tankY <= 0) {
        my_tankY = 0;
    }
	else if (my_tankY >= SCREEN_HEIGHT - 100) {
        my_tankY = SCREEN_HEIGHT - 100;
    }

    for (int i = 0; i < MAX_STONE; ++i) {
		if (stone_coins[i].state) {
			// Calculate the center of the stone
			int stoneCenterX = stone_coins[i].x + 15; // Half of the stone's width
			int stoneCenterY = stone_coins[i].y + 25; // Half of the stone's height

			// Calculate the distance between the tank's center and the stone's center
			int distanceX = abs(my_tankX + 50 - stoneCenterX);
			int distanceY = abs(my_tankY + 50 - stoneCenterY);

			// Calculate the sum of half the widths of the stone and tank
			int halfStoneWidth = 35 / 2;
			int halfTankWidth = 100 / 2;

			// Check if the tank is within the area of the stone
			if (distanceX <= (halfStoneWidth + halfTankWidth) && distanceY <= (halfStoneWidth + halfTankWidth)) { 
				// Move the tank back to its previous position before the collision
				my_tankX = prevTankX;
				my_tankY = prevTankY;
			}
		}
	}

	// Update prevTankX and prevTankY with the tank's current position
	prevTankX = my_tankX;
	prevTankY = my_tankY;
}

void update_position_opp_tank(){

	if (currentMenu == LEVEL_1){
		//1st tank
		if (opp_tankX >= SCREEN_WIDTH/2 + 25 ) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		else if (opp_tankX <= 0) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		opp_tankX += opp_tankMoveStep;

		// 2nd tank - Move from right to left until hitting the half screen width, then hit back
		if (opp_tank2X >= SCREEN_WIDTH - 50) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		else if (opp_tank2X  <= 0) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		opp_tank2X += opp_tankMoveStep;
	}


	if (currentMenu == LEVEL_2  || currentMenu == LEVEL_3  ){
		//1st 
		if (opp_tankY >= SCREEN_HEIGHT/2 ) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		else if (opp_tankY <= 0) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		opp_tankY += opp_tankMoveStep;

		//2nd
		if (opp_tank2Y >= SCREEN_HEIGHT - 50) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		else if (opp_tank2Y <= 0) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		opp_tank2Y += opp_tankMoveStep;
	}

	/*if (currentMenu == LEVEL_3  ){
		if (opp_tankY >= SCREEN_HEIGHT - 100) {
			opp_tankMoveStep = -opp_tankMoveStep;
		} else if (opp_tankY <= 0) {
			opp_tankMoveStep = -opp_tankMoveStep;
		}
		opp_tankY += opp_tankMoveStep;
	}*/
}

void update_position_my_bullet(){

	//collision between the tank's bullets and the blue_coin
	for (i = 0; i < MAX_BLUE_COINS; ++i) {
		for (j = 0; j < MAX_MY_BULLET; j++){
			if (blue_coins[i].state && my_bullet[j].state) {

				if (hit(my_bullet[j].x, my_bullet[j].y, blue_coins[i].x, blue_coins[i].y)){
					collectingCoins++;
					blue_coins[i].state = false;
					my_bullet[j].state = false;

					if (musicOn) {
						PlaySound("music\\coin_hit .wav", NULL, SND_ASYNC | SND_FILENAME);
						PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
					}
				}	
			}
		}
	}
	
    //red coin	
	for (i = 0; i < MAX_RED_COINS; ++i) {
		for (j = 0; j < MAX_MY_BULLET; j++){
			if (red_coins[i].state && my_bullet[j].state) {

				if (hit(my_bullet[j].x, my_bullet[j].y, red_coins[i].x, red_coins[i].y)){
					collectingCoinsRED++;
					red_coins[i].state = false;
					my_bullet[j].state = false;

					if (musicOn) {
						PlaySound("music\\coin_hit .wav", NULL, SND_ASYNC | SND_FILENAME);
						PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
					}
				}	
			}
		}
	}

	 // Check collision with stones
    for ( i = 0; i < MAX_STONE; ++i) {
		for (j = 0; j < MAX_MY_BULLET; j++){
          if (stone_coins[i].state && my_bullet[j].state) {

            if (hit(my_bullet[j].x, my_bullet[j].y, stone_coins[i].x, stone_coins[i].y)) {

                my_bullet[j].state = false;
              //  my_bullet[j].state = my_tankX; // Reset bullet position
			}
          }
       }
   }


	if (currentMenu == LEVEL_1){
		for (i = 0; i < MAX_MY_BULLET; i++){
			if (my_bullet[i].state) {
				my_bullet[i].y += my_bullet_speed; // Move the bullet upwards
				if (my_bullet[i].y >= SCREEN_HEIGHT) {
					my_bullet[i].state = false;
				}
			}
		}
	}

	//Level 2
	if (currentMenu == LEVEL_2 || currentMenu == LEVEL_3 ){
		for (i = 0;  i < MAX_MY_BULLET; i++){
			my_bullet[i].x += my_bullet_speed; // Move the bullet side
			if (my_bullet[i].x >= SCREEN_WIDTH) {
				my_bullet[i].state = false;
			}
		}
		// Check for collision between the tank's bullets and the GOLD_coin
		for (int i = 0; i <MAX_GOLD_COINS; ++i) {
			for (j = 0; j < MAX_MY_BULLET; j++){
				if (gold_coins[i].state && my_bullet[j].state) {
					if (hit(my_bullet[j].x, my_bullet[j].y, gold_coins[i].x, gold_coins[i].y)){

						collectingCoinsGOLD++;
						gold_coins[i].state = false;
						my_bullet[j].state = false;

						// Play a sound effect when the coin is hit
						if (musicOn) {
							PlaySound("music\\coin_hit .wav", NULL, SND_ASYNC | SND_FILENAME);
							PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
						}
					}
				}
			}
		}
		// Check for collision between the tank's bullets and the diamond
		for (int i = 0; i <MAX_DIAMOND; ++i) {
			for (j = 0; j < MAX_MY_BULLET; j++){
				if (diamond_coins[i].state && my_bullet[j].state) {
					if (hit(my_bullet[j].x, my_bullet[j].y, diamond_coins[i].x, diamond_coins[i].y)){

						playerLifeCount++;
						PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
						diamond_coins[i].state = false;
						my_bullet[j].state = false;
					}
				}
			}
         }
	 }
}

void update_position_opp_bullet(){
	
    i_got_hit();

// Level 1
	if (currentMenu == LEVEL_1){
		if ( opp_bulletY > 0 ) {  // 1st tank bullet
			opp_bulletY -= 70; //if the number is increased the bullet speed will also increase
		}
		else {
			opp_bullet_reset();
		}
	}
	if (currentMenu == LEVEL_1){
		if ( opp_bullet2Y > 0 ) {  // 2nd tank bullet
			opp_bullet2Y -= 70; //if the number is increased the bullet speed will also increase
		}
		else {
			opp_bullet_reset();
		}
	}

// Level 2
	if (currentMenu == LEVEL_2){
		if (opp_bulletX > 0) {   // 1st tank bullet
			opp_bulletX -= 100;//if the number is increased the bullet speed will also increase
		}
		else if (opp_bullet2X > 0){
			opp_bullet2X -= 100;//if the number is increased the bullet speed will also increase
		}
		else {
			opp_bullet_reset();
		}
	}

// Level 3
	if (currentMenu == LEVEL_3){
		if (opp_bulletX > 0) {  // 1st tank bullet
			opp_bulletX -= 150;//if the number is increased the bullet speed will also increase
		}
		else if (opp_bullet2X > 0) {  // 2nd tank bullet
			opp_bullet2X -= 150;//if the number is increased the bullet speed will also increase
		}
		else {
			opp_bullet_reset();
		}
	}
}

void update_time(){

	int this_time = static_cast<long int> (time(NULL));
	time_toFinish_level = previous_time_Last_Paused + this_time - start_time_for_new_Game;
	time_exit = previous_time_Last_Paused + this_time - start_time_for_new_Game; 
}

void update_difficulty(){

	// if difficulty softness = 1/25; bullet speed will increase 1 per 25 frames
	int difficulty_softness = 50;// Adjust this value to make bullets come faster
	int max_difficulty = 100; // 
	int added_bullet_speed; // it will be no more than initial bullet speed
	added_bullet_speed = min(max_difficulty * initial_opp_bullet_speed, frame_count * difficulty_softness);
	opp_bullet_speed = initial_opp_bullet_speed + added_bullet_speed;
}

void update_positions(int value) {
 if (!isGamePaused) {
        update_position_my_tank();
        update_position_opp_tank();
        update_position_my_bullet();
        update_position_opp_bullet();
        update_time();
        // update_difficulty();
        // Set a delay for updating positions
        frame_count++;
        //cout << frame_count << '\n';
        //delay(0.02);
    }
    // Set a delay for updating positions
    glutTimerFunc(100, update_positions, 0);
}

void drawNewGameText() {

    iClear();
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_level1poster);

	iText(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT - 300, "Enter your name:", GLUT_BITMAP_HELVETICA_18);
	isEnteringName = 1;

	if ( isEnteringName == 1) {
		char playerNameCopy[50];
		strcpy_s(playerNameCopy, playerName.c_str());
		iText(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT - 340, playerNameCopy, GLUT_BITMAP_HELVETICA_18);
	}

    iText(SCREEN_WIDTH / 2 - 20, 80, "Press 'Enter' to continue...", GLUT_BITMAP_HELVETICA_18);

    initializeNewGame();
}

void iDraw() {

  switch (currentMenu) {

    case MENU_NEW_GAME:
        drawNewGameText();
        break;

	case LEVEL_1:
		drawLevel_1();
		break;

	case LEVEL_2:
		drawLevel_2();
		break;

   case LEVEL_3:
		drawLevel_3();
		break;

    case MENU_LEVEL1_COMPLETE:
            Level1_CompletePage();
            break;

  case MENU_LEVEL2_COMPLETE:
        Level2_CompletePage();
        break;

 case MENU_LEVEL3_COMPLETE:
        Level3_CompletePage();
        break;

    case LEVEL_2_BG:
            l2_poster();
            break;

    case LEVEL_3_BG:
            l3_poster();
            break;


    case MENU_ORIGINATORS:
        drawOriginators();
        break;

	case MENU_INSTRUCTION:
        instruction();
        break;

	 case MENU_SCORE:
        score(); // Call the score function to display the "Score" menu
        break;

    case MENU_SHOW_MENU:
        drawPlayOptions();
        break;

    case MENU_OPTIONS:
        drawOptions();
        break;

    case MENU_STORYLINE:
        drawStorylineText();
        break;

    case MENU_ABOUT:
        drawAboutText();
        break;

    case MENU_GAMEPOSTER:
    default:
        drawMenu();
        break;
    }
}
	
void iPassiveMouse(int mx, int my)
{
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      switch (currentMenu) {

		case MENU_OPTIONS:
			if (mx >= 370 && mx <= 570 && my >= 390 && my <= 490) {
				// Play button clicked, activate play functionality
				currentMenu = MENU_SHOW_MENU;
			} else if (mx >= 650 && mx <= 850 && my >= 390 && my <= 490) {
				currentMenu = MENU_ABOUT;
			} else if (mx >= 510 && mx <= 710 && my >= 210 && my <= 310) {
				currentMenu = MENU_ORIGINATORS;
			} else if (mx >= 790 && mx <= 990 && my >= 210 && my <= 310) {
				currentMenu = MENU_INSTRUCTION;
			} else if (mx >= 930 && mx <= 1130 && my >= 390 && my <= 490) {
				currentMenu = MENU_SCORE;
			}
			break;

			case MENU_ABOUT:
				if (mx >= SCREEN_WIDTH / 2 - 150 && mx <= SCREEN_WIDTH / 2 + 150 &&
					my >= 100 && my <= 124) {
					currentMenu = MENU_OPTIONS;
				}
				break;

			case MENU_ORIGINATORS:
				if (mx >= SCREEN_WIDTH / 2 - 150 && mx <= SCREEN_WIDTH / 2 + 150 &&
					my >= SCREEN_HEIGHT / 2 - 40 && my <= SCREEN_HEIGHT / 2 - 16) {
					currentMenu = MENU_OPTIONS;
				}
				break;

			case MENU_INSTRUCTION:
				if (mx >= SCREEN_WIDTH / 2 - 150 && mx <= SCREEN_WIDTH / 2 + 150 &&
					my >= SCREEN_HEIGHT / 2 - 40 && my <= SCREEN_HEIGHT / 2 + 16) {
					currentMenu = MENU_OPTIONS;
				}
				break;
         
		  case MENU_SCORE:
				if (mx >= SCREEN_WIDTH / 2 - 150 && mx <= SCREEN_WIDTH / 2 + 150 &&
					my >= SCREEN_HEIGHT / 2 - 40 && my <= SCREEN_HEIGHT / 2 + 16) {
					currentMenu = MENU_OPTIONS;
				}
				break;


		 case MENU_STORYLINE:
				if (mx >= SCREEN_WIDTH / 2 - 30 && mx <= SCREEN_WIDTH / 2 + 170 &&
					my >= 100 && my <= 124) {
					currentMenu = MENU_OPTIONS;
				}
				break;

		 case MENU_SHOW_MENU:
				if (mx >= 250 && mx <= 400 && my >= 500 && my <= 600) {
					isNewGameSelected = true;
					currentMenu = MENU_NEW_GAME;
				}
				else if (mx >= 250 && mx <= 400 && my >= 380 && my <= 480)  {
					//For handling mouse clicks when "Resume Game" is selected
					loadSavedGame();
					if (isGameOngoing) {
						isGamePaused = false; // Unpause the game since we are resuming
					  }
				}
				break;
			default:
				break;
        }
    }

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (isNewGameSelected) {
            if (mx >= SCREEN_WIDTH / 2 - 350 && mx <= SCREEN_WIDTH / 2 + 350 &&
                my >= SCREEN_HEIGHT - 300 && my <= SCREEN_HEIGHT - 276) {
               // isEnteringName = true;
            }
        }
	}
}

void iKeyboard(unsigned char key) {
	
	if (currentMenu == LEVEL_1 || currentMenu == LEVEL_2 || currentMenu == LEVEL_3) {
		switch (key){
			case 'w':
			case 'W':
				 if (!isGamePaused) {
					 my_tankY += 10;
				 }
				 break;

			case 'a':
			case 'A':
				if (!isGamePaused) {
					my_tankX -= 10;
				}
				break;

			case 's':
			case 'S':
				if (!isGamePaused) {
					my_tankY -= 10;
				}
				break;

			case 'D':
			case 'd':
				if (!isGamePaused) {
					my_tankX += 10; // Move the tank right
				}
				break;

			case 32: // Spacebar: Fire bullets
				if (!isGamePaused) {
					for (int i = 0; i < MAX_MY_BULLET; i++) {
						if (my_bullet[i].state == false) {
							my_bullet[i].state = true;
							if (currentMenu == LEVEL_1) {
								my_bullet[i].x = my_tankX + 25;
								my_bullet[i].y = my_tankY + 100;
							} else if (currentMenu == LEVEL_2 || currentMenu == LEVEL_3) {
								my_bullet[i].x = my_tankX + 25;
								my_bullet[i].y = my_tankY + 70;
							}
							break;
						}
					}
				}
				break;
			default :
				break;
		}
	}

    switch (key) {
		 case '1': // '1' key: Activate Play option
            currentMenu = MENU_SHOW_MENU;
            break;
        case '2': // '2' key: Activate About option
            currentMenu = MENU_ABOUT;
            break;
        case '3': // '3' key: Activate Score option
            currentMenu = MENU_SCORE;
            break;
        case '4': // '4' key: Activate Originators option
            currentMenu = MENU_ORIGINATORS;
            break;
        case '5': // '5' key: Activate Instructions option
            currentMenu = MENU_INSTRUCTION;
            break;
		
		case 13: // Enter key
			switch (currentMenu) {
			case MENU_GAMEPOSTER:
					currentMenu = MENU_STORYLINE;
					break;

				// Add a new case to handle "Enter" press on the l2_poster screen
		    case LEVEL_2_BG:
					if (currentMenu == LEVEL_2_BG) {
						enterPressedOnL2Poster = true;
						currentMenu = LEVEL_2;
						initializeNewGame();
						isGameOngoing = true;
					}
					break;

			   case LEVEL_3_BG:
					if (currentMenu == LEVEL_3_BG) {
						enterPressedOnL3Poster = true;
						currentMenu = LEVEL_3;
						initializeNewGame();
						isGameOngoing = true;
					}
					break;

			  case MENU_NEW_GAME:
					currentMenu = LEVEL_1;
					initializeNewGame();
					isGameOngoing = true;
					break;

				case LEVEL_1:
					// Handle logic. For example, pause/unpause the game or display a message
					break;

				case MENU_LEVEL1_COMPLETE:
						currentMenu = LEVEL_2_BG;
						// Transition to the next page (LEVEL_2_BG)
						break;

			  case MENU_LEVEL2_COMPLETE:
						currentMenu = LEVEL_3_BG;
						// Transition to the next page (LEVEL_3_BG)
						break;

				case MENU_STORYLINE:
					currentMenu = MENU_OPTIONS;
					break;

				case MENU_OPTIONS:
					currentMenu = MENU_SHOW_MENU;
					break;
				
				case MENU_ABOUT:
				case MENU_ORIGINATORS:
				case MENU_INSTRUCTION:
				case MENU_SCORE:
				case MENU_SHOW_MENU:
					currentMenu = MENU_OPTIONS; //to come back to "Main menu"
					break;

				default:
					break;
				}
			break;


        case 27: // Esc key
            handleExit();
            break;

        case 9: // Tab key: pause/unpause
            if (currentMenu == LEVEL_1 || currentMenu == LEVEL_2 || currentMenu == LEVEL_3) {
                isGamePaused = !isGamePaused; // Toggle the pause state
                if (isGamePaused) {
                     previous_time_Last_Paused = time_toFinish_level;
					 previous_time_Last_Paused = time_exit;
                } else {
                    int this_time = static_cast<long int>(time(NULL));
                    start_time_for_new_Game = this_time;
                }
            }
            break;

        default:
            if (isEnteringName == 1) {
                if (key == 8) { // Backspace key
                    if (!playerName.empty()) {
                        playerName.pop_back();
					}
				} else {
                    playerName += key;
				}
			}
			break;
}
}

void iSpecialKeyboard(unsigned char key) {
    int count_bullet = 0;
	cout << count_bullet << endl;
	if (currentMenu == LEVEL_1 || currentMenu == LEVEL_2 || currentMenu == LEVEL_3) {
		for (int i = 0; i < MAX_MY_BULLET; i++){
			if (my_bullet[i].state){
				count_bullet += 1;
			}
		}

		if (count_bullet == 1){
			switch (key){
				case GLUT_KEY_UP:
					{
						my_bullet[1].y += bullet_swing_step; // Move up
						break;
					}
				case GLUT_KEY_DOWN:
					my_bullet[1].y -= bullet_swing_step; // Move down
					break;
				case GLUT_KEY_LEFT:
					my_bullet[1].x -= bullet_swing_step; // Move left
					break;
				case GLUT_KEY_RIGHT:
					my_bullet[1].x += bullet_swing_step; // Move right
					break;
				default:
					break;
			}
		}
	}
}

void bg_uw45(){
	underwater_photos[0] = iLoadImage("pic\\uwpng\\frame_001.png");
	underwater_photos[1] = iLoadImage("pic\\uwpng\\frame_002.png");
	underwater_photos[2] = iLoadImage("pic\\uwpng\\frame_003.png");
	underwater_photos[3] = iLoadImage("pic\\uwpng\\frame_004.png");
	underwater_photos[4] = iLoadImage("pic\\uwpng\\frame_005.png");
	underwater_photos[5] = iLoadImage("pic\\uwpng\\frame_006.png");
	underwater_photos[6] = iLoadImage("pic\\uwpng\\frame_007.png");
	underwater_photos[7] = iLoadImage("pic\\uwpng\\frame_008.png");
	underwater_photos[8] = iLoadImage("pic\\uwpng\\frame_009.png");
	underwater_photos[9] = iLoadImage("pic\\uwpng\\frame_010.png");
	underwater_photos[10] = iLoadImage("pic\\uwpng\\frame_011.png");
	underwater_photos[11] = iLoadImage("pic\\uwpng\\frame_012.png");
	underwater_photos[12] = iLoadImage("pic\\uwpng\\frame_013.png");
	underwater_photos[13] = iLoadImage("pic\\uwpng\\frame_014.png");
	underwater_photos[14] = iLoadImage("pic\\uwpng\\frame_015.png");
	underwater_photos[15] = iLoadImage("pic\\uwpng\\frame_016.png");
	underwater_photos[16] = iLoadImage("pic\\uwpng\\frame_017.png");
	underwater_photos[17] = iLoadImage("pic\\uwpng\\frame_018.png");
	underwater_photos[18] = iLoadImage("pic\\uwpng\\frame_019.png");
	underwater_photos[19] = iLoadImage("pic\\uwpng\\frame_020.png");
	underwater_photos[20] = iLoadImage("pic\\uwpng\\frame_021.png");
	underwater_photos[21] = iLoadImage("pic\\uwpng\\frame_022.png");
	underwater_photos[22] = iLoadImage("pic\\uwpng\\frame_023.png");
	underwater_photos[23] = iLoadImage("pic\\uwpng\\frame_024.png");
	underwater_photos[24] = iLoadImage("pic\\uwpng\\frame_025.png");
	underwater_photos[25] = iLoadImage("pic\\uwpng\\frame_026.png");
	underwater_photos[26] = iLoadImage("pic\\uwpng\\frame_027.png");
	underwater_photos[27] = iLoadImage("pic\\uwpng\\frame_028.png");
	underwater_photos[28] = iLoadImage("pic\\uwpng\\frame_029.png");
	underwater_photos[29] = iLoadImage("pic\\uwpng\\frame_030.png");
	underwater_photos[30] = iLoadImage("pic\\uwpng\\frame_031.png");
	underwater_photos[31] = iLoadImage("pic\\uwpng\\frame_032.png");
	underwater_photos[32] = iLoadImage("pic\\uwpng\\frame_033.png");
	underwater_photos[33] = iLoadImage("pic\\uwpng\\frame_034.png");
	underwater_photos[34] = iLoadImage("pic\\uwpng\\frame_035.png");
	underwater_photos[35] = iLoadImage("pic\\uwpng\\frame_036.png");
	underwater_photos[36] = iLoadImage("pic\\uwpng\\frame_037.png");
	underwater_photos[37] = iLoadImage("pic\\uwpng\\frame_038.png");
	underwater_photos[38] = iLoadImage("pic\\uwpng\\frame_039.png");
	underwater_photos[39] = iLoadImage("pic\\uwpng\\frame_040.png");
	underwater_photos[40] = iLoadImage("pic\\uwpng\\frame_041.png");
	underwater_photos[41] = iLoadImage("pic\\uwpng\\frame_042.png");
	underwater_photos[42] = iLoadImage("pic\\uwpng\\frame_043.png");
	underwater_photos[43] = iLoadImage("pic\\uwpng\\frame_044.png");
	underwater_photos[44] = iLoadImage("pic\\uwpng\\frame_045.png");

}

/*
void bg_space10(){
	space_photos[0] = iLoadImage("pic\\spacepng\\frame_0001.png");
	space_photos[1] = iLoadImage("pic\\spacepng\\frame_0002.png");
	space_photos[2] = iLoadImage("pic\\spacepng\\frame_0003.png");
	space_photos[3] = iLoadImage("pic\\spacepng\\frame_0004.png");
	space_photos[4] = iLoadImage("pic\\spacepng\\frame_0005.png");
	space_photos[5] = iLoadImage("pic\\spacepng\\frame_0006.png");
	space_photos[6] = iLoadImage("pic\\spacepng\\frame_0007.png");
	space_photos[7] = iLoadImage("pic\\spacepng\\frame_0008.png");
	space_photos[8] = iLoadImage("pic\\spacepng\\frame_0009.png");
	space_photos[9] = iLoadImage("pic\\spacepng\\frame_0010.png");
}*/

void bg_menu100(){
	menu_animation[0] = iLoadImage("pic\\menu_ani\\frame_001.png");
	menu_animation[1] = iLoadImage("pic\\menu_ani\\frame_002.png");
	menu_animation[2] = iLoadImage("pic\\menu_ani\\frame_003.png");
	menu_animation[3] = iLoadImage("pic\\menu_ani\\frame_004.png");
	menu_animation[4] = iLoadImage("pic\\menu_ani\\frame_005.png");
	menu_animation[5] = iLoadImage("pic\\menu_ani\\frame_006.png");
	menu_animation[6] = iLoadImage("pic\\menu_ani\\frame_007.png");
	menu_animation[7] = iLoadImage("pic\\menu_ani\\frame_008.png");
	menu_animation[8] = iLoadImage("pic\\menu_ani\\frame_009.png");
	menu_animation[9] = iLoadImage("pic\\menu_ani\\frame_010.png");
	menu_animation[10] = iLoadImage("pic\\menu_ani\\frame_011.png");
	menu_animation[11] = iLoadImage("pic\\menu_ani\\frame_012.png");
	menu_animation[12] = iLoadImage("pic\\menu_ani\\frame_013.png");
	menu_animation[13] = iLoadImage("pic\\menu_ani\\frame_014.png");
	menu_animation[14] = iLoadImage("pic\\menu_ani\\frame_015.png");
	menu_animation[15] = iLoadImage("pic\\menu_ani\\frame_016.png");
	menu_animation[16] = iLoadImage("pic\\menu_ani\\frame_017.png");
	menu_animation[17] = iLoadImage("pic\\menu_ani\\frame_018.png");
	menu_animation[18] = iLoadImage("pic\\menu_ani\\frame_019.png");
	menu_animation[19] = iLoadImage("pic\\menu_ani\\frame_020.png");
	menu_animation[20] = iLoadImage("pic\\menu_ani\\frame_021.png");
	menu_animation[21] = iLoadImage("pic\\menu_ani\\frame_022.png");
	menu_animation[22] = iLoadImage("pic\\menu_ani\\frame_023.png");
	menu_animation[23] = iLoadImage("pic\\menu_ani\\frame_024.png");
	menu_animation[24] = iLoadImage("pic\\menu_ani\\frame_025.png");
	menu_animation[25] = iLoadImage("pic\\menu_ani\\frame_026.png");
	menu_animation[26] = iLoadImage("pic\\menu_ani\\frame_027.png");
	menu_animation[27] = iLoadImage("pic\\menu_ani\\frame_028.png");
	menu_animation[28] = iLoadImage("pic\\menu_ani\\frame_029.png");
	menu_animation[29] = iLoadImage("pic\\menu_ani\\frame_030.png");
	menu_animation[30] = iLoadImage("pic\\menu_ani\\frame_031.png");
	menu_animation[31] = iLoadImage("pic\\menu_ani\\frame_032.png");
	menu_animation[32] = iLoadImage("pic\\menu_ani\\frame_033.png");
	menu_animation[33] = iLoadImage("pic\\menu_ani\\frame_034.png");
	menu_animation[34] = iLoadImage("pic\\menu_ani\\frame_035.png");
	menu_animation[35] = iLoadImage("pic\\menu_ani\\frame_036.png");
	menu_animation[36] = iLoadImage("pic\\menu_ani\\frame_037.png");
	menu_animation[37] = iLoadImage("pic\\menu_ani\\frame_038.png");
	menu_animation[38] = iLoadImage("pic\\menu_ani\\frame_039.png");
	menu_animation[39] = iLoadImage("pic\\menu_ani\\frame_040.png");
	menu_animation[40] = iLoadImage("pic\\menu_ani\\frame_041.png");
	menu_animation[41] = iLoadImage("pic\\menu_ani\\frame_042.png");
	menu_animation[42] = iLoadImage("pic\\menu_ani\\frame_043.png");
	menu_animation[43] = iLoadImage("pic\\menu_ani\\frame_044.png");
	menu_animation[44] = iLoadImage("pic\\menu_ani\\frame_045.png");
	menu_animation[45] = iLoadImage("pic\\menu_ani\\frame_046.png");
	menu_animation[46] = iLoadImage("pic\\menu_ani\\frame_047.png");
	menu_animation[47] = iLoadImage("pic\\menu_ani\\frame_048.png");
	menu_animation[48] = iLoadImage("pic\\menu_ani\\frame_049.png");
	menu_animation[49] = iLoadImage("pic\\menu_ani\\frame_050.png");
	menu_animation[50] = iLoadImage("pic\\menu_ani\\frame_051.png");
	menu_animation[51] = iLoadImage("pic\\menu_ani\\frame_052.png");
	menu_animation[52] = iLoadImage("pic\\menu_ani\\frame_053.png");
	menu_animation[53] = iLoadImage("pic\\menu_ani\\frame_054.png");
	menu_animation[54] = iLoadImage("pic\\menu_ani\\frame_055.png");
	menu_animation[55] = iLoadImage("pic\\menu_ani\\frame_056.png");
	menu_animation[56] = iLoadImage("pic\\menu_ani\\frame_057.png");
	menu_animation[57] = iLoadImage("pic\\menu_ani\\frame_058.png");
	menu_animation[58] = iLoadImage("pic\\menu_ani\\frame_059.png");
	menu_animation[59] = iLoadImage("pic\\menu_ani\\frame_060.png");
	menu_animation[60] = iLoadImage("pic\\menu_ani\\frame_061.png");
	menu_animation[61] = iLoadImage("pic\\menu_ani\\frame_062.png");
	menu_animation[62] = iLoadImage("pic\\menu_ani\\frame_063.png");
	menu_animation[63] = iLoadImage("pic\\menu_ani\\frame_064.png");
	menu_animation[64] = iLoadImage("pic\\menu_ani\\frame_065.png");
	menu_animation[65] = iLoadImage("pic\\menu_ani\\frame_066.png");
	menu_animation[66] = iLoadImage("pic\\menu_ani\\frame_067.png");
	menu_animation[67] = iLoadImage("pic\\menu_ani\\frame_068.png");
	menu_animation[68] = iLoadImage("pic\\menu_ani\\frame_069.png");
	menu_animation[69] = iLoadImage("pic\\menu_ani\\frame_070.png");
	menu_animation[70] = iLoadImage("pic\\menu_ani\\frame_071.png");
	menu_animation[71] = iLoadImage("pic\\menu_ani\\frame_072.png");
	menu_animation[72] = iLoadImage("pic\\menu_ani\\frame_073.png");
	menu_animation[73] = iLoadImage("pic\\menu_ani\\frame_074.png");
	menu_animation[74] = iLoadImage("pic\\menu_ani\\frame_075.png");
	menu_animation[75] = iLoadImage("pic\\menu_ani\\frame_076.png");
	menu_animation[76] = iLoadImage("pic\\menu_ani\\frame_077.png");
	menu_animation[77] = iLoadImage("pic\\menu_ani\\frame_078.png");
	menu_animation[78] = iLoadImage("pic\\menu_ani\\frame_079.png");
	menu_animation[79] = iLoadImage("pic\\menu_ani\\frame_080.png");
	menu_animation[80] = iLoadImage("pic\\menu_ani\\frame_081.png");
	menu_animation[81] = iLoadImage("pic\\menu_ani\\frame_082.png");
	menu_animation[82] = iLoadImage("pic\\menu_ani\\frame_083.png");
	menu_animation[83] = iLoadImage("pic\\menu_ani\\frame_084.png");
	menu_animation[84] = iLoadImage("pic\\menu_ani\\frame_085.png");
	menu_animation[85] = iLoadImage("pic\\menu_ani\\frame_086.png");
	menu_animation[86] = iLoadImage("pic\\menu_ani\\frame_087.png");
	menu_animation[87] = iLoadImage("pic\\menu_ani\\frame_088.png");
	menu_animation[88] = iLoadImage("pic\\menu_ani\\frame_089.png");
	menu_animation[89] = iLoadImage("pic\\menu_ani\\frame_090.png");
	menu_animation[90] = iLoadImage("pic\\menu_ani\\frame_091.png");
	menu_animation[91] = iLoadImage("pic\\menu_ani\\frame_092.png");
	menu_animation[92] = iLoadImage("pic\\menu_ani\\frame_093.png");
	menu_animation[93] = iLoadImage("pic\\menu_ani\\frame_094.png");
	menu_animation[94] = iLoadImage("pic\\menu_ani\\frame_095.png");
	menu_animation[95] = iLoadImage("pic\\menu_ani\\frame_096.png");
	menu_animation[96] = iLoadImage("pic\\menu_ani\\frame_097.png");
	menu_animation[97] = iLoadImage("pic\\menu_ani\\frame_098.png");
	menu_animation[98] = iLoadImage("pic\\menu_ani\\frame_099.png");
	menu_animation[99] = iLoadImage("pic\\menu_ani\\frame_100.png");
}

void bg(){

	bg_game_poster = iLoadImage("pic\\bg_game_poster.jpg");
	bg_storyline =  iLoadImage("pic\\bg_storyline.jpg");
	bg_newgame =  iLoadImage("pic\\bg_newgame.jpg");
	bg_menu =  iLoadImage("pic\\bg_menu.jpg");
	bg_originators =  iLoadImage("pic\\bg_originators.png");
	instruc = iLoadImage("pic\\instruction.png");
	bg_about =  iLoadImage("pic\\bg_about.png");
	bgscore =  iLoadImage("pic\\score.jpg");

	play_button = iLoadImage("pic\\play_button.png");
	about_button =  iLoadImage("pic\\about_button.png");
	score_button =  iLoadImage("pic\\score_button.png");
	originators_button =  iLoadImage("pic\\originators-button.png");
	instruction_button =  iLoadImage("pic\\instruction_button.png");
	main_menu_button =  iLoadImage("pic\\main_menu_button.png");
	playoption_button =  iLoadImage("pic\\play_option_button.png");
	new_game_button =  iLoadImage("pic\\new_game_button.png");
	resume_button =  iLoadImage("pic\\resume_button.png");
	enter_name =  iLoadImage("pic\\enter_name.jpg");

	grass =  iLoadImage("pic\\grass.jpg");
	space = iLoadImage("pic\\SPACE.jpg");
	congrats =  iLoadImage("pic\\l1-congo.jpg");

	bg_level1poster =  iLoadImage("pic\\bg_level1poster.jpg");
	bg_l2poster =  iLoadImage("pic\\2-poster.jpg");
	bg_l3poster =  iLoadImage("pic\\final-poster.jpg");

	my_tank =  iLoadImage("pic\\my_tank.png");
	opp_tank =  iLoadImage("pic\\opp_tank.png");
	my_submarine =  iLoadImage("pic\\my_submarin.png");
	opp_submarine =  iLoadImage("pic\\opp_submarin.png");
	my_spaceship =  iLoadImage("pic\\my_spaceship.png");
	opp_spaceship =  iLoadImage("pic\\opp_spaceship.png");

	opp_sub_bullet =  iLoadImage("pic\\opp-sub_bullet.png");
	my_sub_bullet = iLoadImage("pic\\my-sub_bullet.png");
	my_bullet_image = iLoadImage("pic\\my_bullet.png");
	opp_bullet = iLoadImage("pic\\opp_bullet.png");

    blue_coin= iLoadImage("pic\\blue.png");
	gold_coin= iLoadImage("pic\\gold.png");
	red_coin= iLoadImage("pic\\red.png");
	stone= iLoadImage("pic\\stone.png");
    diamond = iLoadImage("pic\\diamond.png");

	bg_uw45();
	//bg_space10();
	bg_menu100();
}

int main()
{
	if (musicOn) {
		PlaySound("music\\sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}
    
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "GAME");
	bg(); 
	srand(time(0));
	glutTimerFunc(100, update_positions, 0); 

	iStart(); // it will start drawing
	return 0;
}
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <limits>
#include <fstream>
#include <queue>

using namespace std;
int life;
int level;
int score=0;
string playerNickname;
int const screenHeight = 27;
int const screenWidth = 30;
int map[screenHeight][screenWidth];
vector<vector<char>> bricks;
bool useArrowKeys = true;
bool decre_life;
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void hideCursor() 
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
class Paddle 
{
public:
    int x;
    int y;
    int speed;
    char dir;
    
    void draw() 
	{
        for (int i = 0; i < 9; i++)
            map[y][x + i] = 1;
    }

    void move() 
	{
            if (dir == 'L' && x - speed > 0) {
                x -= speed;
            } else if (dir == 'R' && x + speed < screenWidth - 9) {
                x += speed;
            }
            
        if (decre_life) {
            dir = 'S';
            x = screenWidth / 2 - 5;
            y = screenHeight - screenHeight / 7 - 1;
            decre_life = false;
        }
    }
};

class Ball {
public:
    int x;
    int y;
    int speed;
    int dir;

    void draw() {
        map[y][x] = 5;
    }

    void move() {
        if (dir == 0 && !collision(x - speed, y - speed)) {
            x -= speed;
            y -= speed;
        } else if (dir == 1 && !collision(x + speed, y - speed)) {
            x += speed;
            y -= speed;
        } else if (dir == 2 && !collision(x - speed, y + speed)) {
            x -= speed;
            y += speed;
        } else if (dir == 3 && !collision(x + speed, y + speed)) {
            x += speed;
            y += speed;
        }
    }
 
    bool collision(int fx, int fy) {
        if (map[fy][x] == 8) {
            decre_life = true;
            x = screenWidth / 2 - 1;
            y = screenHeight - screenHeight / 7 - 3;
            dir = 4;
            life--;
        } else if (map[fy][fx] != 0 || map[y][fx] != 0 || map[fy][x] != 0) {
            if (map[fy][fx] == 2) { bricks[fy - 2][fx - 6] = ' '; score += 1; }
            else if (map[y][fx] == 2) { bricks[y - 2][fx - 6] = ' '; score += 1; }
            else if (map[fy][x] == 2) { bricks[fy - 2][x - 6] = ' '; score += 1; }

            if (map[y][fx] != 0) bounce(fx, y);
            else if (map[fy][x] != 0) bounce(x, fy);
            else bounce(fx, fy);

            return true;
        }

        return false;
    }

    void bounce(int fx, int fy) {
        if (dir == 0) {
            if (fx < x) dir = 1;
            else if (fy < y) dir = 2;
            else if (fx < x && fy < y) dir = 0;
        } else if (dir == 1) {
            if (fx > x) dir = 0;
            else if (fy < y) dir = 3;
            else if (fx > x && fy < y) dir = 1;
        } else if (dir == 2) {
            if (fx < x) dir = 3;
            else if (fy > y) dir = 0;
            else if (fx < x && fy > y) dir = 2;
        } else if (dir == 3) {
            if (fx > x) dir = 2;
            else if (fy > y) dir = 1;
            else if (fx > x && fy > y) dir = 3;
        }
    }
};

Paddle paddle;
Ball ball;

void generateBricks() {
    bricks.clear();
    int rows = 2 + level;
    if (rows > 9) rows = 9;

    for (int i = 0; i < rows; i++) {
        vector<char> row(17, '#');
        for (int j = 0; j < 17; j++) {
            if (rand() % 100 < 20) {
                row[j] = ' ';
            }
        }
        bricks.push_back(row);
    }
}

void getNickname() {
    cout << "\t\t\t\t\t----------------------" << endl;
    cout << "\t\t\t\t\t|ENTER YOUR NICK-NAME:|" << endl;
    cout << "\t\t\t\t\t-----------------------" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin,playerNickname);
    system("cls");
    gotoxy(50, 1);
    cout << "\t\t\t\t\t|WELCOME " << playerNickname << "|" << endl;
}

void setup() {
    srand(time(NULL));
    score=0;
    decre_life = false;
    life=5; 
    level = 1;
    paddle.x = screenWidth / 2 - 5;
    paddle.y = screenHeight - screenHeight / 7 - 1;
    paddle.speed = 1;
    ball.x = screenWidth / 2;
    ball.y = screenHeight - screenHeight / 7 - 2;
    ball.speed = 1;
    ball.dir = rand() % 4;
    generateBricks();
}

void wall() {
    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            if (j == 0 || j == screenWidth - 1) map[i][j] = 9;  //generates side wall
            else if (i == 0) map[i][j] = 7;   //generated upper wall
            else if (i == screenHeight - 1) map[i][j] = 8;    //generated lower wall
            else map[i][j] = 0;     //generated empety space for ball to move
        }
    }
}

void brick() {
    for (int i = 0; i < bricks.size(); i++) {
        for (int j = 0; j < 17; j++) {
            if (bricks[i][j] == '#') map[i + 2][j + 6] = 2;
        }
    }
}

void layout() {
    wall();
    paddle.draw();
    ball.draw();
    brick();
}

void display() {
    gotoxy(2, 1); cout << "LEVEL: " << level << "   LIFE: " << life << "   SCORE: " << score;

    for (int i = 0; i < screenHeight; i++) {
        for (int j = 0; j < screenWidth; j++) {
            gotoxy(j + 2, i + 3);
            if (map[i][j] == 9) cout << char(219);
            if (map[i][j] == 1) cout << char(219);
            if (map[i][j] == 2) cout << char(240);
            if (map[i][j] == 7) cout << char(219);
            if (map[i][j] == 8) cout << char(233);
            if (map[i][j] == 5) cout << char(254);
            if (map[i][j] == 0) cout << char(32);
        }
    }
}

void input() {
    if (_kbhit()) {
        int key = _getch();
        if (useArrowKeys) {
            switch (key) {
            case 75: // Left arrow
                paddle.dir = 'L';
                break;
            case 77: // Right arrow
                paddle.dir = 'R';
                break;
            case 27: // ESC key
                throw 1; // Throw an exception to return to main menu
            }
        } else {
            switch (key) {
            case 'a':
            case 'A':
                paddle.dir = 'L';
                break;
            case 'd':
            case 'D':
                paddle.dir = 'R';
                break;
            case 27: // ESC key
                throw 1; // Throw an exception to return to main menu
            }
        }
        if (ball.dir == 4) ball.dir = rand() % 2;
    }
}

void movements() {
    paddle.move();
    ball.move();
}

bool levelComplete() {
    for (const auto& row : bricks) {
        for (char c : row) {
            if (c == '#') return false;
        }
    }
    return true;
}

void instructions() {
    cout << "\n------------------------- GAME INSTRUCTIONS -------------------------\n";
    cout << "\nWelcome to the Brick Breaker game!\n";
    cout << "The objective of the game is to break all the bricks by bouncing a ball off a paddle.\n";
    if (useArrowKeys) {
        cout << "Use the left and right arrow keys to move the paddle.\n";
    } else {
        cout << "Use 'A' to move the paddle left and 'S' to move the paddle right.\n";
    }
    cout << "Each time the ball hits a brick, the brick will break, and you earn 10 points.\n";
    cout << "If the ball falls off the screen (below the paddle), you will lose one life.\n";
    cout << "If you lose all lives, the game is over.\n";
    cout << "You can move to the next level once all the bricks are cleared.\n";
    cout << "There are total ten levels in this game with each level the difficulty of the game increases.\n";
    cout << "The difficulty can be increased in two ways either the number of rows of bricks increases up to 7 or number of bricks increases.\n";
    cout << "\nGame Controls:\n";
    if (useArrowKeys) {
        cout << "  - Use LEFT arrow key to move the paddle left.\n";
        cout << "  - Use RIGHT arrow key to move the paddle right.\n";
    } else {
        cout << "  - Use 'A' key to move the paddle left.\n";
        cout << "  - Use 'S' key to move the paddle right.\n";
    }
    cout << "  - Try to break all the bricks on the screen.\n";
    cout << "  - Avoid the ball from falling off the screen.\n";
    cout << "  - Press ESC at any time to return to the main menu.\n";
    cout << "\nGood luck and enjoy the game!\n";
    cout << "\n---------------------------------------------------------------------\n";
}

void gameOver() {
    system("cls");
    cout << " GAMEOVER " << endl;
    cout << " You reached level " << level << endl;
    cout << " Your final score: " << score << endl;
    cout << " Do you want to play again? (y/n)" << endl;
}

const string baseDirectory = "D:\\Desktop\\game_players\\";
void saveScore()
{
    string filename = baseDirectory + playerNickname + ".txt";
    ofstream file(filename);

    if (file.is_open()) {
        file << "Nickname: " << playerNickname << endl;
        file << "Score: " << score << endl;
        file << "Level: " << level << endl;
        file.close();
        cout << "Score saved successfully." << endl;
    } else {
        cout << "Unable to save score." << endl;
    }
}

void showLeaderboard() {
    priority_queue<pair<int, string>> leaderboard;

    string searchPath = baseDirectory + "*.txt";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            string filePath = baseDirectory + findFileData.cFileName;
            ifstream file(filePath);

            string line, nickname;
            int playerScore = 0;

            if (file.is_open()) {
                while (getline(file, line)) {
                    if (line.find("Nickname: ") != string::npos) {
                        nickname = line.substr(10);
                    } else if (line.find("Score: ") != string::npos) {
                        playerScore = stoi(line.substr(7));
                    }
                }
                leaderboard.push({playerScore, nickname});
                file.close();
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|  LEADER-BOARD    |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;
    int rank = 1;
    while (!leaderboard.empty() && rank <= 10) {
        cout << rank << ". " << leaderboard.top().second << ": " << leaderboard.top().first << endl;
        leaderboard.pop();
        rank++;
    }
}


void background_assets()
{
	int x;
	label2:
	cout << "SELECT THE BACKGROUND AND THE GAME ASSETS COLOR:\n";
        cout << "1---BACKGROUND=WHITE         ||  ASSETS=BLUE\n";
        cout << "2---BACKGROUND=GREY          ||  ASSETS=BLACK\n";
        cout << "3---BACKGROUND=RED           ||  ASSETS=LIGHT_YELLOW\n";
        cout << "4---BACKGROUND=GREEN         ||  ASSETS=PURPLE\n";
        cout << "5---DEFAULT COLORS\n";
        cin >> x;
        if (x > 5 || x < 1 || cin.fail() || (cin.peek() != EOF && cin.peek() != '\n')) {
            cout << "Invalid input! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto label2;
        }
        if (x == 1) system("color F9");
        else if (x == 2) system("color 80");
        else if (x == 3) system("color 4E");
        else if (x == 4) system("color A5");
        else if (x == 5) system("color 07");
}
void user_controls()
{
	int x;
	cout << "  \t\t\t\t\t-------------------------" << endl;
    cout << "  \t\t\t\t\t| Choose control scheme: |" << endl;
    cout << "  \t\t\t\t\t-------------------------" << endl;
    
    cout << "  \t\t----------------\t\t\t\t\t---------------------"<<endl;    
    cout << "  \t\t|1. Arrow keys |\t\t\t\t\t|2. 'A' and 'D' keys |"<<endl;
    cout << "  \t\t----------------\t\t\t\t\t---------------------"<<endl;
        controls:
        cout<<"Enter your choice:\n";
		cin >> x;
        if (x > 2 || x < 1 || cin.fail() || (cin.peek() != EOF && cin.peek() != '\n')) {
        cout << "Invalid input! Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto controls;
    }
        if (x == 1) {
            useArrowKeys = true;
        } else if (x == 2) {
            useArrowKeys = false;
        } else {
            cout << "Invalid choice. Defaulting to arrow keys.\n";
            useArrowKeys = true;
        }
}
int main() {
    system("title Brick Breaker Game");
    hideCursor(); 
    int choice;
    cout << "\t\t\t\t\t\tBRICK-BREAKER\n";
label1:
    cout << "MAIN-MENU:\n";
    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|  1-START GAME    |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;

    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|  2-INSTRUCTIONS  |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;

    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|    3-SETTINGS    |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;

    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|  4-LEADERBOARD   |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;

    cout << "  \t\t\t\t\t-------------------" << endl;
    cout << "  \t\t\t\t\t|      5-QUIT      |" << endl;
    cout << "  \t\t\t\t\t-------------------" << endl;
label:
    cout << "\nEnter your choice (1-5): ";
    cin >> choice;
    if (choice > 5 || choice < 1 || cin.fail() || (cin.peek() != EOF && cin.peek() != '\n')) {
        cout << "Invalid input! Please enter a valid number.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto label;
    }
    if (choice == 1) {
        system("cls");
        getNickname();
        while (true) {
        	hideCursor();
            setup(); // Reset the game state
            try {
                while (life > 0 && level <= 10) {
                	
                    display();
                    layout();
                    input();
                    movements();
                    if (levelComplete() && level != 10) {
                        saveScore();
                        level++;
                        generateBricks();
                        ball.x = screenWidth / 2;
                        ball.y = screenHeight - screenHeight / 7 - 2;
                        ball.dir = rand() % 4;
                        paddle.x = screenWidth / 2 - 5;
                        
                        cout << "\n\nLevel " << level - 1 << " complete! Press any key to continue or ESC to return to main menu.";
                        if (_getch() == 27) {
                            throw 1; // Return to main menu
                        }
                        system("cls");
                    }
                }
            } catch (int e) {
                if (e == 1) {
                    system("cls");
                    break; // Exit the while(true) loop and return to main menu
                }
            }
            saveScore();
            char ch;
            gameOver();
            cin >> ch;
            if (ch != 'y' && ch != 'Y') {
                system("cls");
                break; // Exit the while(true) loop and return to main menu
            }
            system("cls");
        }
        goto label1; // Return to main menu after game over or user chooses not to play again
    } else if (choice == 2) {
        instructions();
        system("pause");
        system("cls");
        goto label1;
    } else if (choice == 3) {
    	system("cls");
        cout << "\t\t\t\t-------------------" << endl;
        cout << "\t\t\t\t|    SETTINGS     |" << endl;
        cout << "\t\t\t\t-------------------" << endl;
        gotoxy(50,1);
        cout << "\t\t\t\t| 1-CONTROL |" << endl;
        gotoxy(50,3);
        cout << "\t\t\t\t|2-BACKGROUND-ASSETS|" << endl;
        gotoxy(50,5);
        cout << "\t\t\t\t|3-MAIN-MENU|" << endl;
        settings:
        cout<<"Select the preferable option:\n";
    	int x;
    		cin>>x;
    	if (x > 3 || x < 1 || cin.fail() || (cin.peek() != EOF && cin.peek() != '\n')) {
        cout << "Invalid input! Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto settings;
    }
    
    	if(x==1) 
		{
			user_controls();
			cout << "\t\t\t\t\tSETTING UPDATED SUCCESSFULLY...\n";
			goto label1;
		}
		else if(x==2)
		{
			background_assets();
			cout << "\t\t\t\t\tSETTING UPDATED SUCCESSFULLY...\n";
			goto label1;
		}
		else if(x==3) goto label1;
    } else if (choice == 4) {
        showLeaderboard();
        system("pause");
        system("cls");
        goto label1;
    } else if (choice == 5) {
        cout << "THANK-YOU FOR PLAYING OUR GAME.\nEXITING.....";
        return 0;
    }
    return 0;
}
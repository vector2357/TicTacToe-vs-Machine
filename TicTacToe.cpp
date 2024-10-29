#include <bits/stdc++.h>

using namespace std;

#define DEFAULT  "\033[0m"
#define BLUE     "\033[34m"
#define RED      "\033[31m"
#define GRAY     "\033[90m"
#define GREEN    "\033[32m"     
#define YELLOW   "\033[33m"

int moves;                         
char board[3][3], machine, user;

// initialization of game board
void boardInitial() {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            board[i][j] = ' ';
        }
    }
}

// print the game board on the terminal
void printBoard() {
    for(int i=0; i<3; i++) {
        cout << "\n\t| ";
        for(int j=0; j<3; j++) {
            if(j) cout << " | ";
            
            if(board[i][j] == ' ') {
                cout << i*3 + j + 1;
            }
            else {
                if(board[i][j] == 'X') cout << RED;
                else cout << BLUE;
                
                cout << board[i][j] << DEFAULT;
            }
        }
        cout << " |";
    }
    cout << "\n\n";
}

// check if any player has won so far
bool win(char player) {
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if(board[0][2]==player && board[1][1]==player && board[2][0]==player) return true;
    
    for(int i=0; i<3; i++) {
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player)
            return true;
    }
    for(int j=0; j<3; j++) {
        if(board[0][j]==player && board[1][j]==player && board[2][j]==player)
            return true;
    }
    
    return false;
}

// MiniMax algorithm for machine move
int minimax(bool isMax, int currentMoves) {
    int result = 2;
    
    if(currentMoves == 9) result = 0;
    if(win(machine)) result = 10;
    if(win(user)) result = -10;
    
    if(result != 2) return result;
    
    if(isMax) {
        int maxScore = -1000;
        
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = machine;
                    
                    int score = minimax(false, currentMoves+1);
                    board[i][j] = ' ';
                    
                    maxScore = max(maxScore, score);
                }
            }
        }
        return maxScore;
    }
    else {
        int maxScore = 1000;
        
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(board[i][j] == ' ') {
                    board[i][j] = user;
                    
                    int score = minimax(true, currentMoves+1);
                    board[i][j] = ' ';
                    
                    maxScore = min(maxScore, score);
                }
            }
        }
        return maxScore;
    }
}

// catch the best move position for machine with minimax call
void bestMove() {
    int maxScore = -1000;
    pair<int, int> pos;
    
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = machine;
                
                int score = minimax(false, moves+1);
                
                board[i][j] = ' ';
                
                if(score > maxScore) {
                    maxScore = score;
                    pos = {i, j};
                } 
            }
        }
    }
    board[pos.first][pos.second] = machine;
}

int main()
{
    int game = true;
    
    while(game) {
        system("clear");
        cout << "\nWould you like to play as " << RED << " 'X' " << DEFAULT << "or" << BLUE << " 'O' " << DEFAULT << "? Enter your choice: ";
        cin >> user;
        user = toupper(user);
        system("clear");
        
        while(user != 'X' && user != 'O') {
            cout << "\nInvalid choice! Please enter" << RED << " 'X' " << DEFAULT << "or" << BLUE << " 'O' " << DEFAULT << "to select your symbol: ";
            cin >> user;
            user = toupper(user);
            system("clear");
        }
        
        machine = (user == 'X') ? 'O' : 'X';
        
        char player = 'O';
        int pos;
        moves = 0;
        boardInitial();
        
        while(moves<9 && !win(player)) {
            player = (player == 'X') ? 'O' : 'X';
            cout << "\n --------------------------\n";
            printBoard();
            cout << " --------------------------\n\n";
            
            if(player == user) {
                cout << "Your turn! Choose the position (1-9): ";
                cin >> pos;
                int i = (pos-1)/3, j = (pos-1)%3;
                
                while(pos < 1 || pos > 9 || board[i][j] != ' ') {
                    system("clear");
                    cout << "\n --------------------------\n";
                    printBoard();
                    cout << " --------------------------\n\n";
                    
                    cout << "Invalid position! Please enter a number between 1 and 9, and an empty spot: ";
                    cin >> pos;
                    i = (pos-1)/3, j = (pos-1)%3;
                }
                
                moves++;
                
                board[i][j] = player;
            }
            else {
                bestMove();
                moves++;
            }
            
            system("clear");
        }
        cout << "\n --------------------------\n";
        printBoard();

        if(!win(player)) {
            cout << " ---------- " << YELLOW << "DRAW" << DEFAULT << " ----------\n";
        }
        else {
            string winner = (player == user) ? "PLAYER" : "MACHINE";
            cout << " --------- " << GREEN << winner << DEFAULT << " --------\n";
        }
        cout << "\n\nWould you like to play again? Enter " << GREEN << "1" << DEFAULT << " for Yes or " << RED << "0" << DEFAULT << " for No: ";
        cin >> game;
        
        while(game != 0 && game != 1) {
            system("clear");
            cout << "\nInvalid response! Please enter " << GREEN << "1" << DEFAULT << " for Yes or " << RED << "0" << DEFAULT << " for No: ";
            cin >> game;
        }
    }

    return 0;
}
//Author: Darrell Lawrence
//Purpose: Basic ConnectFour game w/ 2 players. Client/Server interaction will be implemented in next version.

#include <iostream>
#include <string>
#include <sstream>

#define HEIGHT 6
#define WIDTH 7

using namespace std;

string board [HEIGHT][WIDTH]; //Standard ConnectFour board side (6 rows, 7 columns)
int activePlayer = 1; //Player 1 always moves first
int wonGame = 0;

//function declarations:
void buildBoard();
void printBoard();
bool insertPiece(int colMove);
bool checkWin();
bool checkTie();
int player1Turn();
int player2Turn();
int turnController();
void resetGame();

int main(){
    resetGame();
    cout << "\n\nThanks for playing!";
    return 0;
}

void buildBoard(){
    int i;
    int j;
    for (i = 0;i < HEIGHT; i++){
        for (j = 0;j < WIDTH; j++){
            board [i][j] = "[ ]";
        }
    }
}

void printBoard(){
    int i;
    int j;
    for (i = 0;i < HEIGHT; i++){
        cout << "\n";
        cout << "|";
        for (j = 0;j < WIDTH; j++){
            cout << board[i][j];
        }
        cout << "|";
    }
}

bool insertPiece(int colMove){ // Receives player's move. Attempts to legally put piece on the board
    return false;
}

bool checkWin(){
    //if win set wonGame = 1
    return true;
}

bool checkTie(){
    //walk through the entire array (board). If all positions are an X or an O then it is a tie
    int i;
    int j;
    for (i = 0;i < HEIGHT; i++){
        for (j = 0;j < WIDTH; j++){
            if (board[i][j] != "[O]" && board[i][j] != "[X]"){
                return false;
            }
        }
    }
    return true;
}

void resetGame(){
    wonGame = 0;
    bool done = false;
    while (!done){
        activePlayer = 1;
        buildBoard();
        printBoard();
        if (turnController() == 1){
            wonGame = 0;
            done = false;
        }
        else{
            done = true;
        }
    }
}

int gameWon(){
    wonGame = 1;
    cout << "**Player " << activePlayer << " WINS!!!**" << endl;
    cout << "Do you want to play again? (Y/N): " << endl;
    string input;
    getline(cin,input);
    stringstream reset(input);
    if (input == "Y" || input == "y"){
        return 1;
    }
    else if (input == "N" || input == "n"){
        return 0;
    }
    else{
        cout << "Invalid input. Game over.";
        return 0;
    }
}

int player1Turn(){
    int move;
    string input; //holds player input
     
    cout << "\nPlayer 1's move. Input a column number to insert your piece (1-7):";
    
    getline(cin,input);
    stringstream myStream(input);
    myStream >> move;
    
    bool validColumn = false;
    while (!validColumn){
        if (move > 7 || move < 1){ //validating that input is between 1-7
            cout << "\nInvalid input";
            printBoard();
            cout << "\nPlayer 1's move. Input a column number to insert your piece (1-7):";

            getline(cin,input);
            stringstream myStream(input);
            myStream >> move;
        }
        else{
            validColumn = true;
        }  
    }
        
    if (insertPiece(move)){ //attempts to put piece into the board
        if (checkWin()){
            int returnNum;
            returnNum = gameWon();
            return returnNum;
            
        }
        
        else if (checkTie()){
            cout << "**The match was a TIE!**" << endl;
            cout << "Do you want to play again? (Y/N): ";
        }
        else {
            activePlayer = 2; //player 2's turn
            return 2;
        }
    }
    else{ //if move isn't valid: reprints board for player to see and starts player's turn over
        cout << "\nPlease choose a valid position."; //insertPiece() function should be the one to print the board and give the message(s)
        activePlayer = 1;
        return 1;
    } 
}

int player2Turn(){
    cout << "Player 2's turn";
    wonGame = 1;
    return 0;
}

int turnController(){
    while(wonGame == 0){
        if (activePlayer == 1){ //player 1's turn
            int player1Val;
            player1Val = player1Turn();
            if (player1Val == 1){ //returns 1 to reset game
                return 1;
            }
            else if (player1Val == 0){
                return  0;
            }
        }
        else{ //player 2's turn
            int player2Val;
            player2Val = player2Turn();
            if (player2Val == 1){ //returns 1 to reset game
                return 1;
            }
            else if (player2Val == 0){
                return 0;
            }
        }
    }
}




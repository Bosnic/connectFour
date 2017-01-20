//Author: Darrell Lawrence
//Purpose: Basic ConnectFour game w/ 2 players. Client/Server interaction will be implemented in next version.

#include <iostream>
#include <string>
using namespace std;

string board [7][6];
int activePlayer = 1;

//function declarations:
void buildBoard();
void printBoard();
bool validMove();
bool insertPiece(int colMove);
bool checkWin();
int player1Turn();
int player2Turn();
void turnController();

int main(){
    buildBoard ();
    printBoard ();
    
    return 0;
}

void buildBoard(){
    int i;
    int j;
    for (i = 0;i < 6; i++){
        for (j = 0;j < 7; j++){
            board [i][j] = "[]";
        }
    }
}

void printBoard(){
    int i;
    int j;
    for (i = 0;i < 6; i++){
        cout << "\n";
        cout << "|";
        for (j = 0;j < 7; j++){
            cout << board[i][j];
        }
        cout << "|";
    }
}

bool validMove(){
    return false;
}

bool insertPiece(int colMove){
    return false;
}

bool checkWin(){
    return false;
}

int player1Turn(){
    int move;
    char input; //holds player input
    cout << "Player 1's move. Input a column to insert your piece (1-7):";
    cin >> input;
    move = input - '0';
    if (insertPiece(input)){ //attempts to put piece into the board. Returns false if an illegal move
        if (checkWin()){
            cout << "**Player 1 WINS!!!**";
        }
        else {
            activePlayer = 2;
            return 0;
        }
    }
    else{ //if move isn't valid: reprints board for player to see and starts player 1's turn over
        printBoard();
        cout << "Please choose a valid position.";
        activePlayer = 1;
        return 0;
    } 
}

int player2Turn(){
    
}

void turnController(){
    while(!checkWin()){
        if (activePlayer = 1){ //player 1's turn
            player1Turn(); 
        }
        else{ //player 2's turn
            
        }
    }
}




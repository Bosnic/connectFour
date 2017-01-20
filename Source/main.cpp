#include <iostream>
#include <string>
using namespace std;

string board [7][6];
int activePlayer = 1;

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

bool insertPiece(char move[]){
    
}

bool checkWin(){
    
}

void takeTurn(int player){
    char move[1];
    bool validMove;
    if (activePlayer = 1){ //player 1's turn
        cout >> "Player 1's move. Choose a column to insert your piece (1-7):";
        cin >> move;
        validMove = insertPiece(move);
        
        if (validMove){
            if (checkWin()){
                cout << "**Player 1 WINS!!!**";
            }
            else {
                takeTurn(2);
            }
        }
        else{ //reprints board for player to see and starts player 1's turn over
            printBoard();
            cout >> "Please choose a valid position.";
            takeTurn(1);
        }
    }
    else {// player 2's turn
        
    }
    
}

int main(){
    buildBoard ();
    printBoard ();
    
    return 0;
}



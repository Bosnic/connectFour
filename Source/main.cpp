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
int playAgain();

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

bool insertPiece(int colMove){ //Receives player's move. Attempts to legally put piece on the board in that column
    /* 
     * Go to column
     * go to the bottom row of column
     * check to see if there is a piece there (X or O)
     * if no piece: 
     *  -place activePlayer's piece at that location
     *  -return true (that column had space to place a new piece)
     * if there is a piece:
     *  -am I on the last row?
     *      if yes:
     *          -return false (not a valid column to insert a piece)
     *      if no:
     *          -move up 1 row and repeat
    */
    int row = HEIGHT - 1;
    int col = colMove - 1;
    for (row; (row >= 0); row--){
        if (board[row][col] != "[O]" && board[row][col] != "[X]"){
            if (activePlayer == 1){
                board[row][col] = "[X]";
                return true;
            }
            else{
                board[row][col] = "[O]";
                return true;
            }
        }
    }
    
    return false;
}

bool checkWin(){
    
    /*
    *Get valid entry
    *check direction. Is there a "wall" (end of board)?
    *   if no:
    *       Is that direction the same value?
    *           if yes:
    *               -add to counter
    *               -does counter = 4? 
    *                   if yes: return true
    *                   if no: repeat with that direction
    *           if no:
    *               -check next direction
    *   if yes:
    *       -check next direction
    * 
    */
    //Note: if win set wonGame = 1
    return false;
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
        cout << "New Game!";
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
    int newGame = 0;
    cout << "**Player " << activePlayer << " WINS!!!**" << endl;
    newGame = playAgain();
    return newGame;
}

int playAgain(){
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
    
    bool validMove = false;
    validMove = insertPiece(move);
    if (validMove){
        bool winValue;
        winValue = checkWin();
        if (winValue){
            int returnNum;
            returnNum = gameWon();
            return returnNum;    
        }
        
        else if (checkTie()){
            cout << "**The match was a TIE!**" << endl;
            int newGame = 0;
            newGame = playAgain();
            return newGame;
        }
        else {
            printBoard();
            activePlayer = 2; //player 2's turn
            return 2;
        }
    }
    else{ //if move isn't valid: reprints board for player to see and starts player's turn over
        cout << "\nPlease choose a valid position.";
        printBoard();
        activePlayer = 1;
        return 3; //Note: there is no difference between returning 2 or 3. This is just to indicate that something else will happen given variable values at the time
    } 
}

int player2Turn(){
    int move;
    string input; //holds player input
     
    cout << "\nPlayer 2's move. Input a column number to insert your piece (1-7):";
    
    getline(cin,input);
    stringstream myStream(input);
    myStream >> move;
    
    bool validColumn = false;
    while (!validColumn){
        if (move > 7 || move < 1){ //validating that input is between 1-7
            cout << "\nInvalid input";
            printBoard();
            cout << "\nPlayer 2's move. Input a column number to insert your piece (1-7):";

            getline(cin,input);
            stringstream myStream(input);
            myStream >> move;
        }
        else{
            validColumn = true;
        }  
    }
    
    bool validMove = false;
    validMove = insertPiece(move);
    if (validMove){ 
        if (checkWin()){
            int returnNum;
            returnNum = gameWon();
            return returnNum;    
        }
        
        else if (checkTie()){
            cout << "**The match was a TIE!**" << endl;
            int newGame = 0;
            newGame = playAgain();
            return newGame;
        }
        else {
            printBoard();
            activePlayer = 1; //player 1's turn
            return 2;
        }
    }
    else{ //if move isn't valid: reprints board for player to see and starts player's turn over
        cout << "\nPlease choose a valid position.";
        printBoard();
        activePlayer = 2;
        return 3; //Note: there is no difference between returning 2 or 3. This is just to indicate that something else will happen given variable values at the time
    }
}

int turnController(){
    while(wonGame == 0){
        if (activePlayer == 1){ //player 1's turn
            int player1Val;
            player1Val = player1Turn();
            if (player1Val == 1){ //returns 1 to reset game
                return 1;
            }
            else if (player1Val == 0){ //returns 0
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




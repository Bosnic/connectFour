//Author: Darrell Lawrence
//Purpose: Basic ConnectFour game w/ 2 players. Client/Server interaction will be implemented in next version.
//Created: Jan 2017

#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "c4Game.h"


c4Game::c4Game(void){}
c4Game::~c4Game(void){}

void c4Game::INIT(){
    int activePlayer = 1;
    int wonGame = 0;
    newGame();
}

void c4Game::buildBoard(){
    int i;
    int j;
    for (i = 0;i < HEIGHT; i++){
        for (j = 0;j < WIDTH; j++){
            board[i][j] = "[ ]";
        }
    }
}

void c4Game::printBoard(){
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

int c4Game::insertPiece(int colMove){ //Receives player's move. Attempts to legally put piece on the board in that column
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
            }
            else{
                board[row][col] = "[O]";             
            }
            cout << "\nPlayer " << activePlayer << "'s Move: Row " << row + 1 << ", Column " << col + 1; 
            return row;
        }
    } 
    return -1; //not a valid move
}

bool c4Game::checkWin(int rowVal, int columnVal){ //Note: rowVal is array value, columnVal is player's input value (off by 1)
    columnVal = columnVal - 1; //correcting columnVal to match array values
    /*
    *Get valid entry
    *check 3 spaces over in direction. Is there a wall? (Note: never have to check straight up)
    *   if no:
    *       Are all 4 values the same?
    *           if yes:
    *               return true
    *           if no: 
    *              try with next direction
    *   if yes:
    *       check next direction
    */      
    int row = rowVal;
    int col = columnVal;
    
    //check NE (NorthEast)
    //NE (row -1, column + 1)  
    if ((row - 3 >= 0) && (col + 3 <= 6)){
        //check for matches
        if ((board[row][col] == board[row-1][col+1]) &&
            (board[row][col] == board[row-2][col+2]) &&
            (board[row][col] == board[row-3][col+3])){
            
            return true;       
        }
    } 
    
    //check E (East)
    //E (column +1)
    if (col + 3 <= 6){
        //check for matches
        if ((board[row][col] == board[row][col+1]) &&
            (board[row][col] == board[row][col+2]) &&
            (board[row][col] == board[row][col+3])){
            
            return true;       
        }
    }
    
    //check SE (SouthEast)
    //SE (row +1, column + 1)
    if ((row + 3 <= 5) && (col + 3 <= 6)){
        //check for matches
        if ((board[row][col] == board[row+1][col+1]) &&
            (board[row][col] == board[row+2][col+2]) &&
            (board[row][col] == board[row+3][col+3])){
            
            return true;       
        }
    }
    
    //check S (South)
    //S (row + 1)
    if (row + 3 <= 5){
        //check for matches
        if ((board[row][col] == board[row+1][col]) &&
            (board[row][col] == board[row+2][col]) &&
            (board[row][col] == board[row+3][col])){
            
            return true;       
        }
    }
    
    //check SW (SouthWest)
    //SW (row +1, column -1)
    if ((row + 3 <= 5) && (col - 3 >= 0)){
        //check for matches
        if ((board[row][col] == board[row+1][col-1]) &&
            (board[row][col] == board[row+2][col-2]) &&
            (board[row][col] == board[row+3][col-3])){
            
            return true;       
        }
    }
    
    //check W (West)
    //W (column -1)
    if (col - 3 >= 0){
        //check for matches
        if ((board[row][col] == board[row][col-1]) &&
            (board[row][col] == board[row][col-2]) &&
            (board[row][col] == board[row][col-3])){
            
            return true;       
        }
    }
    
    //check NW (NorthWest)
    //NW (row -1, column -1)
    if ((row - 3 >= 0) && (col - 3 >= 0)){
        //check for matches
        if ((board[row][col] == board[row-1][col-1]) &&
            (board[row][col] == board[row-2][col-2]) &&
            (board[row][col] == board[row-3][col-3])){
            
            return true;       
        }
    }  
    return false;
}

bool c4Game::checkTie(){
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

void c4Game::newGame(){
    wonGame = 0;
    bool done = false;
    while (!done){
        activePlayer = 1;
        buildBoard();
        cout << "\n\n**New Game!**  Player 1: X, Player 2: O";
        printBoard();
        if (turnController() == 1){
            wonGame = 0;
            done = false;
        }
        else{
            done = true;
        }
    }
    cout << "\nThanks for playing!";
}

int c4Game::gameWon(){
    wonGame = 1;
    int resetGame = 0;
    cout << "\n\n**Player " << activePlayer << " WINS!!!**" << endl;
    printBoard();
    resetGame = playAgain();
    return resetGame;
}

int c4Game::playAgain(){
    cout << "\nDo you want to play again? (Y/N): ";
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

int c4Game::player1Turn(){
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
    
    int colVal = move;
    int rowVal = 0;
    rowVal = insertPiece(colVal);
    if (rowVal != -1){
        bool winValue;
        winValue = checkWin(rowVal, colVal);
        if (winValue){
            int returnNum;
            returnNum = gameWon();
            return returnNum;    
        }

        else if (checkTie()){
            cout << "\n**The match was a TIE!**" << endl;
            printBoard();
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

int c4Game::player2Turn(){
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
    
    int colVal = move;
    int rowVal = 0;
    rowVal = insertPiece(colVal);
    if (rowVal != -1){
        bool winValue;
        winValue = checkWin(rowVal, colVal);
        if (winValue){
            int returnNum;
            returnNum = gameWon();
            return returnNum;    
        }
        
        else if (checkTie()){
            cout << "\n**The match was a TIE!**" << endl;
            printBoard();
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

int c4Game::turnController(){
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





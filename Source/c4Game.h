#ifndef c4Game_H
#define c4Game_H

#include <string>
//using namespace std;

#define HEIGHT 6
#define WIDTH 7

class c4Game{
    public:
        c4Game();
        ~c4Game(void);
        void INIT();
        void buildBoard();
        void printBoard();
        int insertPiece(int colMove);
        bool checkWin(int rowVal, int columnVal);
        bool checkTie();
        int player1Turn();
        int player2Turn();
        int turnController();
        void newGame();
        int gameWon();
        int playAgain();
        
        //c4Game(void); 
        
    private:
        std::string board [HEIGHT][WIDTH];
        int activePlayer; 
        int wonGame;

};

#endif
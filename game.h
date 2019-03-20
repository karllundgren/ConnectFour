//
// Created by Karl Lundgren on 2019-03-18.
//
#include <vector>
#ifndef CONNECTFOUR_GAME_H
#define CONNECTFOUR_GAME_H
using namespace std;

class game {

private:

    struct turn{
        int column;
        int row;
    };
    vector<vector<char>> board;
    vector<turn> turnHistory;
    char player1;
    char player2;
    char turn;
    int player1wins;
    int player2wins;

public:

    static void playGame();
    ~game();
    game(char player1, char player2);
    char executeTurn(int columnNum);
    void resetBoard();
    void undoTurn();
    void displayBoard();
    void displayWinningBoard();
    bool didWin();

};


#endif //CONNECTFOUR_GAME_H

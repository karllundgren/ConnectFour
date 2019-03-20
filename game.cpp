//
// Created by Karl Lundgren on 2019-03-18.
//
#include <vector>
#include <iostream>

#include "game.h"
using namespace std;

game::~game(){
    this->board = {};
    this->turnHistory = {};
    //this->player1 = NULL;
    //this->player2 = NULL;
    //this->turn = NULL;
}

game::game(char player1, char player2){
    this->player1 = player1;
    this->player2 = player2;

    this->player1wins = 0;
    this->player2wins = 0;

    this->turn = player1;
    this->board = {
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'}
    };
    this->turnHistory = {};
    displayBoard();
}

char game::executeTurn(int columnNum){
    //play token
    //check if column is full
    //play token in first position
    //game is played 'upside down' for faster gameplay

    for (int i = 0; i < 5; i++) {
        if(this->board[i][columnNum] == '_'){
            this->board[i][columnNum] = this->turn;

            struct turn thisTurn;
            thisTurn.column = columnNum;
            thisTurn.row = i;
            turnHistory.push_back(thisTurn);
            if(didWin()){
                if(this->turn == this->player1){
                    this->player1wins++;

                }
                else{
                    this->player2wins++;
                }
                displayWinningBoard();
                return this->turn;
            }

            if(this->turn == this->player1){
                this->turn = this->player2;

            }
            else {
                this->turn = this->player1;
            }
            displayBoard();
            cout << "Player " << this->turn << "'s turn to go\n";
            return '_';
        }

    }

    displayBoard();
    cout << "TOKEN NOT PLACED. NO MORE TOKENS CAN BE PLACED IN COLUMN "<<columnNum+1<<endl;
    return '_';
}
void game::resetBoard(){
    this->board = {
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'},
            {'_','_','_','_','_'}
    };
    this->turnHistory = {};
    this->turn = player1;
    displayBoard();

}
void game::undoTurn(){
    if(!turnHistory.empty()) {
        struct turn thisTurn;
        thisTurn = this->turnHistory.back();
        this->turnHistory.erase(this->turnHistory.end() - 1);
        this->board[thisTurn.row][thisTurn.column] = '_';
        if(this->turn == this->player1){
            this->turn = this->player2;

        }
        else {this->turn = this->player1;}
        displayBoard();
    }
    else{
        cout<<"This is the first turn of the game\n";
    }
}

void game::displayBoard(){
    for (int k = 0; k < 100; ++k) {
        cout<<endl;
    }
    cout << "Enter the column number you want to play in (1-5 from left to right)\nOr: '-1' to quit, '-2' to undo turn, '-3' to reset board\n";
    cout<<" 1 2 3 4 5\n";
    for (int i = 4; i >= 0 ; i--) {
        for (int j = 0; j <5; j++) {
            cout<<"|"<<this->board[i][j];
        }
        cout<<"|"<<endl;
    }

cout<<endl<<endl<<endl;

}

void game::displayWinningBoard(){
    for (int k = 0; k < 5; ++k) {
        cout<<endl;
    }
    cout<<"________________________\n";
    cout<< endl <<"Player " << this->turn << " won the game!!!" << endl;
    cout<<"________________________\n";
    cout<<"Round scores:\nPlayer "<<this->player1wins<<" wins\nPlayer "<<this->player2wins<<" wins\n\n";

    cout<<"***************\n";
    cout<<"*  1 2 3 4 5  *\n";
    for (int i = 4; i >= 0 ; i--) {
        cout<<"* ";
        for (int j = 0; j <5; j++) {
            cout<<"|"<<this->board[i][j];
        }
        cout<<"| *"<<endl;
    }
    cout<<"***************\n";
    cout<<endl<<endl<<endl;
    cout<<"press any key to continue to next game\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    resetBoard();

}

bool game::didWin(){

    struct turn lastTurn = this->turnHistory.back();
    int column = lastTurn.column;
    int row = lastTurn.row;
    int horizontal = 0, vertical = 0, bottomLeftTopRight = 0, topLeftBottomRight = 0;
    char lookingForThis = this->board[row][column];

    //check row
    for (int k = 0; k < 5; k++) {
        if(horizontal == 4){
            break;
        }
        if (this->board[row][k] == lookingForThis){
            horizontal++;
        }
        else{horizontal = 0;}
    }

    //check column
    for (int k = 0; k  < 5; k++) {
        if(vertical == 4){
            break;
        }
        if (this->board[k][column] == lookingForThis){
            vertical++;
        }
        else{break;}
    }

    // bottomLeftTopRight
    //step 1 move along diagonal to upper right
    int r = row, c = column;
    while(r < 4 && c < 4){
        r++, c++;
    }
    //cout<<r<<" "<<c<<endl;
    //step 2 check less than current to bottomLeft
    while (r >= 0 && c >= 0 ){
        if(bottomLeftTopRight == 4){
            break;
        }
        if (this->board[r][c] == lookingForThis){
            //cout<<bottomLeftTopRight<<endl;
            bottomLeftTopRight++;
        }
        else{bottomLeftTopRight = 0;}
        r--, c--;
    }


    // topLeftBottomRight
    //step 1 move along diagonal to upper left
    r = row, c = column;
    while(r > 0 && c < 4){
        r--, c++;
    }

    //step 2 check less than current to bottomRight
    while (r < 5 && c >= 0 ){
       // cout<<r<<" "<<c<<endl;
        if(topLeftBottomRight == 4){
            break;
        }
        if (this->board[r][c] == lookingForThis){
            //cout<<topLeftBottomRight<<endl;
            topLeftBottomRight++;
        }
        else{topLeftBottomRight = 0;}
        r++, c--;
    }

    cout<< topLeftBottomRight<<"sdfsdf"<<endl;

    if ( horizontal >= 4 || vertical >= 4 || bottomLeftTopRight >= 4 || topLeftBottomRight >=4 ){
        return true;
    }

    return false;
}

void game::playGame(){
    char gameControl = '_';
    while(gameControl != 'q') {
        cout<<"Welcome to connect 4!\n\n";
        cout<<"press 's' to start game\n";
        cin>>gameControl;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        int column = 0;
        char player1Symbol, player2Symbol2;
        cout << "Player 1 enter your symbol\n";
        cin >> player1Symbol;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "Player 2 enter your symbol\n";
        cin >> player2Symbol2;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        game myGame = game(player1Symbol, player2Symbol2);


        while (1) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "INVALID INPUT\n";
                cin >> column;
            }
            if (!cin.fail())
                break;
        }
        while (column != -1) {

            cin >> column;
            while (1) {

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "INVALID INPUT\n";
                    cin >> column;
                }

                if (!cin.fail())  {break;}
            }

            cout << endl;
            if (column == -2) {
                myGame.undoTurn();
            }
            else if (column == -3) {
                myGame.resetBoard();
            }
            else if (column >= 1 && column <= 5) {
                myGame.executeTurn(column - 1);
            }
            else {
                cout << "enter a number between 1 and 5 please\n";
            }

        }
    }

}
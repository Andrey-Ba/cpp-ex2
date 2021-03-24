#include <iostream>
#include "Board.hpp"

using namespace std;

//Chech that the input is not out of bound
void test_input(int row, int col)
{
    if(row < 0 || col < 0)
    {
        throw out_of_range("Board starts at 0,0");
    }
}

void ariel::Board::first_board_size(int row, int col, ariel::Direction d, int msglen)
{
    this->top = row;
    this->left = col;
    if(d == ariel::Direction::Horizontal)
    {
        this->bot = row;
        this->right = col + msglen -1;
    }
    else
    {
        this->bot = row + msglen -1;
        this->right = col;
    }
}

void ariel::Board::first_msg(ariel::Direction d, string msg)
{
    int cols = right - left + 1;
    int rows = bot - top + 1;
    chars = new char*[(unsigned long)rows]();
    for(int i = 0; i < rows; i++)
    {
        chars[i] = new char[(unsigned long)cols]();
        for(int j = 0; j < cols; j++)
        {
            chars[i][j] = msg[(unsigned long)(i+j)];
        }
    }
}

//Update if the board go bigger due to input (Split it into 2 more functions, one for horizontal the other for vertical)
bool ariel::Board::update_board_size(int row, int col, ariel::Direction d, int msglen)
{
    bool updated = false;
    int old_top = top;
    int old_bot = bot;
    int old_left = left;
    int old_right = right;

    if(this->top > row){this->top = row; updated = true;}
    if(this->left > col) {this->left = col; updated = true;}
    if(d == ariel::Direction::Horizontal)
    {
        if(this->bot < row) {this->bot = row; updated = true;}
        if(this->right < col + msglen -1) {this->right = col + msglen - 1; updated = true;}
    }
    else
    {
        if(this->bot < row + msglen -1) {this->bot = row + msglen -1; updated = true;}
        if(this->right < col) {this->right = col; updated = true;}
    }
    if(updated)
    {
        update_board(old_top, old_bot, old_left, old_right);
    }
    return updated;
}

void ariel::Board::update_board(int old_top, int old_bot, int old_left, int old_right)
{
    //Construct a new bigger board
    int cols = right - left + 1;
    int rows = bot - top + 1;
    int diff_top = old_top - top;
    int diff_left = old_left - left;
    char** new_board = new char*[(unsigned long)rows]();
    for(int i = 0; i < rows; i++)
    {
        new_board[i] = new char[(unsigned long)cols]();
        for(int j = 0; j < cols; j++)
        {
            new_board[i][j] = '_';
        }
    }

    //Copy and delete the old board
    rows = old_bot - old_top + 1;
    cols = old_right - old_left + 1;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            new_board[i + diff_top][j + diff_left] = chars[i][j];
        }
        delete[] chars[i];
    }
    delete[] chars;
    chars = new_board;
}

void ariel::Board::post_message(int row, int col, Direction d, string msg)
{
    if(d == Direction::Horizontal)
    {
        for(int i = col; i < (unsigned long)col + msg.length(); i++)
        {
            chars[row][i] = msg[(unsigned long)(i - col)];
        }
    }
    else
    {
        for(int i = row; i < (unsigned long)row + msg.length(); i++)
        {
            chars[i][col] = msg[(unsigned long)(i - row)];
        }   
    }
}

namespace ariel {
    void Board::post(int row, int column, Direction direction, std::string message) {
        test_input(row, column);
        //If first call to board, make my life easier and do it in 2 nice build functions.
        if(!chars)
        {
            first_board_size(row, column, direction, message.length());
            first_msg(direction, message);
            return;
        }
        update_board_size(row, column, direction, message.length());
        int r = 0;
        if(row > top){r = row - top;}
        else{r = top - row;}
        int c = 0;
        if(column > left){c = column - left;}
        else{c = left - column;}
        post_message(r, c, direction, message);
    }

    std::string Board::read(int row, int column, Direction direction, int length) {
        test_input(row, column);
        string s = "";
        for(int i = 0; i < length; i++)
        {
            if(!chars)
            {
                s += '_';
            }
            else if(direction == Direction::Horizontal)
            {
                if(column + i > right || column + i < left || row < top || row > bot)
                {
                    s += '_';
                }
                else
                {
                    int j = column - left + i;
                    s += chars[row - top][j];
                }
            }
            else
            {
                if(row + i < top || row + i > bot || column < left || column > right)
                {
                    s += '_';
                }
                else
                {
                    int j = row - top + i;
                    s += chars[j][column - left];
                }
            }
        }
        return s;
    }
    void Board::show() {
        if(!chars)
        {
            cout << "___\n___\n___" << endl;
        }
        cout << "Top: " + to_string(top) + " | Bot: " + to_string(bot) + " | Left: " + to_string(left) + " | Right: " + to_string(right) << endl;
        int cols = right - left + 1;
        int rows = bot - top + 1;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                cout << chars[i][j];
            }
            cout << '\n';
        }
    }
}

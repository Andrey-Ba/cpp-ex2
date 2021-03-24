#pragma once

#include <string>
#include "Direction.hpp"

namespace ariel {
    class Board {
        char **chars;
        //Save all used corners of the board
        int top;
        int left;
        int bot;
        int right;

    private:
        void first_board_size(int, int, Direction, int);
        void first_msg(Direction, std::string);
        bool update_board_size(int, int, Direction, int);
        void update_board(int old_top, int old_bot, int old_left, int old_right);
        void post_message(int, int, Direction, std::string);
    public:
        Board() 
        {
            this->chars = NULL;
            this->top = 0;
            this->left = 0;
            this->bot = 0;
            this->right = 0;
        }
        ~Board()
        {
            if(chars)
            {
                int cols = right - left + 1;
                int rows = bot - top + 1;
                for(int i = 0; i < rows; i++)
                {
                    delete[] chars[i];
                }
                delete[] chars;
            }
        }
        void post(int row, int column, Direction direction, std::string message);
        std::string read(int row, int column, Direction direction, int length);
        void show();
    };
}
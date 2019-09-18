//
//  main.cpp
//  mineSweeper
//
//  Created by Raunit Singh on 18/09/19.
//  Copyright © 2019 Beatrix Kiddo. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class mineSweeper
{
    int N;
    int difficulty;
    vector<pair<int, int>> dir = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    vector<vector<char>> board;
    vector<vector<bool>> covered, flag;
    int numMines;
    int numCovered;
    
    bool isValid(int i, int j)
    {
        return i >= 0 && j >= 0 && i < N && j < N;
    }
    
    void setBoard()
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                if(board[i][j] == 'B')
                    continue;
                int count = 0;
                for(auto & it : dir)
                    if(isValid(i + it.first, j + it.second) && board[i + it.first][j + it.second] == 'B')
                        ++count;
                board[i][j] = char('0' + count);
            }
        }
    }
    
    
    void placeMines(int difficulty)
    {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if(board[i][j] != 'B' && rand() % 5 == 2 && ++numMines)
                    board[i][j] = 'B';
        setBoard();
    }
    
    
    void printBoard()
    {
        for(int i = 0; i < N; ++i)
        {
            cout << "       ";
            for(int j = 0; j < N; j++)
                cout << "--- ";
            cout << endl;
            cout << "      |";
            for(int j = 0; j < N; ++j)
            {
                char c = (covered[i][j]) ? ' ' : board[i][j];
                if(flag[i][j])
                    c = 'F';
                cout << " " << c << " |";
            }
            cout << endl;
        }
        cout << "       ";
        for(int j = 0; j < N; j++)
            cout << "--- ";
        cout << endl;
    }
    
    void dfs(int i, int j)
    {
        if(!isValid(i, j) || board[i][j] == 'B' || !covered[i][j])
            return;
        covered[i][j] = false;
        if(board[i][j] == '0')
            for(auto & it : dir)
                dfs(i + it.first, j + it.second);
    }
    
    
public:
    bool isComplete;
    mineSweeper(int N, int difficulty = 1) : N(N), board(N, vector<char>(N, '0')), difficulty(difficulty), covered(N, vector<bool>(N, true)), numMines(0), numCovered(N * N), isComplete(false), flag(N, vector<bool>(N, false))
    {
        placeMines(difficulty);
        printBoard();
    }
    
    void click(int i, int j)
    {
        if(!isValid(i, j))
        {
            cout << "INVALID" << endl;
            return;
        }
        if(board[i][j] == 'B')
        {
            cout << "YOU LOST :/" << endl;
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                    covered[i][j] = false;
            printBoard();
            return;
        }
        if(covered[i][j])
            dfs(i, j);
        printBoard();
        isComplete = (numCovered == numMines);
        if(isComplete)
            cout << "YOU WON!" << endl;
    }
    
    void setFlag(int i, int j)
    {
        if(isValid(i, j))
            flag[i][j] = true;
        printBoard();
    }
    
};


void play(int n)
{
    cout << "         WELCOME TO MINESWEEPER!" << endl << endl;
    cout << " X Y TO CLICK THE CELL (X, Y) OR -1 -1 TO FLAG" << endl << endl;
    mineSweeper game(n);
    while(!game.isComplete)
    {
        cout << "\n INPUT: ";
        int x, y;
        cin >> x >> y;
        if(x == -1 && y == -1)
        {
            cout << " INPUT FLAG COORDINATES: ";
            cin >> x >> y;
            game.setFlag(x, y);
        }
        else game.click(x, y);
    }
}


int main()
{
    play(5);
}

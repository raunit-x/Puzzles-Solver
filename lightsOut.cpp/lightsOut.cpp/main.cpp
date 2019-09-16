//
//  main.cpp
//  lightsOut.cpp
//
//  Created by Raunit Singh on 15/09/19.
//  Copyright © 2019 Beatrix Kiddo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <map>
#include <string>
#include <unordered_set>

using namespace std;


class lightsOut
{
    vector<vector<bool>> matrix;
    vector<pair<int, int>> dir = {{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int N;
    int tiles;
    bool isValid(int i, int j)
    {
        return i >= 0 && j >= 0 && i < N && j < N;
    }
    
public:
    static int numMoves;
    lightsOut(int N = 4) : N(max(N, 1)), matrix(N, vector<bool>(N, false)), tiles(0) {}
    void print()
    {
        for(int i = 0; i < N; ++i)
        {
            cout << "  ";
            for(int j = 0; j < N; j++)
                cout << "--- ";
            cout << endl;
            cout << " |";
            for(int j = 0; j < N; ++j)
                cout << " " << matrix[i][j] << " |";
            cout << endl;
        }
        cout << "  ";
        for(int j = 0; j < N; j++)
            cout << "--- ";
        cout << endl;
    }
    bool click(int i, int j)
    {
        numMoves += isValid(i, j);
        for(auto & it : dir)
        {
            if(isValid(i + it.first, j + it.second))
            {
                matrix[i + it.first][j + it.second] = !matrix[i + it.first][j + it.second];
                tiles += (matrix[i + it.first][j + it.second]) ? 1 : -1;
            }
        }
        print();
        if(isComplete())
        {
            cout << "YOU WON!" << endl;
            cout << "Number of Moves: " << numMoves << endl;
        }
        return isComplete();
    }
    bool isComplete()
    {
        return tiles == N * N;
    }
    bool allOn(vector<vector<bool>> & matrix)
    {
        int sum = 0;
        for(auto & V : matrix)
            for(bool v : V)
                sum += v;
        return sum == matrix.size() * matrix.size();
    }
    string getState(vector<vector<bool>> & matrix)
    {
        string state = "";
        for(int i = 0; i < matrix.size(); ++i)
            for(int j = 0; j < matrix[0].size(); ++j)
                state += matrix[i][j];
        return state;
    }
    pair<vector<vector<bool>>, int> toggle(vector<vector<bool>> & matrix, int i, int j, int num)
    {
        vector<vector<bool>> newMatrix;
        for(auto & V : matrix)
            newMatrix.push_back(V);
        for(auto & it : dir)
            if(isValid(i + it.first, j + it.second))
            {
                newMatrix[i + it.first][j + it.second] = !newMatrix[i + it.first][j + it.second];
                num += (newMatrix[i + it.first][j + it.second]) ? 1 : -1;
            }
        return {newMatrix, num};
    }
    vector<pair<int, int>> solve()
    {
        queue<pair<pair<vector<vector<bool>>, int>, pair<int, pair<int, int>>>> q; // q.first.first -> matrix, q.first.second -> int [# of on tiles], q.second.first -> # of steps, q.second.second -> <i, j>
        vector<pair<int, int>> steps;
        map<vector<vector<bool>>, pair<vector<vector<bool>>, pair<int, int>>> parent;
        q.push({{matrix, 0}, {0, {-1, -1}}});
        unordered_set<string> visited;
        while(!q.empty())
        {
            auto front = q.front(); q.pop();
            string state = getState(front.first.first);
            if(visited.find(state) != visited.end())
                continue;
            if(front.first.second == matrix.size() * matrix[0].size())
            {
                auto currState = front.first.first;
                while(currState != matrix)
                {
                    steps.push_back(parent[currState].second);
                    currState = parent[currState].first;
                }
                reverse(steps.begin(), steps.end());
                cout << "SOLVABLE IN " << front.second.first << " NUMBER OF MOVE!";
                break;
            }
            visited.insert(state);
            for(int i = 0; i < matrix.size(); ++i)
                for(int j = 0; j < matrix[0].size(); ++j)
                {
                    auto toggled = toggle(front.first.first, i, j, front.first.second);
                    if(visited.find(getState(toggled.first)) == visited.end())
                        parent[toggled.first] = {front.first.first, {i, j}};
                    q.push({toggled, {front.second.first + 1, {i, j}}});
                }
        }
        return steps;
    }
};

int lightsOut :: numMoves = 0;

void play(int n = 4)
{
    lightsOut game(n);
    cout << "WELCOME TO THE LIGHTS OUT GAME!" << endl;
    cout << "Enter -1 -1 to quit the game or play until you have not won!" << endl << endl;
    game.print();
    cout << endl;
    auto steps = game.solve();
    if(steps.empty())
    {
        cout << "NOT A SOLVABLE STATE!" << endl << endl;
        return;
    }
    cout << endl << "STEPS" << endl;
    for(auto & it : steps)
        cout << it.first << " " << it.second << endl;
    
    while(1)
    {
        cout << "\nINPUT: ";
        int i, j;
        cin >> i >> j;
        cout << endl;
        if(game.click(i, j))
            break;
        if(i == -1 && j == -1)
        {
            cout << "AWW RUNNIN TO MOMMY EH? [Y/N]" << endl;
            char ch;
            cin >> ch;
            if(ch == 'y' || ch == 'Y')
            {
                cout << "MUAHAHAHA" << endl;
                break;
            }
            else cout << "YOU BALLER!" << endl;
            continue;
        }
        cout << "Number of moves: " << lightsOut :: numMoves << endl;
    }
}


int main()
{
    play(); // input the size of the board in the play function's argument
}

// WordSearchII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node
{
    bool visited;
    pair<int,int>pos;
    Node(bool visit, pair<int,int>_pos) : visited(visit), pos(_pos){}
};

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
{
    unordered_map<char, vector<Node*>> hash;
    vector<string> result;

    //build the template
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            Node* NewNode = new Node(false, make_pair(i, j));
            char c = board[i][j];
            if (hash.find(c) != hash.end()) // it there already
            {
                auto& sameChar = hash[c];
                sameChar.push_back(NewNode);
            }
            else
            {
                vector<Node*> newVec{ NewNode };
                hash.insert(make_pair( c , newVec ));
            }
        }
    } 
    // add some debugger here print statement here
    for (auto h : hash)
    {
        cout << h.first << ": ";
        for (auto v : h.second)
            cout << "<" << v->pos.first << "," << v->pos.first << "), ";
        cout << endl;
    }

    // Now we find our words
    for (auto word : words)
    {
        // create a copy of hash
        auto tempHash = hash;
        bool found = true;
        for (auto ch : word)
        {
            if (tempHash.find(ch) == tempHash.end())
            {
                found = false;
                break;
            }
            auto Nodes = tempHash[ch]; //vector of nodes
            pair<int, int> curPose(0,0);
            bool seenCh = false;
            for (auto& Node : Nodes)
            {
                if (Node->visited) continue;
                auto nowPos = Node->pos;
                if (abs(nowPos.first - curPose.first) <= 0 || abs(nowPos.second - curPose.second) <= 0)
                {
                    Node->visited = true;
                    seenCh = true;
                    break;
                }
                curPose = nowPos;
            }
            // if it's not there then set false and end current loop
            if (!seenCh)
            {
                found = false;
                break;
            }
        }
        if (found) result.push_back(word);
    }
    return result;
}

int main()
{
    cout << "\n";
}
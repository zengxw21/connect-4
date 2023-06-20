#pragma once

#include <cstdlib>
#include "Judge.h"

class Node{
    int M, N;
    int noX, noY;
    int _x, _y;
    bool turn;
    int optionNum, *options;
    Node *parent, **child;
    double profit = 0;
    int count = 0;
    int flag = -1;
    bool expanded = 0;
public:
    Node(int M, int N, int noX, int noY, int _x = -1, int _y = -1, bool turn = 1, Node *par = nullptr);
    ~Node();
    int x() const;
    int y() const;
    bool getTurn() const;
    bool end();
    bool canExpand() const;
    Node *expand();
    void BackPropagation(double change);
    Node *BestChild(bool ifSet);
    
    static Node *newNode(int M, int N, int noX, int noY, int _x = -1, int _y = -1, bool turn = 1, Node *par = nullptr);
    void set(int M, int N, int noX, int noY, int _x = -1, int _y = -1, bool turn = 1, Node *par = nullptr);
    int canWin(bool turn);

    static Node **NodeList;
    static size_t cnt;
};

const double c = 0.9;
const size_t MAX_SIZE = 1e7;
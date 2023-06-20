#pragma once

#include<sys/time.h>
#include<cstdlib>
#include<utility>
#include<string.h>
#include"Node.hpp"


class UCT{
    int M, N;
    int noX, noY;
    Node *root = nullptr;
    int *weight=nullptr;
    int full_weight = 0;

public:
    UCT(int M, int N, int noX, int noY);
    ~UCT();
    std::pair<int, int> search(int **board, const int *top, double StartTime);
    int calcProfit(int **board, int *top, bool turn, int x, int y);
    void Simulate(int **board, int *top, bool turn, int &x, int &y);
    static double GetTime();
    Node *treePolicy(Node *node);
    double defaultPolicy(Node *node);
    static int **board, *top;
};

const double timeLimit = 2.7e6;
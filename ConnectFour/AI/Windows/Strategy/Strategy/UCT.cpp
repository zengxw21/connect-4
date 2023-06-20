#include"UCT.hpp"

int **UCT::board = nullptr;
int *UCT::top = nullptr;

double UCT::GetTime(){
    timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1e6 + now.tv_usec;
}

UCT::UCT(int M, int N, int noX, int noY):M(M),N(N),noX(noX),noY(noY){
    board = new int *[M];
    for (int i = 0; i < M;i++){
        board[i] = new int[N];
    }
    this->top = new int[N];
}

UCT::~UCT(){
    for (int i = 0; i < M;i++){
        delete[] board[i];
    }
    delete[] board;
    board = nullptr;
    delete[] top;
    top = nullptr;
    
}

std::pair<int,int>UCT::search(int **originBoard,const int*originTop,double startTime){
    srand(clock_t() + (unsigned long long)new char);
    for (int i = 0; i < M;i++){
        memcpy(board[i], originBoard[i], sizeof(int) * N);
    }
    memcpy(top, originTop, sizeof(int) * N);
    Node::cnt = 0;
    root = Node::newNode(M, N, noX, noY);
    while(GetTime()-startTime<timeLimit){
        for (int i = 0; i < M;i++){
        memcpy(board[i], originBoard[i], sizeof(int) * N);
        }
        memcpy(top, originTop, sizeof(int) * N);
        Node *node = treePolicy(root);
        double profitChange = defaultPolicy(node);
        node->BackPropagation(profitChange);
    }
    Node *best = root->BestChild(0);
    return std::make_pair(best->x(), best->y());
}

Node *UCT::treePolicy(Node*node){
    while(!node->end()){
        if(node->canExpand())
        return node->expand();
        node = node->BestChild(1);
    }
    return node;
}

double UCT::defaultPolicy(Node* node){
    bool turn = node->getTurn();
    int x = node->x(), y = node->y();
    int profit = calcProfit(board, top, !turn, x, y);
    while(profit==2){
        Simulate(board, top, turn, x, y);
        profit = calcProfit(board, top, turn, x, y);
        turn = !turn;
    }
    return double(profit);
}

void UCT::Simulate(int **board,int *top,bool turn,int &x,int &y){
    while(!top[y=rand()%N])
        ;
    x == --top[y];
    board[x][y] = int(turn) + 1;
    if(x-1==noX&&y==noY)
        --top[y];
}

int UCT::calcProfit(int **board,int *top,bool turn,int x,int y){
    if(turn&&machineWin(x,y,M,N,board))
        return 1;
    if(!turn&&userWin(x,y,M,N,board))
        return -1;
    if(isTie(N,top))
        return 0;
    return 2;
}
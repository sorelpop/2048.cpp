#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <chrono>
#include <math.h>
#include <random>
#include <fstream>
#include <iterator>
#include <sstream>
#include "global.h"
#include "color.h"
#include "scores.h"
#include "statistics.h"

enum Directions {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Tile {

    public:
        Tile(): value(0), blocked(false) {}
        ull value;
        bool blocked;
        Color::Modifier tileColor(ull);

};

class RandInt {
    public:
        using clock = std::chrono::system_clock;
        RandInt() :dist{0, std::numeric_limits<int>::max()} {
            seed(clock::now().time_since_epoch().count());
        }
        RandInt(const int low, const int high) :dist{low, high} {
            seed(clock::now().time_since_epoch().count());
        }
        int operator() () { return dist(re); }
        void seed(const unsigned int s) { re.seed(s); }
    private:
        std::minstd_rand re;
        std::uniform_int_distribution<> dist;
};

class Game {

    private:
        bool moved;
        bool win;
        bool boardFull;
        bool rexit;
        ull score;
        ull bestScore;
        ull largestTile;
        long long moveCount;
        double duration;
        ull BOARD_SIZE;
        std::vector<std::vector <Tile> > board;
        RandInt randInt;
	bool stateSaved;
	bool noSave;

        void initialiseBoardArray();
        void initialiseContinueBoardArray();
       	bool addTile();
        void collectFreeTiles(std::vector<std::vector<int> > &freeTiles);
        void drawBoard();
        void input(int err = 0);
        bool canMove();
        bool testAdd(int, int, ull);
        void unblockTiles();
        void decideMove(Directions);
        void move(int, int, int, int);
        void statistics();
        void saveStats();
        void saveScore();
	void saveState();
        void playGame(int);
	void setBoardSize();

    public:

        Game() : win(false), moved(true), boardFull(false), rexit(false), score(0), moveCount(-2), largestTile(2), stateSaved(false), noSave(false) {}
        void startGame();
	void continueGame();

};

#endif

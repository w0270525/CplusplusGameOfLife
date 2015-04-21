#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class Organism {

protected:
	int x;
	int y;
	int width;
	int height;
	bool moved;
	string whoAmI;
	int turnCounter;
	int lifeCounter;
	int breedCounter;

	enum direction { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

public:
	Organism();
	Organism(int width, int height);
	virtual ~Organism();

	virtual vector<int> move(vector<int>) = 0;
	virtual string whoIsThis();
	virtual void increaseLifeCounter() = 0;
	virtual int getLifeCounter() = 0;
	virtual void resetLifeCounter() = 0;
	virtual void hasMoved() = 0;
	virtual bool getMoved() = 0;
	virtual void resetMoved() = 0;
	virtual void breed() = 0;
	virtual int getBreedCounter() = 0;
	virtual void resetBreedCounter() = 0;
	virtual void takeTurn() = 0;
	virtual void resetTurn() = 0;
	virtual int getTurn() = 0;
	friend ostream& operator<<(ostream &output, Organism& organism);
	};

#endif

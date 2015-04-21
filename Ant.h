#ifndef _Ant_H
#define _Ant_H

#include <string>
#include "Organism.h"

using namespace std;

class Ant : public Organism {

private:
	string whoAmI;

public:
	Ant();
	Ant(int width, int height);
	virtual ~Ant();

	string whoIsThis();
	int randomize(int start, int end);
	void hasMoved();
	void increaseLifeCounter();
	int getLifeCounter();
	void resetLifeCounter();
	vector<int> move(vector<int> moves);

	bool getMoved();
	void resetMoved();
	void breed();
	int getBreedCounter();
	void resetBreedCounter();
	void takeTurn();
	void resetTurn();
	int getTurn();
};

#endif

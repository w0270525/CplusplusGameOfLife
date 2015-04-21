#ifndef lion_H
#define lion_H

#include <string>
#include "Organism.h"

using namespace std;

class Lion : public Organism {

private:
	string whoAmI;

public:
	Lion();
	Lion(int width, int height);
	virtual ~Lion();

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

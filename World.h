#ifndef _WORLD_H
#define _WORLD_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Organism.h"
#include "Ant.h"
#include "Lion.h"

using namespace std;


//Constants
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;
const int NUMBER_OF_ANTS = 100;
const int NUMBER_OF_LIONS = 5;

class World {

private:
	Organism *landscape[GRID_HEIGHT][GRID_WIDTH];

public:
	
	World();
	virtual ~World();


	Organism* getOrganism(int x, int y);
	Organism& getLandscapePosition(int x, int y);
	int getGridWidth();
	int getGridHeight();
	vector<int> findAvailSpots(bool pred, int startRow, int startCol);

	
	void setOrganism(Organism *organism, int x, int y);

	//Functions
	void setupWorld();
	void move();
	void moveOrganism();
	void resetMoveSwitches();
	int countAnts();
	int countLions();
	int randomize(int start, int end);
	void takeTurn();
	void moveLions();
	void moveAnts();
	void lifeCounters();
	void famine();
	void breedLions();
	void breedAnts();
	void breedAllAnimals();
	
	friend ostream& operator<<(ostream &output, World &world);
};

#endif

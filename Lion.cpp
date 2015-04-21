#include "Lion.h"


Lion::Lion(void)
	{

	this->whoAmI = "lion";
	this->moved = false;
	this->turnCounter = 0;
	this->lifeCounter = 0;
	this->breedCounter = 0;

	}


Lion::~Lion(void)
	{

	}

Lion::Lion(int width, int height)
	{


	}

string Lion::whoIsThis()
	{
	return this->whoAmI;

	} //end function

void Lion::increaseLifeCounter()
	{
	this->lifeCounter++;

	} //end function

int Lion::getLifeCounter()
	{
	return this->lifeCounter;

	} //end function

void Lion::resetLifeCounter()
	{
	this->lifeCounter = 0;

	} //end function

void Lion::breed()
	{
	this->breedCounter++;

	} //end function

int Lion::getBreedCounter()
	{
	return this->breedCounter;

	} //end function

void Lion::takeTurn()
	{
	this->turnCounter++;

	} //end function

void Lion::resetTurn()
	{
	this->turnCounter = 0;

	} //end function

int Lion::getTurn()
	{
	return this->turnCounter;

	} //end function

int Lion::randomize(int start, int end)
	{
	srand(time(NULL));
	int randomNum = rand() % end + start;

	return randomNum;

	} //end function

void Lion::hasMoved()
	{
	this->moved = true;

	} //end function

void Lion::resetMoved()
	{
	this->moved = false;

	} //end function

void Lion::resetBreedCounter()
	{
	this->breedCounter = 0;

	} //end function

vector<int> Lion::move(vector<int> moves)
	{

	vector<int> chosen;

	if (moves.size() > 1)
		{
		vector<int> rows;
		vector<int> cols;

		for (int i = 0; i < moves.size(); i += 2)
			{
			rows.push_back(moves[i]);
			cols.push_back(moves[i + 1]);
			}

		int randChoice = this->randomize(0, rows.size());
		chosen.push_back(rows[randChoice]);
		chosen.push_back(cols[randChoice]);

		}
	else if (moves.size() == 0)
		{
		chosen.push_back(-1);
		chosen.push_back(-1);

		}
	else
		{
		chosen.push_back(moves[0]);
		chosen.push_back(moves[1]);

		}

	return chosen;

	}

bool Lion::getMoved()
	{
	return this->moved;

	} //end function
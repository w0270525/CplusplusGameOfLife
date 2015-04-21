#include "Ant.h"


Ant::Ant(void) {

	this->whoAmI = "ant";
	this->moved = false;
	this->turnCounter = 0;
	this->lifeCounter = 0;
	this->breedCounter = 0;

}

Ant::~Ant(void) {


}

Ant::Ant(int width, int height) {

}


string Ant::whoIsThis() {
	return this->whoAmI;

} //end function

int Ant::randomize(int start, int end) {
	srand(time(NULL));
	int randomNum = rand() % end + start;

	return randomNum;

} //end function

void Ant::hasMoved() {
	this->moved = true;

} //end function

void Ant::increaseLifeCounter() {
	this->lifeCounter++;

} //end function

int Ant::getLifeCounter() {
	return this->lifeCounter;

} //end function

void Ant::resetLifeCounter() {
	this->lifeCounter = 0;

} //end function

void Ant::resetMoved() {
	this->moved = false;

} //end function

void Ant::resetBreedCounter() {
	this->breedCounter = 0;

} //end function

void Ant::breed() {
	this->breedCounter++;

} //end function

int Ant::getBreedCounter() {
	return this->breedCounter;

} //end function

void Ant::takeTurn() {
	this->turnCounter++;

} //end function

void Ant::resetTurn() {
	this->turnCounter = 0;

} //end function

int Ant::getTurn() {
	return this->turnCounter;

} //end function

vector<int> Ant::move(vector<int> moves) {

	vector<int> chosen;

	if (moves.size()>1) {
		vector<int> rows;
		vector<int> cols;

		for (int i = 0; i<moves.size(); i += 2) {
			rows.push_back(moves[i]);
			cols.push_back(moves[i + 1]);
		}

		int randChoice = this->randomize(0, rows.size());
		chosen.push_back(rows[randChoice]);
		chosen.push_back(cols[randChoice]);

	}
	else if (moves.size() == 0) {
		chosen.push_back(-1);
		chosen.push_back(-1);

	}
	else {
		chosen.push_back(moves[0]);
		chosen.push_back(moves[1]);

	}

	return chosen;

}

bool Ant::getMoved() {
	return this->moved;

} //end function
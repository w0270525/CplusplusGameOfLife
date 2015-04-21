#include "World.h"

//Initialize world
World::World(void)
	{


	for (int row = 0; row < this->getGridHeight(); row++)
		{
		for (int column = 0; column < this->getGridWidth(); column++)
			{
			this->landscape[row][column] = NULL;
			}
		}

	}

//Destructor
World::~World(void)
	{


	}



//Functions 

void World::takeTurn()
	{

	this->moveLions();
	this->moveAnts();
	this->lifeCounters();
	this->resetMoveSwitches();
	this->breedAllAnimals();

	} //end takeTurn 


void World::setupWorld()
	{
	vector<int> possibleRows;
	vector<int> possibleColumns;
	vector<int> availAntRows;
	vector<int> availAntCols;
	vector<int> availLionRows;
	vector<int> availLionCols;

	//Populate empty world 
	for (int row = 0; row < this->getGridHeight(); row++) possibleRows.push_back(row);
	for (int column = 0; column < this->getGridWidth(); column++) possibleColumns.push_back(column);

	//Ants

	//Insert Ants
	for (int rows = 0; rows < 10; rows++)
		{
		if (rows % 2 == 0 && rows != 0)
			{
			//Randomizing ant position
			std::srand(time(0));
			random_shuffle(possibleRows.begin(), possibleRows.end());
			random_shuffle(possibleColumns.begin(), possibleColumns.end());
			}
		for (int columns = 0; columns < 10; columns++)
			{
			this->setOrganism(new Ant, possibleRows[rows], possibleColumns[columns]);
			}
		}

	//continue to populate with ants until the max is hit.
	if (this->countAnts() < NUMBER_OF_ANTS)
		{

		//Find Spots
		for (int rows = 0; rows < this->getGridHeight(); rows++)
			{
			for (int columns = 0; columns < this->getGridWidth(); columns++)
				{
				if (&this->getLandscapePosition(rows, columns) == NULL)
					{
					availAntRows.push_back(rows);
					availAntCols.push_back(columns);
					}
				}
			}

		int howManyLeft = NUMBER_OF_ANTS - this->countAnts();
		for (int i = 0; i < howManyLeft; i++)
			{
			int pos = this->randomize(0, availAntRows.size() - 1);
			this->setOrganism(new Ant, availAntRows[pos], availAntCols[pos]);
			availAntRows.erase(availAntRows.begin() + pos);
			availAntCols.erase(availAntCols.begin() + pos);

			} //end outer for
		} //end ant count

	//Lions

	//Find spots for lions 
	for (int rows = 0; rows < this->getGridHeight(); rows++)
		{
		for (int columns = 0; columns < this->getGridWidth(); columns++)
			{
			if (&this->getLandscapePosition(rows, columns) == NULL)
				{
				availLionRows.push_back(rows);
				availLionCols.push_back(columns);
				}
			}
		}
	//sets the correct number of lions in the field.
	for (int lion = NUMBER_OF_LIONS; lion > 0; lion--)
		{
		int pos = this->randomize(0, availLionRows.size() - 1);
		this->setOrganism(new Lion, possibleRows[availLionRows[pos]], possibleColumns[availLionCols[pos]]);
		availLionRows.erase(availLionRows.begin() + pos);
		availLionCols.erase(availLionCols.begin() + pos);
		}

	int lionTestCount = this->countLions();

	} //end function

//returns the number of ants.
int World::countAnts()
	{
	int ants = 0;
	for (int row = 0; row < this->getGridHeight(); row++)
		{
		for (int column = 0; column < this->getGridWidth(); column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "ant")
					{
					ants++;
					}
				}
			}
		}

	return ants;

	}//end countAnts


//returns the number of lions
int World::countLions()
	{
	int lions = 0;
	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "lion")
					{
					lions++;
					}
				}
			}
		}

	return lions;

	} //end countLions


int World::randomize(int start, int end)
	{
	srand(time(NULL));
	int randomNum = rand() % end + start;

	return randomNum;

	} //end randomize 

//
void World::resetMoveSwitches()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				org->resetMoved();
				}
			}
		}

	} //end resetMoveSwitches


void World::moveLions()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "lion" && org->getMoved() != true)
					{
					vector<int> newMove = this->getLandscapePosition(row, column).move(this->findAvailSpots(true, row, column));
					Organism *newOrg = &this->getLandscapePosition(newMove[0], newMove[1]);

					if (newMove[0] != -1 && newMove[1] != -1)
						{
						this->setOrganism(NULL, newMove[0], newMove[1]);
						this->setOrganism(&this->getLandscapePosition(row, column), newMove[0], newMove[1]);
						this->setOrganism(NULL, row, column);
						}

					Organism *x = &this->getLandscapePosition(newMove[0], newMove[1]);
					if (x != NULL)
						{
						x->hasMoved();
						//Lion Eats
						if (newOrg != NULL)
							{
							x->resetLifeCounter();
							}
						}
					}
				} //end null check
			} //end for
		} //end for

	} //end moveLions

void World::moveAnts()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "ant" && org->getMoved() != true)
					{
					vector<int> newMove = this->getLandscapePosition(row, column).move(this->findAvailSpots(false, row, column));

					if (newMove[0] != -1 && newMove[1] != -1)
						{
						this->setOrganism(&this->getLandscapePosition(row, column), newMove[0], newMove[1]);
						this->setOrganism(NULL, row, column);

						}

					Organism *x = &this->getLandscapePosition(newMove[0], newMove[1]);
					if (x != NULL)
						{
						x->hasMoved();
						}
					}
				} //end null check
			} //end for
		} //end for

	} //end moveAnts

//
vector<int> World::findAvailSpots(bool pred, int startRow, int startCol)
	{

	bool foundFood = false;
	vector<int> moves;

	//Asses Possible Moves - In Priority
	if (pred)
		{

		//Look for food
		if (&this->getLandscapePosition(startRow + 1, startCol) != NULL)
			{
			if (this->getLandscapePosition(startRow + 1, startCol).whoIsThis() == "ant")
				{
				moves.push_back(startRow + 1);
				moves.push_back(startCol);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow, startCol + 1) != NULL)
			{
			if (this->getLandscapePosition(startRow, startCol + 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow);
				moves.push_back(startCol + 1);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow - 1, startCol) != NULL)
			{
			if (this->getLandscapePosition(startRow - 1, startCol).whoIsThis() == "ant")
				{
				moves.push_back(startRow - 1);
				moves.push_back(startCol);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow, startCol - 1) != NULL)
			{
			if (this->getLandscapePosition(startRow, startCol - 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow);
				moves.push_back(startCol - 1);
				foundFood = true;
				}
			}

		//Diagonal
		if (&this->getLandscapePosition(startRow + 1, startCol + 1) != NULL)
			{
			if (this->getLandscapePosition(startRow + 1, startCol + 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow + 1);
				moves.push_back(startCol + 1);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow - 1, startCol - 1) != NULL)
			{
			if (this->getLandscapePosition(startRow - 1, startCol - 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow - 1);
				moves.push_back(startCol - 1);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow + 1, startCol - 1) != NULL)
			{
			if (this->getLandscapePosition(startRow + 1, startCol - 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow + 1);
				moves.push_back(startCol - 1);
				foundFood = true;
				}
			}

		if (&this->getLandscapePosition(startRow - 1, startCol + 1) != NULL)
			{
			if (this->getLandscapePosition(startRow - 1, startCol + 1).whoIsThis() == "ant")
				{
				moves.push_back(startRow - 1);
				moves.push_back(startCol + 1);
				foundFood = true;
				}
			}



		//If No Food Is Found...
		if (!foundFood)
			{

			//Look For Move
			if (&this->getLandscapePosition(startRow + 1, startCol) == NULL)
				{
				if ((startRow + 1) > 0 && (startRow + 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow + 1);
					moves.push_back(startCol);
					}
				}

			if (&this->getLandscapePosition(startRow, startCol + 1) == NULL)
				{
				if ((startCol + 1) > 0 && (startCol + 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow);
					moves.push_back(startCol + 1);
					}
				}

			if (&this->getLandscapePosition(startRow - 1, startCol) == NULL)
				{
				if ((startRow - 1) > 0 && (startRow - 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow - 1);
					moves.push_back(startCol);
					}
				}

			if (&this->getLandscapePosition(startRow, startCol - 1) == NULL)
				{
				if ((startCol - 1) > 0 && (startCol - 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow);
					moves.push_back(startCol - 1);
					}
				}

			//Diagonal
			if (&this->getLandscapePosition(startRow + 1, startCol + 1) == NULL)
				{
				if ((startRow + 1) > 0 && (startRow + 1) < GRID_HEIGHT && (startCol + 1) > 0 && (startCol + 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow + 1);
					moves.push_back(startCol + 1);
					}
				}

			if (&this->getLandscapePosition(startRow - 1, startCol - 1) == NULL)
				{
				if ((startRow - 1) > 0 && (startRow - 1) < GRID_HEIGHT && (startCol - 1) > 0 && (startCol - 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow - 1);
					moves.push_back(startCol - 1);
					}
				}

			if (&this->getLandscapePosition(startRow + 1, startCol - 1) == NULL)
				{
				if ((startRow + 1) > 0 && (startRow + 1) < GRID_HEIGHT && (startCol - 1) > 0 && (startCol - 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow + 1);
					moves.push_back(startCol - 1);
					}
				}

			if (&this->getLandscapePosition(startRow - 1, startCol + 1) == NULL)
				{
				if ((startRow - 1) > 0 && (startRow - 1) < GRID_HEIGHT && (startCol + 1) > 0 && (startCol + 1) < GRID_HEIGHT)
					{
					moves.push_back(startRow - 1);
					moves.push_back(startCol + 1);
					}
				}

			} //end move search

		//end predator move/eat
		}
	else
		{

		//Look For Move
		if (&this->getLandscapePosition(startRow + 1, startCol) == NULL)
			{
			if ((startRow + 1) > 0 && (startRow + 1) < GRID_HEIGHT)
				{
				moves.push_back(startRow + 1);
				moves.push_back(startCol);
				}
			}

		if (&this->getLandscapePosition(startRow, startCol + 1) == NULL)
			{
			if ((startCol + 1) > 0 && (startCol + 1) < GRID_HEIGHT)
				{
				moves.push_back(startRow);
				moves.push_back(startCol + 1);
				}
			}

		if (&this->getLandscapePosition(startRow - 1, startCol) == NULL)
			{
			if ((startRow - 1) > 0 && (startRow - 1) < GRID_HEIGHT)
				{
				moves.push_back(startRow - 1);
				moves.push_back(startCol);
				}
			}

		if (&this->getLandscapePosition(startRow, startCol - 1) == NULL)
			{
			if ((startCol - 1) > 0 && (startCol - 1) < GRID_HEIGHT)
				{
				moves.push_back(startRow);
				moves.push_back(startCol - 1);
				}
			}

		}

	return moves;

	} //end findAvailSpots


void World::lifeCounters()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				org->increaseLifeCounter();
				org->takeTurn();
				}
			}
		}

	} //end lifeCounter


void World::famine()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "lion")
					{
					int lives = org->getLifeCounter();
					if (lives > 3)
						{
						this->setOrganism(NULL, row, column);
						}
					}
				}
			}
		}

	} //end famine


void World::breedLions()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "lion")
					{
					int lives = org->getTurn();
					if (lives >= 8)
						{
						org->breed();
						}
					}
				}
			}
		}

	} //end breedLions


void World::breedAnts()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->whoIsThis() == "ant")
					{
					int lives = org->getTurn();
					if (lives >= 3)
						{
						org->breed();
						}
					}
				}
			}
		}

	} //end breedAnts


void World::breedAllAnimals()
	{

	for (int row = 0; row < GRID_HEIGHT; row++)
		{
		for (int column = 0; column < GRID_WIDTH; column++)
			{
			Organism *org = &this->getLandscapePosition(row, column);
			if (org != NULL)
				{
				if (org->getBreedCounter()>0)
					{

					if (org->whoIsThis() == "ant")
						{

						//Look For Breeding Ground
						if (&this->getLandscapePosition(row + 1, column) == NULL && (row + 1) > 0 && (row + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Ant, row + 1, column);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row, column + 1) == NULL && (column + 1) > 0 && (column + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Ant, row, column + 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row - 1, column) == NULL && (row - 1) > 0 && (row - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Ant, row - 1, column);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row, column - 1) == NULL && (column - 1) > 0 && (column - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Ant, row, column - 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else//ant can't breed, resets counters anyway.
							{
							org->resetBreedCounter();
							org->resetTurn();
							}
						} //end ant
					else if (org->whoIsThis() == "lion")
						{

						//Look For Breeding Ground
						if (&this->getLandscapePosition(row + 1, column) == NULL && (row + 1) > 0 && (row + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row + 1, column);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row, column + 1) == NULL && (column + 1) > 0 && (column + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row, column + 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row - 1, column) == NULL && (row - 1) > 0 && (row - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row - 1, column);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row, column - 1) == NULL && (column - 1) > 0 && (column - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row, column - 1);
							org->resetBreedCounter();
							org->resetTurn();

							//Diagonal directions
							}
						else if (&this->getLandscapePosition(row + 1, column + 1) == NULL
								 && (column + 1) > 0 && (column + 1) < GRID_HEIGHT
								 && (row + 1) > 0 && (row + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row + 1, column + 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row - 1, column - 1) == NULL
								 && (column - 1) > 0 && (column - 1) < GRID_HEIGHT
								 && (row - 1) > 0 && (row - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row - 1, column - 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row + 1, column - 1) == NULL
								 && (column - 1) > 0 && (column - 1) < GRID_HEIGHT
								 && (row + 1) > 0 && (row + 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row + 1, column - 1);
							org->resetBreedCounter();
							org->resetTurn();

							}
						else if (&this->getLandscapePosition(row - 1, column + 1) == NULL
								 && (column + 1) > 0 && (column + 1) < GRID_HEIGHT
								 && (row - 1) > 0 && (row - 1) < GRID_HEIGHT)
							{

							this->setOrganism(new Lion, row - 1, column + 1);
							org->resetBreedCounter();
							org->resetTurn();

							}

						}
					}
				}

			} //end for
		} //end for

	} //End breedAllAnimals


Organism& World::getLandscapePosition(int x, int y)
	{
	if (x >= 0 && x <= this->getGridHeight() - 1 && y >= 0 && y <= getGridWidth() - 1)
		{
		return *this->landscape[x][y];
		}
	else
		{
		Organism *test = new Ant;
		delete(test);
		test = NULL;
		return *test;
		}

	}

Organism* World::getOrganism(int x, int y)
	{
	return this->landscape[x][y];

	}

int World::getGridWidth()
	{
	return GRID_WIDTH;

	}

int World::getGridHeight()
	{
	return GRID_HEIGHT;

	}

void World::setOrganism(Organism *organism, int x, int y)
	{
	this->landscape[x][y] = organism;

	}

/*
Jonathan Prince
w0270525
Final Project
PROG C++
"ANT-LIONS"
*/
#include <conio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include "Ant.h"
#include "Organism.h"
#include "Lion.h"
#include "World.h"

#include <Windows.h>//to allow setting console colors.
using namespace std;


//function protypes
void display(World world);
void setColor(unsigned short color);
ostream& operator<<(ostream& output, World& world);
ostream& operator<<(ostream& inOrg, Organism& organism);

//Constant declarations
const short RED = 4;
const short BLUE = 9;
const short WHITE = 7;


const int TIME_TO_SLEEP = 500;//milliseconds
const int ITERATIONS = 1000;
const int EXTINCT = 0;

int numberOfAnts;
int numberOfLions;
int numberOfIterations = 0;


int main()
	{
	World world;

	world.setupWorld();

	display(world);

	_getch();

	return 0;
	}

//runs the display of the game
void display(World world)
	{
	clock_t timer;

	//loop until extinction event happens
	do
		{
		timer = clock();
		cout << "The Game of Life" << endl;
		numberOfIterations += 1;
		//routine for displaying grid of ants/lions

		//Top row of grid displayed
		cout << "+";
		for (int i = 0; i < GRID_WIDTH; i++)
			{
			cout << "-";
			}
		cout << "+" << endl;

		//output world
		world.takeTurn();
		world.breedLions();
		world.breedAnts();
		world.famine();

		cout << world;

		//Bottom row of grid
		cout << "+";
		for (int i = 0; i < GRID_WIDTH; i++)
			{
			cout << "-";
			}
		cout << "+" << endl << endl;


		//output stats
		numberOfAnts = world.countAnts();
		numberOfLions = world.countLions();

		cout << "Total remaining Ants: " + to_string(numberOfAnts) << endl;
		cout << "Total remaining Lions: " + to_string(numberOfLions) << endl;
		cout << "Number of iterations: " + to_string(numberOfIterations) << endl;

		if (numberOfAnts == EXTINCT || numberOfLions == EXTINCT)
			{
			cout << "Extinction occurred." << endl;

			break;//kicks out of while loop ;
			}

		if (numberOfIterations == ITERATIONS)
			{
			cout << to_string(numberOfIterations) + " iterations without an extinction." << endl;
			break;//kicks out of while loop 
			}

		while (clock() - timer <= TIME_TO_SLEEP) {}



		system("cls");

		} while (numberOfAnts != EXTINCT || numberOfLions != EXTINCT || numberOfIterations <= ITERATIONS);




	}//end display()



void setColor(unsigned short color)
	{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
	}

ostream& operator<<(ostream& output, World& world)
	{

	for (int row = 0; row < world.getGridHeight(); row++)
		{
		cout << "|";

		for (int column = 0; column < world.getGridWidth(); column++)
			{

			Organism* test = &world.getLandscapePosition(row, column);
			if (test != NULL)
				{
				cout << world.getLandscapePosition(row, column);
				}
			else
				{
				cout << " ";
				}
			}

		cout << "|" << endl;

		} //end outer

	return output;

	} //end overload

ostream& operator<<(ostream& inOrg, Organism& organism)
	{

	if (organism.whoIsThis() == "ant")
		{
		setColor(BLUE);
		cout << "O";
		setColor(WHITE);


		}
	else if (organism.whoIsThis() == "lion")
		{

		setColor(RED);
		cout << "X";
		setColor(WHITE);
		}

	return inOrg;

	} //end overload

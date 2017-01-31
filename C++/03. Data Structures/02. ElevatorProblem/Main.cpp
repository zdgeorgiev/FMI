/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Ivailov Georgiev
* @idnumber 45115
* @task 1
* @compiler VC
*
*/
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Queue.h"

using namespace std;

static const int SECONDS_PER_FLOOR = 5;

enum DIRECTION {
	UP,
	DOWN,
	NEUTRAL
};

struct FloorCommand
{
	int floor;
	int time;
	DIRECTION direction;

	FloorCommand() : floor(0), time(0) { }

	FloorCommand(int floor, int time, DIRECTION direction = DIRECTION::NEUTRAL) {
		this->floor = floor;
		this->time = time;
		this->direction = direction;
	}

	void print(int time, DIRECTION dir) {
		cout << time << " " << this->floor << " " << (dir == DIRECTION::UP ? "up" : "down") << endl;
	}
};

bool isBetween(int x, int firstBound, int secondBound) {
	return x >= min(firstBound, secondBound) && x <= max(firstBound, secondBound);
}

Queue<FloorCommand> parseCommands(char* argv[]) {

	ifstream f(argv[1]);
	
	int commandsCount = 0;
	int floors = 0;

	f >> floors >> commandsCount;

	Queue<FloorCommand> floorCommands;

	for (size_t i = 0; i < commandsCount; i++)
	{
		FloorCommand currentCommand;

		char type[32];
		char floor[32];
		char direction[32];
		char time[32];

		f >> type >> direction >> floor;

		if (strcmp(type, "call") == 0) {
			f >> time;
			currentCommand.direction = strcmp(direction, "down") ? DIRECTION::DOWN : DIRECTION::UP;
			currentCommand.floor = atoi(floor);
			currentCommand.time = atoi(time);
		}
		else {
			currentCommand.floor = atoi(direction);
			currentCommand.time = atoi(floor);
		}

		floorCommands.enqueue(currentCommand);
	}

	return floorCommands;
}

int main(int argc, char* argv[]) {

	// Read the floor commands from the first argument in argv and store them in queue
	Queue<FloorCommand> floors = parseCommands(argv);

	// We always start from the first floor in time 0
	FloorCommand startFloor = FloorCommand(1, 0);
	int startTime = startFloor.time;
	int floorsArrived = 0;

	while (!floors.isEmpty()) {

		FloorCommand endFloor = floors.peek(); floors.dequeue();
		startTime = max(startTime, endFloor.time);

		DIRECTION direction = startFloor.floor - endFloor.floor >= 0 ? DIRECTION::DOWN : DIRECTION::UP;

		int floorsRemaining = floors.getSize();

		// We can iterate like this because we know the incomming floors 
		// are always in the right order (sorted by time requested)
		for (size_t i = 0; i < floorsRemaining; i++) {
			FloorCommand nextFloor = floors.peek(); floors.dequeue();

			// Rquired time to travel from X to Z (between X and Y)
			int requiredTime = abs(startFloor.floor - nextFloor.floor) * SECONDS_PER_FLOOR;

			// We can travel from X -> Y and stop at Z if:
			//	* Z is >= X && Z <= Y
			//	* Z requestedTime < X startTime + travelTime(X,Z)
			if (isBetween(nextFloor.floor, startFloor.floor, endFloor.floor) &&
				nextFloor.time < startTime + requiredTime) {

				// We dont want to print N different requests
				// for the same floor (only the first one, all others are the same)
				if (nextFloor.floor != startFloor.floor && nextFloor.floor != endFloor.floor) {
					startTime += requiredTime;
					nextFloor.print(startTime, direction);
					startFloor.floor = nextFloor.floor;
				}
			}
			else {
				// If we cant travel to this floor we simply add it back to the top of the queue
				floors.enqueue(nextFloor);
			}
		}

		startTime += abs(startFloor.floor - endFloor.floor) * SECONDS_PER_FLOOR;
		endFloor.print(startTime, direction);
		startFloor.floor = endFloor.floor;
	}

	system("pause");
	return 0;
}
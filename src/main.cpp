#include <iostream>
#include <deque>
#include <ctime>

//Size of the 2D grid
#define GRID_WIDTH 6
#define GRID_HEIGHT 6

using namespace std;

enum TYPE {
	FREE,
	ITEM,
	BOX,
	WALL
};

struct Area {
	Area() :
		x(0),
		y(0),
		distance(-1),
		type(FREE){}

	int x;
	int y;
	int distance;
	TYPE type;

};

deque<Area*> areaQueue;
int playerPositionX = 0;
int playerPositionY = 0;

Area grid[GRID_HEIGHT][GRID_WIDTH];

void printGrid() {
	cout << "Grid:" << endl;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			switch (grid[y][x].type) {
			case FREE:
				cout << "   ";
				break;
			case WALL:
				cout << "  #";
				break;
			case BOX:
				cout << "  B";
				break;
			case ITEM:
				cout << "  *";
				break;
			}
		}
		cout << endl;
	}
}

void clearVisited()
{
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			grid[y][x].distance = -1;
		}
	}
}

/**
 * Fill grid with random values
 */
void fillGrid() {
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			grid[y][x].x = x;
			grid[y][x].y = y;
			//Left upper corner should be reserved for player
			if (y == 0 && x == 0 || y == 0 && x == 1 || x == 0 && y == 1) {
				continue;
			}

			grid[y][x].type = static_cast<TYPE>(rand() % 4);
		}
	}
}

/**
 * Calculate grid using Breadth-first search algorithm
 */
void bfs()
{
	//The grid area where the player is located
	Area* playerArea = &grid[playerPositionY][playerPositionX];
	areaQueue.push_back(playerArea);
	//Since we're already standing in this area, distance to this area should be equal to 0
	playerArea->distance = 0;

	while (!areaQueue.empty()) {
		Area* current = areaQueue.back();
		areaQueue.pop_back();

		//Check left neighbour
		if (current->x - 1 >= 0) {
			Area* left = &grid[current->y][current->x - 1];
			if (left->type <= ITEM) {
				//If we haven't visited this item, push it on the queue
				if (left->distance == -1) {
					areaQueue.push_back(left);
				}

				if (left->distance == -1 || left->distance > current->distance + 1) {
					left->distance = current->distance + 1;
				}
			}
		}

		//Check top neighbour
		if (current->y - 1 >= 0) {
			Area* top = &grid[current->y - 1][current->x];
			if (top->type <= ITEM) {
				//If we haven't visited this item, push it on the queue
				if (top->distance == -1) {
					areaQueue.push_back(top);
				}
				if (top->distance == -1 || top->distance > current->distance + 1) {
					top->distance = current->distance + 1;
				}
			}
		}

		//Check right neighbour
		if (current->x + 1 < GRID_WIDTH) {
			Area* right = &grid[current->y][current->x + 1];
			if (right->type <= ITEM) {
				//If we haven't visited this item, push it on the queue
				if (right->distance == -1) {
					areaQueue.push_back(right);
				}
				if (right->distance == -1 || right->distance > current->distance + 1) {
					right->distance = current->distance + 1;
				}
			}
		}

		//Check bottom neighbour
		if (current->y + 1 < GRID_HEIGHT) {
			Area* bottom = &grid[current->y + 1][current->x];
			if (bottom->type <= ITEM) {
				//If we haven't visited this item, push it on the queue
				if (bottom->distance == -1) {
					areaQueue.push_back(bottom);
				}
				if (bottom->distance == -1 || bottom->distance > current->distance + 1) {
					bottom->distance = current->distance + 1;
				}
			}
		}
	}
}

/**
* Calculate grid using Depth-first search algorithm
*/
void dfs()
{
	//The grid area where the player is located
	Area* playerArea = &grid[playerPositionY][playerPositionX];
	areaQueue.push_back(playerArea);

	while (!areaQueue.empty()) {
		Area* current = areaQueue.back();
		areaQueue.pop_back();
		//Check if we haven't visited this node yet
		if (current->distance == -1) {
			current->distance = 1;

			//Check left neighbour
			if (current->x - 1 >= 0) {
				Area* left = &grid[current->y][current->x - 1];
				if (left->type <= ITEM) {
					areaQueue.push_back(left);
				}
			}

			//Check top neighbour
			if (current->y - 1 >= 0) {
				Area* top = &grid[current->y - 1][current->x];
				if (top->type <= ITEM) {
					areaQueue.push_back(top);
				}
			}

			//Check right neighbour
			if (current->x + 1 < GRID_WIDTH) {
				Area* right = &grid[current->y][current->x + 1];
				if (right->type <= ITEM) {
					areaQueue.push_back(right);
				}
			}

			//Check bottom neighbour
			if (current->y + 1 < GRID_HEIGHT) {
				Area* bottom = &grid[current->y + 1][current->x];
				if (bottom->type <= ITEM) {
					areaQueue.push_back(bottom);
				}
			}

		}
	}
}

void outputDist()
{
	cout << endl;
	cout << "BFS calculated distances" << endl;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			cout << " " << grid[y][x].distance;
		}
		cout << endl;
	}
}

int main()
{
	srand(time(NULL));

	//Fill grid with random values
	fillGrid();

	//Outpu grid on the screen
	printGrid();

	//Calculate Breadth-first search algorithm values
	bfs();

	//Output calculated distances
	outputDist();

	//Clear bfs algorithm outputs
	clearVisited();

	//Calculate Depth-first search algorithm values
	dfs();

	//Output reachable grid areas from players standing position
	outputDist();


	//pause mechanism
	int i;
	cin >> i;
}
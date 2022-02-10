#pragma once
#include "PathfinderInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Pathfinder {
public:
	Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	bool find_maze_path(int grid[][5][5], int r, int c, int h);
	vector<string> solveMaze();

protected:
	static const int ROW_SIZE = 5;
  	static const int COL_SIZE = 5;
  	static const int HEIGHT_SIZE = 5;
  	const int BACKGROUND = 1;
  	const int WALL = 0;
  	const int TEMPORARY = 2; // Used to show this path has been explored
  	const int PATH = 3;
  	int maze_grid[ROW_SIZE][COL_SIZE][HEIGHT_SIZE]; // To hold values
	int temp[ROW_SIZE][COL_SIZE][HEIGHT_SIZE];
  	vector<string> solution;

};


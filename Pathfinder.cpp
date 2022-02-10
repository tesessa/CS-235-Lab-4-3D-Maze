#include "Pathfinder.h"


Pathfinder::Pathfinder() {
//	intialize_random_seed();
	srand(time(0));
	for (int row=0; row<ROW_SIZE; row++) {
		for (int col=0; col<COL_SIZE; col++) {
			for (int height=0; height<HEIGHT_SIZE; height++) {
				maze_grid[row][col][height] = 1;
				}
			}
		}

	}

bool Pathfinder::importMaze(string file_name)
	{	
		int countOnes = 0;
		int counter = 0;
		cout << "importMaze from "<<file_name<<endl;
		ifstream file (file_name.c_str());
		if (file.is_open()) {
			string line;
			int row_count = 0;
			for(int row = 0; row < ROW_SIZE; row++) {
				for(int col = 0; col < COL_SIZE; col++) {
					getline(file, line);
					stringstream ss(line);
					for(int height = 0; height < HEIGHT_SIZE; height++) {
					
					int value;
					ss >> value;
					if(value != 0 && value != 1) {
						return false;
					}
					if (value == 1) {
						countOnes++;
					}
					cout << "["<<row<<"]["<<col<<"]["<<height<<"]= "<<value<<endl;
					maze_grid[row][col][height] = value;
					counter++;
					}
				}
				getline(file, line);
			}
		}
		if(counter != 125) {
			return false;
		}
		if(countOnes == 125) {
			return false;
		}
		if (maze_grid[0][0][0] != 1 || maze_grid[4][4][4] != 1) {
			return false;
		}
	    return(true);
	}






string Pathfinder::toString() const
	{
	    stringstream ss;
	    for(int row = 0; row < ROW_SIZE; row++) {
	        for(int col = 0; col < COL_SIZE; col++) {
		 for(int height = 0; height < HEIGHT_SIZE; height++) {
	            ss << maze_grid[row][col][height];
		    }
	        ss << endl;
	    }
	    ss << endl;
	    }
	    return ss.str();
	}




	bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][HEIGHT_SIZE], int r, int c, int h) {
	  cout << "find_maze_path ["<<r<<"]["<<c<<"]["<<h<<"]"<<endl;
	  cout << this->toString();
	  if (r < 0 || c < 0 || h < 0 || r >= ROW_SIZE || c >= COL_SIZE || h>=HEIGHT_SIZE)
	    return false;      // Cell is out of bounds.
	  else if (grid[r][c][h] != BACKGROUND)
	    return false;      // Cell is on barrier or dead end.
	  else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && h == HEIGHT_SIZE-1) {
	    grid[r][c][h] = PATH;         // Cell is on path
	    solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(h)+")");
	    return true;               // and is maze exit.
	  }
	  else { 
	    // Recursive case.
	    // Attempt to find a path from each neighbor.
	    // Tentatively mark cell as on path.
	    grid[r][c][h] = PATH;
	    if (find_maze_path(grid, r-1, c, h) // Up
	        || find_maze_path(grid, r+1, c, h) // Down
	        || find_maze_path(grid, r, c-1, h) // Left
	        || find_maze_path(grid, r, c+1, h ) //Right 
		|| find_maze_path(grid, r, c, h+1) //forward
		|| find_maze_path(grid, r, c, h-1) //Back
		) {
	      solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(h)+")");
	      return true;
	    }
	    else {
	      grid[r][c][h] = TEMPORARY;  // Dead end.
	      return false;
	    }
	  }
 }






vector<string> Pathfinder::solveMaze()
{
	find_maze_path(maze_grid, 0,0,0);
	for(auto s:solution) {
	cout <<s<<endl;
	}
	return solution;
}

void Pathfinder::createRandomMaze() {
	for(int i = 0; i<ROW_SIZE; i++) {
		for(int j=0; j<COL_SIZE; j++) {
			for(int k=0; k<HEIGHT_SIZE; k++) {
				 maze_grid[i][j][k] = rand()%2;
			}
		}
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

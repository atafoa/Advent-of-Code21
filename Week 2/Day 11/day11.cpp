#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void print_grid(const std::vector<std::vector<int>>& grid){
	for(const auto& row: grid){
		for(const auto& elem: row){
			std::cout << elem;
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<int>> parse_input(const std::string& input_file){
	std::vector<std::vector<int>> grid;
	std::vector<int> row;
	std::ifstream input(input_file);
	std::string line;

	while(std::getline(input, line)){
		for(const auto& c: line)
			row.push_back(c - '0');

		grid.push_back(row);
		row.clear();
	}

	return grid;
}

void update_position(std::vector<std::vector<int>>& grid, int x, int y){

	grid[x][y] += 1;

	if (grid[x][y]==10) {
		int startx = (x-1>=0) ? x-1 : 0;
		int starty = (y-1>=0) ? y-1 : 0;
		int endx = (x+1>grid.size()-1) ? grid.size()-1 : x+1;
		int endy = (y+1>grid[0].size()-1) ? grid[0].size()-1 : y+1;

		for(int idx=startx; idx <= endx; ++idx){
			for(int idy=starty; idy <= endy; ++idy){
				update_position(grid, idx, idy);
			}
		}
	}

}

int part_one(std::vector<std::vector<int>>& grid){

	int count = 0;

	for(int i=0; i<100; ++i){
		for(int x=0; x<grid.size(); ++x){
			for(int y=0; y<grid[0].size(); ++y){
				update_position(grid, x, y);
			}
		}

		// count the flashes
		for(int x=0; x<grid.size(); ++x){
			for(int y=0; y<grid[0].size(); ++y){
				if (grid[x][y] > 9) {
					count++;
					grid[x][y] = 0;
				}
			}
		}
	}

	return count;
}

int part_two(std::vector<std::vector<int>>& grid){

	bool synced = false;
	// We need to keep in mind the steps from part 1
	int step = 100;
	int grid_sum = 0;
	while(!synced){
		grid_sum = 0;
		step++;
		for(int x=0; x<grid.size(); ++x){
			for(int y=0; y<grid[0].size(); ++y){
				update_position(grid, x, y);
			}
		}

		// count the flashes
		for(int x=0; x<grid.size(); ++x){
			for(int y=0; y<grid[0].size(); ++y){
				if (grid[x][y] > 9) {
					grid[x][y] = 0;
				}

				grid_sum += grid[x][y];
			}
		}

		synced = grid_sum == 0;

	}

	print_grid(grid);
	return step;

}



int main(int argc, char* argv[]) {
		
	std::string input_file = "input.txt";
	std::vector<std::vector<int>> grid = parse_input(input_file);
	print_grid(grid);
	std::cout << "-------------------" << std::endl;
	int sol1 = part_one(grid);

	std::cout << sol1 << std::endl;

	int step = part_two(grid);
	std::cout << "Step to sync is: " << step << std::endl;

}
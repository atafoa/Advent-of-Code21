#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Indication {
	int steps;
	string direction;
};

vector<Indication> parse_input(string fileName)
{
	int steps;
	string direction;
	Indication parsed_indication;

	ifstream infile(fileName);
	vector<Indication> directions;

	while (infile >> direction >> steps) 
	{
		parsed_indication.steps = steps;
		parsed_indication.direction = direction;
		directions.push_back(parsed_indication);
	}

	return directions;
}

pair<int, int> part_one(vector<Indication> input_directions)
{
	pair<int, int> coordinates;
	coordinates.first = 0;
	coordinates.second = 0;

	//adjusting horizontal position and depth using input directions
	for (Indication indication: input_directions) 
	{
		if (indication.direction == "down") 
		{
			coordinates.second += indication.steps;
		} 
		else if (indication.direction == "up") 
		{
			coordinates.second -= indication.steps;
		} 
		else 
		{
			coordinates.first  += indication.steps;
		}
	}

	return coordinates;
}

pair<int, int> part_two(vector<Indication> input_directions)
{
	int aim = 0;
	pair<int, int> coordinates;
	coordinates.first = 0;
	coordinates.second = 0;
	
	//adjusting horizontal position and depth using input directions and aim
	for (Indication indication: input_directions) 
	{
		if (indication.direction == "down") 
		{
			aim += indication.steps;
		} 
		else if (indication.direction == "up") 
		{
			aim -= indication.steps;
		} 
		else 
		{
			coordinates.first  += indication.steps;
			coordinates.second += aim * indication.steps;
		}
	}

	return coordinates;
}

int main(int argc, char* argv[]) {
	
	string input_file = "input.txt";
	vector<Indication> input = parse_input(input_file);
	pair<int, int> result1 = part_one(input);
	pair<int, int> result2 = part_two(input);
	cout << "X: " << result1.first << ", depth: " << result1.second << ". Solution is: " << result1.first * result1.second << endl;
	cout << "X: " << result2.first << ", depth: " << result2.second << ". Solution to part 2 is: " << result2.first * result2.second << endl;
	return 0;
}

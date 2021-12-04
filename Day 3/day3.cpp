#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <array>

int main() 
{
	const int bits = 12; // number of bits in the code
	
	// Retrieve input from file
	std::vector<std::bitset<bits>> reports;
	std::ifstream input("input.txt");
	std::string line;
	while(input >> line) 
	{
		reports.push_back(std::bitset<bits>(line));
	}
	
	// Determine gamma and epsilon rate
	std::bitset<bits> gamma_rate, epsilon_rate;
	for(int i = bits-1; i >= 0; i--)
	{
		int counts[2] {0,0};
		for(auto report : reports)
		{
			counts[report[i]]++;
		}
		gamma_rate[i] = counts[0] > counts[1] ? 0 : 1;
	}
	epsilon_rate = std::bitset<bits>(gamma_rate).flip();
	
	std::cout << "Gamma Rate: " << gamma_rate.to_ulong() << std::endl;
	std::cout << "Epsilon Rate : " << epsilon_rate.to_ulong() << std::endl;
	std::cout << "Electric Consumption : " << gamma_rate.to_ulong()*epsilon_rate.to_ulong() << std::endl;

    //part 2
    // Deternination of oxygen_generator_rating
	std::bitset<bits> oxygen_generator_rating;

	std::vector<std::bitset<bits>> most_common(reports); // copy to avoid altering the original input
	for(int i = bits-1; most_common.size() > 1 && i >= 0; i--)
	{
		std::array<std::vector<std::bitset<bits>>,2> filtered;
		for(auto report : most_common)
		{
			filtered[report[i]].push_back(report);
		}
		most_common = filtered[0].size() > filtered[1].size() ? filtered[0] : filtered[1]; // if equal 1 is kept
	}
	oxygen_generator_rating = most_common.at(0);
	
	// Determine tyhe co2_scrubber_rating
	std::bitset<bits> co2_scrubber_rating;

	std::vector<std::bitset<bits>> least_common(reports); // copy to avoid altering the original input
	for(int i = bits-1; least_common.size() > 1 && i >= 0; i--)
	{
		std::array<std::vector<std::bitset<bits>>,2> filtered;
		for(auto report : least_common)
		{
			filtered[report[i]].push_back(report);
		}
		least_common = filtered[0].size() > filtered[1].size() ? filtered[1] : filtered[0]; //if equal 0 is kept
	}
	co2_scrubber_rating = least_common.at(0);
	
    std::cout << std::endl;
	std::cout << "Oxygen generator rating : " << oxygen_generator_rating.to_ulong() << std::endl;
	std::cout << "Carbon dioxide scrubber rating : " << co2_scrubber_rating.to_ulong() << std::endl;
	std::cout << "Survival equipment rating : " << oxygen_generator_rating.to_ulong()*co2_scrubber_rating.to_ulong() << std::endl;
}
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>


bool coutSolution = false; //flag for printing visualization to console

int countOverlapsAndDraw(std::vector<std::vector<int>> inp, int part) {
	std::cout << "Output: ";
	if (!coutSolution) {
		std::cout << "disabled";
	}
	std::cout << std::endl;
	int counter = 0;
	std::ofstream outputFile;
	outputFile.open("output_" + std::to_string(part) + ".txt");
	for (size_t i = 0; i < inp.size(); i++) {
		for (size_t j = 0; j < inp[0].size(); j++) {
			if (coutSolution) {
				if (inp[i][j] == 0) std::cout << ".";
				else std::cout << inp[i][j];
				std::cout << " ";
			}
			if (inp[i][j] == 0) outputFile << ".";
			else outputFile << inp[i][j];
			outputFile << " ";

			if (inp[i][j] > 1) counter++;
		}
		if (coutSolution) std::cout << std::endl;
		outputFile << std::endl;
	}
	outputFile.close();
	return counter;
}

//part 2
void partTwo(std::deque<std::vector<int>> inputVectors, std::vector<std::vector<int>> solveMatrix) {
	for (size_t index = 0; index < inputVectors.size(); index++) {
		std::vector<int> item = inputVectors[index];
		if (item[0] != item[2] && item[1] != item[3]) {
			//fillWhere { xStart, xEnd, yStart, yEnd }
			std::vector<int> fillWhere = { 0, 0, 0, 0 };
			//Find lower on the Y axis
			if (item[1] < item[3]) {
				fillWhere[2] = item[1];
				fillWhere[0] = item[0];
				fillWhere[3] = item[3];
				fillWhere[1] = item[2];
			} else {
				fillWhere[2] = item[3];
				fillWhere[0] = item[2];
				fillWhere[3] = item[1];
				fillWhere[1] = item[0];
			}
			//std::cout << "Diagonal: " << fillWhere[0] << "," << fillWhere[2] << " -> " << fillWhere[1] << "," << fillWhere[3] << std::endl;
			//Right or left diagonal?
			if (fillWhere[0] > fillWhere[1]) {
				// Left
				int xIndex = fillWhere[0];
				for (int yIndex = fillWhere[2]; yIndex <= fillWhere[3]; yIndex++) {
					solveMatrix[yIndex][xIndex] += 1;
					xIndex--;
				}
			} else {
				// Right
				int xIndex = fillWhere[0];
				for (int yIndex = fillWhere[2]; yIndex <= fillWhere[3]; yIndex++) {
					solveMatrix[yIndex][xIndex] += 1;
					xIndex++;
				}
			}
		}
	}
	int overlaps = countOverlapsAndDraw(solveMatrix, 2);
 	std::cout << "Final result: " << overlaps << std::endl << std::endl;
}

int main() {
	std::string line;
	std::ifstream file("input.txt");
	std::deque<std::vector<int>> inputVectors = {};
	std::vector<int> maxSize = { 0, 0 };

	while (std::getline(file, line)) {
		std::stringstream X(line);
		std::string lineVecs;
		int vecIndex = 0;
		while (std::getline(X, lineVecs, ' ')) {
			if (vecIndex == 0) {
				inputVectors.push_back({});
			}
			if (vecIndex != 1) {
				std::stringstream Y(lineVecs);
				std::string vecCor;
				int coordIndex = 0;
				while (std::getline(Y, vecCor, ',')) {
					int vecCorInt = stoi(vecCor);
					inputVectors[inputVectors.size() - 1].push_back(vecCorInt);
					if (coordIndex == 0 || coordIndex == 2) {
						//X axis
						if (vecCorInt > maxSize[0]) {
							maxSize[0] = vecCorInt;
						}
					} else if (vecCorInt > maxSize[1]) {
						maxSize[1] = vecCorInt;
					}
					coordIndex++;
				}
			}
			vecIndex++;
		}
	}

	std::cout << "Loaded vectors (" << inputVectors.size() << ")" << std::endl;
	//Filter vectors
	std::deque<std::vector<int>> filteredInput = {};
	for (size_t index = 0; index < inputVectors.size(); index++) {
		std::vector<int> item = inputVectors[index];
		if (item[0] == item[2] || item[1] == item[3]) {
			filteredInput.push_back(item);
		}
	}
	std::cout << "Filtered vectors (" << filteredInput.size() << ")" << std::endl;

	//Initialize matrix
	std::vector<std::vector<int>> solveMatrix(maxSize[1] + 1, std::vector<int>(maxSize[0] + 1));
	std::cout << "Initialized solve matrix (" << solveMatrix.size() << "," << solveMatrix[0].size() << ")" << std::endl << std::endl;

	for (size_t index = 0; index < filteredInput.size(); index++) {
		std::vector<int> item = filteredInput[index];
		if (item[0] == item[2]) {
			int xCoord = item[0];
			//Same X coord, it's a column
			std::vector<int> fillWhere = { 0, 0 };
			if (item[1] > item[3]) {
				fillWhere[0] = item[3];
				fillWhere[1] = item[1];
			} else {
				fillWhere[0] = item[1];
				fillWhere[1] = item[3];
			}
			for (size_t matrixCol = fillWhere[0]; matrixCol <= fillWhere[1]; matrixCol++) {
				solveMatrix[matrixCol][xCoord] += 1;
			}
		} else {
			//Same Y coord, it's a row
			int yCoord = item[1];
			std::vector<int> fillWhere = { 0, 0 };
			if (item[0] > item[2]) {
				fillWhere[0] = item[2];
				fillWhere[1] = item[0];
			} else {
				fillWhere[0] = item[0];
				fillWhere[1] = item[2];
			}
			for (size_t matrixRow = fillWhere[0]; matrixRow <= fillWhere[1]; matrixRow++) {
				solveMatrix[yCoord][matrixRow] += 1;
			}
		}
	}


	int overlaps = countOverlapsAndDraw(solveMatrix, 1);
	std::cout << "Final result: " << overlaps << std::endl << std::endl;

	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();

	partTwo(inputVectors, solveMatrix);
	return 0;
}
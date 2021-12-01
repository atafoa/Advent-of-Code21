#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//helper function to read input as integer vector
vector<int>fileToVector(const char *name)
{
    vector<int> result;
    ifstream input (name);
    string lineData;

    while(getline(input, lineData))
    {
        int d;
        stringstream lineStream(lineData);

        while (lineStream >> d)
        {
            result.push_back(d);
        }
    }

    return result;
}


//calculate the number of times the sum of measurements in this sliding window increases from the previous sum
int getIncreased(vector<int> depths) 
{
    int increasedCounts = 0;
    for (int i = 3; i < depths.size(); i++)
    {
        int currentDepth = depths[i] + depths[i - 1]+ depths[i - 2];
        int previousDepth = depths[i - 1] + depths[i - 2] + depths[i - 3];
        increasedCounts += (currentDepth > previousDepth) ? 1 : 0;
    }
    return increasedCounts;
}

int main()
{
    vector<int> depths = fileToVector("input.txt");
    int result = getIncreased(depths);
    cout << "Result: " << result << endl;
}
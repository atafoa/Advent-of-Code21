#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//helper function to convert file input to int vector
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

//count the number of times a depth measurement increases from the previous measurement
int getIncreased(vector<int> depths) 
{
    int increasedCounts = 0;
    for (int i = 1; i < depths.size(); i++)
    {
        if(depths[i] > depths[i - 1])
        {
            increasedCounts++;
        }
    }
    return increasedCounts;
}

int main()
{
    vector<int> depths = fileToVector("input.txt");
    int result = getIncreased(depths);
    cout << "Result: " << result << endl;
}
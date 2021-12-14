#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std;

struct Graph {
    vector<vector<int>> adjacent;
    vector<bool> big;
    int start, end;

    Graph(istream& in) {
        map<string, int> index;
        string a, b;

        while (getline(in, a, '-') && getline(in, b)) {
            int ia = index.insert({a, index.size()}).first->second;
            int ib = index.insert({b, index.size()}).first->second;
            adjacent.resize(index.size());
            adjacent[ia].push_back(ib);
            adjacent[ib].push_back(ia);
        }

        big.resize(index.size());
        for (const auto& [cave, i] : index)
            big[i] = cave[0] >= 'A' && cave[0] <= 'Z';

        start = index["start"];
        end = index["end"];
    }

    int paths(bool may_dup) {
        vector<tuple<int, int, bool>> work = {{start, 1 << start, not may_dup}};
        int distinct = 0;

        while (!work.empty()) {
            auto [prev, visited, dup] = work.back();
            work.pop_back();
            for (int nb : adjacent[prev]) {
                if (nb == end)
                    ++distinct;
                else if (big[nb] || !(visited >> nb & 1))
                    work.push_back({nb, visited | 1 << nb, dup});
                else if (!dup && nb != start)
                    work.push_back({nb, visited, true});
            }
        }

        return distinct;
    }
};

int main() {
    ifstream in("input.txt");
    Graph graph(in);
    cout << graph.paths(false) << endl;
    cout << graph.paths(true) << endl;
    return 0;
}
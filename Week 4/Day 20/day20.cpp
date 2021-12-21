#include <iostream>
#include <string>
#include <set>
#include <fstream>


//c++17
auto enhance(const std::set<std::pair<int, int>> &pixels, const std::string &iea, int &infinite)
{
    std::set<std::pair<int, int>> next;
    int mx = INT32_MAX, my = INT32_MAX, lx = INT32_MIN, ly = INT32_MIN;
    for (const auto &[x, y] : pixels)
    {
        mx = std::min(mx, x);
        my = std::min(my, y);
        lx = std::max(lx, x);
        ly = std::max(ly, y);
    }

    for (int y = my - 1; y <= ly + 1; y++)
        for (int x = mx - 1; x <= lx + 1; x++)
        {
            int coord = 0;
            for (int j = y - 1; j <= y + 1; j++)
                for (int i = x - 1; i <= x + 1; i++)
                    if (mx <= i && i <= lx && my <= j && j <= ly)
                        coord = coord << 1 | pixels.count({i, j});
                    else
                        coord = coord << 1 | infinite;
            if (iea[coord] == '#')
                next.insert({x, y});
        }

    infinite = (iea[infinite * (iea.size() - 1)] == '#'); // 0 -> iea[0], 1 -> iea[511]
    return next;
}

int execute(int steps)
{
    std::ifstream input("input.txt");
    std::string iea;
    input >> iea;
    std::set<std::pair<int, int>> pixels;
    for (auto [y, line] = std::pair{0, std::string{}}; input >> line; y++)
        for (int x = 0; x < line.length(); x++)
            if (line[x] == '#')
                pixels.insert({x, y});
    int infinite = 0;
    for (int i = 0; i < steps; i++)
        pixels = enhance(pixels, iea, infinite);
    return pixels.size();
}

int main()
{
    std::cout << "Part 1 " << execute(2) << std::endl; //Part 1
    std::cout << "Part 2 " << execute(50) << std::endl; // Part 2
    return 0;
}
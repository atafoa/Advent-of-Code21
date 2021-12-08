#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <fstream>




int deduct(const std::vector<std::bitset<7>> &entry)
{
    std::unordered_map<std::bitset<7>, int> table = {{0b1111111, 8}};
    std::bitset<7> m4, m1;
    for (int i = 0; i < 10; i++)
    {
        auto e = entry[i];
        if (e.count() == 2)
        {
            m1 = e;
            table[m1] = 1;
        }
        else if (e.count() == 4)
        {
            m4 = e;
            table[m4] = 4;
        }
        else if (e.count() == 3)
            table[e] = 7;
    }
    for (int i = 0; i < 10; i++)
    {
        auto e = entry[i];
        if (e.count() == 6)
        {
            if ((e & m4) == m4)
                table[e] = 9;
            else if ((e & m1) == m1)
                table[e] = 0;
            else
                table[e] = 6;
        }
        else if (e.count() == 5)
        {
            if ((e & m1) == m1)
                table[e] = 3;
            else if ((~e & m4) == ~e)
                table[e] = 2;
            else
                table[e] = 5;
        }
    }
    int num = 0;
    for (int i = entry.size() - 4; i < entry.size(); i++)
        num = 10 * num + table[entry[i]];
    return num;
}

int part1()
{
    std::ifstream fin("input.txt");
    int counter = 0;
    int index = 0;
    for (std::string value; fin >> value; index = (index + 1) % 15)
    {
        if (index <= 10)
            continue;
        int len = value.size();
        if (len == 2 || len == 4 || len == 3 || len == 7)
            counter++;
    }
    return counter;
}

int part2()
{
    std::ifstream fin("input.txt");
    int sum = 0;
    std::vector<std::bitset<7>> entry;
    for (std::string value; fin >> value;)
    {
        std::bitset<7> mask = 0;
        for (char c : value)
            mask |= 1 << (c - 'a');
        entry.push_back(mask);
        if (entry.size() == 15)
        {
            sum += deduct(entry);
            entry.clear();
        }
    }
    return sum;
}

int main()
{
    int result1 = part1();
    int result2 = part2();

    std::cout << "Part 1: " << result1 << std::endl;
    std::cout << "Part 2: " << result2 << std::endl;
    return 0;
}
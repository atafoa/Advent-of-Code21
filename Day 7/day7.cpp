#include <iostream>

using namespace std;

#define endl '\n'


#define maxN 10000

int a[maxN];
int len;

void testcase() {
    std::sort(a, a + len);
    int pos = a[len / 2];
    long long ans = 0;
    for (int i = 0; i < len; ++i) {
        ans += abs(a[i] - pos);
    }
    cout << ans << endl;
}

void testcase2() {
    long long sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += a[i];
    }
    long double avg = sum / len;
    // ans for avg and avg + 1
    long long ans1 = 0, ans2 = 0;
    int num1 = (int) avg, num2 = num1 + 1;
    for (int i = 0; i < len; ++i) {
        int dist = abs(a[i] - num1);
        ans1 += (long long) dist * (dist + 1) / 2;
    }
    for (int i = 0; i < len; ++i) {
        int dist = abs(a[i] - num2);
        ans2 += (long long) dist * (dist + 1) / 2;
    }
    cout << min(ans1, ans2) << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    std::string line;
    len = 0;
    while (std::getline(cin, line) && cin) {
        int prev = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == ',') {
                a[len++] = stoi(line.substr(prev, i - prev));
                prev = i + 1;
            }
        }
        a[len++] = stoi(line.substr(prev, line.length() - prev));
    }
    testcase();
    testcase2();
    return 0;
}
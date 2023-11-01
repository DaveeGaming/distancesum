#include <array>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>

void printmatrix(std::vector<std::vector<int>>& input) {
    for (auto v :input) {
        for (auto i : v) {
            std::cerr << i;
        }
        std::cerr << '\n';
    }
}

int inputCharToInt(char c) {
    switch (c) {
        case '-': return 0;
        case 'X': return -17;
        case 'T': return -16;
        default:
            std::string tmp {c };
            return -std::stoi(tmp, nullptr, 16);
    }
}

int main(){
    int n{}, m{};
    std::cin >> n >> m;
    std::vector<std::vector<int>> input(n); 
    for (int i = 0; i < n; ++i) {
        std::string tmp;
        std::cin >> tmp;
        std::vector<int> line(m);
        for (int j = 0; j < m; ++j) {
            line[j] = inputCharToInt(tmp[j]);
        }
        input[i] = line;
    }
    printmatrix(input);
}


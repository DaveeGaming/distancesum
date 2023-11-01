#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

void printmatrix(const std::vector<std::vector<int>>& input) {
    for (const auto v :input) {
        for (const auto i : v) {
            printf("%03d ", i);
        }
        printf("\n");
    }
}

int inputCharToInt(const char c) {
    switch (c) {
        case '-': return 0;
        case 'X': return -17;
        case 'T': return -16;
        default:
            char hex = toupper(c);
            if (hex >= 'A' && hex <= 'F') return -(hex-'A'+10);
            else if (hex >= '0' && hex <= '9') return -(hex - '0');
            return 0;
    }
}

void getInputFromCin(std::vector<std::vector<int>>& input, std::pair<int,int>& start, int m, int n) {
    for (int i = 0; i < m; ++i) {
        std::string tmp;
        std::cin >> tmp;
        for (int j = 0; j < n; ++j) {
            input[i][j] = inputCharToInt(tmp[j]);
            if (tmp[j] == 'T') start = std::make_pair(i,j);
        }
    }
    if (start.first == -1) {

    }
}

bool isCellValid(std::vector<std::vector<int>>& input, int x, int y) {
    int m = input.size();
    int n = input[0].size();
    if ( (x >= 0 && x < m) && (y >= 0 && y < n)) {
         return true;
    }
    return false;
}

constexpr std::pair<int,int> offsets[4] {{0, 1}, {0, -1}, {1, 0}, {-1, 0} };

void calculateDistanceMatrix(std::vector<std::vector<int>>& input, std::pair<int,int>& start) {
    std::queue<std::pair<int,int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        std::pair<int,int> cell = queue.front();
        queue.pop();
        for (auto offset : offsets) {
            std::pair<int,int> adj {cell.first + offset.first, cell.second + offset.second};
            if (isCellValid(input, adj.first, adj.second)) {
                int currDistance = std::max(input[cell.first][cell.second],0);
                if (/* input[adj.first][adj.second] > currDistance  || */ input[adj.first][adj.second] == 0) {
                    input[adj.first][adj.second] = currDistance + 1;
                    queue.push(adj);
                }
            }
        }

    }

}

int main(){
    int m, n;
    std::cin >> m >> n;
    auto input = std::vector<std::vector<int>>(m, std::vector<int>(n));
    std::pair<int,int> startpos(-1,-1);
    getInputFromCin(input, startpos, m, n);
    calculateDistanceMatrix(input, startpos);
    printmatrix(input);
}

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

constexpr std::pair<int,int> offsets[4] {{0, 1}, {-1, 0}, {0, -1}, {1, 0} };

int inputCharToInt(const char c) {
    switch (c) {
        case '-': return 0;
        case 'X': return -17;
        case 'T': return -16;
        default:
            int hex = toupper(c);
            if (hex >= 'A' && hex <= 'F') return -(hex-'A'+10);
            else if (hex >= '0' && hex <= '9') return -(hex - '0');
            return 0;
    }
}

void getInputFromCin(std::vector<std::vector<int>>& input, std::pair<int,int>& start,const int m,const int n) {
    for (int i = 0; i < m; ++i) {
        std::string tmp;
        tmp.reserve(n);
        std::cin >> tmp;
        for (int j = 0; j < n; ++j) {
            input[i][j] = inputCharToInt(tmp[j]);
            if (tmp[j] == 'T') start = std::make_pair(i,j);
        }
    }
    if (start.first == -1) {
        std::cout << "0";
        std::exit(0);
    }
}

bool isCellValid(const std::vector<std::vector<int>>& input,const int x,const int y) {
    return ( (x >= 0 && x < input.size()) && (y >= 0 && y < input[0].size()));
}


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
                if (input[adj.first][adj.second] == 0) {
                    input[adj.first][adj.second] = currDistance + 1;
                    queue.push(adj);
                }
            }
        }
    }
}


int readGoalDistanceSum(const std::vector<std::vector<int>>& input) {
    int distancesum {0};
    for (int i = 0; i < input.size(); ++i) {
        for (int j = 0; j < input[i].size(); ++j) {
            if (input[i][j] < 0 && input[i][j] > -16) {
                int mask = -input[i][j];
                int closestDistance {std::numeric_limits<int>::max()};
                if (mask & 1 && isCellValid(input, i, j + 1) && input[i][j + 1] > 0) closestDistance = std::min(closestDistance, input[i][j + 1]);
                if (mask & 2 && isCellValid(input, i - 1, j) && input[i - 1][j] > 0) closestDistance = std::min(closestDistance, input[i - 1][j]);
                if (mask & 4 && isCellValid(input, i, j - 1) && input[i][j - 1] > 0) closestDistance = std::min(closestDistance, input[i][j - 1]);
                if (mask & 8 && isCellValid(input, i + 1, j) && input[i + 1][j] > 0) closestDistance = std::min(closestDistance, input[i + 1][j]);

                if (closestDistance == std::numeric_limits<int>::max()) closestDistance = 0;
                distancesum += closestDistance;
            }
        }
    }
    return distancesum;
}

int main(){
    int m, n;
    std::cin >> m >> n;
    auto input = std::vector<std::vector<int>>(m, std::vector<int>(n));
    std::pair<int,int> startpos(-1,-1);
    getInputFromCin(input, startpos, m, n);
    calculateDistanceMatrix(input, startpos);
    std::cout << readGoalDistanceSum(input);
}

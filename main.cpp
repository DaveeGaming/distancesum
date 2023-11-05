#include <iostream>
#include <queue>
#include <limits>

constexpr std::pair<int,int> offsets[4] {{0, 1}, {-1, 0}, {0, -1}, {1, 0} };

template <typename T>
class Matrix {
public:
    Matrix(int row, int col) {
        data = new T*[row];
        for (int i = 0; i < row; ++i) {
            data[i] = new T[col];
            for (int j = 0; j < col; ++j) {
                data[i][j] = T{};
            }
        }
        this->row = row;
        this->col = col;
    }
    ~Matrix(){
        for (int i = 0; i < row; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    T* operator[] (int i) const {
        return data[i];
    }

    int row{};
    int col{};
private:
    T **data;
};

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

void getInputFromCin(Matrix<int> & input, std::pair<int,int>& start) {
    for (int i = 0; i < input.row; ++i) {
        std::string tmp;
        std::cin >> tmp;
        for (int j = 0; j < input.col; ++j) {
            input[i][j] = inputCharToInt(tmp[j]);
            if (tmp[j] == 'T') start = std::make_pair(i,j);
        }
    }
    if (start.first == -1) {
        std::cout << "0";
        std::exit(0);
    }
}

bool isCellValid(const Matrix<int> & input,const int x,const int y) {
    return ( (x >= 0 && x < input.row) && (y >= 0 && y < input.col));
}


void calculateDistanceMatrix(Matrix<int> & input,const std::pair<int,int>& start) {
    std::queue<std::pair<int,int>> queue;
    queue.push(start);
    Matrix<bool> visited(input.row,input.col);
    for (int i = 0; i < input.row; ++i) {
        for (int j = 0; j < input.col; ++j) {
            visited[i][j] = input[i][j] < 0;
        }
    }

    while (!queue.empty()) {
        std::pair<int,int> cell = queue.front();
        int currDistance = std::max(input[cell.first][cell.second],0);
        queue.pop();

        for (auto const offset : offsets) {
            std::pair<int,int> adj {cell.first + offset.first, cell.second + offset.second};

            if (isCellValid(input, adj.first, adj.second) && !visited[adj.first][adj.second]) {
                input[adj.first][adj.second] = currDistance + 1;
                visited[adj.first][adj.second] = true;
                queue.push(adj);

            }
        }
    }
}


int readGoalDistanceSum(const Matrix<int> & input) {
    int distancesum {0};
    for (int i = 0; i < input.row; ++i) {
        for (int j = 0; j < input.col; ++j) {
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
    Matrix<int> input(m,n);
    std::pair<int,int> startpos(-1,-1);
    getInputFromCin(input, startpos);
    calculateDistanceMatrix(input, startpos);
    std::cout << readGoalDistanceSum(input);
}
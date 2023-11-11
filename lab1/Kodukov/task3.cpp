// 1, 3, 6, 13, 24, 48, 86, 160, 282, 500, 859, 1479, 2485, 4167, 6879, 11297, 18334, 29601, 47330, 75278, 118794, 186475, 290783, 451194, 696033, 1068745, 1632658, 2483234, 3759612, 5668963, 8512309, 12733429, 18974973, 28175955, 41691046, 61484961, 90379784, 132441995, 193487501, 281846923 

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <unordered_set>
#include <cmath>
#include <shared_mutex>
#include <set>

const int N = 25;

typedef unsigned char uchar;

struct Diagram {
    uchar data[N][N];

    Diagram() {
        std::memset(data, 0, N * N);
    }

    Diagram(const Diagram& other) {
        *this = other;
    }

    Diagram& operator=(const Diagram& other) {
        std::memcpy(data, other.data, sizeof(uchar) * N * N);
        return *this;
    }
};

typedef std::vector<Diagram> DiagramsVec;

void print_diag(std::ofstream &file, const Diagram &diag) {
    for (size_t i = 0; i < N; i++) {
        if (diag.data[i][0] == 0)
            break;
        if (i != 0)
            file << ", ";
        for (size_t j = 0; j < N; j++) {
            if (diag.data[i][j] == 0)
                break;
            if (j != 0)
                file << " ";
            file << int(diag.data[i][j]);
        }
    }
    file << "\n";
}

bool check_exist(const DiagramsVec &diagrams, const Diagram &new_diag) {
    for (auto &diag: diagrams) {
        bool difference_found = false;
        for (size_t i = 0; i < N; i++) {
            if (difference_found)
                break;
            if (new_diag.data[i][0] == 0)
                break;

            for (size_t j = 0; j < N; j++){
                if (new_diag.data[i][j] == 0)
                    break;

                if (diag.data[i][j] != new_diag.data[i][j]) {
                    difference_found = true;
                    break;
                }
            }
        }
        if (!difference_found)
            return true;
    }
    return false;
}

void add_one_cell(DiagramsVec &prev_diagrams, int N, DiagramsVec &result_diagrams) {
    result_diagrams.clear();
    // result_diagrams.reserve(prev_diagrams.size() * 2 + 1);
    
    // check every diagram with N-1 cells
    for (auto &diag: prev_diagrams) {
        for (int i = 0; i < N; i++) {
            // cant go up further
            if (i != 0 && diag.data[i - 1][0] == 0)
                break;

            for (int j = 0; j < N; j++) {
                // cant go right further
                if (j != 0 && diag.data[i][j - 1] == 0)
                    break;
                
                uchar &cur_cell = diag.data[i][j];
                // check if it possible to increse this cells
                bool left_bigger = (i == 0 || diag.data[i - 1][j] > cur_cell);
                bool bottom_bigger = (j == 0 || diag.data[i][j - 1] > cur_cell);

                if (left_bigger && bottom_bigger) {
                    cur_cell++;
                    if (!check_exist(result_diagrams, diag)){
                        result_diagrams.push_back(diag);
                    }
                    cur_cell--;
                }
            }
        }
    }
}

using cl = std::chrono::high_resolution_clock;

int main() {
    Diagram start_diag;
    DiagramsVec cur_diagrams;
    DiagramsVec prev;
    cur_diagrams.push_back(start_diag);

    for (int lvl = 1; lvl < N + 1; lvl++) {
        prev = std::move(cur_diagrams);
        auto start = cl::now();

        add_one_cell(prev, N, cur_diagrams);

        auto end = cl::now();
        auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Level: " << lvl << ". Count: " << cur_diagrams.size() << " [" << time_ms << "ms]\n";
        std::ofstream file("./" + std::to_string(lvl) + ".txt", std::ios_base::out);
        file << "Level: " << lvl << ". Count: " << cur_diagrams.size() << "\n";
        for (auto &diag: cur_diagrams)
            print_diag(file, diag);
        file.close();
    }

    return 0;
}

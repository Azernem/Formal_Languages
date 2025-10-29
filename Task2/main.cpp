#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<int> searchUnreachible(std::string file) {
    std::vector<std::vector<int>> mas;
    std::ifstream f(file);
    std::string line;
    while (std::getline(f, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            row.push_back(num);
        }
        mas.push_back(row);
    }
    
    std::vector<int> result;
    for (int i = 0; i < mas.size(); i++) {
        bool hasEdge = false;
        for (int j = 0; j < mas[i].size(); j++) {
            if (mas[i][j] == 1 && i != j) {
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            result.push_back(i + 1);
        }
    }
    std::ofstream out("result.txt");
    for (int num : result) {
        out << num << " ";
    }
    out.close();
    
    return result;
}

int main() {
    std::vector<int> result = searchUnreachible("input.txt");
    std::cout << "Result: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Result.txt" << std::endl;
    
    return 0;
}
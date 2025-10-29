#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Vertex {
    string name;
    vector<Vertex*> neighbors;

    Vertex(const string& n) : name(n) {}
};

vector<Vertex*> Bypass(Vertex* start) {
    queue<Vertex*> q;
    vector<Vertex*> reachable;
    set<string> visited;

    q.push(start);
    visited.insert(start->name);

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        reachable.push_back(current);

        for (auto* neigh : current->neighbors) {
            if (visited.find(neigh->name) == visited.end()) {
                q.push(neigh);
                visited.insert(neigh->name);
            }
        }
    }

    return reachable;
}

int main() {
    ifstream file("1.txt");
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл 1.txt" << endl; return 1;
    }
    map<string, Vertex*> vertices;
    vector<string> lines;
    string line;

    //Считываем
    while (getline(file, line)) {
        if (!line.empty())
            lines.push_back(line);
    }
    file.close();

    // вершины
    for (const auto& l : lines) {
        if (l.find(':') == string::npos) continue;
        string left = l.substr(0, l.find(':'));
        left.erase(remove_if(left.begin(), left.end(), ::isspace), left.end());

        if (vertices.find(left) == vertices.end())
            vertices[left] = new Vertex(left);
    }

    for (const auto& l : lines) {
        size_t colon = l.find(':');
        if (colon == string::npos) continue;

        string left = l.substr(0, colon);
        string right = l.substr(colon + 1);

        // Удаляем пробелы
        left.erase(remove_if(left.begin(), left.end(), ::isspace), left.end());
        right.erase(remove_if(right.begin(), right.end(), ::isspace), right.end());

        Vertex* from = vertices[left];

        for (char& c : right) {
            if (c == '(' || c == ')' || c == ';')
                c = ' ';
        }

        stringstream ss(right);
        string token;
        while (getline(ss, token, ',')) {
            // заменяем '#' на пробел
            replace(token.begin(), token.end(), '#', ' ');
            stringstream subtok(token);
            string sub;
            while (subtok >> sub) {
                if (vertices.find(sub) == vertices.end())
                    vertices[sub] = new Vertex(sub);
                from->neighbors.push_back(vertices[sub]);
            }
        }
    }
    // BFS 
    cout << "Обход графа в ширину (BFS)" << endl;

    if (vertices.find("G") != vertices.end()) {
        vector<Vertex*> reachable = Bypass(vertices["G"]);

        for (auto* v : reachable)
            cout << v->name << endl;
    } else {
        cout << "Нет вершины G в грамматике." << endl;
    }

    for (auto& p : vertices)
        delete p.second;
    return 0;
}
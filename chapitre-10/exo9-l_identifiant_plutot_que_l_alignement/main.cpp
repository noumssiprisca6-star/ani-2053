#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> planche;
    int nextId = 1;

    long long occasions = 0;
    long long repercutes = 0;
    long long recherches = 0;

    for (int i = 0; i < n; ++i) {
        std::string op;
        std::cin >> op;

        if (op == "AJOUTE") {
            planche.push_back(nextId++);
        }
        else if (op == "SUPPRIME") {
            int c;
            std::cin >> c;
            std::vector<int> idx(c);
            for (int j = 0; j < c; ++j) {
                std::cin >> idx[j];
            }
            std::sort(idx.rbegin(), idx.rend());

            for (int index : idx) {
                if (index >= 0 && index < (int)planche.size()) {
                    planche.erase(planche.begin() + index);
                }
            }

            occasions += 1;
            repercutes += 2 * c;
        }
        else if (op == "MONTE") {
            int index;
            std::cin >> index;
            if (index >= 0 && index + 1 < (int)planche.size()) {
                std::swap(planche[index], planche[index + 1]);
                occasions += 1;
                repercutes += 2;
            }
        }
        else if (op == "DESCEND") {
            int index;
            std::cin >> index;
            if (index > 0 && index < (int)planche.size()) {
                std::swap(planche[index], planche[index - 1]);
                occasions += 1;
                repercutes += 2;
            }
        }
        else if (op == "DESSINE") {
            recherches += planche.size();
        }
    }

    std::cout << "ORDRE";
    if (planche.empty()) {
        std::cout << " AUCUN\n";
    } else {
        for (int id : planche) {
            std::cout << " " << id;
        }
        std::cout << "\n";
    }

    std::cout << "OCCASIONS " << occasions << "\n";
    std::cout << "REPERCUTES " << repercutes << "\n";
    std::cout << "RECHERCHES " << recherches << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }
    std::string dummy;
    std::getline(std::cin, dummy);

    std::map<std::string, std::vector<std::string>> adj;
    std::vector<std::string> fichiers;

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            --i;
            continue;
        }
        std::stringstream ss(line);
        std::string fichier;
        ss >> fichier;
        fichiers.push_back(fichier);

        int k;
        ss >> k;
        for (int j = 0; j < k; ++j) {
            std::string inc;
            ss >> inc;
            adj[inc].push_back(fichier);
        }
    }

    int q;
    if (!(std::cin >> q)) {
        return 0;
    }
    std::vector<std::string> questions(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> questions[i];
    }

    auto getRecompilesCount = [&](const std::string& start) {
        std::set<std::string> recompileSet;
        std::queue<std::string> fileQueue;

        fileQueue.push(start);

        if (start.size() >= 4 && start.rfind(".cpp") == start.size() - 4) {
            recompileSet.insert(start);
        }

        while (!fileQueue.empty()) {
            std::string curr = fileQueue.front();
            fileQueue.pop();

            if (adj.count(curr)) {
                for (const auto& next : adj[curr]) {
                    if (next.size() >= 4 && next.rfind(".cpp") == next.size() - 4) {
                        recompileSet.insert(next);
                    }
                    fileQueue.push(next);
                }
            }
        }
        return static_cast<int>(recompileSet.size());
    };

    std::vector<int> resultats(q);
    for (int i = 0; i < q; ++i) {
        resultats[i] = getRecompilesCount(questions[i]);
        std::cout << questions[i] << " " << resultats[i] << "\n";
    }

    std::string plusLourd = "AUCUN";
    int maxPoids = -1;

    for (const auto& f : fichiers) {
        if (f.size() >= 2 && f.rfind(".h") == f.size() - 2) {
            int poids = getRecompilesCount(f);
            if (poids > maxPoids) {
                maxPoids = poids;
                plusLourd = f;
            }
        }
    }

    if (maxPoids <= 0) {
        std::cout << "PLUS_LOURD AUCUN\n";
    } else {
        std::cout << "PLUS_LOURD " << plusLourd << " " << maxPoids << "\n";
    }

    return 0;
}
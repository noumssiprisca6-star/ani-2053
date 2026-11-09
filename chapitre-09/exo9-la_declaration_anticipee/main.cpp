#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

int main() {
    int u;
    if (!(std::cin >> u)) {
        return 0;
    }
    std::string dummy;
    std::getline(std::cin, dummy);

    std::map<std::string, bool> inclureMap;
    std::vector<std::string> order;

    for (int i = 0; i < u; ++i) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            --i;
            continue;
        }
        std::stringstream ss(line);
        std::string type, emploi;
        ss >> type >> emploi;

        if (inclureMap.find(type) == inclureMap.end()) {
            inclureMap[type] = false;
            order.push_back(type);
        }

        if (emploi == "VALEUR" || emploi == "BASE" || emploi == "CORPS" || emploi == "TAILLE") {
            inclureMap[type] = true;
        }
    }

    int aCount;
    if (!(std::cin >> aCount)) {
        aCount = 0;
    }

    std::set<std::string> inclusActuels;
    for (int i = 0; i < aCount; ++i) {
        std::string incl;
        std::cin >> incl;
        inclusActuels.insert(incl);
    }

    int nbInclure = 0;
    int nbAnticiper = 0;
    int inclusionsRetirees = 0;

    for (const auto& type : order) {
        bool besoinDef = inclureMap[type];
        if (besoinDef) {
            std::cout << type << " INCLURE\n";
            nbInclure++;
        } else {
            std::cout << type << " ANTICIPER\n";
            nbAnticiper++;
            if (inclusActuels.count(type)) {
                inclusionsRetirees++;
            }
        }
    }

    std::cout << "INCLURE " << nbInclure << "\n";
    std::cout << "ANTICIPER " << nbAnticiper << "\n";
    std::cout << "INCLUSIONS_RETIREES " << inclusionsRetirees << "\n";

    return 0;
}
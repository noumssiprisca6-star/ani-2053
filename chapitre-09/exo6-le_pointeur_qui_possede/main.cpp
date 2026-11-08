#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

struct Instruction {
    int ligne;
    std::string type;
    std::string arg1;
    std::string arg2;
};

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }
    std::string dummy;
    std::getline(std::cin, dummy);

    std::vector<Instruction> instructions;
    bool hasCopy = false;
    std::vector<int> copyLignes;

    for (int i = 1; i <= n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "COPY") {
            hasCopy = true;
            copyLignes.push_back(i);
            std::string a, b;
            ss >> a >> b;
            instructions.push_back({i, type, a, b});
        } else if (type == "NEW" || type == "RESET" || type == "USE") {
            std::string a;
            ss >> a;
            instructions.push_back({i, type, a, ""});
        } else if (type == "MOVE") {
            std::string a, b;
            ss >> a >> b;
            instructions.push_back({i, type, a, b});
        }
    }

    if (hasCopy) {
        for (int l : copyLignes) {
            std::cout << "REFUSE " << l << "\n";
        }
        return 0;
    }

    std::vector<std::string> apparitionOrder;
    auto trackVar = [&](const std::string& v) {
        if (std::find(apparitionOrder.begin(), apparitionOrder.end(), v) == apparitionOrder.end()) {
            apparitionOrder.push_back(v);
        }
    };

    for (const auto& inst : instructions) {
        if (inst.type == "NEW" || inst.type == "RESET" || inst.type == "USE") {
            trackVar(inst.arg1);
        } else if (inst.type == "MOVE") {
            trackVar(inst.arg1);
            trackVar(inst.arg2);
        }
    }

    std::map<std::string, int> varObj;
    int creesCount = 0;
    int detruitsCount = 0;
    int nulsCount = 0;
    std::vector<std::string> output;

    auto detruireObjet = [&](int objId) {
        if (objId > 0) {
            detruitsCount++;
            output.push_back("DETRUIT " + std::to_string(objId));
        }
    };

    for (const auto& inst : instructions) {
        if (inst.type == "NEW") {
            creesCount++;
            int newObj = creesCount;
            if (varObj.count(inst.arg1) && varObj[inst.arg1] != 0) {
                detruireObjet(varObj[inst.arg1]);
            }
            varObj[inst.arg1] = newObj;
        } else if (inst.type == "MOVE") {
            int sourceObj = varObj.count(inst.arg1) ? varObj[inst.arg1] : 0;
            if (varObj.count(inst.arg2) && varObj[inst.arg2] != 0) {
                detruireObjet(varObj[inst.arg2]);
            }
            varObj[inst.arg2] = sourceObj;
            varObj[inst.arg1] = 0;
        } else if (inst.type == "RESET") {
            if (varObj.count(inst.arg1) && varObj[inst.arg1] != 0) {
                detruireObjet(varObj[inst.arg1]);
                varObj[inst.arg1] = 0;
            }
        } else if (inst.type == "USE") {
            int obj = varObj.count(inst.arg1) ? varObj[inst.arg1] : 0;
            if (obj == 0) {
                nulsCount++;
                output.push_back("NUL " + std::to_string(inst.ligne) + " " + inst.arg1);
            }
        }
    }

    for (auto it = apparitionOrder.rbegin(); it != apparitionOrder.rend(); ++it) {
        const std::string& v = *it;
        if (varObj.count(v) && varObj[v] != 0) {
            detruireObjet(varObj[v]);
            varObj[v] = 0;
        }
    }

    for (const auto& s : output) {
        std::cout << s << "\n";
    }

    std::cout << "CREES " << creesCount << "\n";
    std::cout << "DETRUITS " << detruitsCount << "\n";
    std::cout << "NULS " << nulsCount << "\n";

    return 0;
}

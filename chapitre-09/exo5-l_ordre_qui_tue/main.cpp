#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>

struct Dependency {
    std::string a;
    std::string b;
};

int main() {
    std::vector<std::vector<std::string>> scopes;
    scopes.push_back({});
    
    std::set<std::string> liberges;
    std::vector<Dependency> dependencies;
    std::vector<std::string> output;
    bool plantage = false;
    std::string plantageMsg = "";

    auto libererObjet = [&](const std::string& obj, bool isDestruction) {
        if (liberges.count(obj)) {
            return true;
        }
        for (const auto& dep : dependencies) {
            if (dep.a == obj) {
                if (!liberges.count(dep.b)) {
                    plantage = true;
                    plantageMsg = "PLANTAGE " + dep.a + " " + dep.b;
                    return false;
                }
            }
        }
        liberges.insert(obj);
        if (isDestruction) {
            output.push_back("DETRUIT " + obj);
        } else {
            output.push_back("FERME " + obj);
        }
        return true;
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        if (plantage) {
            continue;
        }

        if (line == "{") {
            scopes.push_back({});
        } else if (line == "}") {
            if (!scopes.empty()) {
                auto currentScope = scopes.back();
                scopes.pop_back();
                for (auto it = currentScope.rbegin(); it != currentScope.rend(); ++it) {
                    if (!libererObjet(*it, true)) {
                        break;
                    }
                }
            }
        } else {
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd;
            if (cmd == "DECL") {
                std::string obj;
                ss >> obj;
                if (!scopes.empty()) {
                    scopes.back().push_back(obj);
                }
            } else if (cmd == "DEPEND") {
                std::string a, b;
                ss >> a >> b;
                dependencies.push_back({a, b});
            } else if (cmd == "FERME") {
                std::string obj;
                ss >> obj;
                if (!liberges.count(obj)) {
                    if (!libererObjet(obj, false)) {
                        break;
                    }
                }
            }
        }
    }

    if (!plantage) {
        while (!scopes.empty()) {
            auto currentScope = scopes.back();
            scopes.pop_back();
            for (auto it = currentScope.rbegin(); it != currentScope.rend(); ++it) {
                if (!libererObjet(*it, true)) {
                    break;
                }
            }
            if (plantage) {
                break;
            }
        }
    }

    if (plantage) {
        std::cout << plantageMsg << "\n";
    } else {
        if (output.empty()) {
            std::cout << "PROPRE\n";
        } else {
            for (const auto& s : output) {
                std::cout << s << "\n";
            }
            std::cout << "PROPRE\n";
        }
    }

    return 0;
}
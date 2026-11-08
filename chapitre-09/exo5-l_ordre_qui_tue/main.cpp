#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

struct Dependency {
    std::string a;
    std::string b;
};

int main() {
    std::vector<std::vector<std::string>> scopes;
    scopes.push_back({});
    
    std::set<std::string> liberes;
    std::vector<Dependency> dependencies;
    std::vector<std::string> output;
    bool plantage = false;
    std::string plantageMsg = "";

    auto libererObjet = [&](const std::string& obj, bool isDestruction) {
        if (liberes.count(obj)) {
            return true;
        }
        for (const auto& dep : dependencies) {
            if (dep.a == obj) {
                if (liberes.count(dep.b)) {
                    plantage = true;
                    plantageMsg = "PLANTAGE " + dep.a + " " + dep.b;
                    return false;
                }
            }
        }
        liberes.insert(obj);
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
                    if (!liberes.count(*it)) {
                        if (!libererObjet(*it, true)) {
                            break;
                        }
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
                if (!liberes.count(obj)) {
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
                if (!liberes.count(*it)) {
                    if (!libererObjet(*it, true)) {
                        break;
                    }
                }
            }
            if (plantage) {
                break;
            }
        }
    }

    for (const auto& s : output) {
        std::cout << s << "\n";
    }

    if (plantage) {
        std::cout << plantageMsg << "\n";
    } else {
        std::cout << "PROPRE\n";
    }

    return 0;
}
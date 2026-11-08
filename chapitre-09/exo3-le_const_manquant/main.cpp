#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

struct Methode {
    std::string nom;
    bool dejaConst;
    int modifie;
    std::vector<std::string> appels;
};

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::string dummy;
    std::getline(std::cin, dummy);

    std::vector<Methode> methodes(n);
    std::map<std::string, int> indices;

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string declareStr;
        ss >> methodes[i].nom >> declareStr >> methodes[i].modifie;
        methodes[i].dejaConst = (declareStr == "const");
        
        int k;
        ss >> k;
        for (int j = 0; j < k; ++j) {
            std::string appel;
            ss >> appel;
            methodes[i].appels.push_back(appel);
        }
        indices[methodes[i].nom] = i;
    }

    std::map<std::string, bool> peutEtreConst;
    for (int i = 0; i < n; ++i) {
        if (methodes[i].dejaConst) {
            peutEtreConst[methodes[i].nom] = true;
        } else if (methodes[i].modifie == 1) {
            peutEtreConst[methodes[i].nom] = false;
        }
    }

    bool changement = true;
    while (changement) {
        changement = false;
        for (int i = 0; i < n; ++i) {
            if (methodes[i].dejaConst || methodes[i].modifie == 1) continue;
            if (peutEtreConst.find(methodes[i].nom) != peutEtreConst.end()) continue;

            bool ok = true;
            for (const auto& app : methodes[i].appels) {
                if (indices.find(app) == indices.end()) {
                    ok = false;
                    break;
                }
                int idxApp = indices[app];
                if (methodes[idxApp].modifie == 1) {
                    ok = false;
                    break;
                }
                if (!methodes[idxApp].dejaConst) {
                    if (peutEtreConst[app] == false) {
                        ok = false;
                        break;
                    }
                    if (peutEtreConst.find(app) ==peutEtreConst.end()) {
                        ok = false;
                    }
                }
            }
            if (ok) {
                peutEtreConst[methodes[i].nom] = true;
                changement = true;
            }
        }
    }

    std::vector<std::string> pourrait;
    for (int i = 0; i < n; ++i) {
        if (!methodes[i].dejaConst && peutEtreConst[methodes[i].nom] == true) {
            pourrait.push_back(methodes[i].nom);
        }
    }

    std::vector<std::string> racines;
    for (const auto& nom : pourrait) {
        int idx = indices[nom];
        bool toutesConst = true;
        for (const auto& app : methodes[idx].appels) {
            int idxApp = indices[app];
            if (!methodes[idxApp].dejaConst) {
                toutesConst = false;
                break;
            }
        }
        if (toutesConst) {
            racines.push_back(nom);
        }
    }

    int passes = 0;
    std::set<std::string> traite;
    for (const auto& m : methodes) {
        if (m.dejaConst) traite.insert(m.nom);
    }

    while (traite.size() < methodes.size()) {
        std::vector<std::string> aAjouter;
        for (int i = 0; i < n; ++i) {
            if (traite.count(methodes[i].nom)) continue;
            if (methodes[i].modifie == 1) continue;
            if (peutEtreConst[methodes[i].nom] != true) continue;

            bool appOk = true;
            for (const auto& app : methodes[i].appels) {
                if (!traite.count(app)) {
                    appOk = false;
                    break;
                }
            }
            if (appOk) {
                aAjouter.push_back(methodes[i].nom);
            }
        }

        if (aAjouter.empty()) break;
        for (const auto& nom : aAjouter) {
            traite.insert(nom);
        }
        passes++;
    }

    std::cout << "POURRAIT";
    if (pourrait.empty()) {
        std::cout << " AUCUN";
    } else {
        for (const auto& m : pourrait) {
            std::cout << " " << m;
        }
    }
    std::cout << "\n";

    std::cout << "RACINES";
    if (racines.empty()) {
        std::cout << " AUCUN";
    } else {
        for (const auto& m : racines) {
            std::cout << " " << m;
        }
    }
    std::cout << "\n";

    std::cout << "PASSES " << passes << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

enum Etat { ABSENT, ECRIT, DEFAUT, SUPPRIME };

std::string etatToString(Etat e) {
    switch (e) {
        case ECRIT: return "ECRIT";
        case DEFAUT: return "DEFAUT";
        case SUPPRIME: return "SUPPRIME";
        default: return "ABSENT";
    }
}

int main() {
    std::string className;
    if (!(std::cin >> className)) return 0;
    std::string line;
    std::getline(std::cin, line);

    Etat destructeur = ABSENT;
    Etat copie = ABSENT;
    Etat affectationCopie = ABSENT;
    Etat deplacement = ABSENT;
    Etat affectationDeplacement = ABSENT;

    while (std::getline(std::cin, line)) {
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        std::string cleanLine = "";
        for (char c : line) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                cleanLine += c;
            }
        }

        if (cleanLine.empty()) continue;

        Etat currentEtat = ECRIT;
        if (cleanLine.rfind("=delete;", cleanLine.length() - 8) != std::string::npos ||
            (cleanLine.length() >= 8 && cleanLine.substr(cleanLine.length() - 8) == "=delete;")) {
            currentEtat = SUPPRIME;
        } else if (cleanLine.length() >= 9 && cleanLine.substr(cleanLine.length() - 9) == "=default;") {
            currentEtat = DEFAUT;
        }

        std::string dSig = "~" + className + "(";
        std::string cSig = className + "(const" + className + "&";
        std::string acSig = className + "&operator=(const" + className + "&";
        std::string mSig = className + "(" + className + "&&";
        std::string amSig = className + "&operator=(" + className + "&&";

        if (cleanLine.find(dSig) != std::string::npos) {
            destructeur = currentEtat;
        } else if (cleanLine.rfind(cSig, 0) == 0) {
            size_t idx = cSig.length();
            if (idx < cleanLine.length() && cleanLine[idx] == '&') {
                continue;
            }
            copie = currentEtat;
        } else if (cleanLine.rfind(acSig, 0) == 0) {
            size_t idx = acSig.length();
            if (idx < cleanLine.length() && cleanLine[idx] == '&') {
                continue;
            }
            affectationCopie = currentEtat;
        } else if (cleanLine.rfind(mSig, 0) == 0) {
            deplacement = currentEtat;
        } else if (cleanLine.rfind(amSig, 0) == 0) {
            affectationDeplacement = currentEtat;
        }
    }

    std::cout << "DESTRUCTEUR " << etatToString(destructeur) << "\n";
    std::cout << "COPIE " << etatToString(copie) << "\n";
    std::cout << "AFFECTATION_COPIE " << etatToString(affectationCopie) << "\n";
    std::cout << "DEPLACEMENT " << etatToString(deplacement) << "\n";
    std::cout << "AFFECTATION_DEPLACEMENT " << etatToString(affectationDeplacement) << "\n";

    std::string regle = "INCOMPLETE";
    bool zeroDecl = (destructeur == ABSENT && copie == ABSENT && affectationCopie == ABSENT && deplacement == ABSENT && affectationDeplacement == ABSENT);
    bool cinqDecl = (destructeur != ABSENT && copie != ABSENT && affectationCopie != ABSENT && deplacement != ABSENT && affectationDeplacement != ABSENT);
    bool troisDecl = (destructeur != ABSENT && copie != ABSENT && affectationCopie != ABSENT && deplacement == ABSENT && affectationDeplacement == ABSENT);

    if (zeroDecl) {
        regle = "ZERO";
    } else if (cinqDecl) {
        regle = "CINQ";
    } else if (troisDecl) {
        regle = "TROIS";
    }

    std::cout << "REGLE " << regle << "\n";

    if (regle == "INCOMPLETE") {
        bool hasDepl = (deplacement != ABSENT || affectationDeplacement != ABSENT);
        std::vector<std::pair<std::string, Etat>> membres = {
            {"DESTRUCTEUR", destructeur},
            {"COPIE", copie},
            {"AFFECTATION_COPIE", affectationCopie},
            {"DEPLACEMENT", deplacement},
            {"AFFECTATION_DEPLACEMENT", affectationDeplacement}
        };
        int limit = hasDepl ? 5 : 3;
        for (int i = 0; i < limit; ++i) {
            if (membres[i].second == ABSENT) {
                std::cout << "MANQUE " << membres[i].first << "\n";
            }
        }
    }

    std::string possede = (destructeur == ECRIT) ? "OUI" : "NON";
    std::string unique = (copie == SUPPRIME && (deplacement == ECRIT || deplacement == DEFAUT || affectationDeplacement == ECRIT || affectationDeplacement == DEFAUT)) ? "OUI" : "NON";

    std::cout << "POSSEDE " << possede << "\n";
    std::cout << "UNIQUE " << unique << "\n";

    return 0;
}
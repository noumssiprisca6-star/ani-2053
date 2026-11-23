#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> pile_utilisateur;
    std::vector<int> traits_outil;

    int prochain_trait = 0;
    long long total_autres = 0;
    long long annulables_outil = 0;

    long long num_annule = 0;
    long long justes = 0;
    long long riens = 0;
    long long trahis = 0;

    std::string ligne;
    while (std::getline(std::cin, ligne)) {
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }
        if (ligne.empty()) {
            continue;
        }

        std::istringstream iss(ligne);
        std::string op;
        iss >> op;

        if (op == "TRAIT") {
            ++prochain_trait;
            ++total_autres;
            ++annulables_outil;
            pile_utilisateur.push_back("TRAIT " + std::to_string(prochain_trait));
            traits_outil.push_back(prochain_trait);
        } else if (op == "EFFACE") {
            ++total_autres;
            pile_utilisateur.push_back("EFFACE");
            traits_outil.clear();
        } else if (op == "RANGE") {
            ++total_autres;
            pile_utilisateur.push_back("RANGE");
        } else if (op == "DEPOSE" || op == "DEPLACE" || op == "SUPPRIME" || op == "MIROIR") {
            std::string nom;
            iss >> nom;
            ++total_autres;
            pile_utilisateur.push_back(op + " " + nom);
        } else if (op == "ANNULE") {
            ++num_annule;

            std::string x = "AUCUNE";
            if (!pile_utilisateur.empty()) {
                x = pile_utilisateur.back();
                pile_utilisateur.pop_back();
            }

            std::string y = "RIEN";
            if (!traits_outil.empty()) {
                int num_t = traits_outil.back();
                traits_outil.pop_back();
                y = "TRAIT " + std::to_string(num_t);
            }

            std::string verdict;
            if ((x == "AUCUNE" && y == "RIEN") || (x == y)) {
                verdict = "JUSTE";
                ++justes;
            } else if (y == "RIEN") {
                verdict = "RIEN";
                ++riens;
            } else {
                verdict = "TRAHI";
                ++trahis;
            }

            std::cout << "ANNULE " << num_annule
                      << " ATTENDU " << x
                      << " OBTENU " << y
                      << ' ' << verdict << '\n';
        }
    }

    std::cout << "JUSTES " << justes << '\n';
    std::cout << "RIENS " << riens << '\n';
    std::cout << "TRAHIS " << trahis << '\n';
    std::cout << "ANNULABLES " << annulables_outil << " SUR " << total_autres << '\n';

    return 0;
}
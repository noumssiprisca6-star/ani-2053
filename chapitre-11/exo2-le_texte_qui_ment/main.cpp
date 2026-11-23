#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct CommitState {
    std::string hash;
    std::unordered_set<std::string> fonctions;
};

static bool est_vraie(const std::unordered_set<std::string>& etat,
                       const std::string& etat_annonce,
                       const std::string& fonction) {
    bool presente = (etat.find(fonction) != etat.end());
    if (etat_annonce == "DISPONIBLE") {
        return presente;
    }
    return !presente;
}

int main() {
    int h = 0;
    if (!(std::cin >> h)) {
        return 0;
    }

    std::vector<CommitState> historique;
    historique.reserve(h);
    std::unordered_map<std::string, int> index_par_hash;
    index_par_hash.reserve(h);

    std::unordered_set<std::string> courantes;

    for (int i = 0; i < h; ++i) {
        std::string hash;
        std::string action;
        int k = 0;
        std::cin >> hash >> action >> k;

        for (int j = 0; j < k; ++j) {
            std::string fn;
            std::cin >> fn;
            if (action == "AJOUTE") {
                courantes.insert(fn);
            } else if (action == "RETIRE") {
                courantes.erase(fn);
            }
        }

        index_par_hash[hash] = i;
        historique.push_back({hash, courantes});
    }

    int a = 0;
    std::cin >> a;

    long long mensonges = 0;

    for (int i = 0; i < a; ++i) {
        std::string hash;
        std::string etat_annonce;
        std::string fonction;
        std::cin >> hash >> etat_annonce >> fonction;

        int idx_ecriture = index_par_hash[hash];
        int dernier = h - 1;

        if (est_vraie(historique[dernier].fonctions, etat_annonce, fonction)) {
            std::cout << "ANNONCE " << (i + 1) << " VRAI\n";
        } else {
            ++mensonges;
            int debut_mensonge = dernier;
            while (debut_mensonge > idx_ecriture &&
                   !est_vraie(historique[debut_mensonge - 1].fonctions, etat_annonce, fonction)) {
                --debut_mensonge;
            }
            std::cout << "ANNONCE " << (i + 1) << " MENT " << historique[debut_mensonge].hash << '\n';
        }
    }

    std::cout << "MENSONGES " << mensonges << '\n';

    return 0;
}
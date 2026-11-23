#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Entree {
    std::string nom;
    int valeur = 0;
    int cout = 0;
    std::string etiquette;
    std::string genre;
    std::string cible;
    int ordre = 0;
    bool exclue = false;
    std::string raison;
    std::string case_nom;
    int case_rang = 0;
};

static int rang_etiquette(const std::string& e) {
    if (e == "MESUREE") {
        return 0;
    }
    if (e == "OBSERVEE") {
        return 1;
    }
    return 2;
}

static void determiner_case(Entree& e) {
    bool val_forte = (e.valeur >= 3);
    bool cout_eleve = (e.cout >= 3);
    if (val_forte && !cout_eleve) {
        e.case_nom = "MAINTENANT";
        e.case_rang = 0;
    } else if (val_forte && cout_eleve) {
        e.case_nom = "DECOUPER";
        e.case_rang = 1;
    } else if (!val_forte && !cout_eleve) {
        e.case_nom = "EN_PASSANT";
        e.case_rang = 2;
    } else {
        e.case_nom = "ON_NE_LE_FAIT_PAS";
        e.case_rang = 3;
    }
}

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::string ligne;
    std::getline(std::cin, ligne);

    std::vector<Entree> entrees;
    entrees.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }
        if (ligne.empty()) {
            --i;
            continue;
        }

        std::istringstream iss(ligne);
        Entree e;
        iss >> e.nom >> e.valeur >> e.cout >> e.etiquette >> e.genre;
        if (e.genre == "SOCLE") {
            iss >> e.cible;
        }
        e.ordre = i;

        if (e.genre == "REECRITURE") {
            e.exclue = true;
            e.raison = "reecriture";
        } else if (e.genre == "CHOIX") {
            e.exclue = true;
            e.raison = "choix";
        } else if (e.etiquette == "-") {
            e.exclue = true;
            e.raison = "sans_etiquette";
        }

        entrees.push_back(e);
    }

    std::unordered_map<std::string, int> valeur_manque_garde;
    for (const Entree& e : entrees) {
        if (!e.exclue && e.genre == "MANQUE") {
            valeur_manque_garde[e.nom] = e.valeur;
        }
    }

    std::vector<Entree> gardees;
    std::vector<Entree> hors_liste;
    bool a_refus = false;

    for (Entree e : entrees) {
        if (e.exclue) {
            hors_liste.push_back(e);
            continue;
        }
        if (e.genre == "SOCLE") {
            auto it = valeur_manque_garde.find(e.cible);
            if (it != valeur_manque_garde.end() && it->second > e.valeur) {
                e.valeur = it->second;
            }
        }
        determiner_case(e);
        if (e.case_nom == "ON_NE_LE_FAIT_PAS") {
            a_refus = true;
        }
        gardees.push_back(e);
    }

    std::sort(gardees.begin(), gardees.end(), [](const Entree& a, const Entree& b) {
        if (a.case_rang != b.case_rang) {
            return a.case_rang < b.case_rang;
        }
        int ra = rang_etiquette(a.etiquette);
        int rb = rang_etiquette(b.etiquette);
        if (ra != rb) {
            return ra < rb;
        }
        if (a.valeur != b.valeur) {
            return a.valeur > b.valeur;
        }
        if (a.cout != b.cout) {
            return a.cout < b.cout;
        }
        return a.ordre < b.ordre;
    });

    for (const Entree& g : gardees) {
        std::cout << g.case_nom << ' ' << g.nom << ' ' << g.etiquette << '\n';
    }

    for (const Entree& h : hors_liste) {
        std::cout << "HORS_LISTE " << h.nom << ' ' << h.raison << '\n';
    }

    std::cout << "VERDICT " << (a_refus ? "HONNETE" : "COMPLAISANT") << '\n';

    return 0;
}
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Contournement {
    std::string nom;
    long long fois = 0;
    int premiere_sec = 0;
    int ordre_entree = 0;
    bool dit = false;
};

static int parse_mm_ss(const std::string& s) {
    size_t pos = s.find(':');
    int mm = std::stoi(s.substr(0, pos));
    int ss = std::stoi(s.substr(pos + 1));
    return mm * 60 + ss;
}

int main() {
    std::string tag;
    int n = 0;
    if (!(std::cin >> tag >> n)) {
        return 0;
    }

    std::vector<Contournement> items;
    std::unordered_map<std::string, size_t> index_par_nom;
    long long hors_seance = 0;
    int ordre = 0;

    for (int i = 0; i < n; ++i) {
        std::string temps_str;
        std::string nom;
        std::cin >> temps_str >> nom;
        int sec = parse_mm_ss(temps_str);

        if (sec > 20 * 60) {
            ++hors_seance;
            continue;
        }

        auto it = index_par_nom.find(nom);
        if (it == index_par_nom.end()) {
            Contournement c;
            c.nom = nom;
            c.fois = 1;
            c.premiere_sec = sec;
            c.ordre_entree = ordre++;
            index_par_nom[nom] = items.size();
            items.push_back(c);
        } else {
            Contournement& c = items[it->second];
            ++c.fois;
            if (sec < c.premiere_sec) {
                c.premiere_sec = sec;
            }
        }
    }

    int m = 0;
    std::cin >> tag >> m;
    std::vector<std::string> cites(m);
    std::unordered_set<std::string> set_cites;
    set_cites.reserve(m);

    for (int i = 0; i < m; ++i) {
        std::cin >> cites[i];
        set_cites.insert(cites[i]);
        auto it = index_par_nom.find(cites[i]);
        if (it != index_par_nom.end()) {
            items[it->second].dit = true;
        }
    }

    std::sort(items.begin(), items.end(), [](const Contournement& a, const Contournement& b) {
        if (a.fois != b.fois) {
            return a.fois > b.fois;
        }
        if (a.premiere_sec != b.premiere_sec) {
            return a.premiere_sec < b.premiere_sec;
        }
        return a.ordre_entree < b.ordre_entree;
    });

    long long non_dits = 0;
    long long somme_fois_non_dits = 0;
    long long somme_fois_total = 0;

    for (const Contournement& c : items) {
        std::cout << c.nom << ' ' << c.fois << ' ' << (c.dit ? "DIT" : "NON_DIT") << '\n';
        somme_fois_total += c.fois;
        if (!c.dit) {
            ++non_dits;
            somme_fois_non_dits += c.fois;
        }
    }

    long long part_non_dite = (somme_fois_total == 0)
                                ? 0
                                : (100 * somme_fois_non_dits) / somme_fois_total;

    std::vector<std::string> dit_sans_vu;
    for (const std::string& nom : cites) {
        if (index_par_nom.find(nom) == index_par_nom.end()) {
            dit_sans_vu.push_back(nom);
        }
    }

    std::cout << "NON_DITS " << non_dits << '\n';
    std::cout << "PART_NON_DITE " << part_non_dite << '\n';
    std::cout << "DIT_SANS_VU";
    if (dit_sans_vu.empty()) {
        std::cout << " AUCUN\n";
    } else {
        for (const std::string& nom : dit_sans_vu) {
            std::cout << ' ' << nom;
        }
        std::cout << '\n';
    }
    std::cout << "HORS_SEANCE " << hors_seance << '\n';

    return 0;
}
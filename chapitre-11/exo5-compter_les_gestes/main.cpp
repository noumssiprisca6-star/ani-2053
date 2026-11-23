#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct TacheActive {
    std::string nom;
    long long t_debut = 0;
    long long min_gestes = 0;
    long long par_jour = 0;
    long long gestes = 0;
    long long attente = 0;
};

static std::string formater_duree_mm_ss(long long total_secondes) {
    long long minutes = total_secondes / 60;
    long long secondes = total_secondes % 60;
    std::string ss = (secondes < 10 ? "0" : "") + std::to_string(secondes);
    return std::to_string(minutes) + ":" + ss;
}

int main() {
    bool en_cours = false;
    TacheActive courante;

    std::vector<std::string> lignes_terminees;
    long long total_secondes_jour = 0;

    std::string ligne;
    while (std::getline(std::cin, ligne)) {
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }
        if (ligne.empty()) {
            continue;
        }

        std::istringstream iss(ligne);
        long long t = 0;
        std::string action;
        if (!(iss >> t >> action)) {
            continue;
        }

        if (action == "DEBUT") {
            std::string nom;
            long long min_g = 0;
            long long par_j = 0;
            iss >> nom >> min_g >> par_j;
            en_cours = true;
            courante = TacheActive{nom, t, min_g, par_j, 0, 0};
        } else if (action == "FIN") {
            std::string nom;
            iss >> nom;
            if (en_cours) {
                long long en_trop = (courante.gestes > courante.min_gestes)
                                        ? (courante.gestes - courante.min_gestes)
                                        : 0;
                long long duree = t - courante.t_debut;
                long long sec_jour = static_cast<long long>(
                    (static_cast<__int128>(courante.attente) * courante.par_jour) / 1000);
                total_secondes_jour += sec_jour;

                std::string res = courante.nom +
                                  " GESTES " + std::to_string(courante.gestes) +
                                  " EN_TROP " + std::to_string(en_trop) +
                                  " DUREE " + std::to_string(duree) +
                                  " ATTENTE " + std::to_string(courante.attente) +
                                  " JOUR " + formater_duree_mm_ss(sec_jour);
                lignes_terminees.push_back(res);
                en_cours = false;
            }
        } else if (action == "CLIC" || action == "TOUCHE" || action == "MOLETTE" || action == "GLISSE") {
            if (en_cours) {
                ++courante.gestes;
            }
        } else if (action == "ATTENTE") {
            long long d = 0;
            iss >> d;
            if (en_cours) {
                courante.attente += d;
            }
        }
    }

    for (const std::string& l : lignes_terminees) {
        std::cout << l << '\n';
    }

    if (en_cours) {
        std::cout << courante.nom << " INACHEVEE\n";
    }

    std::cout << "TOTAL_JOUR " << formater_duree_mm_ss(total_secondes_jour) << '\n';

    return 0;
}
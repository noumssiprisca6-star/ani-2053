#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct ImageItem {
    std::string nom;
    double x, y;
    double largeur, hauteur;
    double echelle;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<ImageItem> images(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> images[i].nom >> images[i].x >> images[i].y
                 >> images[i].largeur >> images[i].hauteur >> images[i].echelle;
    }

    int q;
    if (!(std::cin >> q)) return 0;

    int erreurs = 0;

    for (int k = 1; k <= q; ++k) {
        double px, py;
        std::cin >> px >> py;

        std::string a = "AUCUN";
        std::string b = "AUCUN";

        // Recherche à rebours (de la dernière à la première) pour A
        for (int i = n - 1; i >= 0; --i) {
            double demiW = images[i].largeur * images[i].echelle * 0.5;
            double demiH = images[i].hauteur * images[i].echelle * 0.5;
            if (std::abs(px - images[i].x) <= demiW && std::abs(py - images[i].y) <= demiH) {
                a = images[i].nom;
                break;
            }
        }

        // Recherche à l'endroit (de la première à la dernière) pour B
        for (int i = 0; i < n; ++i) {
            double demiW = images[i].largeur * images[i].echelle * 0.5;
            double demiH = images[i].hauteur * images[i].echelle * 0.5;
            if (std::abs(px - images[i].x) <= demiW && std::abs(py - images[i].y) <= demiH) {
                b = images[i].nom;
                break;
            }
        }

        std::cout << "CLIC " << k << " " << a << " " << b << "\n";

        if (a != b) {
            erreurs++;
        }
    }

    std::cout << "ERREURS " << erreurs << "\n";

    return 0;
}
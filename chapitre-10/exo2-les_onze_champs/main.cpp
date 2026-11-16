#include <iostream>
#include <string>
#include <vector>

struct ImageRecord {
    long long id;
    double x, y;
    double echelle, rotation, opacite;
    int miroirX, miroirY;
    long long largeur, hauteur;
    int selected;
    std::string chemin;
    long long octets;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<ImageRecord> original(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> original[i].id >> original[i].x >> original[i].y
                 >> original[i].echelle >> original[i].rotation >> original[i].opacite
                 >> original[i].miroirX >> original[i].miroirY
                 >> original[i].largeur >> original[i].hauteur
                 >> original[i].selected >> original[i].chemin >> original[i].octets;
    }

    int restentCount = 0;
    int changesCount = 0;
    int j = 1;

    for (int i = 0; i < n; ++i) {
        int k = i + 1;
        if (original[i].octets == 0) {
            std::cout << "ITEM " << k << " SAUTE\n";
            continue;
        }

        std::cout << "ITEM " << k << " " << j;
        std::string changesList = "";
        int localChanges = 0;

        if (original[i].id != 0) {
            changesList += " id";
            localChanges++;
        }
        if (original[i].selected == 1) {
            changesList += " selected";
            localChanges++;
        }
        if (original[i].chemin != "-") {
            changesList += " sourcePath";
            localChanges++;
        }

        if (localChanges == 0) {
            std::cout << " AUCUN";
        } else {
            std::cout << changesList;
        }
        std::cout << "\n";

        restentCount++;
        changesCount += localChanges;
        j++;
    }

    std::cout << "RESTENT " << restentCount << "\n";
    std::cout << "CHANGES " << changesCount << "\n";

    return 0;
}
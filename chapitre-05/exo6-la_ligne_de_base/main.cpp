#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Glyphe {
    char c;
    long long avance;
    long long x0, y0, x1, y1;
    bool existe;
};

struct Crenage {
    char c1;
    char c2;
    long long k;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int G = 0;
    if (!(std::cin >> G)) {
        return 0;
    }

    std::vector<Glyphe> tableGlyphes;
    for (int i = 0; i < G; ++i) {
        char c;
        long long avance, x0, y0, x1, y1;
        std::cin >> c >> avance >> x0 >> y0 >> x1 >> y1;
        tableGlyphes.push_back({c, avance, x0, y0, x1, y1, true});
    }

    int K = 0;
    if (!(std::cin >> K)) {
        return 0;
    }

    std::vector<Crenage> tableCrenages;
    for (int i = 0; i < K; ++i) {
        std::string couple;
        long long k;
        std::cin >> couple >> k;
        tableCrenages.push_back({couple[0], couple[1], k});
    }

    std::string texte;
    long long ox = 0, oy = 0;
    if (!(std::cin >> texte >> ox >> oy)) {
        return 0;
    }

    long long x = ox;
    long long minx = 2e18, miny = 2e18;
    long long maxx = -2e18, maxy = -2e18;
    bool dessineAuMoinsUn = false;
    int absents = 0;

    for (size_t i = 0; i < texte.length(); ++i) {
        char courant = texte[i];
        
        Glyphe* gCourant = nullptr;
        for (auto& gl : tableGlyphes) {
            if (gl.c == courant) {
                gCourant = &gl;
                break;
            }
        }

        if (gCourant == nullptr) {
            std::cout << courant << " ABSENT\n";
            absents++;
            continue;
        }

        std::cout << courant << " " << x << "\n";

        if (gCourant->x1 > gCourant->x0 && gCourant->y1 > gCourant->y0) {
            long long rx0 = x + gCourant->x0;
            long long ry0 = oy + gCourant->y0;
            long long rx1 = x + gCourant->x1;
            long long ry1 = oy + gCourant->y1;

            if (!dessineAuMoinsUn) {
                minx = rx0;
                miny = ry0;
                maxx = rx1;
                maxy = ry1;
                dessineAuMoinsUn = true;
            } else {
                minx = std::min(minx, rx0);
                miny = std::min(miny, ry0);
                maxx = std::max(maxx, rx1);
                maxy = std::max(maxy, ry1);
            }
        }

        x += gCourant->avance;

        if (i + 1 < texte.length()) {
            char suivant = texte[i + 1];
            for (const auto& cr : tableCrenages) {
                if (cr.c1 == courant && cr.c2 == suivant) {
                    x += cr.k;
                    break;
                }
            }
        }
    }

    std::cout << "CURSEUR " << x << "\n";

    if (!dessineAuMoinsUn) {
        std::cout << "BOITE AUCUNE\n";
        std::cout << "MONTE 0\n";
        std::cout << "DESCEND 0\n";
        std::cout << "ECRAN RIEN\n";
    } else {
        std::cout << "BOITE " << minx << " " << miny << " " << maxx << " " << maxy << "\n";

        long long monte = (miny < oy) ? (oy - miny) : 0;
        long long descend = (maxy > oy) ? (maxy - oy) : 0;

        std::cout << "MONTE " << monte << "\n";
        std::cout << "DESCEND " << descend << "\n";

        std::string ecran = "VISIBLE";
        if (maxy <= 0) {
            ecran = "HORS";
        } else if (miny < 0) {
            ecran = "COUPE";
        }
        std::cout << "ECRAN " << ecran << "\n";
    }

    std::cout << "ABSENTS " << absents << "\n";

    return 0;
}


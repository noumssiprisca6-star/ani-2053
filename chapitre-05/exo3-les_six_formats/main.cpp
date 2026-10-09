#include <iostream>
#include <string>

struct Format {
    std::string nom;
    long long octetsParPixel;
    bool couleur;
    bool transparence;
    bool flottant;
};

const Format TABLE_FORMATS[] = {
    {"GRAY8",    1,  false, false, false},
    {"GRAY_A16", 2,  false, true,  false},
    {"RGB24",    3,  true,  false, false},
    {"RGBA32",   4,  true,  true,  false},
    {"RGB96F",   12, true,  false, true},
    {"RGBA128F", 16, true,  true,  true}
};

bool trouverFormat(const std::string& nom, Format& resultat) {
    for (int i = 0; i < 6; ++i) {
        if (TABLE_FORMATS[i].nom == nom) {
            resultat = TABLE_FORMATS[i];
            return true;
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long w = 0, h = 0;
    int n = 0;

    if (!(std::cin >> w >> h >> n)) {
        return 0;
    }

    long long totalOctetsCible = 0;
    long long compteurSansPerte = 0;
    long long compteurRefuses = 0;

    for (int i = 0; i < n; ++i) {
        std::string nomSource, nomCible;
        std::cin >> nomSource >> nomCible;

        Format fmtSource, fmtCible;
        bool sourceOk = trouverFormat(nomSource, fmtSource);
        bool cibleOk = trouverFormat(nomCible, fmtCible);

        if (!sourceOk || !cibleOk) {
            std::cout << nomSource << " " << nomCible << " REFUSE\n";
            compteurRefuses++;
            continue;
        }

        long long octetsSource = w * h * fmtSource.octetsParPixel;
        long long octetsCible = w * h * fmtCible.octetsParPixel;

        std::string pertes = "";

        if (fmtSource.transparence && !fmtCible.transparence) {
            pertes += "TRANSPARENCE";
        }

        if (fmtSource.couleur && !fmtCible.couleur) {
            if (!pertes.empty()) {
                pertes += "+";
            }
            pertes += "COULEUR";
        }

        if (fmtSource.flottant && !fmtCible.flottant) {
            if (!pertes.empty()) {
                pertes += "+";
            }
            pertes += "ETENDUE";
        }

        if (pertes.empty()) {
            pertes = "AUCUNE";
            compteurSansPerte++;
        }

        totalOctetsCible += octetsCible;

        std::cout << nomSource << " " << nomCible << " " << octetsSource << " " << octetsCible << " " << pertes << "\n";
    }

    std::cout << "TOTAL " << totalOctetsCible << "\n";
    std::cout << "SANS_PERTE " << compteurSansPerte << "\n";
    std::cout << "REFUSES " << compteurRefuses << "\n";

    return 0;
}

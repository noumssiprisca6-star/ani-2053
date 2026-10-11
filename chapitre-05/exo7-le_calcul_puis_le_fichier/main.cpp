#include <iostream>
#include <string>
#include <vector>

struct Son {
    std::string nom;
    long long frequence;
    long long canaux;
    long long bits;
    long long duree;
    long long fichier;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long S = 0;
    if (!(std::cin >> S)) {
        return 0;
    }

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::vector<Son> sons(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> sons[i].nom >> sons[i].frequence >> sons[i].canaux 
                 >> sons[i].bits >> sons[i].duree >> sons[i].fichier;
    }

    long long totalMemoireOctets = 0;
    long long compteFlux = 0;
    long long compteRefuses = 0;

    for (int i = 0; i < N; ++i) {
        if (sons[i].bits != 8 && sons[i].bits != 16 && sons[i].bits != 24 && sons[i].bits != 32) {
            std::cout << sons[i].nom << " REFUSE\n";
            compteRefuses++;
            continue;
        }

        long long brut = (sons[i].frequence * sons[i].canaux * (sons[i].bits / 8) * sons[i].duree) / 1000;
        long long pourcent = (sons[i].fichier * 100) / brut;

        if (brut > S) {
            std::cout << sons[i].nom << " " << brut << " " << pourcent << " FLUX\n";
            compteFlux++;
        } else {
            std::cout << sons[i].nom << " " << brut << " " << pourcent << " MEMOIRE\n";
            totalMemoireOctets += brut;
        }
    }

    std::cout << "MEMOIRE " << totalMemoireOctets << "\n";
    std::cout << "FLUX " << compteFlux << "\n";
    std::cout << "REFUSES " << compteRefuses << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long D = 0, C = 0;
    if (!(std::cin >> D >> C)) {
        return 0;
    }

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::vector<long long> t(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> t[i];
    }

    if (N == 0) {
        std::cout << "VOIX_MAX 0\n";
        std::cout << "RETARD_MAX 0\n";
        std::cout << "COUPES 0\n";
        return 0;
    }

    std::vector<long long> voix(N);
    for (int i = 0; i < N; ++i) {
        long long count = 0;
        for (int j = 0; j <= i; ++j) {
            if (t[j] + D > t[i]) {
                count++;
            }
        }
        voix[i] = count;
    }

    std::vector<long long> retard(N);
    long long finPrecedente = 0;
    for (int i = 0; i < N; ++i) {
        long long debutChargement = std::max(t[i], finPrecedente);
        long long finChargement = debutChargement + C;
        retard[i] = finChargement - t[i];
        finPrecedente = finChargement;
    }

    std::vector<std::string> etat(N);
    for (int i = 0; i < N; ++i) {
        if (i + 1 < N && t[i + 1] < t[i] + D) {
            etat[i] = "COUPE";
        } else {
            etat[i] = "ENTIER";
        }
    }

    long long voixMax = 0;
    long long retardMax = 0;
    long long coupesCount = 0;

    for (int i = 0; i < N; ++i) {
        std::cout << t[i] << " " << voix[i] << " " << retard[i] << " " << etat[i] << "\n";

        if (voix[i] > voixMax) {
            voixMax = voix[i];
        }
        if (retard[i] > retardMax) {
            retardMax = retard[i];
        }
        if (etat[i] == "COUPE") {
            coupesCount++;
        }
    }

    std::cout << "VOIX_MAX " << voixMax << "\n";
    std::cout << "RETARD_MAX " << retardMax << "\n";
    std::cout << "COUPES " << coupesCount << "\n";

    return 0;
}
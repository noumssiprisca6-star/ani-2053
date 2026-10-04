#include <iostream>

int main() {
    int C, R, W, H, F, D, P;
    if (!(std::cin >> C >> R >> W >> H >> F >> D >> P)) {
        return 0;
    }

    int N;
    if (!(std::cin >> N)) {
        return 0;
    }

    int caseActuelle = 0;
    int tempsAccumule = 0;
    int totalAvances = 0;
    int totalPlafonnes = 0;

    for (int i = 0; i < N; ++i) {
        int dt;
        std::cin >> dt;

        if (dt > P) {
            dt = P;
            totalPlafonnes++;
        }

        tempsAccumule += dt;

        while (tempsAccumule >= D) {
            tempsAccumule -= D;
            caseActuelle = (caseActuelle + 1) % F;
            totalAvances++;
        }

        int col = caseActuelle % C;
        int lig = caseActuelle / C;
        int x = col * W;
        int y = lig * H;

        std::cout << caseActuelle << " " << x << " " << y << " " << W << " " << H << "\n";
    }

    std::cout << "AVANCES " << totalAvances << "\n";
    std::cout << "PLAFONNES " << totalPlafonnes << "\n";

    return 0;
}

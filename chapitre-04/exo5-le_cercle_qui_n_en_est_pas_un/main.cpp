#include <iostream>
#include <cmath>

int main() {
    int N;
    if (!(std::cin >> N)) {
        std::cout << "VISIBLES 0\n";
        std::cout << "REFUSES 0\n";
        return 0;
    }

    const double PI = 3.141592653589793;
    int visibles = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i) {
        int r, n;
        std::cin >> r >> n;

        if (n < 3) {
            std::cout << r << " " << n << " REFUSE\n";
            refuses++;
            continue;
        }

        double g = r * (1.0 - std::cos(PI / n));
        int ecart = std::floor(g * 1000.0);

        if (r == 0 || g == 0.0) {
            std::cout << r << " " << n << " " << ecart << " JAMAIS\n";
        } else {
            int zoom = std::ceil(100.0 / g);
            if (zoom <= 100) {
                std::cout << r << " " << n << " " << ecart << " " << zoom << " VISIBLE\n";
                visibles++;
            } else {
                std::cout << r << " " << n << " " << ecart << " " << zoom << " INVISIBLE\n";
            }
        }
    }

    std::cout << "VISIBLES " << visibles << "\n";
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}


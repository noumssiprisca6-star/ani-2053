#include <iostream>
#include <string>
#include <algorithm>

int main() {

    int N;
    if (!(std::cin >> N)) {
        std::cout << "REFUSES 0\n";
        return 0;
    }

    int refuses = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom;
        int w, h, px, py, ox, oy, sx, sy, angle;
        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        int mod_angle = angle % 360;
        if (mod_angle < 0) {
            mod_angle += 360;
        }

        if (mod_angle % 90 != 0) {
            std::cout << nom << " ANGLE REFUSE\n";
            refuses++;
            continue;
        }

        int c = 0;
        int s = 0;

        if (mod_angle == 0) {
            c = 1;
            s = 0;
        } else if (mod_angle == 90) {
            c = 0;
            s = 1;
        } else if (mod_angle == 180) {
            c = -1;
            s = 0;
        } else if (mod_angle == 270) {
            c = 0;
            s = -1;
        }

        int lx[4] = {0, w, w, 0};
        int ly[4] = {0, 0, h, h};

        int wx[4];
        int wy[4];

        for (int j = 0; j < 4; ++j) {
            int ax = (lx[j] - ox) * sx;
            int ay = (ly[j] - oy) * sy;

            int rx = ax * c - ay * s;
            int ry = ax * s + ay * c;

            wx[j] = px + rx;
            wy[j] = py + ry;
        }

        int minx = std::min({wx[0], wx[1], wx[2], wx[3]});
        int maxx = std::max({wx[0], wx[1], wx[2], wx[3]});
        int miny = std::min({wy[0], wy[1], wy[2], wy[3]});
        int maxy = std::max({wy[0], wy[1], wy[2], wy[3]});

        std::cout << nom << " COINS " << wx[0] << " " << wy[0] << " " << wx[1] << " " << wy[1] << " " << wx[2] << " " << wy[2] << " " << wx[3] << " " << wy[3] << "\n";

        std::cout << nom << " BOITE " << minx << " " << miny << " " << maxx << " " << maxy << "\n";
    }

    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

double formatCoord(double val) {
    if (std::abs(val) < 0.005) {
        return 0.0;
    }
    return val;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double W, H;
    if (!(std::cin >> W >> H)) return 0;

    double cx = 0.0;
    double cy = 0.0;
    double zoom = 1.0;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "VERS_MONDE") {
            double px, py;
            std::cin >> px >> py;
            double x = cx + (px - W * 0.5) / zoom;
            double y = cy + (py - H * 0.5) / zoom;
            std::cout << "MONDE " << std::fixed << std::setprecision(2) 
                      << formatCoord(x) << " " << formatCoord(y) << "\n";
        }
        else if (cmd == "VERS_PIXEL") {
            double mx, my;
            std::cin >> mx >> my;
            double x = (mx - cx) * zoom + W * 0.5;
            double y = (my - cy) * zoom + H * 0.5;
            std::cout << "PIXEL " << std::fixed << std::setprecision(2) 
                      << formatCoord(x) << " " << formatCoord(y) << "\n";
        }
        else if (cmd == "DEPLACE") {
            double dx, dy;
            std::cin >> dx >> dy;
            cx = cx - dx / zoom;
            cy = cy - dy / zoom;
        }
        else if (cmd == "ZOOM") {
            double f, px, py;
            std::cin >> f >> px >> py;
            double ax = cx + (px - W * 0.5) / zoom;
            double ay = cy + (py - H * 0.5) / zoom;
            zoom = zoom * f;
            if (zoom < 0.02) zoom = 0.02;
            if (zoom > 64.0) zoom = 64.0;
            cx = ax - (px - W * 0.5) / zoom;
            cy = ay - (py - H * 0.5) / zoom;
        }
        else if (cmd == "GRILLE") {
            double m;
            std::cin >> m;
            double s = 1.0;
            while (s * zoom < m) {
                s *= 2.0;
            }
            while (s * 0.5 * zoom >= m) {
                s *= 0.5;
            }
            std::cout << "GRILLE " << std::fixed << std::setprecision(6) << s << "\n";
        }
        else if (cmd == "ORIGINE") {
            cx = 0.0;
            cy = 0.0;
            zoom = 1.0;
        }
    }

    std::cout << "CENTRE " << std::fixed << std::setprecision(2) 
              << formatCoord(cx) << " " << formatCoord(cy) << "\n";
    std::cout << "ZOOM " << std::fixed << std::setprecision(2) << zoom << "\n";

    return 0;
}
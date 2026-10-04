#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Objet {
    std::string nom;
    int x;
    int y;
    int angle;
    int echelle;
    int niveau;
};

int main() {
    int N;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::vector<Objet> objets;
    std::map<std::string, int> indexMap;
    int maxProfondeur = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom, parent;
        int tx, ty, anglePropre, echellePropre;
        std::cin >> nom >> parent >> tx >> ty >> anglePropre >> echellePropre;

        Objet obj;
        obj.nom = nom;

        if (parent == "-") {
            obj.x = tx;
            obj.y = ty;

            int a = anglePropre % 360;
            if (a < 0) a += 360;
            obj.angle = a;

            obj.echelle = echellePropre;
            obj.niveau = 1;
        } else {
            int pIdx = indexMap[parent];
            const Objet& p = objets[pIdx];

            int ax = tx * p.echelle;
            int ay = ty * p.echelle;

            int c = 1, s = 0;
            if (p.angle == 90) { c = 0; s = 1; }
            else if (p.angle == 180) { c = -1; s = 0; }
            else if (p.angle == 270) { c = 0; s = -1; }

            int rx = ax * c - ay * s;
            int ry = ax * s + ay * c;

            obj.x = p.x + rx;
            obj.y = p.y + ry;

            int a = (p.angle + anglePropre) % 360;
            if (a < 0) a += 360;
            obj.angle = a;

            obj.echelle = p.echelle * echellePropre;
            obj.niveau = p.niveau + 1;
        }

        if (obj.niveau > maxProfondeur) {
            maxProfondeur = obj.niveau;
        }

        objets.push_back(obj);
        indexMap[nom] = i;

        std::cout << obj.nom << " " << obj.x << " " << obj.y << " " << obj.angle << " " << obj.echelle << "\n";
    }

    std::cout << "PROFONDEUR " << maxProfondeur << "\n";

    return 0;
}


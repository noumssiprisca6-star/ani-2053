#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct TextureInfo {
    int id;
    int libérations = 0;
    bool estSupprimée = false;
};

int main() {
    int s, v, f;
    if (!(std::cin >> s >> v >> f)) {
        return 0;
    }

    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<TextureInfo> textures;
    int totalCreées = 0;
    int plantageOp = -1;
    int texturePlantage = -1;
    bool plantageFin = false;

    auto libererTexture = [&](int &libCompteur, int idTex, int opIdx, bool estFin) {
        libCompteur++;
        if (libCompteur > 1) {
            plantageOp = opIdx;
            texturePlantage = idTex;
            plantageFin = estFin;
            return false;
        }
        return true;
    };

    for (int i = 1; i <= n; ++i) {
        std::string op;
        std::cin >> op;

        if (plantageOp != -1) {
            continue;
        }

        if (op == "AJOUTE") {
            totalCreées++;
            textures.push_back({totalCreées, 0, false});
        } else if (op == "SUPPRIME") {
            int idx;
            std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int>(textures.size())) {
                for (int k = 0; k < s; ++k) {
                    if (!libererTexture(textures[idx].libérations, textures[idx].id, i, false)) {
                        break;
                    }
                }
                textures.erase(textures.begin() + idx);
            }
        } else if (op == "VIDE") {
            for (auto &t : textures) {
                for (int k = 0; k < v; ++k) {
                    if (!libererTexture(t.libérations, t.id, i, false)) {
                        break;
                    }
                }
                if (plantageOp != -1) {
                    break;
                }
            }
            textures.clear();
        }
    }

    if (plantageOp != -1) {
        if (plantageFin) {
            std::cout << "PLANTAGE FIN TEXTURE " << texturePlantage << "\n";
        } else {
            std::cout << "PLANTAGE " << plantageOp << " TEXTURE " << texturePlantage << "\n";
        }
        return 0;
    }

    for (auto &t : textures) {
        for (int k = 0; k < f; ++k) {
            if (!libererTexture(t.libérations, t.id, -1, true)) {
                break;
            }
        }
        if (plantageOp != -1) {
            break;
        }
    }

    if (plantageOp != -1) {
        if (plantageFin) {
            std::cout << "PLANTAGE FIN TEXTURE " << texturePlantage << "\n";
        } else {
            std::cout << "PLANTAGE " << plantageOp << " TEXTURE " << texturePlantage << "\n";
        }
        return 0;
    }

    std::cout << "CREEES " << totalCreées << "\n";

    int fuites = 0;
    std::vector<int> perdues;
    
   
    
    return 0;
}
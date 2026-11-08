#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Texture {
    int id;
    int liberations = 0;
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

    std::vector<Texture> textures;
    std::vector<Texture> toutesTextures;
    int totalCrees = 0;
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
            totalCrees++;
            Texture t{totalCrees, 0};
            textures.push_back(t);
            toutesTextures.push_back(t);
        } else if (op == "SUPPRIME") {
            int idx;
            std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int>(textures.size())) {
                int idTex = textures[idx].id;
                for (auto &t : toutesTextures) {
                    if (t.id == idTex) {
                        for (int k = 0; k < s; ++k) {
                            if (!libererTexture(t.liberations, t.id, i, false)) {
                                break;
                            }
                        }
                        break;
                    }
                }
                textures.erase(textures.begin() + idx);
            }
        } else if (op == "VIDE") {
            for (auto &tex : textures) {
                int idTex = tex.id;
                for (auto &t : toutesTextures) {
                    if (t.id == idTex) {
                        for (int k = 0; k < v; ++k) {
                            if (!libererTexture(t.liberations, t.id, i, false)) {
                                break;
                            }
                        }
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

    for (auto &tex : textures) {
        int idTex = tex.id;
        for (auto &t : toutesTextures) {
            if (t.id == idTex) {
                for (int k = 0; k < f; ++k) {
                    if (!libererTexture(t.liberations, t.id, -1, true)) {
                        break;
                    }
                }
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

    std::cout << "CREEES " << totalCrees << "\n";

    int fuites = 0;
    std::vector<int> perdues;

    for (const auto &t : toutesTextures) {
        if (t.liberations == 0) {
            fuites++;
            perdues.push_back(t.id);
        }
    }

    std::cout << "FUITES " << fuites << "\n";
    std::cout << "PERDUES";
    if (perdues.empty()) {
        std::cout << " AUCUN\n";
    } else {
        for (int id : perdues) {
            std::cout << " " << id;
        }
        std::cout << "\n";
    }

    return 0;
}
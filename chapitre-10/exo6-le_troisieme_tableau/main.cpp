#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

bool contains(const std::string& line, const std::string& target) {
    return line.find(target) != std::string::npos;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string lineAdd, lineDel, lineSwap;
    if (!std::getline(std::cin, lineAdd)) return 0;
    if (!std::getline(std::cin, lineDel)) return 0;
    if (!std::getline(std::cin, lineSwap)) return 0;

    bool addTex = contains(lineAdd, "textures");
    bool addSrc = contains(lineAdd, "sources");
    bool delTex = contains(lineDel, "textures");
    bool delSrc = contains(lineDel, "sources");
    bool swapTex = contains(lineSwap, "textures");
    bool swapSrc = contains(lineSwap, "sources");

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<std::string> modele;
    std::vector<std::string> textures;
    std::vector<std::string> sources;

    for (int i = 0; i < n; ++i) {
        std::string op;
        std::cin >> op;
        if (op == "AJOUTE") {
            std::string nom;
            std::cin >> nom;
            modele.push_back(nom);
            if (addTex) textures.push_back(nom);
            if (addSrc) sources.push_back(nom);
        } else if (op == "SUPPRIME") {
            int c;
            std::cin >> c;
            std::vector<int> idx(c);
            for (int j = 0; j < c; ++j) {
                std::cin >> idx[j];
            }
            std::sort(idx.rbegin(), idx.rend());

            for (int index : idx) {
                if (index >= 0 && index < (int)modele.size()) {
                    modele.erase(modele.begin() + index);
                }
                if (delTex && index >= 0 && index < (int)textures.size()) {
                    textures.erase(textures.begin() + index);
                }
                if (delSrc && index >= 0 && index < (int)sources.size()) {
                    sources.erase(sources.begin() + index);
                }
            }
        } else if (op == "MONTE") {
            int index;
            std::cin >> index;
            if (index >= 0 && index + 1 < (int)modele.size()) {
                std::swap(modele[index], modele[index + 1]);
                if (swapTex && index + 1 < (int)textures.size()) {
                    std::swap(textures[index], textures[index + 1]);
                }
                if (swapSrc && index + 1 < (int)sources.size()) {
                    std::swap(sources[index], sources[index + 1]);
                }
            }
        } else if (op == "DESCEND") {
            int index;
            std::cin >> index;
            if (index > 0 && index < (int)modele.size()) {
                std::swap(modele[index], modele[index - 1]);
                if (swapTex && index < (int)textures.size()) {
                    std::swap(textures[index], textures[index - 1]);
                }
                if (swapSrc && index < (int)sources.size()) {
                    std::swap(sources[index], sources[index - 1]);
                }
            }
        }
    }

    size_t L = modele.size();
    if (textures.size() > L) L = textures.size();
    if (sources.size() > L) L = sources.size();

    int decalés = 0;
    for (size_t i = 0; i < L; ++i) {
        std::string m = (i < modele.size()) ? modele[i] : "-";
        std::string t = (i < textures.size()) ? textures[i] : "-";
        std::string s = (i < sources.size()) ? sources[i] : "-";

        std::cout << i << " " << m << " " << t << " " << s << "\n";

        if (m == "-" || t == "-" || s == "-" || m != t || m != s) {
            decalés++;
        }
    }

    std::cout << "DECALES " << decalés << "\n";

    return 0;
}
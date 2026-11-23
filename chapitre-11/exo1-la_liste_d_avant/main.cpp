#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::string label;
    int n = 0;
    if (!(std::cin >> label >> n)) {
        return 0;
    }
    std::vector<std::string> avant(n);
    std::unordered_set<std::string> set_avant;
    set_avant.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> avant[i];
        set_avant.insert(avant[i]);
    }

    int c = 0;
    std::cin >> label >> c;
    std::unordered_set<std::string> corrige;
    corrige.reserve(c);
    for (int i = 0; i < c; ++i) {
        std::string key;
        std::cin >> key;
        corrige.insert(key);
    }

    int a = 0;
    std::cin >> label >> a;
    std::unordered_set<std::string> apres;
    apres.reserve(a);
    long long nouvelles = 0;
    for (int i = 0; i < a; ++i) {
        std::string key;
        std::cin >> key;
        apres.insert(key);
        if (set_avant.find(key) == set_avant.end()) {
            ++nouvelles;
        }
    }

    long long vraies = 0;
    long long fausses = 0;
    long long oubliees = 0;

    for (int i = 0; i < n; ++i) {
        const std::string& key = avant[i];
        std::string categorie;
        if (corrige.find(key) != corrige.end()) {
            categorie = "DEVENUE_FAUSSE";
            ++fausses;
        } else if (apres.find(key) != apres.end()) {
            categorie = "ENCORE_VRAIE";
            ++vraies;
        } else {
            categorie = "OUBLIEE";
            ++oubliees;
        }
        std::cout << (i + 1) << ' ' << key << ' ' << categorie << '\n';
    }

    long long denom = vraies + oubliees;
    long long part_oubliee = (denom == 0) ? 0 : (100 * oubliees) / denom;

    std::cout << "VRAIES " << vraies << '\n';
    std::cout << "FAUSSES " << fausses << '\n';
    std::cout << "OUBLIEES " << oubliees << '\n';
    std::cout << "NOUVELLES " << nouvelles << '\n';
    std::cout << "PART_OUBLIEE " << part_oubliee << '\n';

    return 0;
}
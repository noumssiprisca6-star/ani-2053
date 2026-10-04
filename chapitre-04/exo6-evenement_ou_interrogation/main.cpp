#include <iostream>
#include <string>

int main() {
    int v, N;
    if (!(std::cin >> v >> N)) {
        return 0;
    }

    bool spaceEnfoncee = false;
    bool leftEnfoncee = false;
    bool rightEnfoncee = false;

    int xe = 0;
    int xi = 0;

    int sautsEvt = 0;
    int sautsInterro = 0;
    int manques = 0;

    for (int i = 1; i <= N; ++i) {
        int k;
        std::cin >> k;

        int spacePlusDansImage = 0;

        for (int j = 0; j < k; ++j) {
            std::string evt;
            std::cin >> evt;

            char type = evt[0];
            std::string nom = evt.substr(1);

            if (type == '+') {
                if (nom == "SPACE") {
                    spaceEnfoncee = true;
                    sautsEvt++;
                    spacePlusDansImage++;
                } else if (nom == "RIGHT") {
                    rightEnfoncee = true;
                    xe += v;
                } else if (nom == "LEFT") {
                    leftEnfoncee = true;
                    xe -= v;
                }
            } else if (type == '-') {
                if (nom == "SPACE") {
                    spaceEnfoncee = false;
                } else if (nom == "RIGHT") {
                    rightEnfoncee = false;
                } else if (nom == "LEFT") {
                    leftEnfoncee = false;
                }
            }
        }

        if (spaceEnfoncee) {
            sautsInterro++;
        }
        if (rightEnfoncee) {
            xi += v;
        }
        if (leftEnfoncee) {
            xi -= v;
        }

        if (spacePlusDansImage > 0 && !spaceEnfoncee) {
            manques += spacePlusDansImage;
        }

        std::cout << i << " " << xe << " " << xi << "\n";
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEvt << "\n";
    std::cout << "SAUTS INTERROGATION " << sautsInterro << "\n";
    std::cout << "MANQUES " << manques << "\n";

    return 0;
}


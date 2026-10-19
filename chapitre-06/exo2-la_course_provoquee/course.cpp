#include <iostream>
#include <vector>
#include "../canvaskit/include/NKThreading/NkThread.h"

using namespace nkentseu;
using namespace nkentseu::threading;

int main() {
    long long attendu = 8LL * 1000000LL;
    long long compteur = 0;

    std::vector<NkThread*> fils;
    fils.reserve(8);

    for (int i = 0; i < 8; ++i) {
        fils.push_back(new NkThread([&compteur](void*) {
            for (int j = 0; j < 1000000; ++j) {
                compteur += 1;
            }
        }));
    }

    for (auto* fil : fils) {
        fil->Join();
        delete fil;
    }

    std::cout << "Total : " << compteur << " / Attendu : " << attendu << std::endl;
    return 0;
}
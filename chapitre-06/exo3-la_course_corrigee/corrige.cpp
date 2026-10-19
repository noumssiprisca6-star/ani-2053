#include <iostream>
#include <vector>
#include <algorithm>
#include "../canvaskit/include/NKThreading/NkThread.h"
#include "../canvaskit/include/NKThreading/NkMutex.h"
#include "../canvaskit/include/NKThreading/NkScopedLock.h"
#include "../canvaskit/include/NKCore/NkAtomic.h"
#include "../canvaskit/include/NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

int main() {
    NkChrono chrono;
    void* q = nullptr;

    long long totalSansProtection = 0;
    long long tempsSansProtection[3];
    for (int m = 0; m < 3; ++m) {
        totalSansProtection = 0;
        (void)chrono.Reset();
        std::vector<NkThread*> fils;
        for (int i = 0; i < 8; ++i) {
            fils.push_back(new NkThread([&totalSansProtection, q](void*) {
                (void)q;
                for (int j = 0; j < 1000000; ++j) {
                    totalSansProtection += 1;
                }
            }));
        }
        for (auto* fil : fils) {
            fil->Join();
            delete fil;
        }
        tempsSansProtection[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::sort(tempsSansProtection, tempsSansProtection + 3);

    long long totalMutex = 0;
    NkMutex mutex;
    long long tempsMutex[3];
    for (int m = 0; m < 3; ++m) {
        totalMutex = 0;
        (void)chrono.Reset();
        std::vector<NkThread*> fils;
        for (int i = 0; i < 8; ++i) {
            fils.push_back(new NkThread([&totalMutex, &mutex, q](void*) {
                (void)q;
                for (int j = 0; j < 1000000; ++j) {
                    threading::NkScopedLock<NkMutex> lock(mutex);
                    totalMutex += 1;
                }
            }));
        }
        for (auto* fil : fils) {
            fil->Join();
            delete fil;
        }
        tempsMutex[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::sort(tempsMutex, tempsMutex + 3);

    NkAtomicInt totalAtomique(0);
    long long tempsAtomique[3];
    for (int m = 0; m < 3; ++m) {
        totalAtomique.Store(0);
        (void)chrono.Reset();
        std::vector<NkThread*> fils;
        for (int i = 0; i < 8; ++i) {
            fils.push_back(new NkThread([&totalAtomique, q](void*) {
                (void)q;
                for (int j = 0; j < 1000000; ++j) {
                    totalAtomique.FetchAdd(1);
                }
            }));
        }
        for (auto* fil : fils) {
            fil->Join();
            delete fil;
        }
        tempsAtomique[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::sort(tempsAtomique, tempsAtomique + 3);

    long long totalLocalFinal = 0;
    long long tempsLocale[3];
    for (int m = 0; m < 3; ++m) {
        long long totauxLocaux[8] = {0};
        (void)chrono.Reset();
        std::vector<NkThread*> fils;
        for (int i = 0; i < 8; ++i) {
            fils.push_back(new NkThread([totauxLocaux, i, q](void*) {
                (void)q;
                long long local = 0;
                for (int j = 0; j < 1000000; ++j) {
                    local += 1;
                }
                const_cast<long long*>(totauxLocaux)[i] = local;
            }));
        }
        for (auto* fil : fils) {
            fil->Join();
            delete fil;
        }
        long long somme = 0;
        for (int i = 0; i < 8; ++i) {
            somme += totauxLocaux[i];
        }
        totalLocalFinal = somme;
        tempsLocale[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::sort(tempsLocale, tempsLocale + 3);

    std::cout << "Sans protection : " << totalSansProtection << " / " << tempsSansProtection[1] << "ms" << std::endl;
    std::cout << "Mutex : " << totalMutex << " / " << tempsMutex[1] << "ms" << std::endl;
    std::cout << "Atomique : " << totalAtomique.Load() << " / " << tempsAtomique[1] << "ms" << std::endl;
    std::cout << "Local : " << totalLocalFinal << " / " << tempsLocale[1] << "ms" << std::endl;

    return 0;
}
#include <iostream>
#include <vector>
#include "../canvaskit/include/NKThreading/NkThreadPool.h"
#include "../canvaskit/include/NKThreading/NkThread.h"
#include "../canvaskit/include/NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

void TacheCourte(void*) {
    volatile long long somme = 0;
    for (int i = 0; i < 1000; ++i) {
        somme += i;
    }
}

void TacheLongue(void*) {
    volatile long long somme = 0;
    for (int i = 0; i < 100000; ++i) {
        somme += i;
    }
}

int main() {
    NkThreadPool pool;
    std::cout << "Ouvriers : " << pool.GetNumWorkers() << std::endl;

    NkChrono chrono;
    void* q = nullptr;

    // Échauffement de la réserve
    for (int i = 0; i < 200; ++i) {
        pool.Enqueue([&](auto&&...) { TacheCourte(q); });
    }
    pool.Join();

    long long tempsReserve[3];
    for (int m = 0; m < 3; ++m) {
        (void)chrono.Reset();
        for (int i = 0; i < 200; ++i) {
            pool.Enqueue([&](auto&&...) { TacheCourte(q); });
        }
        pool.Join();
        tempsReserve[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::cout << "Réserve : " << tempsReserve[0] << "ms, " << tempsReserve[1] << "ms, " << tempsReserve[2] << "ms" << std::endl;

    long long tempsFils[3];
    for (int m = 0; m < 3; ++m) {
        (void)chrono.Reset();
        std::vector<NkThread*> fils;
        fils.reserve(200);
        for (int i = 0; i < 200; ++i) {
            fils.push_back(new NkThread([](void*) { TacheCourte(nullptr); }));
        }
        for (auto* fil : fils) {
            fil->Join();
            delete fil;
        }
        tempsFils[m] = static_cast<long long>(chrono.Elapsed().ToMilliseconds());
    }
    std::cout << "Fils : " << tempsFils[0] << "ms, " << tempsFils[1] << "ms, " << tempsFils[2] << "ms" << std::endl;

    (void)chrono.Reset();
    for (int i = 0; i < 200; ++i) {
       pool.Enqueue([&](auto&&...) { TacheCourte(q); });
    }
    pool.Join();
    long long tempsReserveLong = static_cast<long long>(chrono.Elapsed().ToMilliseconds());

    (void)chrono.Reset();
    std::vector<NkThread*> filsLongs;
    filsLongs.reserve(200);
    for (int i = 0; i < 200; ++i) {
        filsLongs.push_back(new NkThread([](void*) { TacheLongue(nullptr); }));
    }
    for (auto* fil : filsLongs) {
        fil->Join();
        delete fil;
    }
    long long tempsFilsLong = static_cast<long long>(chrono.Elapsed().ToMilliseconds());

    std::cout << "Tâche longue : " << tempsReserveLong << "ms, " << tempsFilsLong << "ms" << std::endl;

    return 0;
}


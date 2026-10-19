#include <iostream>
#include <vector>
#include "../canvaskit/include/NKThreading/NkThread.h"
#include "../canvaskit/include/NKThreading/NkMutex.h"
#include "../canvaskit/include/NKThreading/NkScopedLock.h"
#include "../canvaskit/include/NKTime/NkChrono.h"

using namespace nkentseu;
using namespace nkentseu::threading;

/* Version qui se fige :
threading::NkScopedLock<NkMutex> lock1(m2);
NkChrono::SleepMilliseconds(100);
threading::NkScopedLock<NkMutex> lock2(m1);
*/

int main() {
    NkMutex m1;
    NkMutex m2;
    void* q = nullptr;

    NkThread filA([&m1, &m2, q](void*) {
        (void)q;
        threading::NkScopedLock<NkMutex> lock1(m1);
        NkChrono::SleepMilliseconds(100);
        threading::NkScopedLock<NkMutex> lock2(m2);
    });

    NkThread filB([&m1, &m2, q](void*) {
        (void)q;
        threading::NkScopedLock<NkMutex> lock1(m1);
        NkChrono::SleepMilliseconds(100);
        threading::NkScopedLock<NkMutex> lock2(m2);
    });

    filA.Join();
    filB.Join();

    return 0;
}
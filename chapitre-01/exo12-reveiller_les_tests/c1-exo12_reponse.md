
```markdown
# Rapport : Activation et Exécution des Tests Unitaires

---

## 1. Désactivation des Tests dans le Workspace

* **Fichier identifié :** `NKentseu.json`
* **Ligne responsable :** Ligne `451 & 453`
* **Code/Configuration identifié(e) :**
  ```python

   dutc(enable=False)

    dute(enable=False)
  

```

---

## 2. Exécution Forcee de la Suite de Tests

* **Commande utilisée pour lancer les tests :**
```bash
jenga test --project NKCore_Tests

```


* **Module ciblé :** `NKCore_Tests`

---

## 3. Résultats de l'Exécution des Tests
## 3. Résultats de l'Exécution des Tests

| Métrique | Nombre |
| --- | --- |
| **Suites de tests existantes dans le module** | **9** *(NKAudio_Tests)* |
| **Suites de tests exécutées** | **9** *(Échec durant la phase de compilation)* |
| **Suites de tests réussies (Pass)** | **9** |
| **Suites de tests échouées (Fail)** | **0** *(Non exécutées)* |

---

* **RESULTAT**
```bash

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.4.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Building NKCore_Tests...
Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (4 projects):
  1. __Unitest__ [STATIC_LIB] → 
  2. NKPlatform [STATIC_LIB] → 
  3. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  4. NKCore_Tests [TEST_SUITE] (depends: NKCore, __Unitest__, NKPlatform)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: __Unitest__                                                      Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 11 source file(s)
✓   [1/11] Compiled: ConsoleReport.cpp
✓   [2/11] Compiled: Benchmark.cpp
✓   [3/11] Compiled: PerformanceReporter.cpp
✓   [4/11] Compiled: TestAggregator.cpp
✓   [5/11] Compiled: TestAssert.cpp
✓   [6/11] Compiled: Profiler.cpp
✓   [7/11] Compiled: TestLauncher.cpp
✓   [8/11] Compiled: TestCase.cpp
✓   [9/11] Compiled: TestReporter.cpp
✓   [10/11] Compiled: Unitest.cpp
✓   [11/11] Compiled: TestRunner.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\__Unitest__\Unitest.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 17.75s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKPlatform                                                       Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 7 source file(s)
✓   [1/7] Compiled: NkArchDetect.cpp
✓   [2/7] Compiled: NkCGXDetect.cpp
✓   [3/7] Compiled: NkCompilerDetect.cpp
✓   [4/7] Compiled: NkEndianness.cpp
✓   [5/7] Compiled: NkEnv.cpp
✓   [6/7] Compiled: NkCPUFeatures.cpp
✓   [7/7] Compiled: NkPlatformConfig.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKPlatform.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.11s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCore                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 5 source file(s)
✓   [1/5] Compiled: NkLimits.cpp
✓   [2/5] Compiled: NkAssert.cpp
✓   [3/5] Compiled: NkTraits.cpp
✓   [4/5] Compiled: NkBits.cpp
✓   [5/5] Compiled: NkPlatform.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKCore.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.73s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCore_Tests                                                     Kind: TEST_SUITE  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)
✓   [1/3] Compiled: Entry.cpp
✓   [2/3] Compiled: benchmark_smoke.cpp
✓   [3/3] Compiled: test_smoke.cpp
ℹ Linking...
✓ Built: Build\Tests\Debug-Windows\NKCore_Tests.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 6.97s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  4/4
Time:           31.55s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════


Running tests for NKCore_Tests...
╔======================================================================╗
║                                                                      ║
║      ██╗   ██╗███╗   ██╗██╗████████╗███████╗███████╗████████╗        ║
║      ██║   ██║████╗  ██║██║╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝        ║
║      ██║   ██║██╔██╗ ██║██║   ██║   █████╗  ███████╗   ██║           ║
║      ██║   ██║██║╚██╗██║██║   ██║   ██╔══╝  ╚════██║   ██║           ║
║      ╚██████╔╝██║ ╚████║██║   ██║   ███████╗███████║   ██║           ║
║       ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝   ╚══════╝╚══════╝   ╚═╝           ║
║                                                                      ║
║                C++ Unit Testing Framework v1.0.0                     ║
║              Fast, Reliable, and Developer-Friendly                  ║
║                                                                      ║
║  Number of tests: 9                                                  ║
║  Verbose mode: enabled                                               ║
║  Colors: enabled                                                     ║
║  Progress bar: disabled                                              ║
║                                                                      ║
║               Session started: 2026-09-14 20:45:33                   ║
║                                                                      ║
╚======================================================================╝

[INF] C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKCore\tests\benchmark_smoke.cpp:95 [NKCore Benchmark] Atomic FetchAdd NK=0.000125 ms STL=0.000096 ms ratio=1.304
✓ NKCoreBenchmark_AtomicFetchAddNkVsStdAtomic   [OK]  4/4 assertions  (166ms)
  ✓ 4 assertion(s) réussie(s) (moy: 41ms/assert)
[INF] C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKCore\tests\benchmark_smoke.cpp:59 [NKCore Benchmark] Optional Toggle NK=0.000188 ms STL=0.000129 ms ratio=1.457
✓ NKCoreBenchmark_OptionalToggleVsStdOptional   [OK]  5/5 assertions  (170ms)
  ✓ 5 assertion(s) réussie(s) (moy: 34ms/assert)
✓ NKCoreSmoke_AtomicCounterAndCompareExchange   [OK]  7/7 assertions  (< 1ms)
  ✓ 7 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_BitsUtilities                     [OK]  7/7 assertions  (< 1ms)
  ✓ 7 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_ByteWrapperOperators              [OK]  1/1 assertions  (< 1ms)
  ✓ 1 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_OptionalBasicLifecycle            [OK]  5/5 assertions  (< 1ms)
  ✓ 5 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_OptionalSwapAndGetIf              [OK]  6/6 assertions  (< 1ms)
  ✓ 6 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_VariantSetAndVisit                [OK]  4/4 assertions  (< 1ms)
  ✓ 4 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKCoreSmoke_VariantSwapAndGetIf               [OK]  6/6 assertions  (< 1ms)
  ✓ 6 assertion(s) réussie(s) (moy: < 1ms/assert)


┌────────────────────── RÉSULTATS DES TESTS ──────────────────────┐
│ SUCCÈS                                                          │
├─────────────────────────────────────────────────────────────────┤
│ Tests :      9 réussis, 9 au total          │
│ Assertions : 45 réussies, 45 au total         │
│ Taux succès : Tests: 100.0%, Assertions: 100.0%        │
│ Temps total : 337ms (37ms/test)     │
└──────────────────────────────────────────────────────────────┘

✅ Tous les tests sont réussis !

All tests passed for NKCore_Tests.
```

## 4. Analyse et Remarques


* **Exécution globale :** La suite de tests s'est exécutée avec un taux de succès de 100%.

D* **étail des tests :** Les 9 tests au total ont été exécutés et validés sans aucun échec.

* **Détail des assertions :**Les 45 assertions incluses dans les tests ont toutes été vérifiées avec succès (100% de réussite).

 * **Performance :** L'exécution de la suite a pris un temps total de 337 ms, soit une moyenne très rapide de 37 ms par test.

 > * **NOTE** : Reintialisation de NKentseu .jenga







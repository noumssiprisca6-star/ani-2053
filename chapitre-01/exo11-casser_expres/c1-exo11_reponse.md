# Rapport de Test : Injection de Faute & Résolution de Dépendances (NKMath)

---

## 1. Contexte de l'Expérimentation
* **Module ciblé :** `NKMath`
* **Fichier modifié :** `Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp` (Ligne `29`  )
* **Erreur injectée :** `retrait du u sur namespace nkentseu{}`
* **Commande exécutée :** `jenga build`
* **Temps total du build (jusqu'à l'arrêt complet) :** 2 minutes 26.8 secondes (`2m26.8s`)
* **Comportement du Build Engine :** Le moteur utilise une stratégie **parallèle et tolérante jusqu'au signalement  de l'echec**. Même lorsqu'une erreur fatale survient dans `NkRectangle.cpp`, le compilateur n'interrompt pas immédiatement les autres workers : il termine la compilation des fichiers C++ indépendants du même module (`NkSIMD.cpp`, `NkSegment.cpp`, `NkVec.cpp`) avant de marquer le projet `NKMath` comme échoué.


---

## 2. Métriques de Compilation

| Métrique | Valeur Observée |
| :--- | :--- |
| **Temps total avant arrêt :** | ` 2m26.8s` |
| **Statut final du Build :** 


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

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKPlatform                                                       Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 7 source file(s)
✓   [1/7] Compiled: NkCGXDetect.cpp
✓   [2/7] Compiled: NkArchDetect.cpp
✓   [3/7] Compiled: NkCompilerDetect.cpp
✓   [4/7] Compiled: NkEndianness.cpp
✓   [5/7] Compiled: NkEnv.cpp
✓   [6/7] Compiled: NkPlatformConfig.cpp
✓   [7/7] Compiled: NkCPUFeatures.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKPlatform.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 18.96s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCore                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 5 source file(s)
✓   [1/5] Compiled: NkAssert.cpp
✓   [2/5] Compiled: NkLimits.cpp
✓   [3/5] Compiled: NkTraits.cpp
✓   [4/5] Compiled: NkBits.cpp
✓   [5/5] Compiled: NkPlatform.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKCore.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 10.45s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMemory                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 14 source file(s)
✓   [1/14] Compiled: NkFunction.cpp
✓   [2/14] Compiled: NkContainerAllocator.cpp
✓   [3/14] Compiled: NkGc.cpp
✓   [4/14] Compiled: NkFunctionSIMD.cpp
✓   [5/14] Compiled: NkGlobalOperators.cpp
✓   [6/14] Compiled: NkHash.cpp
✓   [7/14] Compiled: NkMemory.cpp
✓   [8/14] Compiled: NkMultiLevelAllocator.cpp
✓   [9/14] Compiled: NkProfiler.cpp
✓   [10/14] Compiled: NkPoolAllocator.cpp
✓   [11/14] Compiled: NkTag.cpp
✓   [12/14] Compiled: NkTracker.cpp
✓   [13/14] Compiled: NkUtils.cpp
✓   [14/14] Compiled: NkAllocator.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMemory.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 20.03s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKContainers                                                     Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 42 source file(s)
✓   [1/42] Compiled: NkArray.cpp
✓   [2/42] Compiled: NkTuple.cpp
✓   [3/42] Compiled: NkBTree.cpp
✓   [4/42] Compiled: NkUnorderedMap.cpp
✓   [5/42] Compiled: NkBind.cpp
✓   [6/42] Compiled: NkTrie.cpp
✓   [7/42] Compiled: NkFunctional.cpp
✓   [8/42] Compiled: NkPriorityQueue.cpp
✓   [9/42] Compiled: NkFunction.cpp
✓   [10/42] Compiled: NkPair.cpp
✓   [11/42] Compiled: NkBinaryTree.cpp
✓   [12/42] Compiled: NkPool.cpp
✓   [13/42] Compiled: NkSet.cpp
✓   [14/42] Compiled: NkRingBuffer.cpp
✓   [15/42] Compiled: NkInitializerList.cpp
✓   [16/42] Compiled: NkUnorderedSet.cpp
✓   [17/42] Compiled: NkMap.cpp
✓   [18/42] Compiled: NkHashMap.cpp
✓   [19/42] Compiled: NkContainers.cpp
✓   [20/42] Compiled: NkIterator.cpp
✓   [21/42] Compiled: NkDoubleList.cpp
✓   [22/42] Compiled: NkDeque.cpp
✓   [23/42] Compiled: NkList.cpp
✓   [24/42] Compiled: NkVector.cpp
✓   [25/42] Compiled: NkGraph.cpp
✓   [26/42] Compiled: NkASCII.cpp
✓   [27/42] Compiled: NkQuadTree.cpp
✓   [28/42] Compiled: NkEncoding.cpp
✓   [29/42] Compiled: NkUTF16.cpp
✓   [30/42] Compiled: NkUTF32.cpp
✓   [31/42] Compiled: NkUTF8.cpp
✓   [32/42] Compiled: NkBasicString.cpp
✓   [33/42] Compiled: NkFormat.cpp
✓   [34/42] Compiled: NkString.cpp
✓   [35/42] Compiled: NkStringBuilder.cpp
✓   [36/42] Compiled: NkStringHash.cpp
✓   [37/42] Compiled: NkOptional.cpp
✓   [38/42] Compiled: NkStringUtils.cpp
✓   [39/42] Compiled: NkResult.cpp
✓   [40/42] Compiled: NkStringView.cpp
✓   [41/42] Compiled: NkVariant.cpp
✓   [42/42] Compiled: NkSpan.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 49.11s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 12 source file(s)
✓   [1/12] Compiled: NkAngle.cpp
✓   [2/12] Compiled: NkEulerAngle.cpp
✓   [3/12] Compiled: NkColor.cpp
✓   [4/12] Compiled: NkFunctions.cpp
✓   [5/12] Compiled: NkMat.cpp
✓   [6/12] Compiled: NkQuat.cpp
✓   [7/12] Compiled: NkRandom.cpp
✓   [8/12] Compiled: NkRange.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkRectangle.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:38:3: error: use of undeclared identifier 'NkRectangle'; did you mean                    ║
║ 'nkentseu::math::NkRectangle'?                                                               ║
║    38 |                 NkRectangle::NkRectangle() : corner(0.0f, 0.0f), size(1.0f, 1.0f) {  ║
║       |                 ^~~~~~~~~~~                                                          ║
║       |                 nkentseu::math::NkRectangle                                          ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRectangle. ║
║ h:57:9: note: 'nkentseu::math::NkRectangle' declared here                                    ║
║    57 |                 class NkRectangle {                                                  ║
║       |                       ^                                                              ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:38:16: error: cannot define or redeclare 'NkRectangle' here because namespace 'math'     ║
║ does not enclose namespace 'NkRectangle'                                                     ║
║    38 |                 NkRectangle::NkRectangle() : corner(0.0f, 0.0f), size(1.0f, 1.0f) {  ║
║       |                 ~~~~~~~~~~~~~^                                                       ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:49:3: error: use of undeclared identifier 'NkRectangle'; did you mean                    ║
║ 'nkentseu::math::NkRectangle'?                                                               ║
║ 49 |                 NkRectangle::NkRectangle(const NkVector2f &cornerPoint, const           ║
║ NkVector2f &dimensions)                                                                      ║
║       |                 ^~~~~~~~~~~                                                          ║
║       |                 nkentseu::math::NkRectangle                                          ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRectangle. ║
║ h:57:9: note: 'nkentseu::math::NkRectangle' declared here                                    ║
║    57 |                 class NkRectangle {                                                  ║
║       |                       ^                                                              ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:49:16: error: cannot define or redeclare 'NkRectangle' here because namespace 'math'     ║
║ does not enclose namespace 'NkRectangle'                                                     ║
║ 49 |                 NkRectangle::NkRectangle(const NkVector2f &cornerPoint, const           ║
║ NkVector2f &dimensions)                                                                      ║
║       |                 ~~~~~~~~~~~~~^                                                       ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:50:13: error: use of undeclared identifier 'cornerPoint'                                 ║
║    50 |                         : corner(cornerPoint), size(dimensions) {                    ║
║       |                                  ^~~~~~~~~~~                                         ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:50:32: error: use of undeclared identifier 'dimensions'                                  ║
║    50 |                         : corner(cornerPoint), size(dimensions) {                    ║
║       |                                                     ^~~~~~~~~~                       ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:62:3: error: use of undeclared identifier 'NkRectangle'; did you mean                    ║
║ 'nkentseu::math::NkRectangle'?                                                               ║
║ 62 |                 NkRectangle::NkRectangle(float32 x, float32 y, float32 width, float32   ║
║ height)                                                                                      ║
║       |                 ^~~~~~~~~~~                                                          ║
║       |                 nkentseu::math::NkRectangle                                          ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRectangle. ║
║ h:57:9: note: 'nkentseu::math::NkRectangle' declared here                                    ║
║    57 |                 class NkRectangle {                                                  ║
║       |                       ^                                                              ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:62:16: error: cannot define or redeclare 'NkRectangle' here because namespace 'math'     ║
║ does not enclose namespace 'NkRectangle'                                                     ║
║ 62 |                 NkRectangle::NkRectangle(float32 x, float32 y, float32 width, float32   ║
║ height)                                                                                      ║
║       |                 ~~~~~~~~~~~~~^                                                       ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:13: error: use of undeclared identifier 'x'; did you mean '_complex::x'?              ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                  ^                                                   ║
║       |                                  _complex::x                                         ║
║ C:/msys64/ucrt64/include/math.h:268:12: note: '_complex::x' declared here                    ║
║   268 |     double x;                                                                        ║
║       |            ^                                                                         ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:13: error: invalid use of non-static data member 'x'                                  ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                  ^                                                   ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:16: error: use of undeclared identifier 'y'; did you mean '_complex::y'?              ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                     ^                                                ║
║       |                                     _complex::y                                      ║
║ C:/msys64/ucrt64/include/math.h:269:12: note: '_complex::y' declared here                    ║
║   269 |     double y;                                                                        ║
║       |            ^                                                                         ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:16: error: invalid use of non-static data member 'y'                                  ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                     ^                                                ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:25: error: use of undeclared identifier 'width'                                       ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                              ^~~~~                                   ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:63:32: error: use of undeclared identifier 'height'                                      ║
║    63 |                         : corner(x, y), size(width, height) {                        ║
║       |                                                     ^~~~~~                           ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:75:3: error: use of undeclared identifier 'NkRectangle'; did you mean                    ║
║ 'nkentseu::math::NkRectangle'?                                                               ║
║ 75 |                 NkRectangle::NkRectangle(const NkVector2f &cornerPoint, float32 width,  ║
║ float32 height)                                                                              ║
║       |                 ^~~~~~~~~~~                                                          ║
║       |                 nkentseu::math::NkRectangle                                          ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src/NKMath/NkRectangle. ║
║ h:57:9: note: 'nkentseu::math::NkRectangle' declared here                                    ║
║    57 |                 class NkRectangle {                                                  ║
║       |                       ^                                                              ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:75:16: error: cannot define or redeclare 'NkRectangle' here because namespace 'math'     ║
║ does not enclose namespace 'NkRectangle'                                                     ║
║ 75 |                 NkRectangle::NkRectangle(const NkVector2f &cornerPoint, float32 width,  ║
║ float32 height)                                                                              ║
║       |                 ~~~~~~~~~~~~~^                                                       ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:76:13: error: use of undeclared identifier 'cornerPoint'                                 ║
║    76 |                         : corner(cornerPoint), size(width, height) {                 ║
║       |                                  ^~~~~~~~~~~                                         ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:76:32: error: use of undeclared identifier 'width'                                       ║
║    76 |                         : corner(cornerPoint), size(width, height) {                 ║
║       |                                                     ^~~~~                            ║
║ C:\Users\jouvence                                                                            ║
║ computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle. ║
║ cpp:76:39: error: use of undeclared identifier 'height'                                      ║
║    76 |                         : corner(cornerPoint), size(width, height) {                 ║
║       |                                                            ^~~~~~                    ║
║ fatal error: too many errors emitted, stopping now [-ferror-limit=]                          ║
║ 20 errors generated.                                                                         ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                Time: 48.24s  │
│ Errors: 20  | Failed files: 1                                                                │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  4/5
Failed:         1
Errors:         20
Time:           2m26.8s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ NKMath
```
---




## 3. État d'Exécution des Projets

### Projets construits avec succès (4/5)
Ces projets ont été compilés intégralement car ils se situent en **amont** de `NKMath` dans le graphe de dépendances :

1. **`NKPlatform`** (Durée : `18.96s` — 7 fichiers)
2. **`NKCore`** (Durée : `10.45s` — 5 fichiers)
3. **`NKMemory`** (Durée : `20.03s` — 14 fichiers)
4. **`NKContainers`** (Durée : `49.11s` — 42 fichiers)

### Projet en échec (1/5)
*  **`NKMath`** (Échec au fichier `NkRectangle.cpp` — 20 erreurs générées)

---

## 4. Enseignements sur l'Ordre de Construction (Build Order)

1. **Graphe Dirige:**  Le log de sortie confirme que l'ordre de compilation est séquentiel au niveau des bibliothèques :
   
   $$\text{NKPlatform} \longrightarrow \text{NKCore} \longrightarrow \text{NKMemory} \longrightarrow \text{NKContainers} \longrightarrow \text{NKMath}$$
   
   Chaque projet attend la mise à disposition des bibliothèques statiques (`.lib`) de ses dépendances directes avant de finaliser son édition de liens (linking).

2. **Isolation des dépendances :** L'échec survenu dans `NKMath` n'a pas impacté les 4 premiers modules. Cela démontre que les dépendances descendent vers `NKMath` (qui dépend de tout le monde), mais qu'aucun des 4 modules précédents ne dépend de `NKMath`.

---

## 4. Remise en État du Fichier

Pour corriger l'erreur et rétablir le build, jwe suis  retourner le contenu du fichier `Kernel/Foundation/NKMath/src/NKMath/NkRectangle.cpp` avec son espace de nommage (`namespace nkentseu {}`) :


Le document structure les résultats de mesure, analyse l'écart entre les configurations **Debug** et **Release**, et remonte directement aux lignes explicatives du fichier `.jenga`.

```markdown
#  Rapport d'Expérimentation : Comparaison des Configurations Debug vs Release

> **Projet :** `NewProjet`  
> **Outil de Build :** Jenga  
> **Objectif :** Mesurer l'impact des options de compilation sur la taille des binaires et la durée du build entre les modes `Debug` et `Release`, puis identifier les lignes de configuration `.jenga` responsables de ces écarts.

---

##  1. Tableau Comparatif des Mesures

### Protocole
1. Nettoyage initial des artefacts de build (`jenga clean`).
2. Compilation intégrale en configuration **Debug**, mesure du temps et de la taille du binaire produit.
3. Nettoyage, puis compilation intégrale en configuration **Release**, mesure des mêmes métriques.

```bash
# Compilation Debug
jenga clean
jenga build --config Debug


# Compilation Release
jenga clean
time jenga build --config Release

```

---

### Relevé des Métriques (Les 4 Nombres)

| Configuration | Temps de Build     | Taille du Binaire                             |              Description       
|--|--|--|--|
| **Debug**     | `~ 2.91s` *(N1)*   | `~ 1.61 k0` et ` 1.64k0` sur le disque *(N2)* | Code non optimisé, symboles de débogage inclus.|
| **Release**   | `~ 3.12s` *(N3)*   | `~  1.61ko` et `1.64ko` sur le disque  *(N4)*    | Code hautement optimisé, symboles retirés.   |



---



## 2. Explication des Écart



### 1. Écart de Temps de Construction (Debug vs Release)

* **Release est généralement plus long à compiler que Debug  :**
En mode Release, le compilateur effectue des passes d'analyse lourdes pour optimiser le code (inlining de fonctions, déroulage de boucles, élimination de code mort , etc.). Ces passes d'optimisation demandent une charge calculatoire importante au processeur lors de la compilation generalement

### 2. Écart de Taille du Binaire (N2 vs N4)
 
 MON PROJET ACTUEL EST TRES LEGER  par consequent  je me dis que  c'est pourquoi la configuration de Debug est la meme que celle de Release au niveau de la taille binaire. Par consequent `N2 = N4`
 Je vais  compiler un projet dans Nkentseu afin d'observer la difference binaire entre la configuration debug et release et constater les observetions


---
 ##  . Tableau Comparatif des Mesures pour le projet NKMath

### Protocole
1. Nettoyage initial des artefacts de build (`jenga clean`).
2. Compilation intégrale en configuration **Debug**, mesure du temps et de la taille du binaire produit.
3. Nettoyage, puis compilation intégrale en configuration **Release**, mesure des mêmes métriques.

```bash
# Compilation Release
jenga clean
jenga build --target NkMath --config Release
```
* **Resultat**
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

Configuration: Release
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
✓   [1/7] Compiled: NkArchDetect.cpp
✓   [2/7] Compiled: NkCGXDetect.cpp
✓   [3/7] Compiled: NkCompilerDetect.cpp
✓   [4/7] Compiled: NkEndianness.cpp
✓   [5/7] Compiled: NkEnv.cpp
✓   [6/7] Compiled: NkPlatformConfig.cpp
✓   [7/7] Compiled: NkCPUFeatures.cpp
ℹ Linking...
✓ Built: Build\Lib\Release-Windows\NKPlatform.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 5.06s  │
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
✓ Built: Build\Lib\Release-Windows\NKCore.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 12.62s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMemory                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 14 source file(s)
✓   [1/14] Compiled: NkFunction.cpp
✓   [2/14] Compiled: NkContainerAllocator.cpp
✓   [3/14] Compiled: NkFunctionSIMD.cpp
✓   [4/14] Compiled: NkGc.cpp
✓   [5/14] Compiled: NkGlobalOperators.cpp
✓   [6/14] Compiled: NkHash.cpp
✓   [7/14] Compiled: NkMemory.cpp
✓   [8/14] Compiled: NkMultiLevelAllocator.cpp
✓   [9/14] Compiled: NkPoolAllocator.cpp
✓   [10/14] Compiled: NkProfiler.cpp
✓   [11/14] Compiled: NkAllocator.cpp
✓   [12/14] Compiled: NkTag.cpp
✓   [13/14] Compiled: NkUtils.cpp
✓   [14/14] Compiled: NkTracker.cpp
ℹ Linking...
✓ Built: Build\Lib\Release-Windows\NKMemory.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 14.05s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKContainers                                                     Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 42 source file(s)
✓   [1/42] Compiled: NkHashMap.cpp
✓   [2/42] Compiled: NkBinaryTree.cpp
✓   [3/42] Compiled: NkBTree.cpp
✓   [4/42] Compiled: NkMap.cpp
✓   [5/42] Compiled: NkPriorityQueue.cpp
✓   [6/42] Compiled: NkSet.cpp
✓   [7/42] Compiled: NkTrie.cpp
✓   [8/42] Compiled: NkUnorderedMap.cpp
✓   [9/42] Compiled: NkUnorderedSet.cpp
✓   [10/42] Compiled: NkArray.cpp
✓   [11/42] Compiled: NkPool.cpp
✓   [12/42] Compiled: NkRingBuffer.cpp
✓   [13/42] Compiled: NkBind.cpp
✓   [14/42] Compiled: NkFunction.cpp
✓   [15/42] Compiled: NkFunctional.cpp
✓   [16/42] Compiled: NkPair.cpp
✓   [17/42] Compiled: NkTuple.cpp
✓   [18/42] Compiled: NkInitializerList.cpp
✓   [19/42] Compiled: NkIterator.cpp
✓   [20/42] Compiled: NkContainers.cpp
✓   [21/42] Compiled: NkDeque.cpp
✓   [22/42] Compiled: NkDoubleList.cpp
✓   [23/42] Compiled: NkList.cpp
✓   [24/42] Compiled: NkVector.cpp
✓   [25/42] Compiled: NkGraph.cpp
✓   [26/42] Compiled: NkQuadTree.cpp
✓   [27/42] Compiled: NkASCII.cpp
✓   [28/42] Compiled: NkEncoding.cpp
✓   [29/42] Compiled: NkUTF16.cpp
✓   [30/42] Compiled: NkUTF32.cpp
✓   [31/42] Compiled: NkUTF8.cpp
✓   [32/42] Compiled: NkFormat.cpp
✓   [33/42] Compiled: NkBasicString.cpp
✓   [34/42] Compiled: NkString.cpp
✓   [35/42] Compiled: NkStringHash.cpp
✓   [36/42] Compiled: NkStringBuilder.cpp
✓   [37/42] Compiled: NkOptional.cpp
✓   [38/42] Compiled: NkResult.cpp
✓   [39/42] Compiled: NkStringView.cpp
✓   [40/42] Compiled: NkVariant.cpp
✓   [41/42] Compiled: NkSpan.cpp
✓   [42/42] Compiled: NkStringUtils.cpp
ℹ Linking...
✓ Built: Build\Lib\Release-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 16.66s  │
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
✓   [9/12] Compiled: NkSIMD.cpp
✓   [10/12] Compiled: NkRectangle.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Release-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 12.23s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           1m0.8s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```



``` bash
# Compilation Debug
jenga clean
jenga build --target NkMath --config Debug

```
*  **Resultat**
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
│  ✓ Build Successful                                                             Time: 3.97s  │
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
│  ✓ Build Successful                                                             Time: 2.78s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMemory                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 14 source file(s)
✓   [1/14] Compiled: NkContainerAllocator.cpp
✓   [2/14] Compiled: NkFunction.cpp
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
│  ✓ Build Successful                                                             Time: 4.84s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKContainers                                                     Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 42 source file(s)
✓   [1/42] Compiled: NkBTree.cpp
✓   [2/42] Compiled: NkBinaryTree.cpp
✓   [3/42] Compiled: NkHashMap.cpp
✓   [4/42] Compiled: NkSet.cpp
✓   [5/42] Compiled: NkMap.cpp
✓   [6/42] Compiled: NkPriorityQueue.cpp
✓   [7/42] Compiled: NkUnorderedMap.cpp
✓   [8/42] Compiled: NkTrie.cpp
✓   [9/42] Compiled: NkUnorderedSet.cpp
✓   [10/42] Compiled: NkArray.cpp
✓   [11/42] Compiled: NkPool.cpp
✓   [12/42] Compiled: NkRingBuffer.cpp
✓   [13/42] Compiled: NkBind.cpp
✓   [14/42] Compiled: NkFunction.cpp
✓   [15/42] Compiled: NkPair.cpp
✓   [16/42] Compiled: NkTuple.cpp
✓   [17/42] Compiled: NkFunctional.cpp
✓   [18/42] Compiled: NkIterator.cpp
✓   [19/42] Compiled: NkInitializerList.cpp
✓   [20/42] Compiled: NkContainers.cpp
✓   [21/42] Compiled: NkDeque.cpp
✓   [22/42] Compiled: NkDoubleList.cpp
✓   [23/42] Compiled: NkVector.cpp
✓   [24/42] Compiled: NkList.cpp
✓   [25/42] Compiled: NkGraph.cpp
✓   [26/42] Compiled: NkQuadTree.cpp
✓   [27/42] Compiled: NkASCII.cpp
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
✓   [39/42] Compiled: NkStringView.cpp
✓   [40/42] Compiled: NkResult.cpp
✓   [41/42] Compiled: NkVariant.cpp
✓   [42/42] Compiled: NkSpan.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 11.23s  │
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
✓   [9/12] Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 13.55s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           36.39s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```



---

### Relevé des Métriques  de NKMath (Les 4 Nombres)

| Configuration | Temps de Build     |   Taille du Binaire                             |                   Description                    
|--|--|--|--|
| **Release**   | `~ 1m.08s` *(N1)*  |    `~ 776 k0`  *(N2)*| Code non optimisé, symboles de débogage inclus.
**Debug**     | `~ 36.39s` *(N3)*  |  `~ 776 ko`  *(N4)* | Code hautement optimisé, symboles retirés.   


---

### mon analyse :
Malgre plusieurs essaie sur des projets different , la configuration debug et release possede le meme nombre d'octect
Pourtant dans le generaliste : 

* **Debug est juste un peu plus volumineux que Release  :**
* **Symboles de débogage :** La configuration Debug conserve les tables de symboles (noms de variables, fonctions, numéros de lignes du code source) indispensables pour un débogueur (ex: GDB, LLDB, MSVC Debugger).
* **Inlining & DCE :** La configuration Release supprime le code mort (*Dead Code Elimination*) et applique l'optimisation par la taille/vitesse, réduisant drastiquement l'empreinte finale du fichier exécutable ou de la bibliothèque.


* **EXCEPTION** : je dois faire certainement exception et j'ainmerias savoir si c'est normal 
---

## 3. Identification des Lignes dans le `.jenga`

Les quatre nombres enregistrés découlent directement des directives déclarées dans les filtres de configuration du fichier `.jenga` :

```python
    # =========================================================================
    # CONFIGURATIONS DE COMPILATION (Source des 4 Nombres)
    # =========================================================================

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG"])
        optimize("Off")       # <-- Explique N1 (Build rapide) et N2 (Code non compressé)
        symbols(True)         # <-- pour le debug ( inclusion des symboles de débogage normalement ca rend la taille un peu plus lourde )

    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")     # <-- Explique N3 (Build plus long / passes d'optimisation) 
                              #      pour release  (Taille réduite par DCE / inlining)
        symbols(False)        # <--  pour release ( suppression des symboles ceci doit normalement rendre la taille plus legere )

```

---

##  Points d'Interrogation et Hypothèses (?)

Monsieur , est ce que si la taille de debug et de release en binaire est pareil ca pose un probleme ou bien est ce que ce style d'exception est justifiable 


---



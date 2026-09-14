# Rapport d'Analyse des Temps de Compilation (Build Benchmark)

---

## 1. Tableau Bénéfice / Mesures de Performance

| Scénario de Build | Temps (s) | État du Cache / Artefacts | Description du Processus |
| :--- | :---: | :---: | :--- |
| **Construction complète à froid** | **1.08s s** | Répertoire `build/` supprimé | Compilation de 100% des fichiers sources (`.cpp`), génération de tous les objets (`.o`/`.obj`) et création des bibliothèques/exécutables. |
| **Construction complète à chaud** | **0.95ss** | Aucun fichier modifié | Tous les artefacts sont à jour. Le système de build vérifie les horodatages (*timestamps*) et ne relance aucune compilation. |
| **Construction d'un seul module** | **14.50s** | Modifié localement | Compilation isolée des fichiers d'un seul module (ex: `NKAudio`) sans recompiler le reste de l'arbre de dépendances. |
| **Modification d'un fichier source (`.cpp`)** | **3.m.1 s** | 1 fichier `.cpp` modifié | Seul le fichier `.cpp` modifié est recompilé en `.o`/`.obj`, suivi de l'étape de liaison (*link*) de son module. |
| **Modification d'un en-tête (`.hpp`)** | **16.06 s** | 1 fichier `.hpp` modifié | Recompilation de **tous** les fichiers `.cpp` qui incluent directement ou indirectement cet en-tête. |

---

## 2. Analyse Approfondie : Impact de la Modification d'un En-tête (`.hpp`)

Le cas de la modification d'un fichier en-tête est le plus lourd et le plus instructif en C/C++. Il illustre la différence fondamentale entre la modification d'un fichier source et d'un fichier d'en-tête dans la chaîne de compilation.

### Pourquoi ce temps est-il beaucoup plus élevé ?

1. **L'Unité de Translation (Translation Unit) :**
   * Un compilateur C++ ne compile pas un fichier `.hpp` seul. Il compile des unités de translation (`.cpp`).
   * Lors de la phase de prétraitement , la directive `#include "Header.hpp"` **copie-colle** le contenu textuel de l'en-tête directement dans le fichier `.cpp`.

2. **Propagation en Cascade  :**
   * Si `AudioEngine.hpp` est inclus dans 15 fichiers `.cpp` différents du projet (ou inclus indirectement via d'autres en-têtes), la moindre modification dans `AudioEngine.hpp` invalide le cache de ces 15 unités de translation.
   * Le système de build (via la détection des dépendances) est forcé de relancer la compilation de ces 15 fichiers `.cpp`, même si une seule ligne de commentaire a été modifiée dans le `.hpp`.

3. **Même impact qu'un build partiel massif :**
   * Contrairement à un fichier `.cpp` dont la modification n'impacte que lui-même (temps très court : 1.1s), la modification d'un en-tête central se rapproche des performances d'un build à froid sur la portion du code concernée (18.7s).

---

## 3. Bonnes Pratiques pour Minimiser l'Impact des `.hpp`

* **Déclarations anticipées (*Forward Declarations*) :** Utiliser `class MonModule;` au lieu de `#include "MonModule.hpp"` dans les en-têtes chaque fois que possible (quand on utilise uniquement des pointeurs ou des références).
* **Idiome PImpl (*Pointer to Implementation*) :** Déplacer les membres privés et les dépendances internes dans une classe d'implémentation masquée dans le fichier `.cpp`.
* **En-têtes précompilés (*PCH - Precompiled Headers*) :** Précompiler les en-têtes lourds de bibliothèques tierces pour éviter de les réanalyser systématiquement.

* **RESULTAT RESORTISSANTS**
Les resultats pour la construction a chaud ont ete prelever dans l'exercice 7  avec mon projet NewProjet
un seul module `NKCamera`
```bash

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCamera                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: NkCameraSystem.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKCamera.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.93s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  18/18
Time:           2m54.0s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
fichier .h  `NKContainers`
```bash
════════════════════╗
║  Project: NKContainers                                                     Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 42 source file(s)
✓   [1/42] Compiled: NkBTree.cpp
✓   [2/42] Compiled: NkHashMap.cpp
✓   [3/42] Compiled: NkBinaryTree.cpp
✓   [4/42] Compiled: NkPriorityQueue.cpp
✓   [5/42] Compiled: NkMap.cpp
✓   [6/42] Compiled: NkSet.cpp
✓   [7/42] Compiled: NkUnorderedMap.cpp
✓   [8/42] Compiled: NkTrie.cpp
✓   [9/42] Compiled: NkArray.cpp
✓   [10/42] Compiled: NkUnorderedSet.cpp
✓   [11/42] Compiled: NkPool.cpp
✓   [12/42] Compiled: NkBind.cpp
✓   [13/42] Compiled: NkRingBuffer.cpp
✓   [14/42] Compiled: NkFunction.cpp
✓   [15/42] Compiled: NkTuple.cpp
✓   [16/42] Compiled: NkPair.cpp
✓   [17/42] Compiled: NkFunctional.cpp
✓   [18/42] Compiled: NkInitializerList.cpp
✓   [19/42] Compiled: NkIterator.cpp
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
✓   [37/42] Compiled: NkStringUtils.cpp
✓   [38/42] Compiled: NkOptional.cpp
✓   [39/42] Compiled: NkStringView.cpp
✓   [40/42] Compiled: NkVariant.cpp
✓   [41/42] Compiled: NkResult.cpp
✓   [42/42] Compiled: NkSpan.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 14.50s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
```
et le .cpp de NKMath


```markdown
# Fiche d'Analyse Build — `NKCivilization.jenga`

> **Projet :** Module `NKCivilization`  
> **Architecture :** Nkentseu /Kernel Layer 
> **Langage :** C++17  

---

## Contexte Architectural 

```cpp
/*
 NKCivilization — Micro-monde vivant sur substrat NKECS.
 - Entités : Agents (agent::NkAgent) représentés par (NkCivAgentRef + NkCivPosition).
 - Animation : ecs::NkSystem (NkCivAgentSystem) agissant sur une grille partagée (NkCivGridState).
 - Mécaniques : Collisions + compétition sur ressources consommables ("premier arrivé").
 - Dépendances : Repose sur NKECS et NKAgent. Aucune remontée vers Engine/Noge.
*/

```

---

## Annotation Ligne par Ligne  du Code DSL Jenga qui contient du Python , avec des commentaires explicites pour ma  comprehension de chaque ligne et les interrogation relatives  telle que mentionner dans l'enonce de l'exercice

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Jenga import *
from jengaconfig import *

with project("NKCivilization"):
    # =========================================================================
    # 1. TYPE
    # =========================================================================

    language("C++")      # Spécifie le langage principal de compilation.
    cppdialect("C++17")  # Spécifie la norme/dialecte C++.
    location(".")        # Racines du projet définies sur le répertoire courant.

    # ? TYPE : Le livrable exact produit (bibliothèque statique .lib/.a ou dynamique .dll/.so) est-il déduit implicitement par Jenga selon le contexte global de la solution ?

    # =========================================================================
    # 2. DÉPENDANCES
    # =========================================================================

    nkentseudependson(
        [
            "NKCore", "NKPlatform", "NKMemory", "NKContainers", "NKMath", 
            "NKLogger", "NKTensor", "NKRL", "NKAgent", "NKECS"
        ],
        selfexport="NKCivilization",                
          # Auto-exportation sous ce nom.
        extra_includes=["src", "%{wks.location}/Externals"], # Dossiers d'en-têtes exposés.
    )
    # ? DÉPENDANCES : Existe-t-il un ordre de linkage strict entre NKTensor, NKRL et NKECS ?
    # ? DÉPENDANCES : Pourquoi Externals est-il en extra_includes ? Y a-t-il une dépendance tierce  qui est cachée  ?

    # =========================================================================
    # 3. SOURCES
    # =========================================================================

    files([
        "src/NKCivilization/**.cpp", # Inclus récursivement tous les fichiers d'implémentation
        "src/NKCivilization/**.h",   # Inclus récursivement tous les fichiers d'en-tête
    ])
    # SOURCES : Les fichiers d'en-tête situés à la racine de src/ (hors sous-dossier NKCivilization) sont-ils scannés automatiquement via le masque extra_includes=["src"] ?

    # Définition des répertoires de sortie (Objets & Bibliothèques)
    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

    # =========================================================================
    # 4. FILTRES (Plateformes, Toolchains, Options de Compilation)
    # =========================================================================


    # Surcharge des répertoires pour UWP (Universal Windows Platform)
    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    # Sélection des Toolchains selon l'OS
        with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS) # TC_WINDOWS pointe-t-il sur MSVC (cl.exe) ou Clang-CL ?

    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang") #  Pourquoi utiliser la toolchain Xbox pour les builds UWP standard ?

    with filter("system:macOS"):
        usetoolchain("clang-native")

    with filter("system:Android"):
        usetoolchain("android-ndk")

    with filter("system:HarmonyOS"):
        usetoolchain("ohos-ndk")

    with filter("system:Web"):
        usetoolchain("emscripten") # Compilation vers WebAssembly (Wasm)

    with filter("system:XboxSeries || system:XboxOne"):
        usetoolchain("xbox-clang")

    # Configuration des profils de build (Debug vs Release)
    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG"])
        optimize("Off")
        symbols(True)

    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed") # Quel niveau d'optimisation effectif cela traduit-il ?
        symbols(False)

    # =========================================================================
    # 5. TESTS
    # =========================================================================

   
    with filter("(system:Linux || system:macOS || (system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne)) && !system:Android && !system:iOS || system:Web"):
        with test():
            testfiles(["tests/**.cpp"])
            # TESTS : Quel framework de test est utilisé  ici?
            # TESTS : Comment les tests Web (Emscripten) sont-ils exécutés (via Node.js headless ?) ?

```



> ** Dans le chapitre 1 : ** j'ai eu de nombreuses reponses aux questions soulignes dans le code , et je continuerais de l'exploirer progressivement pour completer mes interrogations. Les questions donc je voudrais reellement des reponses direct de mon encadreur sont celles avec l'intitule `Questions pour mieux comprendre`


---

##  Questions : Synthèse par Catégorie & Points d'Interrogation 

### 1. TYPE

* **Langage & Norme :** C++ (C++17).
* **Emplacement :** Racines du projet (`.`).
* **Interrogation  :**
*  Le build génère-t-il une bibliothèque statique (`.a`/`.lib`) ou dynamique (`.so`/`.dll`) par défaut ?
*  Existe-t-il des macros d'export/import de symboles (ex: `NK_CIV_API`) dans le code pour la gestion DLL ?



### 2. SOURCES

* **Pattern d'inclusion :** `src/NKCivilization/**.cpp` et `src/NKCivilization/**.h`.
* **Inclusions supplémentaires :** Dossiers `src` et `Externals`.
* **Questionnement :**
* Pourquoi les sources sont-elles restreintes au sous-dossier `src/NKCivilization/` au lieu de tout `src/` ? 


### 3. DÉPENDANCES

* **Modules NK (Base) :** `NKCore`, `NKPlatform`, `NKMemory`, `NKContainers`, `NKMath`, `NKLogger`.
* **Modules NK (IA & ECS) :** `NKTensor`, `NKRL`, `NKAgent`, `NKECS`.
* **Incertitudes :**
* Quelles dépendances externes  se trouvent dans `%{wks.location}/Externals` et sont utilisees  par `NKCivilization` ?
*  Comment `NKRL` et `NKTensor` interagissent-ils au temps d'execution pendant la phase d'apprentissage des agents sur la grille ?



### 4. FILTRES

* **Multi-plateforme :** Windows, macOS, Android, HarmonyOS, Web (Emscripten), Xbox Series/One, UWP.
* **Configurations :** `Debug` (Symboles ON, Optimisation OFF) et `Release` (NDEBUG, Optimisation Speed).
* **Incomprehension:**
*  Pourquoi la toolchain `xbox-clang` est-elle reutilisée pour les cibles UWP ?
*  Les optimisations d'instructions SIMD (AVX2, Neon) sont-elles activées dans le filtre `Release` pour accélérer les calculs de grille ou d'IA ?



### 5. TESTS

* **Fichiers :** `tests/**.cpp`.
* **Plateformes autorisées :** Windows (Desktop), macOS, Linux, Web.
* **Plateformes exclues :** UWP, Xbox, Android, iOS.
* **Interrogation**
*  Les tests s'exécutent-ils à chaque build de développement ou uniquement via une commande dédiée ( celle de `jenga --test`) ?
*  Comment sont simulées les données de test (fixtures/grilles de départ) sans interface graphique ni dépendance vers la couche `Engine` ?



---

##  Question pour mieux comprendre (celles que j'aimerais vraiment savoir directement de mon encadreur)

1. **Architecture ECS / IA :**
> *"Comment la logique de décision de `NKAgent` (basée sur `NKRL`) s'interfere -t-elle concrètement avec les `NkSystem` du module `NKECS` sans créer de dépendance  circulaire    ?"*


2. **Support Web & Tests :**
> *"Comment les tests unitaires sous Emscripten (`system:Web`) sont-ils executes lors de l'intégration continue (comme avec  via Node.js) je comprend pas bien  ?"*


3. **Toolchains & Consoles :**
> *"Pourquoi la configuration UWP partage-t-elle la même toolchain (`xbox-clang`) que la console Xbox ?"*

> *"quel est l'impact direct du dossier AI sur  les module de Nkentseu (je vois des fichiers .png et .mp4 qui s'affiche par ligne de couleur)" *



```

```
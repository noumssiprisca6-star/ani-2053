
---

### Fichier : `c1-exo6_reponse.md`

```markdown
# Compte Rendu d'Expérimentation : Gestion des Dépendances Jenga    (`dependson` vs `links`)  Erruer de dependance

## 📂 Structure et Code du Projet choisit pour creer des dependances

```text
NewProjet/
├── NewProjet.jenga
├── c1-exo6_reponse.md
├── main.cpp
├── Affichage/
│   ├── Affiche.jenga
│   ├── Affichage.h
│   └── Affichage.cpp
└── Calculateur/
    ├── Calcul.jenga
    ├── Calcul.h
    └── Calcul.cpp

```


---

### 1. Code des Fichiers C++

####  Module Calcul (`Calculateur/`)

`Calculateur/Calcul.h`

```h
#ifndef CALCUL_H
#define CALCUL_H

class Calcul {
public:
void Bonjour();
int additionner(int a, int b);
};
#endif


```

`Calculateur/Calcul.cpp`


```cpp
#include "Calcul.h"
#include<iostream>

int Calcul::additionner(int a, int b) {
    return a + b;
}
    void Calcul::Bonjour(){
   std::cout<<"Bonjour depuis Calcul.cpp"<<std::endl;
    }

```

`Calculateur/Calcul.jenga`

```py
with project ("Calcul"):
    staticlib()
    cppdialect("c++17")
    cppcompiler("clang++")
    language("c++")
    files(["./**.cpp"])
    includedirs(["."])
   

```

####  Module Affichage (`Affichage/`)

`Affichage/Affichage.h`

```h
#ifndef SALUT_H
#define SALUT_H

class Affichage {
public:
    void AfficherResultat(int valeur);
    void Tester();
};

#endif

```

`Affichage/Affichage.cpp`

```cpp
#include "Affiche.h"
#include"../Calculateur/Calcul.h"
#include <iostream>

void Affichage::AfficherResultat(int valeur) {
    Calcul calculer ;
    int res = calculer.additionner(valeur,0);
    std::cout << "Le resultat du calcul est : " << valeur << std::endl;
}
 void Affichage::Tester(){
    Calcul calculer;
  calculer. Bonjour();
 }

```

`Affichage/Affichage.jenga`


```py

with project ("afficher") :
    staticlib()
    cppdialect("c++17")
    cppcompiler("clang++")
    language("c++")
    files(["./**.cpp"])
    includedirs(["../Calculateur"]) 
    dependson(["Calcul"])           
    links(["Calcul"])               

```

####  Module main(`NewProjet`)

`NewProjet/main.cpp`


```cpp

#include<iostream>
#include"Calculateur/Calcul.h"
#include"Affichage/Affiche.h"

int main(){

    Calcul op;
    Affichage ecran ;
    Affichage test ;
    
    int resultat = op.additionner(15,25);
    ecran.AfficherResultat(resultat);
    test.Tester();
    return 0;
}

```

---

### 2. Configuration du Build (`NewProjet.jenga`)

```python
import os
from Jenga import *
from Jenga.GlobalToolchains import RegisterJengaGlobalToolchains

with workspace("compile"):
    RegisterJengaGlobalToolchains()
    cppdialect("c++17")
    configurations(["Debug", "Release"])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64, TargetArch.ARM64])
    startproject("NewProject")

    with include("Affichage/Affiche.jenga"):
        pass
    with include("Calculateur/Calcul.jenga"):
        pass

    with project("NewProject"):
        consoleapp()
        cppdialect("c++17")
        cppcompiler("clang++")
        language("c++")
        includedirs(["."])
        files(["./**.cpp"])
        dependson(["Calcul", "afficher"])

```

---

## Expérimentations et Résultats

###  Test 1 : Retrait de `dependson`

#### Manipulation

Suppression de la ligne `dependson(["Calcul", "afficher"])` dans `affiche.jenga`.

#### Commandes d'exécution

```bash
jenga clean
jenga build

```

#### Message / Erreur obtenu(e)

```text
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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  NewProject.exe
     C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-01\exo6-les_deux_erreurs_de_dependance\NewProjet\Build\Bin\Debug-Windows\NewProject\NewProject.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Le resultat du calcul est : 40
Bonjour depuis Calcul.cpp

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.19s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-01\exo6-les_deux_erreurs_de_dependance\NewProjet> jenga build

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

Build Order (3 projects):
  1. Calcul [STATIC_LIB] → 
  2. afficher [STATIC_LIB] → 
  3. NewProject [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Calcul                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Calcul.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\Calcul\Calcul.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.09s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: afficher                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Affiche.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\afficher\afficher.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.11s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NewProject                                                      Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)
✓   [1/3] Compiled: Affiche.cpp
✓   [2/3] Compiled: Calcul.cpp
✓   [3/3] Compiled: main.cpp
ℹ Linking...
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:/msys64/ucrt64/bin/ld: cannot find -lCalcul: No such file or directory                     ║
║ C:/msys64/ucrt64/bin/ld: cannot find -lafficher: No such file or directory                   ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocation)            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\NewProject\NewProject.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 1.90s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  2/3
Failed:         1
Errors:         1
Time:           4.11s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ NewProject

```

> **Analyse du message :** Sans `dependson`, Jenga n'établit aucun ordre de compilation  et ne transmet pas les bibliothèques `Calcul` et `afficher` au linker. La compilation du code source réussit, mais l'édition de liens échoue car les symboles des fonctions appelées dans `main.cpp` n'existent pas dans l'exécutable.

---

### 2️Test 2 : Remise de `dependson` et Retrait de `links`

#### Manipulation

Réintégration de `dependson(["Calcul", "afficher"])` et suppression de toute directive `links(...)` éventuelle.

#### Commandes d'exécution

```bash
jenga clean
jenga build

```

#### Message && Comportement obtenu

```text
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

Build Order (3 projects):
  1. Calcul [STATIC_LIB] → 
  2. afficher [STATIC_LIB] (depends: Calcul) → 
  3. NewProject [CONSOLE_APP] (depends: Calcul, afficher)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Calcul                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Calcul.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\Calcul\Calcul.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.78s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: afficher                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Affiche.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\afficher\afficher.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.69s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NewProject                                                      Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)
✓   [1/3] Compiled: Affiche.cpp
✓   [2/3] Compiled: Calcul.cpp
✓   [3/3] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\NewProject\NewProject.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.89s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  3/3
Time:           2.36s
Status:         ✓ SUCCESS
═══════════════════════════════════════════════════════════════════════════════
```

> **Analyse du message :** Le build se déroule sans erreur. Les cibles `Calcul` et `afficher` sont automatiquement compilées **avant** `NewProject`, puis liées implicitement par Jenga. Ici je pense que cela pouurait decouler du fait qu'il y'ait une abscence de librairies dans mon projet par consequent l'abscence de links ici ou non permet toujours une inclusion des bibliotheques `Calcul` et `afficher`

>**Plusieurs essaies  avec des projets possedent des librairies:** j'ai fait des test de retrait des links dans les perojets de Nkentseu ce situant dans le dossiers applications  . Par exemple , le projet  NKSComputeCheck , dans son .jenga on peu constater qu'il est directement relier a Nkentseudependson par consequent , meme en abscence de links vers des bibliotheques specifiques , la compilation s'effectue normalement. Apres avoir essayer avec le projet `NkCamera` ,`NKSLCoompiter`,`NKAudio` et `NKData`. la commande jenga build s'effectuait sans erreur meme apres aqe j'ai eu a hote les links


---

##  Synthèse : Ce qui distingue les deux messages

| Critère | Retrait de `dependson` | Retrait de `links` (avec `dependson`) 


| **Résultat du Build** | **Échec** à l'édition de liens (*Linker Error*). 
| **Réussite** de la compilation (*Build Success*). 
| **Ordre de Construction** | Ignoré (`NewProject` se compile isolément).
| Strict (`Calcul` et `afficher` sont compilés en premier). 
| **Résolution des Symboles** | `LNK2019`: Symboles indéfinis. | Symboles résolus automatiquement par propagation. |

### Justification 

#### D'apres mes remarques 

1. **Rôle de `dependson` :** Définit la **dépendance temporelle** dans le graphe de compilation . Il indique à Jenga la séquence exacte de génération des cibles.
2. **Rôle de `links` vs `dependson` :** Dans les systèmes modernes de méta-build comme Jenga, `dependson` inclut déjà la transmission des dépendances de liaison (*Link Dependencies*). Par conséquent, retirer la directive explicite `links` n'invalide pas l'édition de liens si `dependson` est présent.

```

---


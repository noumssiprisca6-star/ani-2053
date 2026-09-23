# Exercice : Fenêtre graphique minimale et fermeture propre (NkEngine)

## 1. Énoncé de l'exercice

> *« Écrivez le plus petit programme qui ouvre une fenêtre, la garde ouverte, et se termine proprement. Comptez ses lignes, et retrouvez chacune dans le chapitre. »*

>**Creation du Workspace et configuration du exo1-la_fenetre_nue.jenga*

---

## 2. Code source minimal

```cpp
#include "NKWindow/NKWindow.h" //ligne 1
#include "NKWindow/NKMain.h" //ligne 2

using namespace nkentseu ; //ligne 3

int nkmain(const NkEntryState &state) { //ligne 4
    NkWindowConfig cfg; //ligne 5
    cfg.title  = "Ma fenetre"; //ligne6
    cfg.width  = 1280; //ligne 7
    cfg.height = 720; // ligne 8

    NkWindow window(cfg); //ligne 9
    if (!window.IsOpen()) { // ligne 10
        logger.Error(" La  creation fenetre echouee"); //ligne 11
        return -1; //ligne 12
    } //ligne 13
    while (window.IsOpen()) { /* les evenements arrivent ici */ } //ligne 14
    return 0; //ligne 15
} //ligne 16

```

---

## 3. Décompte physique complet (16 lignes) et lien avec le chapitre celui que j'ai consulte sur la plateforme 

Le programme  comporte **16 lignes physiques de code**. 

| N° | Ligne de code | Rôle & Correspondance dans le chapitre |
| --- | --- | --- |
| **1** | `#include "NKWindow/NKWindow.h"` | **Gestion des fenêtres :** Inclus la classe `NkWindow` et la structure `NkWindowConfig`. |
| **2** | `#include "NKWindow/NKMain.h"` | **Point d'entrée du moteur :** Inclus l'infrastructure nécessaire pour surcharger le `main` standard. |
| **3** | `using namespace nkentseu ;` | **Espace de nommage :** Évite de préfixer toutes les classes par `nkentseu::`. |
| **4** | `int nkmain(const NkEntryState &state) {` | **Point d'entrée principal :** Définit la fonction d'entrée `nkmain` appelée par le moteur. |
| **5** | `    NkWindowConfig cfg;` | **Configuration :** Instancie la structure de configuration de la fenêtre avec ses valeurs par défaut. |
| **6** | `    cfg.title  = "Ma fenetre";` | **Configuration :** Définit le titre de la fenêtre. |
| **7** | `    cfg.width  = 1280;` | **Configuration :** Spécifie la largeur de la fenêtre (1280 pixels). |
| **8** | `    cfg.height = 720;` | **Configuration :** Spécifie la hauteur de la fenêtre (720 pixels). |
| **9** | `    NkWindow window(cfg);` | **Cycle de vie :** Instancie la fenêtre et initialise la surface d'affichage auprès de l'OS (RAII). |
| **10** | `    if (!window.IsOpen()) {` | **Gestion des erreurs :** Vérifie que la création et le contexte d'affichage ont réussi. |
| **11** | `        logger.Error(" La  creation fenetre echouee");` | **Système de Log :** Écrit un message d'erreur dans le journal en cas d'échec d'ouverture. |
| **12** | `        return -1;` | **Gestion des erreurs :** Arrête immédiatement le programme en renvoyant un code d'erreur (`-1`). |
| **13** | `    }` | **Syntaxe C++ :** Clôture le bloc conditionnel de vérification d'erreur (`if`). |
| **14** | `    while (window.IsOpen()) { /* les evenements arrivent ici */ }` | **Boucle principale (Game Loop) :** Bloque la fin de la fonction et maintient la fenêtre ouverte tant qu'elle est valide. |
| **15** | `    return 0;` | **Terminaison propre :** Libère les ressources restantes et renvoie le code de succès (`0`) à l'OS. |
| **16** | `}` | **Syntaxe C++ :** Marque la fin du bloc d'instructions de la fonction principale `nkmain`. |

---

## 4. Synthèse des critères d'évaluation

* **Ouvre une fenêtre :** Déclaré à la **ligne 9** (`NkWindow window(cfg);`).
* **La garde ouverte :** Assuré par la boucle `while` à la **ligne 14** (`window.IsOpen()`).
* **Se termine proprement :** Géré par le test de la **ligne 10**, le retour d'erreur à la **ligne 12** (`return -1;`) et le retour nominal à la **ligne 15** (`return 0;`).
* **Décompte des lignes :**
* **16 lignes physiques** au total dans le fichier source.
* **10 instructions exécutables** à l'intérieur de la fonction `nkmain` (lignes 5, 6, 7, 8, 9, 10, 11, 12, 14, 15).


>**l'execution du programme c'est bien deroule meme comme apres ouverture de la fenetre , la fermeture provoque quelque petit bug mais qui s'extompe rapidement**

>** Le resultat de l'execution est dans le fichier `Capture`se trouvant dans le dossier`exo1-la_fenetre_nue`
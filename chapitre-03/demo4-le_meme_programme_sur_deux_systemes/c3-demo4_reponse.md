
#  Comparaison d'exécution multi-plateforme (Windows vs Linux)

>**le test sur l'envirionnement   Linux fut fait sur la machine d'un ami `(Nyeck)`, les configurations pour mon environnement de linux ont  echouer de nombreuses reprises chez moi
---

## 2. Code C++ utilisé

Le code suivant a été compilé et exécuté sur les deux environnements  , a chaque fois il a fallu changer la configuration du .jenga avec le ` targetoses([TargetOS.LINUX])` targetoses([TargetOS.WINDOW]) pour les plateformes en questions

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("La creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen()) { 
        while (NkEvent* ev = NkEvents().PollEvent()) {

            // Fermeture de la fenêtre
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
        }
    }
    return 0;
}

```

---

## 3. Relevé des changements observés entre Windows et Linux



### A. Rendu Visuel et Gestionnaires de Fenêtres 

* **Bordures et Décorations :**
* **Windows :** Utilise l'API Win32  avec la barre de titre standard (boutons Réduire, Agrandir, Fermer en haut à droite, coins arrondis sous Windows 11).
* **Linux :** Le rendu dépend du gestionnaire de fenêtres/bureau utilisé . Les boutons de contrôle sont plus petit que sur window et opaques , le titre de la fenetre est situe au milieu


* **Les bordures:**les bordures sur linux sont plus epaissent  que sur windowlorsque la fenetre perd le focus sur linux , c'est bordures deviennent grises

### B. Gestion des Événements et Entrées/Sorties

* **Positionnement initial de la fenêtre :**
* **Windows :** Centré ou positionné par défaut selon le comportement classique de Win32.
* **Linux :** la fenetre apparait au centre 





### C. Console et Logs 

* **Format des chemins et dossiers :**
* Les messages système affichent des séparateurs `\` sous Windows et `/` sous Linux.


* **Encodage et Couleurs :**
* Le terminal Linux gère nativement les séquences de couleurs ANSI d'affichage des logs .
* Sous Windows, l'affichage dans l'invite de commande  ou PowerShell utilise l'encodage console Windows.



### D. Binaire et Dépendances

* **Format du binaire :**
* **Windows :** Génère un fichier exécutable Portable Executable (`.exe`).
* **Linux :** Génère un fichier sans extention




---

## 4. Tableau comparatif synthétique

| Élément d'observation | Windows | Linux |
| --- | --- | --- |
| **Format du binaire** | Executable (`.exe`) | sans extension|
| **Gestionnaire graphique** | Desktop Window Manager (DWM) | X11 / Wayland |
| **Style de la fenêtre** | Style natif Win32 / Windows 11 | Style selon le thème GTK / Qt |
| **Gestion console / logs** | Console Win32 / PowerShell | terminal WSL |
| **Séparateur de fichier** | `\` (Antislash) | `/` (Slash) |

---

## 5. Conclusion

Même si le code source C++ reste identique, le comportement final (apparence de la fenêtre, intégration au bureau, logs et format de binaire) est entièrement pris en charge par le système d'exploitation sous-jacent.

L'architecture de **NKentseu** permet d'isoler le développeur de ces différences en fournissant une interface uniforme (`NkWindow`, `NkEvents`), assurant ainsi la **portabilité** du code entre Windows et Linux.

>** ceux sont toutes les differences que jai pu observe en utilisant la machine de `MAEL` pour le test su linux et ma machine pour le test sur window
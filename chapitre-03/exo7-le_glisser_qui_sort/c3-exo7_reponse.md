# Capture de la Souris lors d'un Glisser-Déposer 


## 1. Explication de la Consigne et des Concepts

L'objectif de cet exercice est de comprendre le comportement de la capture de la souris  lors d'une action de **cliquer-glisser** (*drag*) qui commence dans la fenêtre et se termine à l'extérieur.

* **Sans capture :** La fenêtre ne reçoit les événements de la souris que tant que le curseur reste à l'intérieur de ses limites.
* **Avec capture :** La fenêtre s'approprie le flux d'événements de la souris. Elle continue de recevoir la position du curseur et l'état des boutons, même si le curseur sort de la fenêtre.

---

## 2. Déroulement de l'Execution

### Étape 1 : Le Glisser-Déposer SANS Capture

1. **Action :**
 - Clique à l'intérieur de la fenêtre
 -  maintient du bouton enfoncé
 - déplacement du curseur vers l'extérieur de la fenêtre.
2. **Relâchement :**  relâchement du  bouton de la souris à l'extérieur de la fenêtre.

#### Observation du comportement :
* Tant que le curseur est dans la fenêtre, le suivi du mouvement fonctionne.
* **Dès que le curseur franchit la bordure :** La fenêtre arrête de recevoir les événements de mouvement (`NkMouseMoveEvent`).
* **Lors du relâchement à l'extérieur :** La fenêtre ne reçoit pas l'événement de relâchement (`NkMouseButtonReleasedEvent`).

---
## Resultat 
```bash

[2026-09-25 17:02:16.706] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (785; 331)
[2026-09-25 17:02:16.713] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (767; 279)
[2026-09-25 17:02:16.993] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (743; 82)
[2026-09-25 17:02:17.002] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (750; 26)
[2026-09-25 17:02:18.762] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (780; 11)
[2026-09-25 17:02:18.772] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (783; 55)
[2026-09-25 17:02:18.782] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (790; 100)
[2026-09-25 17:02:20.532] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (778; 380)
[2026-09-25 17:02:20.539] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (707; 410)
[2026-09-25 17:02:20.549] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (589; 467)
[2026-09-25 17:02:20.559] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (475; 528)
[2026-09-25 17:02:20.568] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (410; 564)
[2026-09-25 17:02:20.579] [INF] [default] [c3-exo7_main.cpp:25 in nkmain] -> mouse (357; 597)
```

### Étape 2 : Le Glisser-Déposer AVEC Capture

1. **Action :** 
- clique à l'intérieur de la fenêtre. Le programme active immédiatement la capture de la souris (`NkMouseButtonPressEvent` , ` window.CaptureMouse(true);` ).
2. **Déplacement :** 
- glisser le curseur en dehors de la fenêtre tout en maintenant le bouton enfoncé.
3. **Relâchement :**  
- relâchement du  bouton de la souris à l'extérieur de la fenêtre. Le programme libère la capture (`NkMouseButtonReleaseEvent` ,` window.CaptureMouse(false);`).

## Resultat

```bash

[2026-09-25 16:45:02.464] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (761; -6)
[2026-09-25 16:45:02.474] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (767; -16)
[2026-09-25 16:45:02.485] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (775; -25)
[2026-09-25 16:45:02.493] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (780; -32)
[2026-09-25 16:45:02.716] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (794; -31)
[2026-09-25 16:45:02.728] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (793; -30)
[2026-09-25 16:45:02.736] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (792; -29)
[2026-09-25 16:45:02.746] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (792; -28)
[2026-09-25 16:45:02.756] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (792; -27)
[2026-09-25 16:45:02.778] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (791; -27)
[2026-09-25 16:45:02.806] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (791; -26)
[2026-09-25 16:45:02.826] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (790; -26)
[2026-09-25 16:45:02.846] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (790; -25)
[2026-09-25 16:45:02.863] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (789; -24)
[2026-09-25 16:45:02.871] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (788; -23)
[2026-09-25 16:45:02.878] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (787; -22)
[2026-09-25 16:45:02.887] [INF] [default] [c3-exo7_main.cpp:30 in nkmain] -> mouse (786; -20)

```
 


#### Observation du comportement :

* La fenêtre continue de recevoir toutes les coordonnées $X, Y$ du curseur, même en dehors de ses limites.
* L'événement de relâchement du bouton est parfaitement intercepté par la fenêtre, quel que soit l'endroit où se trouve la souris sur l'écran.

---

## 3. Description de la Différence du Point de Vue de l'Utilisateur

. **La différence :**
* **Sans capture :** Dès que le curseur dépasse le bord de la fenêtre, le programme "perd" le suivi. Si vous relâchez le bouton à l'extérieur, le programme ne le sait pas et pense que vous maintenez toujours le clic.
* **Avec capture :** Le programme continue de suivre le déplacement du curseur et détecte parfaitement le moment exact où on relâchez le bouton, même si on est  à l'autre bout de l'écran.



| Critère | Sans Capture | Avec Capture |
| :--- | :--- | :--- |
| **Continuité du mouvement** | LJJe suivi s'arrête brusquement dès que l'on sort de la fenêtre. | Le suivi est fluide et continu, même à l'extérieur de la fenêtre. |
| **Relâchement du clic** | **Sensation de "blocage" :** Le programme reste bloqué en mode "glisser" car il n'a pas vu que l'utilisateur a relâché le bouton. | **Comportement naturel :** Le glisser-déposer se termine normalement dès que le bouton est relâché. |
| **Expérience globale** | Frustrante et bugguée pour un composant d'interface (ex: barre de défilement, slider). | Conforme aux attentes de l'utilisateur sur un système d'exploitation moderne. |

---

## 4. Code C++ illustrer dans `c3-exo7_main.cpp`

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state)
{
    NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen())
    {
 
        while (NkEvent *ev = NkEvents().PollEvent()){
            /*Gestion de la  capture lorsdes evenement de la souris */

            if (auto *press = ev->As<NkMouseButtonPressEvent>())
            {
                /*active la capture lors du clic*/
                if (press->IsLeft()) {
                  window.CaptureMouse(true);
                }
           
            }
            /*relache la capture au moment ou le bouton est relâché */

            if(auto *relache = ev->As<NkMouseButtonReleaseEvent>()){
                window.CaptureMouse(false);
            }

            if (auto *move = ev->As<NkMouseMoveEvent>()){
                logger.Info("mouse ({0}; {1})",move->GetX() , move->GetY());
            }
            /*evenement pour fermer la fenetre avec le bouton en forme de croix */
            if(ev->Is<NkWindowCloseEvent>()){
                window.Close();
            }
            /*evenement pour fermer la fenetre avec le bouton k */
            if(auto *q = ev->As<NkKeyPressEvent>() ){

                if(q->GetKey() == NkKey::NK_K){
                    window.Close();
                }
            }

        }
    }

  return 0;
  
}
```
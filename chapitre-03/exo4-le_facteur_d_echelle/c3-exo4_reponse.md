#  Taille de fenêtre, Cible de rendu et Facteur d'échelle


## 1. Définition des Variables Observées

1. **Taille de la fenêtre (Logique) :** Dimensions perçues par le système d'exploitation (pixels logiques).
2. **Cible de rendu (Physique) :** Nombre réel de pixels traités par le moteur graphique/GPU (`Taille Fenêtre × Facteur d'échelle`).
3. **Facteur d'échelle :** Ratio appliqué par le système (`1.0` pour 100%, `1.25` pour 125%).

---

## 2. Implémentation C++ (`c3-exo4_main.cpp`)

Le code suivant initialise la fenêtre et affiche les trois valeurs dans le terminal :

```cpp

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La creation fenetre echouee");
        return -1;
    }
     
    logger.Info("Taille rendu par la fenetre : {0}", window.GetSize());
    logger.Info( "La taille rendu par la cible de rendu : {0} x {1}", window.GetSize().x ,window.GetSize().y);
    logger.Info("le facteur d'echelle: {0}", window.GetDpiScale());
    

    while (window.IsOpen()) {
        while (NkEvent *ev = NkEvents().PollEvent()){
            if(ev->Is<NkWindowCloseEvent>()){
             window.Close();
            }
        }
    }
    return 0;
}

```

---

## 3. Relevé des Mesures Côte à Côte

### Test 1 :  Facteur d'Échelle  afficher  (100%)

```
[2026-09-25 18:48:09.448] [INF] [default] [c3-exo4_main.cpp:19 in nkmain] -> Taille rendu par la fenetre : (800, 600)
[2026-09-25 18:48:09.453] [INF] [default] [c3-exo4_main.cpp:20 in nkmain] -> La taille rendu par la cible de rendu : 800 x 600
[2026-09-25 18:48:09.453] [INF] [default] [c3-exo4_main.cpp:21 in nkmain] -> le facteur d'echelle: 1
```

### Test 2 : Échelle modifiée  a partir des parametre de mon ordinateur au niveau de la mise a l'echelle (125%)
 
```

[2026-09-25 18:55:59.368] [INF] [default] [c3-exo4_main.cpp:19 in nkmain] -> Taille rendu par la fenetre : (798, 592)
[2026-09-25 18:55:59.369] [INF] [default] [c3-exo4_main.cpp:20 in nkmain] -> La taille rendu par la cible de rendu : 798 x 592
[2026-09-25 18:55:59.369] [INF] [default] [c3-exo4_main.cpp:21 in nkmain] -> le facteur d'echelle: 1.25

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
---



## 5. Tableau Récapitulatif des Mesures

| Test | Taille Fenêtre (Logique) | Facteur d'Échelle  | Cible de Rendu (Physique) |
| --- | --- | --- | --- |
| **Écran standard (100%)** | `800 x 600` | `1.0` | `800 x 600` |
| **Écran zoomé (150%)** | `800 x 600` | `1.25` | `798 x 592` |

---

## 4. Analyse des Résultats

* **Relation mathématique :**

$$\text{Cible de Rendu} = \text{Taille Fenêtre} \times \text{Facteur d'Échelle}$$


* **Observation :**
Lorsque le facteur d'échelle est égal à `1.0`, chaque pixel logique correspond exactement à un pixel physique sur l'écran.
Lorsque le système utilise un facteur d'échelle supérieur (comme avec  `1.5` pour un affichage à 150%), la taille logique de la fenêtre reste constante (`800x600`), mais la carte graphique calcule une image plus grande (`798 x 592`) afin d'assurer un rendu visuel net et proportionné sur des écrans à haute densité.

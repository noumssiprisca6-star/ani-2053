#  Taille de fenêtre, Cible de rendu et Facteur d'échelle

## 1. Informations Générales
- **Date du test :** 24/08/2026
- **Système d'exploitation :** window
- **Résolution native de l'écran :** `800 x 600 px`

---

## 2. Définition des Variables Observées

1. **Taille de la fenêtre (Logique) :** Dimensions perçues par le système d'exploitation (pixels logiques).
2. **Cible de rendu (Physique) :** Nombre réel de pixels traités par le moteur graphique/GPU (`Taille Fenêtre × Facteur d'échelle`).
3. **Facteur d'échelle :** Ratio appliqué par le système (`1.0` pour 100%, `1.5` pour 150%).

---

## 3. Implémentation C++ (`c3-exo4_main.cpp`)

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
        logger.Error("La creation fenetre a echoue");
        return -1;
    }

    // 1. Taille logique de la fenetre
    int windowWidth  = cfg.width;
    int windowHeight = cfg.height;

    // 2. Facteur d'echelle
    float scale = 1.0f; 

    // 3. Calcul de la cible de rendu
    int renderWidth  = static_cast<int>(windowWidth * scale);
    int renderHeight = static_cast<int>(windowHeight * scale);

    // Affichage cote a cote
    std::cout << "==================================================" << std::endl;
    std::cout << "Taille Fenetre    : " << windowWidth << " x " << windowHeight << std::endl;
    std::cout << "Cible de Rendu    : " << renderWidth << " x " << renderHeight << std::endl;
    std::cout << "Facteur d'Echelle : " << scale << std::endl;
    std::cout << "==================================================" << std::endl;

    while (window.IsOpen()) { 
        /* gestion des evenements */ 
    }
    return 0;
}

```

---

## 4. Relevé des Mesures Côte à Côte

### Test 1 : Échelle standard (100%)
*Réglage système : 100%*
```
==================================================
Taille Fenetre    : 800 x 600
Cible de Rendu    : 800 x 600
Facteur d'Echelle : 1
==================================================
```
---

### Test 2 : Échelle modifiée 
*Réglage système : [1.5 f pour 150% ]*
```
==================================================
Taille Fenetre    : 800 x 600
Cible de Rendu    : 1200 x 900
Facteur d'Echelle : 1.5
==================================================
```
---



## 5. Tableau Récapitulatif des Mesures

| Test | Taille Fenêtre (Logique) | Facteur d'Échelle  | Cible de Rendu (Physique) |
| --- | --- | --- | --- |
| **Écran standard (100%)** | `800 x 600` | `1.0` | `800 x 600` |
| **Écran zoomé (150%)** | `800 x 600` | `1.5` | `1200 x 900` |

---

## 4. Analyse des Résultats

* **Relation mathématique :**

$$\text{Cible de Rendu} = \text{Taille Fenêtre} \times \text{Facteur d'Échelle}$$


* **Observation :**
Lorsque le facteur d'échelle est égal à `1.0`, chaque pixel logique correspond exactement à un pixel physique sur l'écran.
Lorsque le système utilise un facteur d'échelle supérieur (comme avec  `1.5` pour un affichage à 150%), la taille logique de la fenêtre reste constante (`800x600`), mais la carte graphique calcule une image plus grande (`1200x900`) afin d'assurer un rendu visuel net et proportionné sur des écrans à haute densité.

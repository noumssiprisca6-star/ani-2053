
#  Gestion dynamique et statique du Curseur

## 1. Implémentation du découpage en 7 zones

Pour changer la forme du curseur selon la zone survolée, l'événement de déplacement du curseur (`NkMouseMoveEvent`) a été configuré pour diviser la largeur de la fenêtre (`width`) en 7 intervalles égaux :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 2000; // Tests réalisés avec 800, 3, 2000
    cfg.height = 1000; // Tests réalisés avec 600, 2, 1000

    NkString NewTitle = cfg.title;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("La creation de la fenetre a echoue");
        return -1;
    }

    // ÉTAPE A : Positionnement/Définition initiale du curseur (Une seule fois au démarrage)
    window.SetCursor(NkWindow::NkCursorType::Hand);

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            
            // ÉTAPE B : Gestion de la fermeture de la fenêtre
            if (auto* closeEvent = ev->As<NkWindowCloseEvent>()) {
                window.Close();
            }

            // ÉTAPE C : Découpage dynamique de la fenêtre en 7 zones selon X
            if (auto* mouse = ev->As<NkMouseMoveEvent>()) {
                const float width = static_cast<float>(window.GetSize().width);
                const float x = static_cast<float>(mouse->GetX());

                if (width > 0.0f) {
                    if (x < width / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Arrow);
                    } 
                    else if (x < width * 2.0f / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Hand);
                    } 
                    else if (x < width * 3.0f / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Arrow);
                    } 
                    else if (x < width * 4.0f / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Hand);
                    } 
                    else if (x < width * 5.0f / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Arrow);
                    } 
                    else if (x < width * 6.0f / 7.0f) {
                        window.SetCursor(NkWindow::NkCursorType::Hand);
                    } 
                    else {
                        window.SetCursor(NkWindow::NkCursorType::Arrow);
                    }
                }
            }
        }
    }

    return 0;
}

```




## 2. Rôle et justification de chaque insertion de ligne  pour la segmentation de la fentre en 7 zones :

1. **Les Inclusions (`#include ...`) :**
* Donnent accès aux fonctions de gestion de la fenêtre et à la lecture des événements (fermeture de fenêtre, mouvements de souris).


2. **La Configuration (`cfg.width`, `cfg.height`) :**
* Définit la taille initiale de la fenêtre de test ($2000 \times 1000$).


3. **L'appel `window.SetCursor(...)` avant la boucle :**
* Répond à la consigne : **le curseur est posé une seule fois à l'initialisation du programme** (forme de main au départ).


4. **La Boucle `while (window.IsOpen())` :**
* Garde l'application ouverte et lit tous les événements en temps réel.


5. **Le Cast `ev->As<NkMouseMoveEvent>()` :**
* Détecte dès que la souris bouge et récupère sa position exacte sur l'axe horizontal $X$ via `mouse->GetX()`.


6. **Le Calcul des 7 Zones (`width / 7.0f`) :**
* Calcule la taille relative de chaque zone en divisant la largeur par 7. L'utilisation de nombres flottants (`float`) garantit un résultat précis, même si la fenêtre est très petite.

---

## 3. Description de l'Expérience : Poser le curseur une seule fois au démarrage

### Manipulation

Un unique appel à `window.SetCursor(NkWindow::NkCursorType::Hand);` est exécuté lors de la phase d'initialisation du programme, en dehors et avant la boucle principale de traitement d'événements.

### Ce qui se passe à l'écran

1. **Lancement :** Dès la création de la fenêtre, le curseur prend immédiatement la forme d'une **main**.
2. **Sans gestion d'événement :** Si on n'ajoute rien dans la boucle, le curseur reste bloqué en forme de main partout dans la fenêtre.
3. **Avec la boucle de mouvement :** Dès que la souris bouge d'un pixel, le gestionnaire `NkMouseMoveEvent` prend le relais et met à jour la forme du curseur selon la zone ($1$ à $7$) survolée.


---

## 4. Analyse des Résultats selon la Dimension de la Fenêtre

Pendant les tests, la configuration a été modifiée avec différentes valeurs de `width` et `height` pour évaluer le comportement du découpage :

| Dimensions ($W \times H$) | Largeur d'une zone ($\frac{W}{7}$) | Observations |
| --- | --- | --- |
| **$2000 \times 1000$** | $\approx 285 \text{ px}$ | **Très grand :** Les zones sont larges, les changements de curseur sont bien espacés. |
| **$800 \times 600$** | $\approx 114 \text{ px}$ | **Standard :** Découpage équilibré et transitions fluides. |
| **$3 \times 2$** | $\approx 0,42 \text{ px}$ | **Extrême :** Chaque zone fait moins d'un pixel. Le curseur change à la moindre micro-variation. L'utilisation de `float` évite tout plantage ou division par zéro. |

>** On observe donc un changement fluide de la forme du curseur a chaque passage d'une zone a une autre  .
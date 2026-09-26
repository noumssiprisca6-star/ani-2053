#  Multi-Fenêtres & Événements de Clic 

Ce programme crée deux fenêtres distinctes et affiche dans la console quelle fenêtre a reçu un clic de souris.

---

## 1. Code source : `c3-exo11_main.cpp`

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName = "MultiWindowClick";
    d.enableMultiWindow = true; // Active le support multi-fenêtres
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1. Création des deux fenêtres
    NkWindowConfig cfg1;
    cfg1.title  = "Fenetre 1";
    cfg1.width  = 500;
    cfg1.height = 400;
    cfg1.x      = 100;
    cfg1.y      = 100;

    NkWindowConfig cfg2;
    cfg2.title  = "Fenetre 2";
    cfg2.width  = 500;
    cfg2.height = 400;
    cfg2.x      = 650;
    cfg2.y      = 100;

    NkWindow window1(cfg1);
    NkWindow window2(cfg2);

    if (!window1.IsOpen() || !window2.IsOpen()) {
        logger.Error("Echec de la creation de l'une des fenetres.");
        return -1;
    }

    logger.Info("Fenetres ouvertes. Cliquez dans l'une d'elles !");

    // 2. Boucle principale tant qu'au moins une fenêtre est ouverte
    while (window1.IsOpen() || window2.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {

            // Gestion de la fermeture d'une fenêtre spécifique
            if (ev->Is<NkWindowCloseEvent>()) {
                if (ev->GetWindowId() == window1.GetId()) {
                    window1.Close();
                    logger.Info("Fenetre 1 fermee.");
                } else if (ev->GetWindowId() == window2.GetId()) {
                    window2.Close();
                    logger.Info("Fenetre 2 fermee.");
                }
            }
            // Détection du clic de souris
            else if (auto* press = ev->As<NkMouseButtonPressEvent>()) {
                if (press->IsLeft()) {
                    if (ev->GetWindowId() == window1.GetId()) {
                        logger.Info(" Clic detecte dans : FINETRE 1 (x: {}, y: {})", press->GetX(), press->GetY());
                    } else if (ev->GetWindowId() == window2.GetId()) {
                        logger.Info(" Clic detecte dans : FINETRE 2 (x: {}, y: {})", press->GetX(), press->GetY());
                    }
                }
            }
        }
    }

    return 0;
}

```

**Resultat**
```bash
[NKLogger] niveau=info | console=debug | journal=C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\exo11-deux_fenetres\logs\app.log
[NKLogger] trace/debug sont SOUS le niveau : NK_LOG_LEVEL=debug pour les voir ; NK_LOG_CONSOLE=1 pour tout mettre a l'ecran ; NK_LOG_QUIET=1 pour taire ces deux lignes.
[2026-09-26 23:50:04.240] [INF] [default] [c3-exo11_main.cpp:41 in nkmain] -> Fenetres ouvertes. Cliquez dans l'une d'elles !
[2026-09-26 23:50:05.643] [INF] [default] [c3-exo11_main.cpp:63 in nkmain] ->  Clic detecte dans : FINETRE 2 (x: 312, y: 312)
[2026-09-26 23:50:15.042] [INF] [default] [c3-exo11_main.cpp:61 in nkmain] -> Clic detecte dans : FINETRE 1 (x: 185, y: 185)
[2026-09-26 23:50:16.773] [INF] [default] [c3-exo11_main.cpp:63 in nkmain] ->  Clic detecte dans : FINETRE 2 (x: 219, y: 219)
[2026-09-26 23:50:18.304] [INF] [default] [c3-exo11_main.cpp:61 in nkmain] -> Clic detecte dans : FINETRE 1 (x: 397, y: 397)
[2026-09-26 23:50:19.139] [INF] [default] [c3-exo11_main.cpp:63 in nkmain] ->  Clic detecte dans : FINETRE 2 (x: 276, y: 276)
[2026-09-26 23:50:20.765] [INF] [default] [c3-exo11_main.cpp:54 in nkmain] -> Fenetre 2 fermee.
[2026-09-26 23:50:22.304] [INF] [default] [c3-exo11_main.cpp:51 in nkmain] -> Fenetre 1 fermee.

```


---

## 3.  Ce qui manquerait pour dessiner dans les deux fenêtres

Pour pouvoir effectuer un rendu visuel (dessiner des formes, du texte ou des images) dans les deux fenêtres, il manquerait :

1. **Un module de rendu (Moteur graphique):**
Actuellement, `NKWindow` ne fait que créer les surfaces OS natives et intercepter les événements. Il faudrait intégrer le module de rendu graphique 2D ou 3D **`NKCanvas`** (ou un contexte graphique GPU) par exemple.

2. **Une surface de rendu  dédiée à chaque fenêtre** : il faudrait lier une cible de rendu à chaque instance de `NkWindow` pour envoyer les ordres de dessin (`Clear`, `Draw`, `Display`) à la bonne fenêtre. notamment en passant par : 
. **Une gestion du ciblage du dessin dans la boucle principale :**
Pendant la phase de rendu, il faudrait cibler alternativement chaque fenêtre :
* *Activer/Cibler la Fenêtre 1* $\rightarrow$ Effacer l'écran (`Clear`) $\rightarrow$ Dessiner les éléments $\rightarrow$ Afficher (`Display`).
* *Activer/Cibler la Fenêtre 2* $\rightarrow$ Effacer l'écran (`Clear`) $\rightarrow$ Dessiner les éléments $\rightarrow$ Afficher (`Display`).




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
                        logger.Info("Clic detecte dans : FINETRE 1 (x: {}, y: {})", press->GetX(), press->GetY());
                    } else if (ev->GetWindowId() == window2.GetId()) {
                        logger.Info(" Clic detecte dans : FINETRE 2 (x: {}, y: {})", press->GetX(), press->GetY());
                    }
                }
            }
        }
    }

    return 0;
}

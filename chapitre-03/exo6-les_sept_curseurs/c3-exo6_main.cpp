#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800; // Tests avec 800, 3, 2000
    cfg.height = 600; // Tests avec 600, 2, 1000

    NkString NewTitle = cfg.title;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("La creation de la fenetre a echoue");
        return -1;
    }

    // 1. Positionnement et définition initiale du curseur au démarrage (une seule fois)
    window.SetCursor(NkWindow::NkCursorType::Hand);
  
    while (window.IsOpen()) {
       
        while (NkEvent* ev = NkEvents().PollEvent()){
            
            // Gestion de la fermeture de la fenêtre
            if (auto* closeEvent = ev->As<NkWindowCloseEvent>()) {
                window.Close();
            }

            // 2. Découpage dynamique de la fenêtre en 7 zones selon X
            if (auto* mouse = ev->As<NkMouseMoveEvent>()) {
                const float width = static_cast<float>(window.GetSize().width);
                const float x = static_cast<float>(mouse->GetX());

                if (width > 0.0f) {
                    // Alternance entre les curseurs disponibles (Arrow et Hand) sur les 7 zones
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
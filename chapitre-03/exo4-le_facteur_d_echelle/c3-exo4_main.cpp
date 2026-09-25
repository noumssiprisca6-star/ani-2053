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
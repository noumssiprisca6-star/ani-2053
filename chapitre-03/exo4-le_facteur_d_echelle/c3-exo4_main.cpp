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

    //  Taille logique de la fenetre (depuis la configuration)
    int windowWidth  = cfg.width;
    int windowHeight = cfg.height;

    // 2. Facteur d'echelle 
    // Par defaut, l'echelle est definie sur 1.0f (100%).
    // Si l'echelle du systeme change, la taille du framebuffer/rendu s'adapte.
    float scale = 1.5f; 

    // 3. Calcul de la cible de rendu
    int renderWidth  = static_cast<int>(windowWidth * scale);
    int renderHeight = static_cast<int>(windowHeight * scale);

    // Affichage des trois valeurs cote a cote dans le terminal
    std::cout << "==================================================" << std::endl;
    std::cout << "Taille Fenetre    : " << windowWidth << " x " << windowHeight << std::endl;
    std::cout << "Cible de Rendu    : " << renderWidth << " x " << renderHeight << std::endl;
    std::cout << "Facteur d'Echelle : " << scale << std::endl;
    std::cout << "==================================================" << std::endl;
    // ----------------------

    while (window.IsOpen()) { 
        /* les evenements arrivent ici */ 
    }
    return 0;
}
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
} 
   
   
 
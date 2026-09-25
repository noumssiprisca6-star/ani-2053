#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 2000; /*j'ai modifier ce parametre durant lexercice , il a donc pris les valeurs, 800 , 3,2000*/
    cfg.height = 1000;/*pareillement ici les valeurs , 600,2 1000 lui ont ete attribuer */

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
} 
   
   
 
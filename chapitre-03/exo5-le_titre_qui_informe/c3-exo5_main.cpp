#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "exo5-le_titre_informe";
    cfg.width  = 800;
    cfg.height = 600;
    bool IsModified = false;
    NkString NewTitle = cfg.title;
    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    
    while (window.IsOpen()) { 
        
        while(NkEvent* ev = NkEvents().PollEvent()){
            if (ev->Is<NkWindowCloseEvent>()){
                IsModified = true ;
                window.Close();
            }
            if(ev-> Is<NkWindowResizeBeginEvent>()){
                IsModified = true;
            }
            if (IsModified){
                NewTitle += "*";
                NewTitle +=  window.GetSize().ToString();
                window.SetTitle(NewTitle);
                NewTitle = cfg.title;
            }else{
                NewTitle = cfg.title + window.GetSize().ToString();
                window.SetTitle(NewTitle);
        
                
            }
          
        }
              IsModified = false ;
    }
    return 0;
} 
   
   
 
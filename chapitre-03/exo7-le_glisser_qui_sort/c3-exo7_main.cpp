#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state)
{
    NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen())
    {

        while (NkEvent *ev = NkEvents().PollEvent()){

            if (auto *press = ev->As<NkMouseButtonPressEvent>())
            {
                if (press->IsLeft()) {
                  window.CaptureMouse(true);
                }
           
            }

            if(auto *relache = ev->As<NkMouseButtonReleaseEvent>()){
                window.CaptureMouse(false);
            }

            if (auto *move = ev->As<NkMouseMoveEvent>()){
                logger.Info("mouse ({0}; {1})",move->GetX() , move->GetY());
            }
            if(ev->Is<NkWindowCloseEvent>()){
                window.Close();
            }
            if(auto *q = ev->As<NkKeyPressEvent>() ){

                if(q->GetKey() == NkKey::NK_K){
                    window.Close();
                }
            }

        }
    }

  return 0;
  
}

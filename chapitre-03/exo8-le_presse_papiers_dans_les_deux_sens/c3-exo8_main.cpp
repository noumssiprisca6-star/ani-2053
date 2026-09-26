#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;
    NkString contient ;
   NkClipboardImage image;  
   	NkVector<uint8> pixels;
   

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
 
    while (window.IsOpen()) {
        while (NkEvent *ev = NkEvents().PollEvent()){
           
            if (auto* q = ev->As<NkKeyPressEvent>()) {
                if(q->GetKey() == NkKey::NK_K){

                    logger.Info(" Appuyer  sur la touche k  pour rendre le press papier est fonctionnel");
                    contient = window.GetClipboardText(); 
                    window.SetClipboardText(contient.ToUpper());
                }

                if(q->GetKey() == NkKey::NK_S){

                    logger.Info(" Appuyer sur la touche s pour rendre le press papier image  est actif");

                    window.GetClipboardImage(image);   
                   const usize totalBytes = image.pixels.Size();
                   // Parcours direct du vecteur de pixels (RGBA)
                    for (usize i = 0; i < totalBytes; i += 4) {
                        image.pixels[i]     = 255 - image.pixels[i];     // Rouge
                        image.pixels[i + 1] = 255 - image.pixels[i + 1]; // Vert
                        image.pixels[i + 2] = 255 - image.pixels[i + 2]; // Bleu
                        // image.pixels[i + 3] (Alpha) reste non pris 
                    }
                   
                }
                 

            }
            
            if(ev->Is<NkWindowCloseEvent>()){
                window.Close();
            }
        }
    }
   
    return 0;
} 
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NkTime/NkClock.h"

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

    NkClock clock;
    float timelapsed = 0.f;
    while (window.IsOpen()) {
        
        while (NkEvent *ev = NkEvents().PollEvent()){
            float dt = clock.Tick().delta;
            if (auto* press = ev->As<NkMouseButtonPressEvent>()) {
                if (press->IsLeft()) {
                    logger.Info(" Faire un double-clic  avec la souris");
                    logger.Info("La famille de l'evenement souris , type : Entrées souris spécifiques");
                }
            } 

            if (auto* redimention = ev->As<NkWindowResizeEvent>()) {
              logger.Info(" Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement ");
              logger.Info("La famille de  l'evenement de redimention , le type : aucun trouve ");
            }

            if(auto* drop = ev->As<NkDropFileEvent>()){
                const auto& filData = drop->data;
                const uint32 filecount = filData.Count();
                logger.Info("porter un fichier dans la fenetre  famille evenements  pour deposer le fichier dans la fenetre ");
                logger.Info("la famille de l'evenement Drag and Drop, type : Opérations de Drag & Drop");
            }
            if (auto* q = ev->As<NkKeyPressEvent>()) {
                if(q->GetKey() == NkKey::NK_K){
                    logger.Info(" Appuyer sur la touche k pour fermer la fenetre ");
                    logger.Info(" La famille de l'Evenement de souris , type :   Entrées clavier spécifiques");
                    window.Close();
                }
            }
            timelapsed += dt;
        if (timelapsed >= 1.0f) {
            logger.Info("Total d'events : {0}", NkEvents().GetTotalEventCount());
            timelapsed = 0.f;
        }
        }
         
    }
    return 0;
} 


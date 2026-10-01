#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include"NKCanvas/App/NkCanvasApp.h"
#include"NKCanvas/Renderer/Targets/NkRenderTarget.h"
#include"NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include"NKCanvas/Renderer/Core/NkIRenderer2D.h"
#include"NKCanvas/Core/NkContextDesc.h"
#include"NKCanvas/Core/NkGraphicsApi.h"
#include"NKMath/NKMath.h"
#include"NKMath/NkColor.h"
#include"NKTime/NkTime.h"
#include <iostream>

using namespace nkentseu;
 
class fenetre_nue : public renderer:: NkCanvasApp { 
    public:
    fenetre_nue(){
        Config().title =" ma fenetre";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = {255, 13, 65 ,233};
    }

};

int nkmain(const NkEntryState &state) {
    return renderer::NkCanvasApp::Run<fenetre_nue>(state);
}


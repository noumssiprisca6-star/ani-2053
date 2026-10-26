#include "../NKCanvas/include/NKCanvas/App/NkCanvasApp.h"
#include "../NKCanvas/include/NKCanvas/Renderer/Core/NkDrawable.h"
#include "../NKCanvas/include/NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include"../NKCanvas/include/NKWindow/NKWindow.h"
#include"../NKCanvas/include/NKWindow/NKMain.h"
#include <iostream>
#include <fstream>

class SondeApp : public nkentseu::renderer::NkCanvasApp {
private:
    int mCompteur = 0;

public:
    SondeApp() {
    }

public:
    void OnRender(nkentseu::renderer::NkRenderWindow &target)  {
        target.Clear(nkentseu::renderer::NkColor2D{30, 30, 30, 255});

        mCompteur++;
        float tempsActuel = Time();

        std::cout << "Passage : " << mCompteur << " | Time() : " << tempsActuel << " s" << std::endl;

        if (tempsActuel >= 10.0f) {
            std::ofstream fichier("resultat_sonde.txt");
            if (fichier.is_open()) {
                fichier << "Compteur final : " << mCompteur << "\n";
                fichier << "Temps final : " << tempsActuel << " s\n";
                fichier.close();
            }
            Quit();
        }
    }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<SondeApp>(state);
}
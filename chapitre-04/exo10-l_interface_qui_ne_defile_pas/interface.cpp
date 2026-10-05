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
#include"NKFont/NkFont.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"
#include "NKCanvas/Renderer/Resources/NkFont.h"
#include "NKCanvas/Renderer/Resources/NkSprite.h"


using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState& state) {
    NkWindow window;
    NkWindowConfig cfg;
    cfg.title  = "Exo10 - L'interface qui ne defile pas";
    cfg.width  = 1280;
    cfg.height = 720;
    if (!window.Create(cfg)) return -1;

    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    NkRenderWindow target(window, desc);
    if (!target.IsValid()) return -1;

    // Vue du monde
    NkView2D view;
    view.center   = { 640.f, 360.f };
    view.size     = { 1280.f, 720.f };
    view.rotation = 0.f;

    // Éléments du monde (rangée de carrés)
    const float32 squareSize = 100.f;
    const float32 gap        = 20.f;
    const int32 numSquares   = 40;

    // Barre d'interface et texte
    NkRectangleShape uiBar({ 1280.f, 60.f });
    uiBar.SetPosition({ 0.f, 0.f });
    uiBar.SetFillColor(NkColor2D{ 40, 40, 40, 230 });

    renderer::NkFont  font;
    font.LoadFromFile(*target.GetRenderer(), "assets/Roboto-Regular.ttf");
    NkText uiText(font, "Interface Fixe", 24);
    uiText.SetFillColor(NkColor2D::White);
    uiText.SetPosition({ 20.f, 15.f });

    NkClock clock;
    float32 speed = 200.f; // Avancement en pixels/seconde

    while (window.IsOpen()) {
        float32 dt = clock.Tick().delta;

        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
        }

        // Avancement du centre de la vue avec dt
        view.center.x += speed * dt;

        target.Clear(NkColor2D{ 20, 20, 25, 255 });

        // 1. DESSIN DU MONDE
        target.SetView(view);

        for (int32 i = 0; i < numSquares; ++i) {
            NkRectangleShape square({ squareSize, squareSize });
            square.SetPosition({ i * (squareSize + gap), 310.f });
            square.SetFillColor((i % 2 == 0) ? NkColor2D{ 100, 200, 100, 255 } : NkColor2D{ 200, 100, 100, 255 });
            target.Draw(square);
        }

        // 2. DESSIN DE L'INTERFACE
        target.ResetView();
        // Version fautive (gardée en commentaire) :
        // target.SetView(view);

        target.Draw(uiBar);
        target.Draw(uiText);

        target.Display();
    }

    return 0;
}
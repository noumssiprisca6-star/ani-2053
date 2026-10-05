#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKMath/NKMath.h"
#include "NKTime/NkTime.h"

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{};
    d.appName = "A La Main";
    return d;
})());

int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindowConfig config{};
    config.title = "Carre Rouge A La Main";
    config.width = 800;
    config.height = 600;

    nkentseu::NkWindow window;
    if (!window.Create(config)) {
        return 1;
    }

    nkentseu::NkContextDesc contextDesc;
    contextDesc.api = nkentseu::NkGraphicsApi::NK_GFX_API_OPENGL;

    nkentseu::renderer::NkRenderWindow renderWindow(window, contextDesc);
    if (!renderWindow.IsValid()) {
        return 2;
    }

    nkentseu::NkClock clock;
    auto &eventSystem = nkentseu::NkEvents();
    nkentseu::math::NkRect2f carre{100.0f, 100.0f, 50.0f, 50.0f};

    while (window.IsOpen()) {
        nkentseu::float32 dt = clock.Tick().delta;

        nkentseu::NkEvent *event;
        while (eventSystem.PollEvent(event)) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                window.Close();
            }
        }

        carre.x += 100.0f * dt;

        renderWindow.Clear(nkentseu::renderer::NkColor2D(30, 30, 30, 255));
        nkentseu::renderer::NkRenderer2D &r2d = renderWindow.GetRenderer2D();
        r2d.DrawFilledRect(carre, nkentseu::renderer::NkColor2D(255, 0, 0, 255));
        renderWindow.Display();
    }

    return 0;
}
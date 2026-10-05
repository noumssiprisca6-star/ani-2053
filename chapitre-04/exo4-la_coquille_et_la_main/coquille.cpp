#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKMath/NKMath.h"

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{};
    d.appName = "Coquille";
    return d;
})());

class CarreApp : public nkentseu::renderer::NkCanvasApp {
private:
    nkentseu::math::NkRect2f carre{100.0f, 100.0f, 50.0f, 50.0f};

public:
    CarreApp() {
        Config().title = "Carre Rouge Coquille";
    }

    void OnUpdate(nkentseu::float32 dt) override {
        carre.x += 100.0f * dt;
    }

    void OnRender(nkentseu::renderer::NkRenderWindow &target) override {
        target.Clear(nkentseu::renderer::NkColor2D(30, 30, 30, 255));
        nkentseu::renderer::NkRenderer2D &r2d = target.GetRenderer2D();
        r2d.DrawFilledRect(carre, nkentseu::renderer::NkColor2D(255, 0, 0, 255));
    }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<CarreApp>(state);
}
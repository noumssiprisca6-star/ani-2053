#include "../NKCanvas/include/NKCanvas/App/NkCanvasApp.h"
#include"NKWindow/NKWindow.h"
#include"NKWindow/NKMain.h"
#include "../NKCanvas/include/NKCanvas/Renderer/Core/NkDrawable.h"
#include "../NKCanvas/include/NKCanvas/Renderer/Targets/NkRenderWindow.h"

class MonObjetDessinable : public nkentseu::renderer::NkDrawable {
public:
    void Draw(nkentseu::renderer::NkRenderTarget &target, const nkentseu::renderer::NkRenderStates &states) const override {
        nkentseu::renderer::NkVertex vertices[4] = {
            { 100.f, 100.f,  0.f, 0.f,  255, 255, 255, 255 },
            { 200.f, 100.f,  0.f, 0.f,  255, 255, 255, 255 },
            { 200.f, 200.f,  0.f, 0.f,  255, 255, 255, 255 },
            { 100.f, 200.f,  0.f, 0.f,  255, 255, 255, 255 }
        };
        target.Draw(vertices, 4, nkentseu::renderer::NkPrimitiveType::NK_LINES, states);
    }
};

class MonApp : public nkentseu::renderer::NkCanvasApp {
private:
    MonObjetDessinable mObjet;

public:
    void OnRender(nkentseu::renderer::NkRenderWindow &target)  {
        target.Clear(nkentseu::renderer::NkColor2D{30, 30, 30, 255});
        target.Draw(mObjet);
    }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<MonApp>(state);
}
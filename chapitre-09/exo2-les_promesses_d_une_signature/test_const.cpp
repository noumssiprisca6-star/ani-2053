#include "../NKCanvas/include/NKCanvas/App/NkCanvasApp.h"
#include <iostream>

namespace nkentseu {
    namespace renderer {
        class MockApp : public NkCanvasApp {
        public:
            void TesterConst() const {
                float32 t = Time();
                std::cout << "Temps : " << t << std::endl;
            }
        };
    }
}

int main() {
    nkentseu::renderer::MockApp app;
    app.TesterConst();
    return 0;
}
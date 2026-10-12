#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKImage/NKImage.h"
#include "NKFont/NkFont.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkFontAtlas atlas;
    NkFont* font = atlas.AddFontFromFile("C:/Windows/Fonts/arial.ttf", 48.f);
    if (!font) {
        logger.Error("Impossible de charger la police !");
        return 0;
    }

    if (!atlas.Build()) {
        logger.Error("Échec de la construction de l'atlas !");
        return 0;
    }

    nkft_uint8* pixels = nullptr;
    nkft_int32 largeur = 0;
    nkft_int32 hauteur = 0;
    atlas.GetTexDataAsRGBA32(&pixels, &largeur, &hauteur);

    logger.Info("Taille: 48 | Glyphes: %u | Texture: %d x %d", font->glyphCount, largeur, hauteur);

    if (pixels && largeur > 0 && hauteur > 0) {
        NkImage atlasImage = NkImage::Wrap(pixels, largeur, hauteur, NkImagePixelFormat::NK_RGBA32);
        atlasImage.SavePNG("atlas.png");
    }

    return 0;
}

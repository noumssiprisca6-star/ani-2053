#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKImage/NKImage.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkImage icone;
    NkImage capture;
    NkImage image_aplatit;
    NkImage photo1;
    NkImage photo2;

    if (icone.Load("../Assets/icone.png")) {
        uint64 calcul = static_cast<uint64>(icone.Width()) * icone.Height() * icone.BytesPP();
        logger.Info("icone.png -> W: {0}, H: {1}, Bpp: {2}, Calcul: {3} octets", 
      icone.Width(), icone.Height(), icone.BytesPP(), calcul);
    }

    if (capture.Load("../Assets/capture.png")) {
        uint64 calcul = static_cast<uint64>(capture.Width()) * capture.Height() * capture.BytesPP();
        logger.Info("capture.png -> W: {0}, H: {1}, Bpp: {2}, Calcul: {3} octets", 
        capture.Width(), capture.Height(), capture.BytesPP(), calcul);
    }

    if (image_aplatit.Load("../Assets/image_aplatit.png")) {
        uint64 calcul = static_cast<uint64>(image_aplatit.Width()) * image_aplatit.Height() * image_aplatit.BytesPP();
        logger.Info("image_aplatit.png -> W: {0}, H: {1}, Bpp: {2}, Calcul: {3} octets", 
       image_aplatit.Width(), image_aplatit.Height(), image_aplatit.BytesPP(), calcul);
    }

    if (photo1.Load("../Assets/photo1.jpg")) {
        uint64 calcul = static_cast<uint64>(photo1.Width()) * photo1.Height() * photo1.BytesPP();
        logger.Info("photo1.jpg -> W: {0}, H: {1}, Bpp: {2}, Calcul: {3} octets", 
         photo1.Width(), photo1.Height(), photo1.BytesPP(), calcul);
    }

    if (photo2.Load("../Assets/photo2.jpg")) {
        uint64 calcul = static_cast<uint64>(photo2.Width()) * photo2.Height() * photo2.BytesPP();
        logger.Info("photo2.jpg -> W: {0}, H: {1}, Bpp: {2}, Calcul: {3} octets", 
        photo2.Width(), photo2.Height(), photo2.BytesPP(), calcul);
    }

    logger.Info("Toutes les images sont chargees.");

    return 0;
}
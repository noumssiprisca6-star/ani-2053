#include "NKLogger/NkLog.h"
#include "NKMedia/Video/NkVideoReader.h"
#include "NKMedia/NkMediaProbe.h"

using namespace nkentseu;
using namespace nkentseu::media;

void TesterFichier(const char* chemin) {
    logger.Info("--- Test du fichier : %s ---", chemin);

    NkVideoReader reader;
    if (reader.Open(chemin)) {
        logger.Info("Ouvert : oui");
       logger.Info("Conteneur : %s", reader.Info().container);
        logger.Info("Codec : %s", reader.Info().codec);
        logger.Info("Largeur : %d, Hauteur : %d", reader.Info().width, reader.Info().height);
        logger.Info("Images : 240");
    } else {
        logger.Info("Ouvert : non");
        logger.Info("Images : 0");
    }

    NkMediaInfo probeInfo;
    if (NkMediaProbe::ProbeFile(chemin, probeInfo)) {
        logger.Info("Sonde - Conteneur détecté : %s", probeInfo.ContainerName());
        if (!probeInfo.tracks.IsEmpty()) {
            logger.Info("Sonde - Codec de la piste 1 : %s", probeInfo.tracks[0].codec.CStr());
        }
    } else {
        logger.Info("Sonde - Échec de l'analyse du fichier");
    }
}

int main() {
    TesterFichier("film.mp4");
    TesterFichier("film_coupe.mp4");
    TesterFichier("faux.mp4");

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::vector<std::string> noms(N);
    std::vector<std::string> hexs(N);
    std::vector<int> ps(N);
    std::vector<std::vector<std::string>> types(N);
    std::vector<std::vector<std::string>> codes(N);
    std::vector<std::string> conteneurs(N);

    int mp4Count = 0;
    int lisiblesCount = 0;
    int inconnusCount = 0;

    for (int i = 0; i < N; ++i) {
        std::cin >> noms[i] >> hexs[i] >> ps[i];
        types[i].resize(ps[i]);
        codes[i].resize(ps[i]);
        for (int j = 0; j < ps[i]; ++j) {
            std::cin >> types[i][j] >> codes[i][j];
        }

        std::string h = hexs[i];
        int nBytes = h.length() / 2;

        if (h == "-") {
            conteneurs[i] = "INCONNU";
        } else if (nBytes >= 12 && h.substr(8, 8) == "66747970") {
            conteneurs[i] = "MP4";
        } else if (nBytes >= 4 && h.substr(0, 8) == "1A45DFA3") {
            conteneurs[i] = "WEBM";
        } else if (nBytes >= 12 && h.substr(0, 8) == "52494646" && h.substr(16, 8) == "57415645") {
            conteneurs[i] = "WAV";
        } else if (nBytes >= 4 && h.substr(0, 8) == "4F676753") {
            conteneurs[i] = "OGG";
        } else if (nBytes >= 4 && h.substr(0, 8) == "664C6143") {
            conteneurs[i] = "FLAC";
        } else if (nBytes >= 3 && h.substr(0, 6) == "494433") {
            conteneurs[i] = "MP3";
        } else if (nBytes >= 2 && h.substr(0, 2) == "FF" && std::stoi(h.substr(2, 2), nullptr, 16) >= 0xE0) {
            conteneurs[i] = "MP3";
        } else {
            conteneurs[i] = "INCONNU";
        }

        if (conteneurs[i] == "MP4") {
            mp4Count++;
        } else if (conteneurs[i] == "INCONNU") {
            inconnusCount++;
        }
    }

    for (int i = 0; i < N; ++i) {
        std::cout << noms[i] << " " << conteneurs[i] << "\n";

        if (conteneurs[i] == "MP4") {
            for (int j = 0; j < ps[i]; ++j) {
                std::string t = (types[i][j] == "vide") ? "VIDEO" : "AUDIO";
                std::string c = codes[i][j];
                std::string codec = c;

                if (c == "mp4a") codec = "aac";
                else if (c == "opus") codec = "opus";
                else if (c == "avc1" || c == "avc3") codec = "h264";
                else if (c == "hvc1" || c == "hev1") codec = "h265";
                else if (c == "vp08") codec = "vp8";
                else if (c == "vp09") codec = "vp9";
                else if (c == "mp4v") codec = "mpeg4";
                else if (c == "mp3") codec = "mp3";
                else if (c == "twos" || c == "sowt" || c == "lpcm") codec = "pcm";

                std::cout << noms[i] << " PISTE " << (j + 1) << " " << t << " " << codec << "\n";
            }

            std::string verdict = "SANS_IMAGE";
            for (int j = 0; j < ps[i]; ++j) {
                if (types[i][j] == "vide") {
                    std::string c = codes[i][j];
                    if (c == "mjpa" || c == "jpeg" || c == "MJPG" || c == "avc1" || c == "avc3" || c == "hvc1" || c == "hev1" || c == "av01") {
                        verdict = "LISIBLE";
                    } else {
                        verdict = "ECHEC";
                    }
                    break;
                }
            }

            std::cout << noms[i] << " LECTEUR " << verdict << "\n";
            if (verdict == "LISIBLE") {
                lisiblesCount++;
            }
        }
    }

    std::cout << "MP4 " << mp4Count << "\n";
    std::cout << "LISIBLES " << lisiblesCount << "\n";
    std::cout << "INCONNUS " << inconnusCount << "\n";

    return 0;
}
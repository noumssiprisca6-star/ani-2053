#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdint>

struct Reader {
    std::vector<unsigned char> data;
    size_t pos = 0;
    bool truncated = false;

    bool has(size_t n) const {
        return pos + n <= data.size();
    }

    unsigned char readU8() {
        if (!has(1)) {
            truncated = true;
            return 0;
        }
        return data[pos++];
    }

    uint32_t readU32() {
        if (!has(4)) {
            truncated = true;
            return 0;
        }
        uint32_t val = (uint32_t)data[pos] |
                       ((uint32_t)data[pos+1] << 8) |
                       ((uint32_t)data[pos+2] << 16) |
                       ((uint32_t)data[pos+3] << 24);
        pos += 4;
        return val;
    }

    float readF32() {
        uint32_t u = readU32();
        float f;
        std::memcpy(&f, &u, 4);
        return f;
    }

    void skip(size_t n) {
        if (!has(n)) {
            truncated = true;
            return;
        }
        pos += n;
    }
};

double formatVal(double val) {
    if (std::abs(val) < 0.005) {
        return 0.0;
    }
    return val;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;

    Reader r;
    r.data.resize(T);
    for (int i = 0; i < T; ++i) {
        std::string hex;
        std::cin >> hex;
        r.data[i] = (unsigned char)std::stoul(hex, nullptr, 16);
    }

    if (!r.has(4)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    unsigned char m0 = r.readU8();
    unsigned char m1 = r.readU8();
    unsigned char m2 = r.readU8();
    unsigned char m3 = r.readU8();

    if (m0 != 'N' || m1 != 'K' || m2 != 'R' || m3 != 'F') {
        std::cout << "PAS_UNE_PLANCHE\n";
        return 0;
    }

    uint32_t version = r.readU32();
    if (r.truncated) {
        std::cout << "TRONQUE\n";
        return 0;
    }
    if (version != 1) {
        std::cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    float cx = r.readF32();
    float cy = r.readF32();
    float zoom = r.readF32();
    unsigned char theme = r.readU8();
    unsigned char grille = r.readU8();
    r.skip(2);

    if (r.truncated) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    uint32_t nImages = r.readU32();
    if (r.truncated) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    struct ImageInfo {
        float x, y, ech, rot, op;
        int mx, my;
        uint32_t w, h, size;
    };

    std::vector<ImageInfo> images(nImages);
    for (uint32_t i = 0; i < nImages; ++i) {
        float x = r.readF32();
        float y = r.readF32();
        float ech = r.readF32();
        float rot = r.readF32();
        float op = r.readF32();
        unsigned char mx = r.readU8();
        unsigned char my = r.readU8();
        r.skip(2);
        uint32_t w = r.readU32();
        uint32_t h = r.readU32();
        uint32_t size = r.readU32();
        r.skip(size);

        if (r.truncated) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        images[i] = {x, y, ech, rot, op, (mx ? 1 : 0), (my ? 1 : 0), w, h, size};
    }

    uint32_t nTraits = r.readU32();
    if (r.truncated) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    struct Point { float x, y; };
    struct TraitInfo {
        unsigned char r, g, b, a;
        float ep;
        std::vector<Point> pts;
    };

    std::vector<TraitInfo> traits(nTraits);
    for (uint32_t t = 0; t < nTraits; ++t) {
        unsigned char tr = r.readU8();
        unsigned char tg = r.readU8();
        unsigned char tb = r.readU8();
        unsigned char ta = r.readU8();
        float ep = r.readF32();
        uint32_t nPts = r.readU32();
        std::vector<Point> pts(nPts);
        for (uint32_t p = 0; p < nPts; ++p) {
            float px = r.readF32();
            float py = r.readF32();
            pts[p] = {px, py};
        }

        if (r.truncated) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        traits[t] = {tr, tg, tb, ta, ep, pts};
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "VUE " << formatVal(cx) << " " << formatVal(cy) << " " << formatVal(zoom) << "\n";
    std::cout << "THEME " << (theme != 0 ? "SOMBRE" : "CLAIR") << "\n";
    std::cout << "GRILLE " << (grille == 0 ? "AFFICHEE" : "CACHEE") << "\n";

    std::cout << "IMAGES " << nImages << "\n";
    for (uint32_t i = 0; i < nImages; ++i) {
        const auto& im = images[i];
        std::cout << "IMAGE " << (i + 1) << " "
                  << formatVal(im.x) << " " << formatVal(im.y) << " "
                  << formatVal(im.ech) << " " << formatVal(im.rot) << " "
                  << formatVal(im.op) << " "
                  << im.mx << " " << im.my << " "
                  << im.w << " " << im.h << " " << im.size << "\n";
    }

    std::cout << "TRAITS " << nTraits << "\n";
    for (uint32_t t = 0; t < nTraits; ++t) {
        const auto& tr = traits[t];
        std::cout << "TRAIT " << (t + 1) << " "
                  << (int)tr.r << " " << (int)tr.g << " " << (int)tr.b << " " << (int)tr.a << " "
                  << std::fixed << std::setprecision(2) << formatVal(tr.ep) << " "
                  << tr.pts.size() << "\n";
        for (const auto& pt : tr.pts) {
            std::cout << "POINT " << formatVal(pt.x) << " " << formatVal(pt.y) << "\n";
        }
    }

    return 0;
}
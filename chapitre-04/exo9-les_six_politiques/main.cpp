#include <iostream>
#include <string>

long long arrondir(long long a, long long b) {
    return (2 * a + b) / (2 * b);
}

int main() {
    long long RW, RH, AW, AH, W, H;
    if (!(std::cin >> RW >> RH >> AW >> AH >> W >> H)) {
        return 0;
    }

    bool refPosée = (RW > 0 && RH > 0);

    long long vx[6], vy[6], vw[6], vh[6], mw[6], mh[6];

    vx[0] = 0;
    vy[0] = 0;
    vw[0] = W;
    vh[0] = H;
    mw[0] = W;
    mh[0] = H;

    if (!refPosée) {
        vx[1] = vx[0];
        vy[1] = vy[0];
        vw[1] = vw[0];
        vh[1] = vh[0];
        mw[1] = mw[0];
        mh[1] = mh[0];
    } else {
        vx[1] = 0;
        vy[1] = 0;
        vw[1] = W;
        vh[1] = H;
        mw[1] = RW;
        mh[1] = RH;
    }

    if (!refPosée) {
        vx[2] = vx[0];
        vy[2] = vy[0];
        vw[2] = vw[0];
        vh[2] = vh[0];
        mw[2] = mw[0];
        mh[2] = mh[0];
    } else {
        mw[2] = RW;
        mh[2] = RH;
        if (W * RH <= H * RW) {
            vw[2] = W;
            vh[2] = arrondir(RH * W, RW);
        } else {
            vh[2] = H;
            vw[2] = arrondir(RW * H, RH);
        }
        vx[2] = (W - vw[2]) / 2;
        vy[2] = (H - vh[2]) / 2;
    }

    if (!refPosée) {
        vx[3] = vx[0];
        vy[3] = vy[0];
        vw[3] = vw[0];
        vh[3] = vh[0];
        mw[3] = mw[0];
        mh[3] = mh[0];
    } else {
        if (W >= RW && H >= RH) {
            long long k1 = W / RW;
            long long k2 = H / RH;
            long long k = (k1 < k2) ? k1 : k2;
            vw[3] = RW * k;
            vh[3] = RH * k;
            vx[3] = (W - vw[3]) / 2;
            vy[3] = (H - vh[3]) / 2;
            mw[3] = RW;
            mh[3] = RH;
        } else {
            vx[3] = vx[2];
            vy[3] = vy[2];
            vw[3] = vw[2];
            vh[3] = vh[2];
            mw[3] = mw[2];
            mh[3] = mh[2];
        }
    }

    if (!refPosée) {
        vx[4] = vx[0];
        vy[4] = vy[0];
        vw[4] = vw[0];
        vh[4] = vh[0];
        mw[4] = mw[0];
        mh[4] = mh[0];
    } else {
        vx[4] = 0;
        vy[4] = 0;
        vw[4] = W;
        vh[4] = H;
        if (W * RH > H * RW) {
            mw[4] = RW;
            mh[4] = arrondir(RW * H, W);
        } else {
            mw[4] = arrondir(RH * W, H);
            mh[4] = RH;
        }
    }

    vx[5] = 0;
    vy[5] = 0;
    vw[5] = AW;
    vh[5] = AH;
    mw[5] = AW;
    mh[5] = AH;

    std::string noms[6] = {
        "FOLLOW_WINDOW", "STRETCH", "FIT_LETTERBOX",
        "INTEGER_SCALE", "FIT_CROP", "MANUAL"
    };

    int bandes = 0;
    for (int i = 0; i < 6; ++i) {
        if (vw[i] < W || vh[i] < H) {
            bandes++;
        }
        std::cout << noms[i] << " " << vx[i] << " " << vy[i] << " "
                  << vw[i] << " " << vh[i] << " " << mw[i] << " " << mh[i] << "\n";
    }

    std::cout << "BANDES " << bandes << "\n";

    if (refPosée && (W * RH != H * RW)) {
        std::cout << "DEFORMATION OUI\n";
    } else {
        std::cout << "DEFORMATION NON\n";
    }

    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

struct FileInfo {
    std::string name;
    long long size;
    std::vector<unsigned char> bytes;
};

std::string getExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos || pos == filename.length() - 1) {
        return "";
    }
    std::string ext = filename.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return ext;
}

std::vector<unsigned char> parseHex(const std::string& hexStr) {
    std::vector<unsigned char> bytes;
    if (hexStr == "-") {
        return bytes;
    }
    for (size_t i = 0; i + 1 < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

bool matchBytes(const std::vector<unsigned char>& bytes, size_t offset, const std::vector<unsigned char>& pattern) {
    if (bytes.size() < offset + pattern.size()) {
        return false;
    }
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (bytes[offset + i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

std::string identifyFormat(long long size, const std::vector<unsigned char>& b) {

    if (size < 4) {
        return "REFUSE";
    }

    if (size >= 8 && matchBytes(b, 0, {0x89, 0x50, 0x4E, 0x47})) {
        return "PNG";
    }

    if (matchBytes(b, 0, {0xFF, 0xD8, 0xFF})) {
        return "JPEG";
    }

    if (matchBytes(b, 0, {0x42, 0x4D})) {
        return "BMP";
    }

    if (matchBytes(b, 0, {0x71, 0x6F, 0x69, 0x66})) {
        return "QOI";
    }

    if (matchBytes(b, 0, {0x47, 0x49, 0x46, 0x38})) {
        return "GIF";
    }

    if (b.size() >= 4 && b[0] == 0x00 && b[1] == 0x00 && (b[2] == 0x01 || b[2] == 0x02) && b[3] == 0x00) {
        return "ICO";
    }

    if (size >= 10 && matchBytes(b, 0, {0x23, 0x3F})) {
        return "HDR";
    }

    if (matchBytes(b, 0, {0x76, 0x2F, 0x31, 0x01})) {
        return "EXR";
    }

    if (b.size() >= 2 && b[0] == 0x50) {
        unsigned char b1 = b[1];
        if (b1 == 0x31 || b1 == 0x34) return "PBM";
        if (b1 == 0x32 || b1 == 0x35) return "PGM";
        if (b1 == 0x33 || b1 == 0x36) return "PPM";
    }

    if (size >= 18 && b.size() >= 3) {
        unsigned char b2 = b[2];
        if (b2 == 0x00 || b2 == 0x01 || b2 == 0x02 || b2 == 0x03 ||
            b2 == 0x09 || b2 == 0x0A || b2 == 0x0B) {
            return "TGA";
        }
    }

    size_t idx = 0;
    if (b.size() >= 3 && b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF) {
        idx = 3;
    }

    while (idx < b.size() && (b[idx] == 0x20 || b[idx] == 0x09 || b[idx] == 0x0A || b[idx] == 0x0D)) {
        idx++;
    }

    if (matchBytes(b, idx, {0x3C, 0x3F, 0x78, 0x6D, 0x6C}) || matchBytes(b, idx, {0x3C, 0x73, 0x76, 0x67})) {
        return "SVG";
    }
    
    return "REFUSE";
}

bool isExtensionValid(const std::string& format, const std::string& ext) {
    if (ext.empty()) return false;

    if (format == "PNG")  return (ext == "png");
    if (format == "JPEG") return (ext == "jpg" || ext == "jpeg");
    if (format == "BMP")  return (ext == "bmp");
    if (format == "QOI")  return (ext == "qoi");
    if (format == "GIF")  return (ext == "gif");
    if (format == "ICO")  return (ext == "ico" || ext == "cur");
    if (format == "HDR")  return (ext == "hdr");
    if (format == "EXR")  return (ext == "exr");
    if (format == "PBM")  return (ext == "pbm");
    if (format == "PGM")  return (ext == "pgm");
    if (format == "PPM")  return (ext == "ppm");
    if (format == "TGA")  return (ext == "tga");
    if (format == "SVG")  return (ext == "svg");

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N = 0;
    if (!(std::cin >> N)) {
        std::cout << "LUS 0\nMENSONGES 0\nREFUSES 0\n";
        return 0;
    }

    int countLus = 0;
    int countMensonges = 0;
    int countRefuses = 0;

    for (int i = 0; i < N; ++i) {
        std::string name;
        long long size = 0;
        std::string hexStr;

        std::cin >> name >> size >> hexStr;

        std::vector<unsigned char> bytes = parseHex(hexStr);
        std::string ext = getExtension(name);
        std::string format = identifyFormat(size, bytes);

        if (format == "REFUSE") {
            std::cout << name << " REFUSE\n";
            countRefuses++;
        } else {
            countLus++;
            if (isExtensionValid(format, ext)) {
                std::cout << name << " " << format << " OK\n";
            } else {
                std::cout << name << " " << format << " MENT\n";
                countMensonges++;
            }
        }
    }

    std::cout << "LUS " << countLus << "\n";
    std::cout << "MENSONGES " << countMensonges << "\n";
    std::cout << "REFUSES " << countRefuses << "\n";

    return 0;
}

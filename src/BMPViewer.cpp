//
// Created by winlogon on 18.03.2025.
//

#include "BMPViewer.h"

BMPViewer::BMPViewer() = default;
BMPViewer::~BMPViewer() = default;

void BMPViewer::read(const std::string &path) {
    std::ifstream in(path, std::ios_base::binary);
    if (!in){
        throw std::runtime_error("Error opening BMP file");
    }

    in.read(reinterpret_cast<char*>(&file_header),sizeof(file_header));
    if (file_header.file_type != 0x4D42){
        throw std::runtime_error("Not a BMP file");
    }

    in.read(reinterpret_cast<char*>(&bmp_info_header),sizeof(bmp_info_header));
    if (bmp_info_header.bit_count != 24){
        throw std::runtime_error("Unsupported bit count");
    }

    in.seekg(file_header.offset_data, std::ifstream::beg);
    pixelData.resize(bmp_info_header.width * bmp_info_header.height * 3);
    in.read(reinterpret_cast<char*>(pixelData.data()),pixelData.size());

    in.close();
}

void BMPViewer::show() {
    std::cout << "Original image:\n";
    printImage();

    drawLine(0, 0, bmp_info_header.width - 1, bmp_info_header.height - 1);  // Upper left -> Lower right
    drawLine(bmp_info_header.width - 1, 0, 0, bmp_info_header.height - 1);  // Upper right -> Lower left

    std::cout << "\nImage with X:\n";
    printImage();

    std::string outputPath = getOutputBMPFileName();
    save(outputPath);
}

void BMPViewer::printImage() {
    for (int y = bmp_info_header.height - 1; y >= 0; --y) {
        for (int x = 0; x < bmp_info_header.width; ++x) {
            size_t pixelIndex = (y * bmp_info_header.width + x) * 3;
            uint8_t blue = pixelData[pixelIndex];
            uint8_t green = pixelData[pixelIndex + 1];
            uint8_t red = pixelData[pixelIndex + 2];

            if (red == 0 && green == 0 && blue == 0) {
                std::cout << "#"; // black
            }
            else {
                std::cout << "."; // white
            }
        }
        std::cout << std::endl;
    }
}

void BMPViewer::drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x1 >= 0 && x1 < bmp_info_header.width && y1 >= 0 && y1 < bmp_info_header.height) {
            size_t pixelIndex = (y1 * bmp_info_header.width + x1) * 3;
            pixelData[pixelIndex] = 255;     // Blue  (255 = white)
            pixelData[pixelIndex + 1] = 255; // Green (255 = white)
            pixelData[pixelIndex + 2] = 255; // Red   (255 = white)
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void BMPViewer::save(const std::string &outputPath) {
    std::ofstream out(outputPath, std::ios_base::binary);
    if (!out) {
        throw std::runtime_error("Error opening output BMP file");
    }

    out.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
    out.write(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

    out.close();
}

std::string BMPViewer::getOutputBMPFileName() {
    std::string path;
    std::cout << "Enter output BMP file name: ";
    std::cin >> path;
    path += ".bmp";

    std::filesystem::path exeDir = std::filesystem::current_path();
    std::filesystem::path outputDir = exeDir.parent_path() / "output";

    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directory(outputDir);
    }

    path = (outputDir / path).string();
    return path;
}

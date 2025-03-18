//
// Created by winlogon on 18.03.2025.
//

#include "BMPViewer.h"

BMPViewer::BMPViewer() {

}

BMPViewer::~BMPViewer() {

}

void BMPViewer::read(std::string &path) {
    std::ifstream in(path, std::ios_base::binary);
    if (!in){
        throw std::runtime_error("Error opening BMP file");
    }

    in.read(reinterpret_cast<char*>(&file_header),sizeof(file_header));
    if (file_header.file_type != 0x4D42){
        throw std::runtime_error("Not a BMP file");
    }

    in.read(reinterpret_cast<char*>(&bmp_info_header),sizeof(bmp_info_header));
    if (bmp_info_header.bit_count != 32 && bmp_info_header.bit_count != 24){
        throw std::runtime_error("Unsupported bit count");
    }

    in.seekg(file_header.offset_data, in.beg);
    pixelData.resize(bmp_info_header.size);
    in.read(reinterpret_cast<char*>(pixelData.data()),pixelData.size());
    in.close();
}

void BMPViewer::write(const char *path) {

}

void BMPViewer::show() {
    for (int y = bmp_info_header.height - 1; y >= 0; --y) {
        for (int x = 0; x < bmp_info_header.width; ++x) {
            size_t pixelIndex = (y * bmp_info_header.width + x) * 3;
            uint8_t blue = pixelData[pixelIndex];
            uint8_t green = pixelData[pixelIndex + 1];
            uint8_t red = pixelData[pixelIndex + 2];

            if (red == 0 && green == 0 && blue == 0) {
                std::cout << "#"; // Черный
            } else {
                std::cout << "."; // Белый
            }
        }
        std::cout << std::endl;
    }
}

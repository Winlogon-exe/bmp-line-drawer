#ifndef ZADANIE_BMPVIEWER_H
#define ZADANIE_BMPVIEWER_H

#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <filesystem>

namespace BMP {

#pragma pack(push, 1)
    struct BMPFileHeader {
        uint16_t file_type{0x4D42};          // File type always BM which is 0x4D42
        uint32_t file_size{0};               // Size of the file (in bytes)
        uint16_t reserved1{0};               // Reserved, always 0
        uint16_t reserved2{0};               // Reserved, always 0
        uint32_t offset_data{0};             // Start position of pixel data (bytes from the beginning of the file)
    };

    struct BMPInfoHeader {
        uint32_t size{0};                      // Size of this header (in bytes)
        int32_t width{0};                      // width of bitmap in pixels
        int32_t height{0};                     // width of bitmap in pixels
                                               //       (if positive, bottom-up, with origin in lower left corner)
                                               //       (if negative, top-down, with origin in upper left corner)
        uint16_t planes{1};                    // No. of planes for the target device, this is always 1
        uint16_t bit_count{0};                 // No. of bits per pixel
        uint32_t compression{0};               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
        uint32_t size_image{0};                // 0 - for uncompressed images
        int32_t x_pixels_per_meter{0};
        int32_t y_pixels_per_meter{0};
        uint32_t colors_used{0};               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
        uint32_t colors_important{0};          // No. of colors used for displaying the bitmap. If 0 all colors are required
    };

#pragma pack(pop)

    class BMPViewer {
    public:
        BMPViewer();
        ~BMPViewer();

    public:
        void read(const std::string &path);
        void show();

    private:
        void drawLine(int x1, int y1, int x2, int y2);
        void printImage();
        void save(const std::string &outputPath);
        std::string getOutputBMPFileName();

    private:
        BMPFileHeader file_header;
        BMPInfoHeader bmp_info_header;
        std::vector<uint8_t> pixelData;
    };

} // namespace BMP

#endif //ZADANIE_BMPVIEWER_H

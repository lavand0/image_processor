#include "bmp.h"

#include <fstream>
#include <ios>

namespace image_processor::image_format {

image::Image BMP::Read(const std::string &path) {
    std::ifstream file;

    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("File can't be read");
    }

    unsigned char file_header[BMP::FILE_HEADER_SIZE];
    unsigned char info_header[BMP::INFO_HEADER_SIZE];

    file.read(reinterpret_cast<char *>(file_header), BMP::FILE_HEADER_SIZE);
    file.read(reinterpret_cast<char *>(info_header), BMP::INFO_HEADER_SIZE);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Not a BMP file");
    }

    int width = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);  // NOLINT
    int height =
        (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);  // NOLINT

    image::Image image(width, height);

    const int padding_amount = ((4 - (width * 3) % 4) % 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char color[3];
            file.read(reinterpret_cast<char *>(color), 3);

            image.SetColor(
                image::Color{
                    .r = static_cast<float>(color[2]) / 255.0f,  // NOLINT
                    .g = static_cast<float>(color[1]) / 255.0f,  // NOLINT
                    .b = static_cast<float>(color[0]) / 255.0f,  // NOLINT
                },
                x, y);
        }
        file.ignore(padding_amount);
    }
    file.close();

    return image;
}

void BMP::Save(const image::Image &image, const std::string &path) {
    std::ofstream file;

    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("File can't be saved");
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (image.GetWidth() * 3) % 4) % 4);

    const int file_size = BMP::FILE_HEADER_SIZE + BMP::INFO_HEADER_SIZE + image.GetWidth() * image.GetHeight() * 3 +
                          padding_amount * image.GetHeight();

    unsigned char file_header[BMP::FILE_HEADER_SIZE];
    unsigned char info_header[BMP::INFO_HEADER_SIZE];

    BMP::CreateFileHeader(file_header, file_size);
    BMP::CreateInfoHeader(info_header, image.GetWidth(), image.GetHeight());

    file.write(reinterpret_cast<char *>(file_header), BMP::FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char *>(info_header), BMP::INFO_HEADER_SIZE);

    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            unsigned char r = static_cast<unsigned char>(image.GetColor(x, y).r * 255.0f);  // NOLINT
            unsigned char g = static_cast<unsigned char>(image.GetColor(x, y).g * 255.0f);  // NOLINT
            unsigned char b = static_cast<unsigned char>(image.GetColor(x, y).b * 255.0f);  // NOLINT

            unsigned char color[] = {b, g, r};

            file.write(reinterpret_cast<char *>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
    file.close();
}

void BMP::CreateFileHeader(unsigned char *file_header, const int file_size) const {
    // File type
    file_header[0] = 'B';
    file_header[1] = 'M';
    // File size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;   // NOLINT
    file_header[4] = file_size >> 16;  // NOLINT
    file_header[5] = file_size >> 24;  // NOLINT

    for (int i = 6; i < BMP::FILE_HEADER_SIZE; ++i) {  // NOLINT
        if (i == 10) {                                 // NOLINT
            // Pixel data offset
            file_header[i] = BMP::FILE_HEADER_SIZE + BMP::INFO_HEADER_SIZE;
            continue;
        }

        file_header[i] = 0;
    }
}

void BMP::CreateInfoHeader(unsigned char *info_header, const int width, const int height) const {
    // Header size
    info_header[0] = BMP::INFO_HEADER_SIZE;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;
    // Image width
    info_header[4] = width;
    info_header[5] = width >> 8;   // NOLINT
    info_header[6] = width >> 16;  // NOLINT
    info_header[7] = width >> 24;  // NOLINT
    // Image height
    info_header[8] = height;         // NOLINT
    info_header[9] = height >> 8;    // NOLINT
    info_header[10] = height >> 16;  // NOLINT
    info_header[11] = height >> 24;  // NOLINT
    // Planes
    info_header[12] = 1;  // NOLINT
    info_header[13] = 0;  // NOLINT
    // Bits per pixel (RGB)
    info_header[14] = 24;  // NOLINT

    for (int i = 15; i < BMP::INFO_HEADER_SIZE; ++i) {  // NOLINT
        info_header[i] = 0;
    }
    // X pixels per meter
    info_header[24] = 35;  // NOLINT
    info_header[25] = 46;  // NOLINT
    // Y pixels per meter
    info_header[28] = 35;  // NOLINT
    info_header[29] = 46;  // NOLINT
}

}  // namespace image_processor::image_format

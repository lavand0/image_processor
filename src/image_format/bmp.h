#pragma once

#include "image_format/format.h"

namespace image_processor::image_format {

class BMP : public IImageFormat {
public:
    const char FILE_HEADER_SIZE = 14;
    const char INFO_HEADER_SIZE = 40;

    image::Image Read(const std::string& path) override;
    void Save(const image::Image& image, const std::string& path) override;
    void CreateFileHeader(unsigned char* file_header, const int file_size) const;
    void CreateInfoHeader(unsigned char* info_header, const int width, const int height) const;
};

}  // namespace image_processor::image_format

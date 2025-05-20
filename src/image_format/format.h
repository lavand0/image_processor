#pragma once

#include <image/image.h>
#include <string_view>

namespace image_processor::image_format {

class IImageFormat {
public:
    IImageFormat() = default;
    virtual ~IImageFormat() = default;

    virtual image::Image Read(const std::string& path) = 0;
    virtual void Save(const image::Image& image, const std::string& path) = 0;
};

}  // namespace image_processor::image_format

#pragma once

#include "image/image.h"

#include <stdexcept>
#include <string>

namespace image_processor::image_filter {

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual image::Image Apply(const image::Image& image, std::vector<std::string> params) = 0;
};

}  // namespace image_processor::image_filter

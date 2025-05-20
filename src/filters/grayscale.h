#pragma once

#include "filter.h"

namespace image_processor::image_filter {

class FilterGrayscale : public Filter {

public:
    ~FilterGrayscale() override = default;
    image::Image Apply(const image::Image& image, std::vector<std::string> params) override;

    image::Image Grayscale(const image::Image& image);
};

}  // namespace image_processor::image_filter

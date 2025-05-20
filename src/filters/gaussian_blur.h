#pragma once

#include "matrix_filter.h"

namespace image_processor::image_filter {

class FilterGaussianBlur : public Filter {

public:
    ~FilterGaussianBlur() override = default;
    image::Image Apply(const image::Image& image, std::vector<std::string> params) override;

    image::Image GaussianBlur(const image::Image& image, float sigma);
};

}  // namespace image_processor::image_filter

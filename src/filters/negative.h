#pragma once

#include "filter.h"

namespace image_processor::image_filter {

class FilterNegative : public Filter {

public:
    ~FilterNegative() override = default;
    image::Image Apply(const image::Image& image, std::vector<std::string> params) override;

    image::Image Negative(const image::Image& image);
};

}  // namespace image_processor::image_filter

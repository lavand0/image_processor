#pragma once

#include "filter.h"

namespace image_processor::image_filter {

class FilterPixeling : public Filter {

public:
    FilterPixeling() = default;
    ~FilterPixeling() override = default;

    image::Image Apply(const image::Image &image, std::vector<std::string> params) override;

    image::Image Pixeling(const image::Image &image, int square);
};

}  // namespace image_processor::image_filter

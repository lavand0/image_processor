#pragma once

#include "filter.h"

namespace image_processor::image_filter {

class FilterCrop : public Filter {

public:
    ~FilterCrop() override = default;
    image::Image Apply(const image::Image& image, std::vector<std::string> params) override;

    image::Image Crop(const image::Image& image, int right, int down);
};

}  // namespace image_processor::image_filter

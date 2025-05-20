#pragma once

#include "matrix_filter.h"

namespace image_processor::image_filter {

class FilterEdgeDetection : public MatrixFilter {

public:
    image::Image Apply(const image::Image &image, std::vector<std::string> params) override;
};

}  // namespace image_processor::image_filter

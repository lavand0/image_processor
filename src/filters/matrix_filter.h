#pragma once

#include "filter.h"

namespace image_processor::image_filter {

struct Neighbor {
    int dx = 0;
    int dy = 0;
    float coef = 0.0;
};

class MatrixFilter : public Filter {

public:
    MatrixFilter() = default;
    explicit MatrixFilter(const std::vector<Neighbor> &matrix) : matrix(matrix){};
    ~MatrixFilter() override = default;

    image::Image Apply(const image::Image &image, std::vector<std::string> params) override;

    image::Image ApplyMatrix(const image::Image &image) const;

    std::vector<Neighbor> matrix;
};
}  // namespace image_processor::image_filter

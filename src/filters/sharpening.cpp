#include "sharpening.h"

namespace image_processor::image_filter {

static const MatrixFilter MATRIX({{0, 0, 5}, {1, 0, -1}, {-1, 0, -1}, {0, 1, -1}, {0, -1, -1}});

image::Image FilterSharpening::Apply(const image::Image &image, std::vector<std::string> params) {
    return MATRIX.ApplyMatrix(image);
}

}  // namespace image_processor::image_filter

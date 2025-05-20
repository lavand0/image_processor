#include "matrix_filter.h"

#include <algorithm>

namespace image_processor::image_filter {

image::Color ApplyToPixel(const image::Image &image, const std::vector<Neighbor> &matrix, int x_cur, int y_cur) {
    image::Color color_result;

    int x = 0;
    int y = 0;

    for (auto elem : matrix) {
        x = std::min(image.GetWidth() - 1, std::max(0, x_cur + elem.dx));
        y = std::min(image.GetHeight() - 1, std::max(0, y_cur + elem.dy));
        color_result = color_result + image.GetColor(x, y) * elem.coef;
    }

    color_result.r = std::min(1.0f, std::max(0.0f, color_result.r));
    color_result.g = std::min(1.0f, std::max(0.0f, color_result.g));
    color_result.b = std::min(1.0f, std::max(0.0f, color_result.b));

    return color_result;
}

image::Image MatrixFilter::ApplyMatrix(const image::Image &image) const {
    image::Image image_result(image.GetWidth(), image.GetHeight());

    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            image_result.SetColor(ApplyToPixel(image, matrix, x, y), x, y);
        }
    }
    return image_result;
}

image::Image MatrixFilter::Apply(const image::Image &image, std::vector<std::string> params) {
    return ApplyMatrix(image);
}

}  // namespace image_processor::image_filter

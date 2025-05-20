#include "gaussian_blur.h"

#include <cmath>
#include <numbers>

namespace image_processor::image_filter {

image::Image FilterGaussianBlur::Apply(const image::Image& image, std::vector<std::string> params) {
    try {
        std::stof(params[0]);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid command line argument of blur filter");
    }
    return GaussianBlur(image, std::stof(params[0]));
}

image::Image FilterGaussianBlur::GaussianBlur(const image::Image& image, float sigma) {
    std::vector<Neighbor> matrix;
    float divider = 0;

    for (int dx = static_cast<int>(-1.85 * sigma); dx <= static_cast<int>(1.85 * sigma); ++dx) {      // NOLINT
        for (int dy = static_cast<int>(-1.85 * sigma); dy <= static_cast<int>(1.85 * sigma); ++dy) {  // NOLINT
            double multiplier = 1.0f / (2 * std::numbers::pi * sigma * sigma) *
                                std::pow(std::numbers::e, -((static_cast<float>(dx * dx + dy * dy)) /
                                                            (static_cast<float>(2 * sigma * sigma))));
            matrix.push_back(Neighbor{dx, dy, static_cast<float>(multiplier)});
            divider += static_cast<float>(multiplier);
        }
    }
    for (auto& elem : matrix) {
        elem.coef /= divider;
    }
    auto* filter_ptr = new image_processor::image_filter::MatrixFilter(matrix);
    image::Image image_result = filter_ptr->ApplyMatrix(image);
    delete filter_ptr;

    return image_result;
}

}  // namespace image_processor::image_filter

#include "edge_detection.h"
#include "filters/grayscale.h"

#include <memory>
#include <string>

namespace image_processor::image_filter {

static const MatrixFilter MATRIX({{0, 0, 4}, {1, 0, -1}, {-1, 0, -1}, {0, 1, -1}, {0, -1, -1}});

image::Image FilterEdgeDetection::Apply(const image::Image& image, std::vector<std::string> params) {

    auto* filter_ptr = new image_processor::image_filter::FilterGrayscale;
    image::Image image_result = filter_ptr->Grayscale(image);
    delete filter_ptr;

    image_result = MATRIX.ApplyMatrix(image_result);

    try {
        std::stof(params[0]);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid command line argument of edge filter");
    }

    float threshold = std::stof(params[0]);

    image::Color black{0, 0, 0};
    image::Color white{1, 1, 1};

    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            if (image_result.GetColor(x, y).r > threshold) {
                image_result.SetColor(white, x, y);
            } else {
                image_result.SetColor(black, x, y);
            }
        }
    }

    return image_result;
}

}  // namespace image_processor::image_filter

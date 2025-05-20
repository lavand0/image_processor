#include "crop.h"

#include <string>

namespace image_processor::image_filter {

image::Image FilterCrop::Apply(const image::Image& image, std::vector<std::string> params) {
    try {
        std::stoi(params[0]);
        std::stoi(params[1]);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid command line argument of crop filter");
    }
    return Crop(image, std::stoi(params[0]), std::stoi(params[1]));
}

image::Image FilterCrop::Crop(const image::Image& image, int right, int down) {
    int width = std::min(image.GetWidth(), right);
    int height = std::min(image.GetHeight(), down);

    image::Image image_result(width, height);

    for (int y = image.GetHeight() - height; y < image.GetHeight(); ++y) {
        for (int x = 0; x < width; ++x) {
            image_result.SetColor(image.GetColor(x, y), x, y - image.GetHeight() + height);
        }
    }

    return image_result;
}

}  // namespace image_processor::image_filter

#include "pixeling.h"

#include <cstddef>

namespace image_processor::image_filter {

image::Image FilterPixeling::Apply(const image::Image &image, std::vector<std::string> params) {
    try {
        std::stoi(params[0]);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Invalid command line argument of pixeling filter");
    }
    return Pixeling(image, std::stoi(params[0]));
};

image::Image FilterPixeling::Pixeling(const image::Image &image, int square) {
    image::Image image_result(image.GetWidth(), image.GetHeight());

    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            if (x % square == 0 && y % square == 0) {
                image::Color color;
                size_t cnt = 0;
                for (int j = y; j < std::min(y + square, image.GetHeight()); ++j) {
                    for (int i = x; i < std::min(x + square, image.GetWidth()); ++i) {
                        color = color + image.GetColor(i, j);
                        ++cnt;
                    }
                }
                color = color / static_cast<float>(cnt);
                for (int j = y; j < std::min(y + square, image.GetHeight()); ++j) {
                    for (int i = x; i < std::min(x + square, image.GetWidth()); ++i) {
                        image_result.SetColor(color, i, j);
                    }
                }
            }
        }
    }
    return image_result;
}

}  // namespace image_processor::image_filter

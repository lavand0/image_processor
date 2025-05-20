#include "negative.h"

namespace image_processor::image_filter {

image::Color ToNegative(const image::Color& color) {
    return image::Color{1, 1, 1} - color;
}

image::Image FilterNegative::Apply(const image::Image& image, std::vector<std::string> params) {
    return Negative(image);
};

image::Image FilterNegative::Negative(const image::Image& image) {
    image::Image image_result(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            image_result.SetColor(ToNegative(image.GetColor(x, y)), x, y);
        }
    }
    return image_result;
};

}  // namespace image_processor::image_filter

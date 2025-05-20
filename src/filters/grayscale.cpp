#include "grayscale.h"

namespace image_processor::image_filter {

image::Color ToGray(const image::Color& color) {
    float res = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;  // NOLINT
    return image::Color{
        .r = res,
        .g = res,
        .b = res,
    };
}

image::Image FilterGrayscale::Apply(const image::Image& image, std::vector<std::string> params) {
    return Grayscale(image);
};

image::Image FilterGrayscale::Grayscale(const image::Image& image) {
    image::Image image_result(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            image_result.SetColor(ToGray(image.GetColor(x, y)), x, y);
        }
    }
    return image_result;
};

}  // namespace image_processor::image_filter

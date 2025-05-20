#include "image.h"

namespace image_processor::image {

Image::Image(int width, int height) : width_(width), height_(height), colors_(std::vector<Color>(width * height)) {
}

Image::~Image() {
}

Color Image::GetColor(int x, int y) const {
    return colors_[y * width_ + x];
}

void Image::SetColor(const Color &color, int x, int y) {
    colors_[y * width_ + x].r = color.r;
    colors_[y * width_ + x].g = color.g;
    colors_[y * width_ + x].b = color.b;
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

}  // namespace image_processor::image

#pragma once

#include "image/color.h"

#include <vector>

namespace image_processor::image {

class Image {
public:
    Image(int width, int height);
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    int GetWidth() const;
    int GetHeight() const;

private:
    int width_ = 0;
    int height_ = 0;
    std::vector<Color> colors_;
};

}  // namespace image_processor::image

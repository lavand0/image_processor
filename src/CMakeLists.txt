add_library(
    image_processor_lib

    args/args.cpp

    filters/filter.cpp
    filters/crop.cpp
    filters/edge_detection.cpp
    filters/gaussian_blur.cpp
    filters/grayscale.cpp
    filters/matrix_filter.cpp
    filters/negative.cpp
    filters/pixeling.cpp
    filters/sharpening.cpp

    image/color.cpp
    image/image.cpp

    image_format/bmp.cpp
    image_format/format.cpp
)

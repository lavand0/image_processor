include_directories(src)

add_executable(
    image_processor
    
    bin/main.cpp

    src/args/args.cpp

    src/filters/filter.cpp
    src/filters/crop.cpp
    src/filters/edge_detection.cpp
    src/filters/gaussian_blur.cpp
    src/filters/grayscale.cpp
    src/filters/matrix_filter.cpp
    src/filters/negative.cpp
    src/filters/pixeling.cpp
    src/filters/sharpening.cpp

    src/image/color.cpp
    src/image/image.cpp

    src/image_format/bmp.cpp
    src/image_format/format.cpp
)

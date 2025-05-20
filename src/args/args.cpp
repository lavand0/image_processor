#include "args.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/gaussian_blur.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/pixeling.h"
#include "filters/sharpening.h"

namespace image_processor::args {

namespace {

bool IsValidFilterName(std::string_view name) {
    return name.size() > 2 && name.starts_with('-');
}

}  // namespace

Args::Filter::Filter(std::string_view name, std::vector<std::string>&& parameters)
    : name_(name), parameters_(std::move(parameters)) {
}

std::string_view Args::Filter::Name() const {
    return name_;
}

Args::Args(int argc, char** argv) : input_file_(), output_file_(), filters_() {
    if (argc < 3) {
        throw std::runtime_error("USAGE: image_processor [INPUT_FILE] [OUTPUT_FILE] [[FILTER] [FILTER_PARAMS]...]...");
    }
    input_file_ = argv[1];
    output_file_ = argv[2];

    for (size_t i = 3; i < static_cast<size_t>(argc);) {
        std::string filter_name = argv[i];
        if (!IsValidFilterName(filter_name)) {
            throw std::runtime_error("not valid filter name [" + std::string(filter_name) + "]");
        }
        ++i;
        std::vector<std::string> params;
        for (; i < static_cast<size_t>(argc) && !IsValidFilterName(argv[i]); ++i) {
            params.push_back(argv[i]);
        }
        filters_.emplace_back(filter_name.substr(1), std::move(params));
    }
}

const std::vector<std::string>& Args::Filter::Parameters() const {
    return parameters_;
}

const std::string& Args::InputFile() const {
    return input_file_;
}

const std::string& Args::OutputFile() const {
    return output_file_;
}

const std::vector<Args::Filter>& Args::Filters() const {
    return filters_;
}

image_processor::image_filter::Filter* Args::Filter::GetFilter() const {
    if (name_ == "crop") {
        auto* filter_ptr = new image_processor::image_filter::FilterCrop;
        return filter_ptr;
    } else if (name_ == "gs") {
        auto* filter_ptr = new image_processor::image_filter::FilterGrayscale;
        return filter_ptr;
    } else if (name_ == "neg") {
        auto* filter_ptr = new image_processor::image_filter::FilterNegative;
        return filter_ptr;
    } else if (name_ == "sharp") {
        auto* filter_ptr = new image_processor::image_filter::FilterSharpening;
        return filter_ptr;
    } else if (name_ == "edge") {
        auto* filter_ptr = new image_processor::image_filter::FilterEdgeDetection;
        return filter_ptr;
    } else if (name_ == "blur") {
        auto* filter_ptr = new image_processor::image_filter::FilterGaussianBlur;
        return filter_ptr;
    } else if (name_ == "pix") {
        auto* filter_ptr = new image_processor::image_filter::FilterPixeling;
        return filter_ptr;
    } else {
        throw std::runtime_error("Filter " + name_ + " does not exist");
    }
}

}  // namespace image_processor::args

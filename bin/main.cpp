#include "args/args.h"
#include "image_format/bmp.h"
#include "filters/filter.h"

#include <vector>

int main(int argc, char** argv) {
    image_processor::args::Args args(argc, argv);
    image_processor::image_format::BMP bmp;

    auto image = bmp.Read(args.InputFile());

    for (const auto& filter : args.Filters()) {
        auto* filter_ptr = filter.GetFilter();
        image = filter_ptr->Apply(image, filter.Parameters());
        delete filter_ptr;
    }

    bmp.Save(image, args.OutputFile());
    return 0;
}

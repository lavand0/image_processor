#pragma once

#include "filters/filter.h"

#include <string>

namespace image_processor::args {

class Args {
public:
    class Filter {
    public:
        Filter(std::string_view name, std::vector<std::string>&& parameters);
        std::string_view Name() const;
        const std::vector<std::string>& Parameters() const;
        image_processor::image_filter::Filter* GetFilter() const;

    private:
        std::string name_;
        std::vector<std::string> parameters_;
    };

public:
    Args(int argc, char** argv);

    Args() = default;
    ~Args() = default;

    const std::string& InputFile() const;
    const std::string& OutputFile() const;
    const std::vector<Filter>& Filters() const;

private:
    std::string input_file_;
    std::string output_file_;
    std::vector<Filter> filters_;
};

}  // namespace image_processor::args

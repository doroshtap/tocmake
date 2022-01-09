#ifndef __TOCMAKE_CMAKE_GENERATOR_HPP__
#define __TOCMAKE_CMAKE_GENERATOR_HPP__

#include <tocmake/types.hpp>
#include <string>
#include <vector>

namespace tocmake {
    class cmake_generator {
    public:
        cmake_generator(std::wstring project_name, std::wstring input_dir, std::wstring output_dir);

        void set_target(project_type type);
        void set_sources(std::vector<std::wstring> sources);
        void generate();
    private:
        std::wstring proj;
        std::wstring input_dir;
        std::wstring output_dir;
        std::vector<std::wstring> sources;
        project_type type;
    };
}

#endif // __TOCMAKE_CMAKE_GENERATOR_HPP__

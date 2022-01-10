#include <tocmake/cmake_generator.hpp>
#include <tocmake/logging.hpp>
#include <tocmake/utils.hpp>
#include <filesystem>
#include <fstream>

#pragma warning(push)
#pragma warning(disable: 4715)
static std::wstring vector_to_string(std::vector<std::wstring> sources) {
    if (sources.size() == 0) {
        tocmake::log_err(L"No sources in project selected!");
    } else if (sources.size() == 1) {
        std::wstring res = sources[0];
        std::replace(res.begin(), res.end(), '\\', '/');
        return res;
    } else {
        std::wstring result = sources[0];
        std::replace(result.begin(), result.end(), '\\', '/');

        for (std::size_t i = 1; i < sources.size(); i++) {
            std::wstring temp = sources[i];
            std::replace(temp.begin(), temp.end(), '\\', '/');
            result += L' ' + temp;
        }

        return result;
    }
}
#pragma warning(pop)

tocmake::cmake_generator::cmake_generator(std::wstring project_name, std::wstring input_dir, std::wstring output_dir) {
    this->proj = project_name;
    this->input_dir = input_dir;
    this->output_dir = output_dir;
}

void tocmake::cmake_generator::set_target(tocmake::project_type type) {
    this->type = type;
}

void tocmake::cmake_generator::set_sources(std::vector<std::wstring> sources) {
    this->sources = sources;
}

void tocmake::cmake_generator::generate() {
    std::wofstream cmake_file;

    cmake_file.open(output_dir + L"\\CMakeLists.txt");

    // Minimum version of CMake(3.6 by default)
    cmake_file << "cmake_minimum_required(VERSION 3.6)\n";
    cmake_file << "project(" << proj << ")\n";
    // Generate executable/static or dynamic library
    if (type == application) {
        // Application
        cmake_file << "add_executable(" << proj << " " << vector_to_string(sources) << ")";
    } else if (type == static_library) {
        // Static Library
        cmake_file << "add_library(" << proj << " STATIC " << vector_to_string(sources) << ")";
    } else {
        // Dynamic Library
        cmake_file << "add_library(" << proj << " SHARED " << vector_to_string(sources) << ")";
    }

    cmake_file.close();

    // Now, copy all source files from project.
    // CHECK TODO LATER!!!!!
    for (const auto& src : sources) {
        std::wstring source = std::format(L"{}\\{}", input_dir, src);
        std::wstring target = std::format(L"{}\\{}", output_dir, src);
        
        std::filesystem::create_directories(std::filesystem::path(target).parent_path());

        tocmake::copy_file(source, target);
    }
}

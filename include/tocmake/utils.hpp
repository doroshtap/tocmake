#ifndef __TOCMAKE_UTILS_HPP__
#define __TOCMAKE_UTILS_HPP__

#include <filesystem>
#include <fstream>
#include <string>

namespace tocmake {
    inline std::wstring parent_dir(std::wstring path) {
        return std::filesystem::path(path).parent_path();
    }

    inline bool not_dir(std::wstring path) {
        return std::filesystem::is_directory(path);
    }

    inline bool exists(std::wstring path) {
        return std::filesystem::exists(path);
    }

    inline void create_dir(std::wstring path) {
        std::filesystem::create_directory(path);
    }

    inline void copy_file(std::wstring src, std::wstring dst) {
        std::wifstream source_file(src, std::ios::binary);
        std::wofstream output_file(dst, std::ios::binary);
        output_file << source_file.rdbuf();
        source_file.close();
        output_file.close();
    }
}

#endif // __TOCMAKE_UTILS_HPP__

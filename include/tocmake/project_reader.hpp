#ifndef __TOCMAKE_PROJECT_READER_HPP__
#define __TOCMAKE_PROJECT_READER_HPP__

#include <tocmake/types.hpp>
#include <string>
#include <vector>
#include <map>

namespace tocmake {
    class project_reader {
    public:
        project_reader(std::wstring path);

        project_type get_project_type();

        std::vector<std::wstring> get_sources();
    private:
        std::wstring path;
    };
}

#endif // __TOCMAKE_PROJECT_READER_HPP__

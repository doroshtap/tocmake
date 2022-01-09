#include <tocmake/project_reader.hpp>
#include <tocmake/logging.hpp>
#include <pugixml/pugixml.hpp>
#include <iostream>

static std::string charts_to_string(const pugi::char_t* raw) {
    std::string res;

    for (std::size_t i = 0; raw[i] != '\0'; i++) {
        res.push_back((char)raw[i]);
    }

    return res;
}

tocmake::project_reader::project_reader(std::wstring path) {
    this->path = path;
}

tocmake::project_type tocmake::project_reader::get_project_type() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result) log_err(L"Failed to parse project file `{}`", std::wstring(path.begin(), path.end()));

    for (pugi::xml_node param : doc.child(L"Project").children(L"PropertyGroup")) {
        if (!param.child(L"ConfigurationType")) continue;

        std::wstring t = param.child(L"ConfigurationType").child_value();
        if (t == L"Application") {
            return project_type::application;
        } else if (t == L"StaticLibrary") {
            return project_type::static_library;
        } else if (t == L"DynamicLibrary") {
            return project_type::dynamic_library;
        } else {
            log_err(L"Unsupported project type: `{}`", t);
        }
    }

    return project_type::application;
}

std::vector<std::wstring> tocmake::project_reader::get_sources() {
    std::vector<std::wstring> sources;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result) log_err(L"Failed to parse project file `{}`", std::wstring(path.begin(), path.end()));

    for (pugi::xml_node item : doc.child(L"Project").children(L"ItemGroup")) {
        for (pugi::xml_node src : item.children(L"ClCompile")) {
            sources.push_back(std::wstring(src.attribute(L"Include").value()));
        }

        for (pugi::xml_node inc : item.children(L"ClInclude")) {
            sources.push_back(std::wstring(inc.attribute(L"Include").value()));
        }
    }

    return sources;
}

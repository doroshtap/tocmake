#include <tocmake.hpp>
#include <iostream>
#include <cwctype>
#include <format>

int main(int argc, char* argv[]) {
    tocmake::ArgumentParser program("tcm", "0.2.0");

    program.add_argument("-y", "--yes")
        .help("skip all 'questions'")
        .default_value(false)
        .implicit_value(true);
    
    program.add_argument("-V", "--verbose")
        .help("be verbose")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-s", "--source")
        .required()
        .help("source directory which contains .sln-based project");

    program.add_argument("-o", "--output")
        .required()
        .help("output directory where will be copied project, but it will use CMake instead");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    auto src_s = program.get<std::string>("-s");
    auto out_s = program.get<std::string>("-o");
    std::wstring src(src_s.begin(), src_s.end());
    std::wstring out(out_s.begin(), out_s.end());

    std::transform(src.begin(), src.end(), src.begin(), [](wchar_t c){return std::towlower(c);});
    std::transform(out.begin(), out.end(), out.begin(), [](wchar_t c){return std::towlower(c);});

    if (src == out) {
        tocmake::log_err(L"source directory(`{}`) can't be an output directory(`{}`).", src, out); // Automatically exits
    }

    tocmake::sln_reader sln(src, program.get<bool>("-y"));
    auto projects = sln.collect_projects();

    for (const auto& project : projects) {
        tocmake::log_info(L"Project: `{}`, Path: `{}`", project.first, project.second);
        tocmake::project_reader proj(project.second);
        
        auto type = proj.get_project_type();
        if (program.get<bool>("-V")) { // Verbose
            if (type == tocmake::project_type::application) tocmake::log_info(L"Project Type: Application");
            else if (type == tocmake::project_type::static_library) tocmake::log_info(L"Project Type: Static Library");
            else if (type == tocmake::project_type::dynamic_library) tocmake::log_info(L"Project Type: Dynamic Library");
        }
        auto sources = proj.get_sources();

        if (program.get<bool>("-V")) { // Verbose
            for (const auto& src : sources) {
                tocmake::log_ok(L"Found source file: {}", src);
            }
        }

        tocmake::create_dir(out);
        tocmake::create_dir(out + L'\\' + project.first);
        tocmake::cmake_generator cmake(project.first, tocmake::parent_dir(project.second), out + L'\\' + project.first);
        cmake.set_target(type);
        cmake.set_sources(sources);
        cmake.generate();
    }

    return 0;
}

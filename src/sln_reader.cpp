#include <tocmake/sln_reader.hpp>
#include <tocmake/logging.hpp>
#include <filesystem>
#include <fstream>
#include <cwctype>

void tocmake::sln_reader::advance() {
    pos++;
    if (pos >= current_line.length()) cur = '\0';
    else cur = current_line[pos];
}

wchar_t tocmake::sln_reader::peek() {
    if (pos + 1 >= current_line.length()) return '\0';
    return current_line[pos + 1];
}

void tocmake::sln_reader::whitespace() {
    while (cur == ' ' || cur == '\t' || cur == '\r') advance();
}

void tocmake::sln_reader::skip_ident() {
    whitespace();
    std::size_t start = pos;
    while (std::iswalnum(peek())) {
        advance();
    }
    advance();
}

void tocmake::sln_reader::skip_lparen() {
    whitespace();
    if (cur == '(') {
        advance();
    } else {
        log_err(L"Left parenthesis was expected, after defining project(in solution file)");
    }
}

void tocmake::sln_reader::skip_rparen() {
    whitespace();
    if (cur == ')') {
        advance();
    } else {
        log_err(L"Right parenthesis was expected, after defining project(in solution file)");
    }
}

void tocmake::sln_reader::skip_equals() {
    whitespace();
    if (cur == '=') {
        advance();
    } else {
        log_err(L"Equals sign was expected, after defining project(in solution file)");
    }
}

void tocmake::sln_reader::skip_comma() {
    whitespace();
    if (cur == ',') {
        advance();
    } else {
        log_err(L"Comma sign was expected, after defining name, path etc. of project(in solution file)");
    }
}

std::wstring tocmake::sln_reader::collect_string() {
    whitespace();
    advance();
    std::size_t start = pos;

    while (cur != '\"') {
        advance();
    }

    std::wstring str = current_line.substr(start, pos - start);
    advance();
    return str;
}

inline auto pair_by_index(const std::map<std::wstring, std::wstring>& map, std::size_t index) {
    auto it = map.begin();
    std::advance(it, index);
    return it;
}

inline void check_map(const std::map<std::wstring, std::wstring>& projects) {
    std::map<std::wstring, std::wstring> copy = projects;

    for (std::size_t i = 0; i < projects.size() - 1; i++) {
        for (std::size_t j = 1; j < copy.size(); j++) {
            auto proj = pair_by_index(projects, i);
            auto cproj = pair_by_index(copy, j);
            if (proj->first == cproj->first || proj->second == cproj->second) {
                tocmake::log_err(L"Found projects with the same names or paths.\nProject 1: {}\nPath    1: {}\nProject 2: {}\nPath    2: {}", proj->first, proj->second, cproj->first, cproj->second);
            }
        }
    }
}

inline bool starts_with(const std::wstring& str, const std::wstring& ending) {
    if (str.length() >= ending.length()) {
        return (0 == str.rfind(ending, 0));
    } else {
        return false;
    }
}

inline bool ends_with(const std::wstring& str, const std::wstring& ending) {
    if (str.length() >= ending.length()) {
        return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

tocmake::sln_reader::sln_reader(std::wstring dirpath, bool answer_yes) {
    /*
    dirpath/
        solution.sln
        project/
            project.vcxproj
    */
    this->dir_path = dirpath;
    this->pos = 0;
    this->cur = 0;

    using dir_it = std::filesystem::recursive_directory_iterator;
    std::vector<std::wstring> paths;

    for (const auto& entry: dir_it(dirpath)) {
        if (!entry.is_regular_file()) continue;
        else {
            if (!ends_with(entry.path(), L".sln")) continue;
            else {
                paths.push_back(entry.path());
            }
        }
    }

    if (paths.size() == 0) log_err(L"Not found any .sln file in directory!");
    else if (paths.size() == 1) {
        if (!answer_yes) {
            std::wcout << ansi::foreground_bold << ansi::foreground_blue << L"[INFO]: " << ansi::reset << L"Is `" + paths[0] + L"` a right solution file? [y/n] ";
            std::wstring answer;
            std::wcin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), [](wchar_t c){return std::towlower(c);});
            if (answer == L"y" || answer == L"yes") {
                log_ok(L"Solution file has been found");
                this->solution_path = paths[0];
            } else if (answer == L"n" || answer == L"no") {
                log_err(L"Right solution file has not been found");
            } else {
                log_err(L"Unknown option selected");
            }
        } else {
            this->solution_path = paths[0];
        }
    } else {
        for (int i = 0; i < paths.size(); i++) {
            std::wcout << "[" << i + 1 << "] " << paths[i] << std::endl;
        }
        
        std::wcout << "Choose what .sln file from list: ";
        int index; std::cin >> index; index--;
        if (index >= paths.size() || index < 0) log_err(L"Incorrect option selected");

        this->solution_path = paths[index];
    }
}

// map<name, path>
std::map<std::wstring, std::wstring> tocmake::sln_reader::collect_projects() {
    std::map<std::wstring, std::wstring> projects;

    std::wifstream file(solution_path);
    
    while (std::getline(file, current_line)) {
        // Starts with
        if (starts_with(current_line, L"Project")) {
            pos = 0;
            cur = current_line[pos];
            skip_ident();
            skip_lparen();
            collect_string();
            skip_rparen();
            skip_equals();
            std::wstring name = collect_string();
            skip_comma();
            std::wstring path = collect_string();
            projects.insert(std::make_pair(name, dir_path + L'\\' + path));
            check_map(projects); // Can log an error and exit
        } else {
            continue;
        }
    }

    file.close();

    return projects;
}

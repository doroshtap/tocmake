#ifndef __TOCMAKE_SLN_HPP__
#define __TOCMAKE_SLN_HPP__

#include <string>
#include <map>

namespace tocmake {
    class sln_reader {
    public:
        sln_reader(std::wstring dirpath);

        std::map<std::wstring, std::wstring> collect_projects();
    private:
        void advance();
        wchar_t peek();
        void whitespace();

        void skip_ident();
        void skip_lparen();
        void skip_rparen();
        std::wstring collect_string();
        void skip_equals();
        void skip_comma();

        std::wstring dir_path;
        std::wstring solution_path;
        std::wstring current_line;
        std::size_t pos;
        wchar_t cur;
    };
}

#endif // __TOCMAKE_SLN_HPP__

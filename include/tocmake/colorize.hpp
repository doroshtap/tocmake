#ifndef __TOCMAKE_COLORIZE_HPP__
#define __TOCMAKE_COLORIZE_HPP__

#include <ostream>

namespace tocmake {
    namespace ansi {
        constexpr char reset[] = "\033[0m";
        constexpr char foreground_bold[] = "\033[1m";
        constexpr char foreground_red[] = "\033[31m";
        constexpr char foreground_yellow[] = "\033[33m";
        constexpr char foreground_blue[] = "\033[34m";
        constexpr char foreground_green[] = "\033[32m";
    }

    /*class ansi {
        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & reset(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[0m";
            return os;
            //return (os << "\033[0m");
        }

        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & foreground_bold(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[1m";
            return os;
            //return (os << "\033[1m");
        }

        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & foreground_red(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[31m";
            return os;
            //return (os << "\033[31m");
        }

        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & foreground_yellow(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[33m";
            return os;
            //return (os << "\033[33m");
        }

        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & foreground_blue(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[34m";
            return os;
            //return (os << "\033[34m");
        }

        template <class CharT, class Traits>
        constexpr std::basic_ostream<CharT, Traits> & foreground_green(std::basic_ostream<CharT, Traits> &os) {
            os << "\033[32m";
            return os;
            //return (os << "\033[32m");
        }
    };*/
}

#endif // __TOCMAKE_COLORIZE_HPP__

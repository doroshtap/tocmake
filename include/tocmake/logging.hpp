#ifndef __TOCMAKE_LOGGING_HPP__
#define __TOCMAKE_LOGGING_HPP__

#include <tocmake/colorize.hpp>
#include <iostream>
#include <format>

namespace tocmake {
    template <typename... Args>
    void log_ok(std::wstring fmt, Args&&... args) {
        std::wcout << ansi::foreground_bold << ansi::foreground_green << "[OK]: " << ansi::reset << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
    
    template <typename... Args>
    void log_err(std::wstring fmt, Args&&... args) {
        std::wcout << ansi::foreground_bold << ansi::foreground_red << "[ERROR]: " << ansi::reset << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
    
    template <typename... Args>
    void log_warn(std::wstring fmt, Args&&... args) {
        std::wcout << ansi::foreground_bold << ansi::foreground_yellow << "[WARNING]: " << ansi::reset << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
    
    template <typename... Args>
    void log_info(std::wstring fmt, Args&&... args) {
        std::wcout << ansi::foreground_bold << ansi::foreground_blue << "[INFO]: " << ansi::reset << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
}

#endif // __TOCMAKE_LOGGING_HPP__

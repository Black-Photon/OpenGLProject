#ifndef SPACIALFREEZE_LOGGER_H
#define SPACIALFREEZE_LOGGER_H

using std::string;

namespace logger {
    void message(const string& s) noexcept(true);
    void warn(const string& s) noexcept(true);
    void error(const string& s) noexcept(true);
    // Use only for the last error printed
    void fatal(const string& s) noexcept(true);
    /**
     * Creates a fatal error, symbolising a crash in the application
     * @param s Message to show
     * @param loader Module or type of error
     */
    void fatal(const string& s, const string& loader) noexcept(true);
}

#endif //SPACIALFREEZE_LOGGER_H

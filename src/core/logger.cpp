using std::cout;
using std::cerr;
using std::endl;
using std::string;

namespace logger {
    void message(const string& s) noexcept(true) {
        cout << "[INFO] " << s << endl;
    }

    void warn(const string& s) noexcept(true) {
        cout << "[WARN] " << s << endl;
    }

    void error(const string& s) noexcept(true) {
        cerr << "[ERROR] " << s << endl;
    }

    void fatal(const string& s) noexcept(true) {
        cerr << "[FATAL] " << s << endl;
    }

    void fatal(const string& s, const string& loader) noexcept(true) {
        fatal(s);
        cerr << "        Error Occurred in Module " << loader << endl;
    }
}
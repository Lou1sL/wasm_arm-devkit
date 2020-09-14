#include <string>
#include <ostream>

#define WASM_ARM_CONSOLE_BUFFER ((volatile uint32_t * const) 0x001FF00)

class warm {
public:
    static std::string msg;
    struct COut {
        COut & operator<< (const std::string& str) {
            for(std::size_t i=0;i<str.length();i++) WASM_ARM_CONSOLE_BUFFER[i] = str[i];
            return *this;
        }
    };
    static COut cout;
};
#include <iostream>
#include <cstring>
#include "huffman.h"

class ParameterParserException : public std::logic_error {
public:
    ParameterParserException(std::string _message) : logic_error(_message) {}
};

class ParameterParser {
public:
    ParameterParser() {}
    ParameterParser(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "-o")) {
                if (i +  1 < argc) {
                    parameters[argv[i]] = argv[i + 1];
                } else {
                    throw ParameterParserException("Incorrect parameter value");
                }
                i++;
            } else if (!strcmp(argv[i], "-c")) {
                mode = 1;
            } else if (!strcmp(argv[i], "-u")) {
                mode = 2;
            } else {
                throw ParameterParserException("Incorrect parameters name");
            }

            if (!mode) {
                throw ParameterParserException("Incorrect mode descriprion");
            }
        }
    }

    std::string get_value(std::string key) noexcept {
        return parameters[key];
    }

    int get_mode() const noexcept {
        return mode;
    }
private:
    std::map<std::string, std::string> parameters;
    int mode = 0;
};

int main(int argc, char** argv) {

    ParameterParser parameters;

    try {
        parameters = ParameterParser(argc, argv);
    } catch (ParameterParserException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    std::string input = parameters.get_value("-f");

    std::string output = parameters.get_value("-o");

    int mode = parameters.get_mode();
    
    HuffmanArchiver arc = HuffmanArchiver(mode, input, output);

    if (mode == 1) {
        auto result = arc.print_archived();
        std::cout << result.real << std::endl << result.archived << std::endl << result.additional << std::endl;
    } else {
        auto result = arc.read_archived();
        std::cout << result.archived << std::endl << result.real << std::endl << result.additional << std::endl;
    }

    return 0;
}
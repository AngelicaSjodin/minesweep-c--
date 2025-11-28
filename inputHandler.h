#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <optional>
#include <string>

struct Command {
    char type;  // 'r', 'f', 'q'
    int row;
    int col;
};

class InputHandler {
public:
    std::optional<Command> parse(const std::string &line);
};

#endif
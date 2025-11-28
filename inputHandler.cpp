#include "inputhandler.h"
#include <sstream>
#include <cctype>

std::optional<Command> InputHandler::parse(const std::string &line) {
    std::istringstream iss(line); 
    char t;
    int r, c;

    if (!(iss >> t))
        return std::nullopt;

    t = std::tolower(t);

    if (t == 'q') {
        return Command{t, -1, -1};
    }

    if (!(iss >> r >> c))
        return std::nullopt;

    if (r <= 0 || c <= 0)
        return std::nullopt;

    return Command{t, r, c};
}
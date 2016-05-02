#include "TaskReader.h"
#include <unistd.h>
#include <algorithm>

std::string TaskReader::nextLine() {
    std::vector<char> buffer(BUFFER_SIZE, 0);

    std::string result = "";
    ssize_t read_characters_count;
    while ((read_characters_count = read(STDIN_FILENO, buffer.data(), BUFFER_SIZE)) > 0) {
        result.append(buffer.data(), (unsigned long) read_characters_count);
        if(buffer[read_characters_count - 1] == '\n') {
            result.pop_back();
            return result;
        }
    }
    if(read_characters_count < 0) {
        perror("Error while reading comand");
    }

    return result;
}

std::vector<Task> TaskReader::getComands() {
    auto parts = Utils::split(nextLine(), '|');
    std::vector<Task> comands;
    std::transform(parts.begin(), parts.end(), std::back_inserter(comands),
                   [](std::string s) {return Task(s);}
    );
    return comands;
}

#ifndef MIDTERMSH_COMANDREADER_H
#define MIDTERMSH_COMANDREADER_H

#include <string>
#include <vector>
#include "Task.h"

class TaskReader {
private:
    static const int BUFFER_SIZE = 1024;
    std::string nextLine();
public:
    std::vector<Task> getComands();
};


#endif //MIDTERMSH_COMANDREADER_H

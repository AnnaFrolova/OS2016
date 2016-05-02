#include "TaskReader.h"
#include "Task.h"
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <signal.h>
#include <iostream>

std::vector<pid_t> pids;

void start_tasks(std::vector<Task> tasks, std::vector<pid_t> &pids) {
    int pipe1[2], pipe2[2];
    for(auto task_it = tasks.begin(); task_it != tasks.end(); ++task_it) {
        pipe(pipe2);
        pid_t pid = fork();
        if (pid) {
            if (task_it != tasks.begin()) {
                close(pipe1[0]);
                close(pipe1[1]);
            }
            if(task_it == (--tasks.end())) {
                close(pipe2[0]);
                close(pipe2[1]);
            }

            pids.push_back(pid);
            int status;
            waitpid(pid, &status, 0);
        } else {
            if (task_it != tasks.begin()) {
                dup2(pipe1[0], STDIN_FILENO);
                close(pipe1[0]);
                close(pipe1[1]);
            }
            if(task_it != (--tasks.end())) {
                dup2(pipe2[1], STDOUT_FILENO);
            }
            close(pipe2[0]);
            close(pipe2[1]);

            std::vector<char *> ops {strdup(task_it->name.c_str())};
            for(auto op: task_it->operands) {
                ops.push_back(strdup(op.c_str()));
            }
            ops.push_back(NULL);
            execvp(task_it->name.c_str(), ops.data());
        }
        pipe1[0] = pipe2[0];
        pipe1[1] = pipe2[1];
    }
}

void sig_handler(int sig) {
    std::cerr << "SIGINT!!!\n";
    for (pid_t pid : pids) {
        kill(pid, sig);
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = &sig_handler;
    sigaction(SIGINT, &act, NULL);

    TaskReader reader;

    while(true) {
        write(STDOUT_FILENO, "$", 1);
        auto tasks = reader.getComands();
        if (tasks.empty()) {
            break;
        }
        start_tasks(tasks, pids);
        pids.clear();
    }
}

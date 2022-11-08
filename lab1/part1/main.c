// Program to illustrate the command ls / | wc -l
#include <sys/wait.h>
#include <unistd.h>
#include "../../utilities.c"

int main() {
    int fd[2]; // create a pipe
    if (pipe(fd) == -1) 
        errExit("pipe");

    pid_t pid = fork();
    if (pid == -1) 
        errExit("fork");
    else if (pid == 0) { // child
        if (close(fd[0]) == -1) // close unused read end
            errExit("close");
        dup2(fd[1], STDOUT_FILENO); // change starnard output to pipe
        if (close(fd[1]) == -1) // close unused write end
            errExit("close");
        char *const args[] = {"ls", "/", NULL}; // create array of arguments
        if (execv("/bin/ls", args) == -1) // replace process with ls program
            errExit("execv");
    }
    else { // parent
        if (close(fd[1]) == -1) // close unused write end
            errExit("close");
        dup2(fd[0], STDIN_FILENO); // change starnard input to pipe
        if (close(fd[0]) == -1) // close unused read end
            errExit("close");
        wait(NULL); // wait for child process to finish
        char *const args[] = {"wc", "-l", NULL}; // create array of arguments
        if (execv("/bin/wc", args) == -1) // replace process with wc program
            errExit("execv");
    }
}

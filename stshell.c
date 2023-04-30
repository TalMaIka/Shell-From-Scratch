#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <signal.h>

void childExit(int sig)
{
    printf("Child process terminated.\n");
}

void actualWriting(int fileDIN, int fileDOUT){
    if (fileDIN != 0)
        {
            dup2(fileDIN, 0); // Redirects input to FD.
            close(fileDIN);
        }

        if (fileDOUT != 1)
        {
            dup2(fileDOUT, 1); // Redirects output to FD.
            close(fileDOUT);
        }
}

void writeOut(int outMod, char *outFile){
    if (outMod == 1)
        { // overwrite output
            int fd = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // File descriptor with 'write' mod.
            if (fd < 0)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, 1); // Redirects output to FD.
            close(fd);
        }
        else if (outMod == 2)
        { // append to output
            int fd = open(outFile, O_WRONLY | O_CREAT | O_APPEND, 0644); // File descriptor with 'append' mod.
            if (fd < 0)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, 1); // Redirects output to FD.
            close(fd);
        }
}

void commandExec(char *argv[], int outMod, char *outFile, int fileDIN, int fileDOUT)
{
    if (fork() == 0) // If the process is a inner/child.
    {
        writeOut(outMod,outFile); // Check if there is a output redirect and what mode.
        actualWriting(fileDIN,fileDOUT); // Will write to a file in case of redirection.

        if (execvp(argv[0], argv) == -1) // Checks for errors
        {
            printf("Error (execvp): "); 
            exit(1);
        }
    }
    else
    {
        wait(NULL); // Waiting for the child process to finish running.
    }
}

int main(int argc, char **argv)
{
    int outMod = 0; // Permission flag - 0 for "w" and 1 for "a"
    int i, j, status;
    char cmd[1024];
    char *token;
    char *cd_exit[] = {"cd", "exit"};
    signal(2, childExit); // Will exit the inner process (Child only!)
    char *outFile = NULL;

    while (1)
    {
        // Path indicator.
        char path[1024];
        getcwd(path, sizeof(path));
        printf("%s$ ", path);

        fgets(cmd, 1024, stdin);
        cmd[strlen(cmd) - 1] = '\0'; // replace \n with \0

        /* parse cmd line */
        i = 0;
        token = strtok(cmd, " ");
        while (token != NULL)
        {
            if (strcmp(token, ">") == 0)
            {
                outMod = 1;
                token = strtok(NULL, " ");
                outFile = token;
                break;
            }
            else if (strcmp(token, ">>") == 0)
            {
                outMod = 2;
                token = strtok(NULL, " ");
                outFile = token;
                break;
            }
            else
            {
                argv[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
        }
        argv[i] = NULL;

        /* Is cmd empty */
        if (argv[0] == NULL)
            continue;

        /* for built-in cmds */
        for (j = 0; j < 2; j++)
        {
            if (strcmp(argv[0], cd_exit[j]) == 0)
            {
                // cd -> Change dir.
                if (strcmp(argv[0], "cd") == 0)
                {
                    if (argv[1] == NULL)
                    {
                        // empty arg when exec cd.
                        chdir(getenv("HOME"));
                    }
                    else if (chdir(argv[1]) != -1)
                    {
                        chdir(argv[1]);
                    }
                    else
                    {
                        if (chdir(argv[1]) == -1) // Will print an error if path is not valid.
                        {
                            printf("Error: CD"); 
                        }
                        else
                        {
                            continue;
                        }
                    }
                }

                // Checks for exit keyword in the first argument.
                else if (strcmp(argv[0], "exit") == 0)
                {
                    exit(1);
                }
                break;
            }
        }
        /* for commands not part of the shell command language */
        if (j == 2)
        {

            int pipeCommands[128] = {0}; // Pipes argv array.
            int pipeFD[2 * 128];         // Two file descriptors for each pipe.
            int pipeCount = 0;

            // find and store the positions of the pipes
            for (i = 0; argv[i] != NULL; i++)
            {
                if (strcmp(argv[i], "|") == 0)
                {
                    argv[i] = NULL;
                    pipeCommands[pipeCount++] = i;
                }
            }

            // create pipes
            for (i = 0; i < pipeCount; i++)
            {
                if (pipe(pipeFD + i * 2) == -1)
                {
                    printf("Error (piping): ");
                    exit(1);
                }
            }

            // run commands separated by pipes
            int fileDIN,fileDOUT,outMod;
            char **argvCurr;
            for (i = 0; i <= pipeCount; i++)
            {

                if (i == 0)
                {
                    fileDIN = 0;
                    argvCurr = argv;
                }
                else
                {
                    fileDIN = pipeFD[(i - 1) * 2];
                    argvCurr = &argv[pipeCommands[i - 1] + 1];
                }

                if (i == pipeCount)
                {
                    outMod = outMod;
                }
                else
                {
                    outMod = 0;
                    fileDOUT = pipeFD[i * 2 + 1];
                }
                // Redirection output handler.
                commandExec(argvCurr, outMod, outFile, fileDIN, fileDOUT);

                // Pipes finished hanlder.
                if (i > 0)
                {
                    close(pipeFD[(i - 1) * 2]);
                }
                if (i < pipeCount)
                {
                    close(pipeFD[i * 2 + 1]);
                }
            }
        }
    }
}


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    
    pid_t pid = 0;
    int status = 0;
    
    char** args[] = {
        (char*[]){"echo", "Hello + Jack McDonald", NULL},
        (char*[]){"ps", "T", NULL},
        (char*[]){"ls", NULL},
        (char*[]){"date", NULL},
        (char*[]){"history", "5", NULL},
        (char*[]){"cp", "something1.txt", "something2.txt", NULL},
        (char*[]){"mv", "something1.txt", "something2.txt", NULL},
        (char*[]){"rm", "something1.txt", NULL},
        (char*[]){"mkdir", "something1/something2", NULL},
        (char*[]){"rmdir", "something1/something2", NULL}
    };
    
    for (int i = 1; i <= 10; i++) {
        
        printf("starting child process #%d\n\n", i);
        
        pid = fork();
        
        if (pid < 0) { // fork error
            
            printf("fork #%d failed\n", i);
            
        } else if (pid == 0) { // child process
            
            printf("child process #%d running with pid %d and executing command %s\n\n", i, getpid(), args[i - 1][0]);
            
            execvp(args[i - 1][0], args[i - 1]);
            
            // it can't reach this line unless execvp fails
            printf("execvp failed. errno %d: %s\n", errno, strerror(errno));
            
            return errno;
            
        } else { // parent process
            
            wait(&status);
            
            printf("\nchild process #%d finished with status %d.\n", i, WEXITSTATUS(status));
            
            if (WIFEXITED(status)) {
                
                printf("child process #%d exited normally.\n\n", i);
                
            } else if (WIFSIGNALED(status)) {
                
                printf("child process #%d exited because of signal %d.\n\n", i, WTERMSIG(status));
                
            } else {
                
                printf("child process #%d exited abnormally.\n\n", i);
                
            }
            
            printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
            
        }
    }
    
    printf("done\n");
    
    return 0;
}


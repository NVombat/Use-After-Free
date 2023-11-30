// Reference - https://infosecwriteups.com/heap-exploitation-for-homo-sapiens-f166cd6a59fe

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

int main(int argc, char * argv[]){
    if (argc != 2){
        error(1, 0, "Usage: %s <username>\n", argv[0]);
    }

    printf("Heap Overflow\n");

    char *uname = malloc(64);
    char *cmd = malloc(64);

    // Hard coded command -> overflow to overwrite command
    strcpy(cmd, "whoami");
    strcpy(uname, argv[1]);

    printf("%s is executing the command %s\n\n", uname, cmd);

    system(cmd);
}

// Command -> ./heap_overflow AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAls
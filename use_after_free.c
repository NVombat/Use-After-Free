// Reference: https://infosecwriteups.com/arming-the-use-after-free-bc174a26c5f4

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Okay, so here's what YOU need to do...\n");
    printf("You have access to the source code...\n");
    printf("Try and become root so you can execute a command of your choice and drop a shell...\n");
    printf("If you cannot become root, you stoopid!\n\n");

    char * username = 0;
    char * password = 0;

    int flag = 0;

    clock_t start = clock();

    while(1)
    {
        if(username){
            printf("USERNAME ADDRESS: %x\nUSERNAME: %s\n", username, username);
        }
        if(password){
            printf("PASSWORD ADDRESS: %x\nPASSWORD: %s\n", password, password);
        }

        printf("1: Username\n");
        printf("2: Password\n");
        printf("3: Reset\n");
        printf("4: Login\n");
        printf("5: Exit\n");
        printf("Choose an option [1-5]: ");

        int choice = 0;
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                // Save username
                username = malloc(20*sizeof(char));
                printf("Enter username: ");
                scanf("%254s", username);

                if(!strcmp(username, "root"))
                {
                    printf("[root]: This username is not allowed. Please try again!\n");
                    strcpy(username, "");
                    // Possible Heap overflow?
                    // strcpy(username, argv[0])
                }

                break;

            case 2:
                // Save password
                password = malloc(20*sizeof(char));
                printf("Enter password: ");
                scanf("%254s", password);

                break;

            case 3:
                // Free username and password (when resetting)
                free(password);
                free(username);
                break;

            case 4:
                // Login/Exploit
                if (!password || !username){
                    printf("How tf you gonna log in without both credentials [username & password] dumbass! Set them up first\n");
                    break;
                }

                char * temp_uname = (char*)malloc(20*sizeof(char));
                char * temp_pwd = (char*)malloc(20*sizeof(char));

                printf("Enter username: ");
                scanf("%254s", temp_uname);

                printf("Enter password: ");
                scanf("%254s", temp_pwd);

                // root does not need to authenticate
                if(!strcmp(username, "root"))
                {
                    clock_t end = clock();
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("You took %f seconds...\n", time_spent);

                    flag = 1;
                    printf("Congratulations! You figured out how to exploit the vulnerability and drop a shell you fkn nerd!\n");
                    printf("---SOME PRIVILEGED SHIT GOING ON HERE---\n");

                    // Potential command injection?
                    char * command = (char*)malloc(20*sizeof(char));
                    printf("$ Trying to mimic a shell. Enter a command cuz u root my g: ");
                    scanf("%254s", command);

                    // system("/usr/bin/bash");
                    // system("/usr/bin/ls");
                    system(command);

                    free(command);
                    command = NULL;
                    exit(0);
                }

                if(!strcmp(temp_uname, username) && !strcmp(temp_pwd, password)){
                    printf("Logged in successfully but DID NOT drop a shell sucka!\n");
                }
                else{
                    printf("Incorrect username or password! Try again dumbass!\n");
                }

                free(temp_pwd);
                free(temp_uname);
                temp_uname = NULL;
                temp_pwd = NULL;

                break;

            case 5:
                clock_t end = clock();
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                if (flag == 0){
                    printf("You just wasted %f seconds!\n", time_spent);
                    printf("Seems like you gave up on trying to drop a shell! Sucks to be You(se-After-Free)\n");
                }
                else{
                    printf("You took %f seconds...\n", time_spent);
                    printf("Congratulations! You figured out how to exploit the vulnerability and drop a shell you fkn nerd!\n");
                }
                exit(0);

            default:
                printf("Invalid Option! Try Again Dipshit!\n");
                break;
        }
    }
}

/*
How to exploit the above code:
1 - Select option 1 to allocate a chunk of memory to store the username
2 - Select option 2 to allocate a chunk of memory to store the password
3 - Free the chunks of memory using option 3.
4 - Select option 2 to allocate a chunk of memory for the password so that it can rewrite the contents of the previously allocated username chunk.
5 - Use option 4 to log in and successfully exploit the vulnerability
*/
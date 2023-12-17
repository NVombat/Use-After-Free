#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Okay, so here's what YOU need to do...\n");
    printf("You have access to the source code...\n");
    printf("Try and become root so you can execute a command of your choice and drop a shell...\n");
    printf("There's atleast 2 different ways to exploit this code so...\n");
    printf("If you can't become root, you stoopid!\n");
    printf("Type shit Type shit!\n");

    time_t start_time;
    time(&start_time);

    char * username = 0;
    char * password = 0;

    int flag = 0;

    while(1)
    {
        // Print username and password (with address) to keep a track of the variables
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

                // "root" username not allowed -> set username to ""
                if(!strcmp(username, "root"))
                {
                    printf("[root]: Ain't no way it's that easy. Try again fool!\n");
                    strcpy(username, "");
                    // Possible Heap overflow?
                    // strcpy(username, argv[0])
                }

                break;

            case 2:
                // Save password
                if (!username){
                    printf("What tf are you setting a password for? Set a username first fool\n");
                    break;
                }

                password = malloc(20*sizeof(char));
                printf("Enter password: ");
                scanf("%254s", password);
                printf("Bruh! My grandmother is stronger than that password!\n");

                break;

            case 3:
                // Free username and password (when resetting) (order matters)
                // Freeing username allows the same chunk of memory to be allocated to password if case 3 is followed by case 2
                // The username pointer will still be pointing to that chunk (even after it has been freed)
                // So when we set password to "root", username also becomes "root" as the memory address is the same
                if (!password && !username){
                    printf("Do you want me to reset yo ass? Use your brains man!\n");
                    printf("How tf you gonna reset smth that don't exist!\n");
                    break;
                }

                free(password);
                free(username);

                break;

            case 4:
                // Login/Exploit
                if (!password || !username){
                    printf("How tf you gonna log in without both credentials [username & password] dumbass! Set them up first\n");
                    break;
                }

                // If case 4 follows case 3, temp_uname and temp_pwd get assigned the freed memory chunks
                // So if I enter "root" as temp username, it writes to username because the username pointer is still pointing to that memory chunk too
                // And the same goes for password
                char * temp_uname = (char*)malloc(20*sizeof(char));
                char * temp_pwd = (char*)malloc(20*sizeof(char));

                printf("Enter username: ");
                scanf("%254s", temp_uname);

                printf("Enter password: ");
                scanf("%254s", temp_pwd);

                // root does not need to authenticate
                if(!strcmp(username, "root"))
                {
                    time_t end_time;
                    time(&end_time);

                    double time_spent = difftime(end_time, start_time);
                    printf("You took %.2f seconds...\n", time_spent);

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

                    exit(0);
                }

                if(!strcmp(temp_uname, username) && !strcmp(temp_pwd, password)){
                    printf("%s -- %s -- %s -- %s\n", temp_uname, username, temp_pwd, password);
                    // BUG -> If case 3 is followed by case 4, it is possible to log in with any username and password
                    printf("Logged in successfully but DID NOT drop a shell sucka! Not as smart as you thought you were lmao!\n");
                }
                else{
                    printf("Incorrect username or password! Try again dumbass!\n");
                }

                free(temp_pwd);
                free(temp_uname);

                break;

            case 5:
                time_t end_time;
                time(&end_time);
                double time_spent = difftime(end_time, start_time);

                if (flag == 0){
                    printf("You just wasted %.2f seconds!\n", time_spent);
                    printf("Seems like you gave up on trying to drop a shell! Sucks to be You(se-After-Free)\n");
                }
                else{
                    printf("You took %.2f seconds...\n", time_spent);
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

OR
1 - Select option 1 to allocate a chunk of memory to store the username
2 - Select option 2 to allocate a chunk of memory to store the password
3 - Free the chunks of memory using option 3.
4 - Select option 4 to allocate the chunks of memory to temp_uname and temp_pwd and then enter "root" as the username
*/
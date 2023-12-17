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
                }

                break;

            case 2:
                // Save password
                password = malloc(20*sizeof(char));
                printf("Enter password: ");
                scanf("%254s", password);
                printf("Bruh! My grandmother is stronger than that password!\n");

                break;

            case 3:
                free(password);
                free(username);

                // Ensure no dangling pointers exist
                password = NULL;
                username = NULL;
                break;

            case 4:
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
                    time_t end_time;
                    time(&end_time);

                    double time_spent = difftime(end_time, start_time);
                    printf("You took %.2f seconds...\n", time_spent);

                    flag = 1;
                    printf("Congratulations! You figured out how to exploit the vulnerability and drop a shell you fkn nerd!\n");
                    printf("---SOME PRIVILEGED SHIT GOING ON HERE---\n");

                    char * command = (char*)malloc(20*sizeof(char));
                    printf("$ Trying to mimic a shell. Enter a command cuz u root my g: ");
                    scanf("%254s", command);
                    system(command);

                    free(command);
                    command = NULL;

                    exit(0);
                }

                if(!strcmp(temp_uname, username) && !strcmp(temp_pwd, password)){
                    printf("%s -- %s -- %s -- %s\n", temp_uname, username, temp_pwd, password);
                    printf("Logged in successfully but DID NOT drop a shell sucka! Not as smart as you thought you were lmao!\n");
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
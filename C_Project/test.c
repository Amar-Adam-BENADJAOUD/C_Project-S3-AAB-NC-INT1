#include "test.h"

void part_1_2(int n, int loops){
    //creation of a list
    t_d_list L = create_s_list(n);
    display_all_levels(L);

    //opening of the file
    FILE *log_file = fopen("log.txt", "a");

    //initializations
    char format[] = "%d\t%s\t%s\n" ;
    int level = n;
    char *time_lvl0;
    char *time_all_levels;

    //first test
    startTimer();
    for (int i = 0; i < loops; ++i)
        search0(L, rand()%((int) pow(2, n)-1));
    stopTimer();
    displayTime();

    //transcription
    time_lvl0 = getTimeAsString();

    //second test
    startTimer();
    for (int i = 0; i < loops; ++i)
        general_search(L, rand()%((int) pow(2, n)-1));
    stopTimer();
    displayTime();

    //transcription
    time_all_levels = getTimeAsString();
    fprintf(log_file,format,level,time_lvl0, time_all_levels);

    //closing of the file
    fclose(log_file);
}

void menu(){
    char answer = 'a', m;

    //main part
    while(answer != 'q'){
        printf("Welcome to your Agenda made in EFREI !\n\n");
        printf("What do you wanna do ?");
        //Display of the menu
        printf("\n   A — Create a contact\n   B — Add an appointment\n   C — Cancel an appointment\n   D — Show my agenda\n   E — Quit\n\n >> ");
        scanf("%c", &answer);
        switch (answer) {

            //Create a contact
            case 'A':
                printf("Sorry ...  Lake of time.");
                printf("\n\nPress \'u\' to come back to the men");
                do {
                    scanf(" %c", &m);
                } while (m != 'u');
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;

            //Add an appointment
            case 'B':
                printf("Sorry ...  Lake of time.");
                printf("\n\nPress \'u\' to come back to the men");
                do {
                    scanf(" %c", &m);
                } while (m != 'u');
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;

            //Cancel an appointment
            case 'C':
                printf("Sorry ...  Lake of time.");
                printf("\n\nPress \'u\' to come back to the men");
                do {
                    scanf(" %c", &m);
                } while (m != 'u');
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;

            //Display the hall agenda
            case 'D':
                printf("Sorry ...  Lake of time.");
                printf("\n\nPress \'u\' to come back to the men");
                do {
                    scanf(" %c", &m);
                } while (m != 'u');
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;

            //quit the program
            case 'E':
                answer = 'q';
                break;
        }
    }

}
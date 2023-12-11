#include "agenda.h"

char * scanString() {
    char * prompt = NULL;
    int size = 0;
    char c;

    while ((c = getchar()) != '\n' || size < 3) {
        if ((c > 64 && c < 90) || (c > 96 && c < 123) || c == 45 || c == 32) { //check for valid character
            if (c > 64 && c < 90) //check for uppercase
                c += 32; //turn into lowercase
            size++; //update of the size of the input
            prompt = (char *) realloc(prompt,sizeof(char) * size); //update of the allocated memory
            prompt[size - 1] = c;
        }
        else
            printf("\b"); //remove the last entered character
    }

    prompt = (char *) realloc(prompt, sizeof(char) * (size+1)); //update of the allocated memory
    prompt[size] = '\0'; //add of the character characteristic of strings
    return prompt;
}

int check_hour(int h, int m) {
    if (h > -1 && h < 24 && m > -1 && m < 60)
        return 1;
    return 0;
}

int check_date(int d, int m, int y) {
    if (m == 4 || m == 6 || m == 9 || m == 11) //check for month of 31 days
        if (d > -1 && d < 31)
            return 1;
    if (m == 2) { //check for february
        if (!(y % 100 % 4)) //check for leap year
            if (d > -1 && d < 29)
                return 1;
        if (d > -1 && d < 28)
            return 1;
    }
    if (d > -1 && d < 32) //check for the others months
        return 1;
    return 0;
}

Agenda * create_agenda() {
    Agenda * a = (Agenda *) malloc(sizeof(Agenda)); //allocation of memory for the agenda
    a->n_level = 4; //initialization of the number of levels
    a->head = (Contact **) malloc(4 * sizeof(Contact *)); //allocation of memory for the list of heads
    for (int i = 0; i < 4; i++)
        a->head[i] = NULL; //initialization of each head
    return a;
}

void display_contact(Contact * c, int n){
    while (c != NULL){
        printf("[%s]-->", c->surname_name);
        c = c->next[n];
    }
    printf("[end]");
}

void display_agendas_level(Agenda * a, int n) {
    printf("[Agenda Level %d ] — { ", n);
    display_contact(a->head[n], n);
    printf(" }");
}

void display_agenda(Agenda * a){
    for (int i = 0; i < a->n_level; ++i)
        display_agendas_level(a, i);
}

Contact * create_contact(char * surname, char * name, int n) {

    Contact * contact = (Contact *) malloc(sizeof(Contact)); //allocation of memory for the contact

    contact->surname = (char *) malloc(strlen(surname) + 1); //allocation of memory for the surname
    strcpy(contact->surname, surname); //initialization of the surname

    contact->name = (char *)malloc(strlen(name) + 1); //allocation of memory for the name
    strcpy(contact->name, name); //initialization of the name

    contact->surname_name = (char *)malloc(strlen(surname) + strlen(name) +2); //allocation of memory for the pseudo
    strcpy(contact->surname_name, contact->surname); //initialization of the pseudo
    strcat(contact->surname_name,"_"); //first modification of the pseudo
    strcat(contact->surname_name, contact->name); //second modification of the pseudo

    contact->appointments = NULL; //initialization of the appointment
    contact->n_level = n; //initialization of the number maximum of level of the contact

    contact->next = (Contact **) malloc(n * sizeof(Contact *)); //allocation of memory for the list of next levels
    for (int i = 0; i < n; i++)
        contact->next[i] = NULL; //initialization of the level i

    return contact;
}

void addContact(Agenda * agenda, Contact * contact, Contact * prev){
    if (prev != NULL) {
        for (int i = 0; i < contact->n_level && i < agenda->n_level; i++)
            contact->next[i] = prev->next[i];
        for (int i = contact->n_level - 1; i >= 0 && i < agenda->n_level; i--)
            prev->next[i] = contact;
        //swap previous and new contacts
        if (strcmp(prev->surname_name, contact->surname_name) > 0) {
            char * swap;
            Meeting * appo;
            swap = prev->surname;
            prev->surname = contact->surname;
            contact->surname = swap;
            swap = prev->name;
            prev->name = contact->name;
            contact->name = swap;
            swap = prev->surname_name;
            prev->surname_name = contact->surname_name;
            contact->surname_name = swap;
            appo = prev->appointments;
            prev->appointments = contact->appointments;
            contact->appointments = appo;
        }
    }
    else { //if it's the first contact
        //initialize the pointer to the head
        for (int i = 0; i < contact->n_level && i < agenda->n_level; i++)
            contact->next[i] = agenda->head[i];
        for (int i = contact->n_level - 1; i >= 0 && i < agenda->n_level; i--)
            agenda->head[i] = contact;
    }
}

Meeting * create_appointment(int day, int month, int year, int hour, int minute, int h_duration, int min_duration, char * purpose){
    Meeting * appo = (Meeting *) malloc(sizeof(Meeting)); //allocation of memory for the appointment
    appo->date.day = day; //initialize the day of the appointment
    appo->date.month = month; //initialize the month of the appointment
    appo->date.year = year; //initialize the year of the appointment
    appo->hour.hour = hour; //initialize the hour of the appointment
    appo->hour.minute = minute; //initialize the minute of the appointment
    appo->duration.hour = h_duration; //initialize the hour of duration of the appointment
    appo->duration.minute = min_duration; //initialize the minute of duration of the appointment
    appo->purpose = (char *) malloc(strlen(purpose) + 1); //allocation of memory for the purpose of the appointment
    strcpy(appo->purpose, purpose); //initialize the purpose of the appointment
    appo->next = NULL; //initialize the day of the appointment
    return appo;
}

void add_appointment(Contact * contact, Meeting * appo) {
    appo->next = contact->appointments;
    contact->appointments = appo;
}

void cancel_appointment(Contact * contact, int n) {
    Meeting * appo = contact->appointments; //initialization of the first cursor
    Meeting * prev = contact->appointments; //initialization of the second cursor
    if (n == 1) //check if we got to cancel the first appointment
        contact->appointments = appo->next;
    else {
        //to go through the list
        for (int i=0; i<n-1; i++) {
            prev = appo;
            appo = appo->next;
        }
        prev->next = appo->next; //update links
    }
    free(appo->purpose); //free the memory allocated to list of character which is the purpose
    free(appo); //free the memory allocated to the appointment itself
}

void display_appointment(Meeting  * appo) {
    if (appo == NULL) {
        printf("Pas de rendez vous\n");
        return;
    }
    int i=1;
    while (appo != NULL) {
        printf("Appointment n°%d: the %d/%d/%d at %d:%d while %d:%d for %s.", i, appo->date.day, appo->date.month, appo->date.year, appo->hour.hour, appo->hour.minute, appo->duration.hour, appo->duration.minute, appo->purpose);
        i++;
        appo = appo->next;
    }
}

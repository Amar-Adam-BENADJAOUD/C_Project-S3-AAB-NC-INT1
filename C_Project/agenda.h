#ifndef C_PROJECT_AGENDA_H
#define C_PROJECT_AGENDA_H

//Link with the remainder of the program
#include "timer.h"


//Needed structures

//Date structure
typedef struct DATE {
    int day; //day
    int month; //month
    int year; //year
} Date;

//Time structure
typedef struct timing {
    int hour; //hour
    int minute; //minutes
} Timing;

//Appointment structure
typedef struct RDV {
    Date date; //date of the appointment
    Timing hour; //hourly of the appointment
    Timing duration; //timing of the appointment
    char * purpose; //goal of the appointment
    struct RDV * next; //pointer through the next appointment
} Meeting;

//Contact structure
typedef struct contact {
    char * surname; //name
    char * name; //first name
    char * surname_name; //pseudo for the list
    Meeting * appointments; //list of appointment
    int n_level; //number of levels
    struct contact ** next; //list of pointers on the levels of the next contact
} Contact;

typedef struct agenda {
    Contact ** head; //list of pointers on the levels of the first contact
    int n_level; //number of the maximum levels in the contact of the list
} Agenda;


//FUNCTIONS

//checking function
char * scanString();
int check_hour(int, int);
int check_date(int, int, int);

//function on agenda
Agenda * create_agenda();

//function on contact
Contact * create_contact(char *, char *, int);
void add_contact(Agenda *, Contact *, Contact *);
Contact * Seek(Agenda *, char *, char *, int);

//function on appointment
Meeting * create_appointment(int, int, int, int, int, int, int, char *);
void add_appointment(Contact *, Meeting *);
void cancel_appointment(Contact *, int );

//function of display
void display_appointment(Meeting *);
void display_contact(Contact *, int);
void display_agendas_level(Agenda *, int);
void display_agenda(Agenda *);

#endif //C_PROJECT_AGENDA_H

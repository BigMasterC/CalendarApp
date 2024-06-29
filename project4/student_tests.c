#include "calendar.h"
#include "event.h"
#include "my_memory_checker_216.h"
#include <stdio.h>
#include <stdlib.h>
/*CHICHI!!! REMOVE THESE WHEN DONE RUNNING ON VS-CODE: */
/*#include "calendar.c"
#include "my_memory_checker_216.c"*/

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program will eventually   */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
    return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

static int comp_name(const void *ptr1, const void *ptr2) {
    return strcmp(((Event *)ptr1)->name, ((Event *)ptr2)->name);
}

static int comp_start_time(const void *ptr1, const void *ptr2) {
    return ((Event *)ptr1)->start_time - ((Event *)ptr2)->start_time;
}

/* Testing the initialization of the calendar w/ everything but the "free_data()" function
(used to free additional info about the event)*/
static int test1() {
    int days = 7;
    Calendar *calendar;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*TEST: add_event()*/
/* Adding the same event...4 times! (should only appear ONCE...right?) */
static int test2() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);

        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*TEST: add_event() & remove_event()*/
/* adding a bunch of of the same event and attempting to remove it to see how it would
affect the output of the print. */
static int test3() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);

        if (remove_event(calendar, "Snap meeting") == SUCCESS) {
            remove_event(calendar, "HACS200 Work Due");
            remove_event(calendar, "lunch (?)");
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                return destroy_calendar(calendar);
            }
        }
    }

    return FAILURE;
}

/*TEST: find_event_in_day()*/
/* Removing two events and seeing if they can be found.*/
static int test4() {

    int days = 5, looking_for, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;
    Event *found_event;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, tuesday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, tuesday);

        looking_for = find_event_in_day(calendar, "HACS200 Work Due", wednesday, &found_event);

        if (looking_for == SUCCESS) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                fprintf(stdout, "Found it!: %s\n", found_event->name); /*prints out event found*/
                return destroy_calendar(calendar);
            }
        } else if (looking_for == FAILURE) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                fputs("Could NOT find it :C \n", stdout); /*prints out event found*/
                return destroy_calendar(calendar);
            }
        }
    }

    return FAILURE;
}
/*TEST: find_event()*/
/*Try: Removing two events*/
static int test5() {

    int days = 5, looking_for, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;
    Event *found_event;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, tuesday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, tuesday);

        looking_for = find_event(calendar, "Snap meeting", &found_event);

        if (looking_for == SUCCESS) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                fprintf(stdout, "Found it!: %s\n", found_event->name); /*prints out event found*/
                return destroy_calendar(calendar);
            }
        } else if (looking_for == FAILURE) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                fputs("Could NOT find it :C \n", stdout); /*prints out event found*/
                return destroy_calendar(calendar);
            }
        }
    }

    return FAILURE;
}

/*Testing if the event cannot be found (remove_event() should return FAILURE)*/
static int test6() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch with Boddy (Snap)", 1100, 45, NULL, wednesday);

        if (remove_event(calendar, "Snap meeting") == SUCCESS) {
            if (remove_event(calendar, "HACS200 Work Due") == SUCCESS) {
                /*print_calendar(calendar, stdout, 1);*/
                if (remove_event(calendar, "lunch (?)") == SUCCESS) {
                    if (remove_event(calendar, "lunch with Boddy (Snap)") == SUCCESS) {
                        fputs("COULD NOT REMOVE (Test passed)!!!\n", stdout);
                        return destroy_calendar(calendar);
                    }
                }
            }
        }
    }

    return FAILURE;
}

/***************** START OF TESTING INDIVIDUAL FUNCTIONS *******************/

/*Testing print_calendar's "Information about each event
is printed regardless of if the last parameter of the
'print_calendar()' function is true" characteristics so...
I'm setting the last parameter to false (zero) :D*/

static int test7() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 0) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: add_event()] to make sure events are added in ascending order (on the same day)
...events are compared by minutes*/
static int test8() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS208P Work Due", 800, 15, NULL, tuesday);
        add_event(calendar, "HACS297 Work Due", 800, 5, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: add_event()] to make sure it returns FAILURE if the event already exists*/
static int test9() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);

        if (add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday) == FAILURE) {
            fputs("COULD NOT ADD (Test passed)!!!\n", stdout);
            fputs("\n", stdout);
        }

        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: clear_day() function].. in this test we will be removing all
the events I have planned for tuesday... hW :'C*/
static int test10() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS208P Work Due", 800, 15, NULL, tuesday);
        add_event(calendar, "HACS297 Work Due", 800, 5, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        /*CHANGE SHOWN BELOW*/
        clear_day(calendar, tuesday);

        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: clear_day() function].. in this test we will be removing all
the events I have planned for WEDNESDAY... lunch ;D [EXTREME VERSION]*/
static int test11() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS208P Work Due", 800, 15, NULL, tuesday);
        add_event(calendar, "HACS297 Work Due", 800, 5, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (1)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (2)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (3)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (4)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (5)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (6)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (7)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (8)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (9)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (10)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (11)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (12)", 1200, 45, NULL, wednesday);
        /*CHANGE SHOWN BELOW*/
        clear_day(calendar, wednesday);

        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: clear_calendar() function].. in this test we will be removing all
the events I have planned for November!*/
static int test12() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "HACS208P Work Due", 800, 15, NULL, tuesday);
        add_event(calendar, "HACS297 Work Due", 800, 5, NULL, tuesday);
        add_event(calendar, "HACS200 Work Due", 800, 80, NULL, tuesday);
        add_event(calendar, "Snap meeting", 500, 60, NULL, thursday);
        add_event(calendar, "lunch (?)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (1)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (2)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (3)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (4)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (5)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (6)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (7)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (8)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (9)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (10)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (11)", 1200, 45, NULL, wednesday);
        add_event(calendar, "lunch (12)", 1200, 45, NULL, wednesday);
        /*CHANGE SHOWN BELOW*/
        clear_calendar(calendar);

        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: comp_name()] to make sure events are added in ascending order (on the same day)
...events are compared by NAME (a - z)*/
static int test13() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_name, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "Event: E", 800, 80, NULL, tuesday);
        add_event(calendar, "Event: A", 800, 15, NULL, tuesday);
        add_event(calendar, "Event: D", 800, 5, NULL, tuesday);
        add_event(calendar, "Event: B", 800, 80, NULL, tuesday);
        add_event(calendar, "Event: C", 500, 60, NULL, tuesday);
        add_event(calendar, "Event: Z", 1200, 45, NULL, tuesday);

        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: comp_start_time()] to make sure events are added in ascending order (on the same day)
...events are compared by START_TIME*/
static int test14() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_start_time, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "Event: E", 100, 80, NULL, tuesday);
        add_event(calendar, "Event: A", 900, 15, NULL, tuesday);
        add_event(calendar, "Event: D", 300, 5, NULL, tuesday);
        add_event(calendar, "Event: B", 800, 80, NULL, tuesday);
        add_event(calendar, "Event: C", 500, 60, NULL, tuesday);
        add_event(calendar, "Event: Z", 1200, 45, NULL, tuesday);

        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: add_event] giving invalid arguments (incorrect start_time)*/
static int test15() {

    int days = 5, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;

    if (init_calendar("November", days, comp_start_time, NULL, &calendar) == SUCCESS) {

        if (add_event(calendar, "Event: E", 3000, 80, NULL, tuesday) == FAILURE) {
            fputs("TEST PASSED!!!\n", stdout);
            fputs("\n", stdout);
        }

        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

/*[TESTING: add, remove, and find_event when there is only one day on the calendar*/
static int test16() {

    int days = 1, sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5;
    Calendar *calendar;
    Event *event_found;

    if (init_calendar("November", days, comp_start_time, NULL, &calendar) == SUCCESS) {

        if (add_event(calendar, "random Event", 1200, 80, NULL, sunday) == SUCCESS) {
            if (remove_event(calendar, "random Event") == SUCCESS) {
                if (find_event(calendar, "random Event", &event_found) == FAILURE) {
                    fputs("TEST PASSED!!!\n", stdout);
                    fputs("\n", stdout);
                }
            }
        }

        /*CHANGE SHOWN BELOW*/
        if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
        }
    }

    return FAILURE;
}

int main(void) {
    int result = SUCCESS;

    /***** Starting memory checking *****/
    start_memory_check();
    /***** Starting memory checking *****/

    if (test1() == FAILURE)
        result = FAILURE;

    if (test2() == FAILURE)
        result = FAILURE;

    if (test3() == FAILURE)
        result = FAILURE;

    if (test4() == FAILURE)
        result = FAILURE;

    if (test5() == FAILURE)
        result = FAILURE;

    if (test6() == FAILURE)
        result = FAILURE;

    if (test7() == FAILURE)
        result = FAILURE;

    if (test8() == FAILURE)
        result = FAILURE;

    if (test9() == FAILURE)
        result = FAILURE;

    if (test10() == FAILURE)
        result = FAILURE;

    if (test11() == FAILURE)
        result = FAILURE;

    if (test12() == FAILURE)
        result = FAILURE;

    if (test13() == FAILURE)
        result = FAILURE;

    if (test14() == FAILURE)
        result = FAILURE;

    if (test15() == FAILURE)
        result = FAILURE;

    if (test16() == FAILURE)
        result = FAILURE;

    /****** Gathering memory checking info *****/
    stop_memory_check();
    /****** Gathering memory checking info *****/

    if (result == FAILURE) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

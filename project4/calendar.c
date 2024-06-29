/*
    Name: Chibundu Onwuegbule
    UID: 119312827
    Directory ID: conwueg1
*/

#include "calendar.h"
#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Creating a new Calendar (struct) using the data provided within the parameter list
to initialize the fields.

NOTE TO SELF: last parameter is actually an array of Calendar (struct) pointers*/

/*Initializes a new Calendar struct, allocating memory for its name and events 
array based on input parameters. The comparison and freeing functions are set for 
future use. Returns SUCCESS if successful, FAILURE otherwise.*/
int init_calendar(const char *calendar_name, int num_of_days, int (*compare)(const void *, const void *),
                  void (*free_data)(void *), Calendar **calendar_struct_ptr_arr) {

    /*Making sure the parameters are not empty...*/
    Calendar *new_calendar_struct_ptr;

    if (num_of_days < 1 || calendar_name == NULL || calendar_struct_ptr_arr == NULL) {
        return FAILURE;
    }

    /*creating a new Calendar*/
    new_calendar_struct_ptr = malloc(sizeof(Calendar));

    if (new_calendar_struct_ptr == NULL) {
        return FAILURE;
    }

    /*allocating space for the name of the Calendar within the struct*/
    new_calendar_struct_ptr->name = malloc(strlen(calendar_name) + 1);

    if (new_calendar_struct_ptr->name == NULL) {
        /*TO PREVENT MEMORY LEAKS...*/
        free(new_calendar_struct_ptr); /*because we've failed to allocate memory*/
        new_calendar_struct_ptr = NULL;
        return FAILURE;
    }

    /*allocating space for the "events" field of the struct*/
    new_calendar_struct_ptr->events = calloc(num_of_days, sizeof(Event *));

    if (new_calendar_struct_ptr->events == NULL) {
        /*TO PREVENT MEMORY LEAKS...*/
        free(new_calendar_struct_ptr->name);
        new_calendar_struct_ptr->name = NULL;
        free(new_calendar_struct_ptr); /*because we've failed to allocate memory*/
        new_calendar_struct_ptr = NULL;
        /*free both successful memory allocations so that we have no memory leaks*/
        return FAILURE;
    }

    /*copying over the calendar_name string into the new struct I
    created*/
    strcpy(new_calendar_struct_ptr->name, calendar_name);
    new_calendar_struct_ptr->days = num_of_days;
    /* ERROR: segmentation fault is given for public 2 and beyond when I uncomment (above)*/
    new_calendar_struct_ptr->total_events = 0;

    /*TA QUESTION: should I do this?: FUTURE CHICHI...you sure did lol ...*/
    new_calendar_struct_ptr->comp_func = compare;
    new_calendar_struct_ptr->free_info_func = free_data;

    /*allowing the parameter to point to the new Calendar I made ;]*/
    *calendar_struct_ptr_arr = new_calendar_struct_ptr;

    /*The "*cal..." allows us to access the address held within the variable*/

    /*notice no "&" before so I'm basically stating that I want
    the parameter to point to the same memory address stored
    within the variable and not the memory address of the acutal
    variable within the Stack*/

    return SUCCESS;
}

/*printing the different fields of the Calendar and putting its contents into a file
(@output_stream_file)*/

/*Prints the details of a Calendar, including its name, days, total events, and 
event information if specified. Outputs the information to a designated file stream. 
Returns SUCCESS if successful, FAILURE otherwise.*/
int print_calendar(Calendar *calendar_struct_ptr, FILE *output_stream_file, int has_event) {

    int i;
    Event *event;

    if (calendar_struct_ptr == NULL || output_stream_file == NULL) {
        return FAILURE;
    }

    /*If true...(non-zero)*/
    if (has_event != 0) {

        /*printing out the Calendar's NAME: */
        fputs("Calendar's Name: ", output_stream_file);
        fprintf(output_stream_file, "\"%s\"\n", calendar_struct_ptr->name);

        /*TWO DIFFERENT WAYS TO PUT THINGS IN A FILE...*/

        /*printing out the Calendar's DAYS: */
        fputs("Days: ", output_stream_file);
        fprintf(output_stream_file, "%d\n", calendar_struct_ptr->days);

        /*printing out the Calendar's TOTAL NUM OF EVENTS: */
        fputs("Total Events: ", output_stream_file);
        fprintf(output_stream_file, "%d\n", calendar_struct_ptr->total_events);
        fputs("\n", output_stream_file); /*might be an issue with the spacing*/
    }

    fputs("**** Events ****\n", output_stream_file);

    /*looping through the days on the calendar*/
    for (i = 0; i < calendar_struct_ptr->days; i++) {

        if (calendar_struct_ptr->total_events != 0) {
            fprintf(output_stream_file, "Day %d\n", i + 1);
        }

        /*getting all of the events associated with that day*/
        event = calendar_struct_ptr->events[i];

        while (event != NULL) {
            /*print out the info associated with that event*/

            fprintf(output_stream_file, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
                    event->name, event->start_time, event->duration_minutes);

            /*moving onto the next event on that same day (if any)*/
            event = event->next;
        }
    }

    return SUCCESS;
}

/*adding an event to the Calender (specified in the parameter)*/

/*Adds a new event to the specified day of the Calendar, maintaining an ascending 
order based on the comparison function set during initialization. Returns SUCCESS 
if successful, FAILURE otherwise.*/
int add_event(Calendar *calendar_struct_ptr, const char *event_name, int start_time,
              int duration_minutes, void *additional_info, int day_of_event) {

    Event *existing_event, *new_event, **linked_list_of_events, *curr, *prev;

    if (calendar_struct_ptr == NULL || event_name == NULL || day_of_event < 1 ||
        day_of_event > calendar_struct_ptr->days ||
        start_time < 0 || start_time > 2400 || duration_minutes <= 0) {
        return FAILURE;
    }

    if (find_event_in_day(calendar_struct_ptr, event_name, day_of_event, &existing_event) == SUCCESS) {
        return FAILURE; /* Event with the same name already exists */
    }

    /*allocating memory for new_event...*/
    new_event = malloc(sizeof(Event));

    if (new_event == NULL) {
        return FAILURE;
    }

    new_event->name = malloc(strlen(event_name) + 1);

    if (new_event->name == NULL) {
        free(new_event);
        new_event = NULL;
        return FAILURE;
    }

    /*initiliazing the event details*/
    strcpy(new_event->name, event_name);
    new_event->start_time = start_time;
    new_event->duration_minutes = duration_minutes;
    new_event->info = additional_info;
    new_event->next = NULL;

    /* looking for a place to put this event >:[ */
    linked_list_of_events = &calendar_struct_ptr->events[day_of_event - 1];

    curr = *linked_list_of_events; /*head of the list*/
    prev = NULL;

    /*while (curr != NULL && calendar_struct_ptr->comp_func(new_event, curr) > 0) {
        prev = curr;
        curr = curr->next;
    }*/

    while (curr != NULL) {

        if (calendar_struct_ptr->comp_func != NULL && calendar_struct_ptr->comp_func(new_event, curr) > 0) {
            prev = curr;
            curr = curr->next;
        } else {
            /*Handling condition where the comp_func fails or curr is no longer the correct node*/
            break;
        }
    }

    /*If the new event should be inserted at the beginning...*/
    if (prev == NULL) {
        new_event->next = *linked_list_of_events;
        *linked_list_of_events = new_event;
    } else {
        prev->next = new_event;
        new_event->next = curr;
    }

    /*Updating the totral number of events...*/
    calendar_struct_ptr->total_events++;

    return SUCCESS;
}

/*finding an event in the calendar*/
/*Searches for an event in the entire Calendar based on its name. If found, 
returns a pointer to the event through an out-parameter. Returns SUCCESS if the 
event is found, FAILURE otherwise.*/
int find_event(Calendar *calendar_struct_ptr, const char *event_name, Event **found_event) {

    Event *curr_event;
    int i;

    /*ASK TA: The project description states that "if the out-parameter is NULL,
    no pointer is returned"...so can I just like return FAILURE in that case as well?*/
    if (calendar_struct_ptr == NULL || event_name == NULL || found_event == NULL) {
        return FAILURE;
    }

    /*looking for the event in all the calendar days...*/
    for (i = 0; i < calendar_struct_ptr->days; i++) {
        curr_event = calendar_struct_ptr->events[i]; /*event on that particular day*/

        while (curr_event != NULL) {
            /*going to treat "event" as the head node*/
            if (strcmp(curr_event->name, event_name) == 0) {
                *found_event = curr_event;
                return SUCCESS;
            }

            /*moving onto the next node...*/

            curr_event = curr_event->next;
        }
    }

    /*Event was not found anywhere in the calendar :C*/
    *found_event = NULL; /*would this count as modifying the parameter?*/
    return FAILURE;
}

/*finding an event (given the specific day) in the calendar*/
/*Searches for an event on a specific day of the Calendar based on its name. 
If found, returns a pointer to the event through an out-parameter. 
Returns SUCCESS if the event is found, FAILURE otherwise.*/
int find_event_in_day(Calendar *calendar_struct_ptr, const char *event_name, int day_of_event, Event **found_event) {

    Event *curr_event;

    /*ASK TA: The project description states that "if the out-parameter is NULL,
    no pointer is returned"...so can I just like return FAILURE in that case as well?*/
    if (calendar_struct_ptr == NULL || event_name == NULL || found_event == NULL ||
        day_of_event < 1 || day_of_event > calendar_struct_ptr->days) {
        return FAILURE;
    }

    curr_event = calendar_struct_ptr->events[day_of_event - 1]; /*event on that particular day*/

    while (curr_event != NULL) {
        /*going to treat "event" as the head node*/
        if (strcmp(curr_event->name, event_name) == 0) {
            *found_event = curr_event;
            return SUCCESS;
        }

        /*moving onto the next node...*/

        curr_event = curr_event->next;
    }

    /*Event was not found anywhere in the calendar :C*/
    *found_event = NULL; /*would this count as modifying the parameter?*/
    return FAILURE;
}

/*removing an event from the calendar*/
/*Removes a specified event from the Calendar, deallocating memory and adjusting 
the total number of events. Returns SUCCESS if the event is successfully removed, 
FAILURE otherwise.*/
int remove_event(Calendar *calendar_struct_ptr, const char *event_name) {
    Event *curr = NULL, *prev, *event_to_be_removed;
    char *name_to_free;
    void *info_to_free;
    int num = 0;

    if (calendar_struct_ptr == NULL || event_name == NULL) {
        return FAILURE;
    }

      /*1) look through the Calendar for the event*/
    if (find_event(calendar_struct_ptr, event_name, &event_to_be_removed) == FAILURE) {
        /*passed in a pointer to an event struct (Event *) for the 3rd parameter
      using the "&" symbol*/
        return FAILURE;
        /*If we can't find the event in the first place...
        how would we be able to remove it??!*/
    }

    /* Start searching from the first day in the calendar */
    while (curr == NULL){
        curr = calendar_struct_ptr->events[num];
        prev = NULL;
        if (curr == NULL){
            num++;
            continue;
        }
    }
    /*skipping all the null/empty days (without events)*/


    /* Iterate through the linked list of events */
    while (curr != NULL && !(strcmp(curr->name, event_name)== 0) && num < calendar_struct_ptr->days) {
        prev = curr;
        curr = curr->next;

        if (curr == NULL) {
            /* Move onto the next day */
            num++;
            curr = calendar_struct_ptr->events[num];
            prev = NULL;
        }
    }

    /* If we've found the event_name in that day... */
    if (curr != NULL) {
        if (prev == NULL) {
            /* If we're at the beginning of the list... */
            calendar_struct_ptr->events[num] = curr->next;
        } else {
            prev->next = curr->next;
        }

        /* Save references to the event's info and name */
        info_to_free = curr->info;
        name_to_free = curr->name;

        /* Free the event's info if needed */
        if (info_to_free != NULL && calendar_struct_ptr->free_info_func != NULL) {
            calendar_struct_ptr->free_info_func(info_to_free);
        }

        /* Free the event's name */
        free(name_to_free);
        name_to_free = NULL;

        /* Free the event itself */
        free(curr);
        curr = NULL;

        /* Adjust the number of calendar events */
        calendar_struct_ptr->total_events--;

        return SUCCESS;
    }

    return FAILURE; /* Event not found */
}


/*Retrieves the info field of a specified event in the Calendar based on its name. 
Returns the info pointer if the event is found, NULL otherwise.*/
void *get_event_info(Calendar *calendar_struct_ptr, const char *event_name) {

    Event *event_to_be_found;

    /*we're not going to check if the parameters are NULL bc we can assume that
    the input parameter are not NULL*/

    if (find_event(calendar_struct_ptr, event_name, &event_to_be_found) == FAILURE) {
        return NULL; /*"if the event is not found...(see left)"*/
    }

    return event_to_be_found->info;
}

/*Removes all events from a specific day in the Calendar, deallocating memory and 
adjusting the total number of events. Returns SUCCESS if successful, FAILURE otherwise.*/
int clear_day(Calendar *calendar_struct_ptr, int day_of_event) {

    Event *head_of_day, *temp;

    if (calendar_struct_ptr == NULL || day_of_event < 1 || day_of_event > calendar_struct_ptr->days) {
        return FAILURE;
    }
    /* Directly access the date on the calendar using the "events" array... */
    head_of_day = calendar_struct_ptr->events[day_of_event - 1];
    /*NOV. 13 NOTE: might need to simply change the index to "0"*/

    while (head_of_day != NULL) {
        temp = head_of_day;
        head_of_day = head_of_day->next;

        /* Deallocate the event's name and info field */
        free(temp->name);
        temp->name = NULL;

        if (temp->info != NULL && calendar_struct_ptr->free_info_func != NULL) {
            calendar_struct_ptr->free_info_func(temp->info);
            temp->info = NULL;
        }
        free(temp);
        temp = NULL;

        calendar_struct_ptr->total_events--;
    }

    /* Reset the day to empty */
    calendar_struct_ptr->events[day_of_event - 1] = NULL;

    return SUCCESS;
}

/*Removes all events from the entire Calendar, deallocating memory and resetting
 the total number of events to zero. Returns SUCCESS if successful, FAILURE otherwise.*/
int clear_calendar(Calendar *calendar_struct_ptr) {

    int day_num, exit_code;

    if (calendar_struct_ptr == NULL) {
        return FAILURE;
    }

    for (day_num = 0; day_num < calendar_struct_ptr->days; day_num++) {
        exit_code = clear_day(calendar_struct_ptr, day_num + 1);

        if (exit_code == FAILURE) {
            return FAILURE; /*date cannot be cleared*/
        }
    }

    calendar_struct_ptr->total_events = 0; /*just making sure the number of total_events IS 0 */

    return SUCCESS;
}


/*Deallocates all memory associated with the Calendar, including its name, 
events array, and the Calendar itself. Returns SUCCESS if successful, FAILURE 
otherwise.*/
int destroy_calendar(Calendar *calendar_struct_ptr) {

    clear_calendar(calendar_struct_ptr);
    free(calendar_struct_ptr->name);
    calendar_struct_ptr->name = NULL;
    free(calendar_struct_ptr->events);
    calendar_struct_ptr->events = NULL;
    free(calendar_struct_ptr);
    calendar_struct_ptr = NULL;

    return SUCCESS;
}

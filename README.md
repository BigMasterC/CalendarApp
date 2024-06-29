
### Project 4: Calendar Application in C

#### Overview
This project involves implementing a calendar application in C, utilizing dynamic memory allocation, function pointers, and linked lists for efficient event management.

#### Objectives
- Implement a calendar with essential features.
- Utilize advanced C programming techniques such as dynamic memory allocation and linked lists.
- Ensure efficient event management through optimized functions.

#### Features
- **Dynamic Memory Allocation:** Efficient use of memory for storing calendar events.
- **Function Pointers:** Use of function pointers for flexible and efficient function calls.
- **Linked Lists:** Implement linked lists for dynamic event storage and management.

#### Technologies Used
- **C Programming Language**
- **Makefile**

#### How to Run
1. **Clone the repository:**
   ```sh
   git clone https://github.com/BigMasterC/CalendarApp.git
   cd project4
   ```
2. **Compile the program:**
   ```sh
   make
   ```
3. **Run the program:**
   ```sh
   ./calendar_app
   ```

#### Key Functions
- **Initialize Calendar:** Set up the calendar structure.
- **Add Event:** Add a new event to the calendar.
- **Find Event:** Search for an event in the calendar.
- **Delete Event:** Remove an event and deallocate memory.
- **Sort Events:** Organize events in a specified order.

#### Example Usage
```sh
# Start the calendar application
./calendar_app

# Commands to add and manage events
> initialize_calendar
> add_event "Meeting" "2024-07-01" "10:00"
> add_event "Doctor Appointment" "2024-07-02" "09:00"
> find_event "Meeting"
> delete_event "Doctor Appointment"
> sort_events
```

---



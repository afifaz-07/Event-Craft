# Event Craft

A console-based event management system written in C. Built as a Programming Fundamentals (PF) theory project.

## Features

### Client
- Sign up with personal/organization details
- Login (requires admin verification first)
- View available event facilities (Birthday, Wedding, Corporate, Budget Management)
- Add, view, search, update, and delete events
- Track upcoming events
- View total budget across all events
- View guest counts per event
- Submit complaints

### Admin
- Password-protected admin panel
- Verify users (individually or all at once)
- View all registered users
- Search a user by email
- Delete a user
- View all complaints
- Mark complaints as resolved

## How to Run

1. Compile the program:
   ```bash
   gcc event_craft_no_struct.c -o event_craft
   ```
2. Run it:
   ```bash
   ./event_craft
   ```

## Default Admin Password
```
admin123
```
(Change the `ADMIN_PASS` define at the top of the source file to set your own.)

## Tech
- Language: C
- Storage: In-memory arrays (no database, no structures — uses parallel arrays)

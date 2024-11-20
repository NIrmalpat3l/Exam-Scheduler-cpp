# Exam Scheduling Tool

## Overview

This tool is designed to efficiently schedule exams by assigning them to rooms and time slots. The system ensures that exams with common students are not scheduled at the same time and that rooms have sufficient capacity for the number of students.

## Features

### 1. **Exam Management**
- Add exams with details such as Exam ID, Name, Number of Students, and Student IDs.
- The system validates inputs to ensure the consistency of data.

### 2. **Room Management**
- Add rooms by specifying Room ID and Capacity.
- Ensures that rooms are available with the required capacity.

### 3. **Time Slot Management**
- Add time slots with a specified Date and Slot (Morning/Afternoon).
- Prevents duplicate assignments of time slots.

### 4. **Scheduling Algorithm**
- A backtracking algorithm is used to assign exams to available rooms and time slots while avoiding conflicts.

### 5. **Conflict Detection**
- Conflicts are detected based on overlapping students between exams, ensuring that exams are not scheduled at the same time if they share students.

### 6. **Backtracking and Domain Reduction**
- The system uses backtracking to explore possible assignments for each exam.
- When a conflict is found, the algorithm backtracks and tries different assignments, reducing the search space.

## Usage

1. **Add Exam**: Input the Exam ID, Name, Number of Students, and Student IDs.
2. **Add Room**: Specify Room ID and Capacity.
3. **Add Time Slot**: Choose a Date and Slot (Morning/Afternoon).
4. **Generate Schedule**: Click to generate the schedule after adding all required data.
5. **Reset**: Resets all the input data and the generated schedule.

## Algorithm Details

The backend C++ code uses a backtracking approach to assign exams to rooms and time slots. It checks for conflicts using a conflict matrix, and domains are reduced based on valid assignments. The complexity of the backtracking algorithm is exponential in the worst case, but it efficiently prunes the search space by eliminating invalid assignments early.

### Time Complexity:
- **Conflict Matrix Construction**: O(e^2 * s)
- **Backtracking Search**: O(d^e), where `e` is the number of exams and `d` is the size of the domain (possible room and time slot assignments).

## Files

- **index.html**: Contains the HTML structure for the frontend.
- **script.js**: Implements the logic for handling form submissions, generating schedules, and updating the UI dynamically.
- **styles.css**: Provides styling for the layout and elements on the page.
- **Exam-Scheduler.cpp**: The C++ backend that implements the conflict detection and scheduling algorithm.

## Conclusion

This tool helps in automating the process of exam scheduling while ensuring that there are no conflicts and that all exams are scheduled within available resources. The use of a backtracking algorithm ensures that the tool can handle various combinations of exams, rooms, and time slots.


*This project has been created as part of the 42 curriculum by <fabdul-s>.*

# get_next_line

## Description

get_next_line is a C project whose goal is to implement a function that reads and returns
a single line from a file descriptor each time it is called.

The project introduces the concept of static variables in C, allowing the function to
retain information between calls. By repeatedly calling get_next_line(), a file can be
read line by line without loading the entire file into memory.

The function must work with files as well as standard input, correctly handle different
BUFFER_SIZE values, and manage memory safely.

---

## Instructions

### Function Prototype

```c
char *get_next_line(int fd);
```

### Mandatory Files

- get_next_line.c
- get_next_line_utils.c
- get_next_line.h

### Bonus Files (if implemented)

- get_next_line_bonus.c
- get_next_line_utils_bonus.c
- get_next_line_bonus.h

### Compilation

The project must compile with or without the BUFFER_SIZE macro.

Example compilation command:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

If BUFFER_SIZE is not defined, a default value chosen by the developer must be used.

### Usage Example

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Algorithm Explanation

The get_next_line algorithm relies on incremental reading and persistent storage.

A static variable is used to store leftover data that has been read from the file
descriptor but not yet returned. This allows the function to remember its state
between calls.

Data is read from the file descriptor using read() with a buffer of size BUFFER_SIZE.
Reading continues until a newline character is found or until the end of the file is
reached.

Once a newline is encountered, memory is allocated for the line to be returned.
The line includes the newline character unless the end of file is reached without one.
Any remaining characters after the newline are saved in the static variable for the
next function call.

If the end of the file is reached and there is remaining data, that data is returned.
If there is no remaining data, the function returns NULL.

All allocated memory is properly freed to avoid memory leaks, and the function reads
only what is necessary to return the next line.

---

## Bonus Part

The bonus implementation extends the mandatory behavior by:

- Using only one static variable
- Supporting multiple file descriptors simultaneously

Each file descriptor maintains its own reading state, allowing calls such as:

get_next_line(fd3);
get_next_line(fd4);
get_next_line(fd5);
get_next_line(fd3);

without losing track of the reading position of each file descriptor.

Bonus files use the _bonus.c and _bonus.h suffix and are evaluated only if the mandatory
part is perfectly implemented.

---

## Resources

- POSIX read() documentation
  https://man7.org/linux/man-pages/man2/read.2.html

- Static variables in C
  https://en.wikipedia.org/wiki/Static_variable

- File descriptors
  https://man7.org/linux/man-pages/man2/open.2.html

### AI Usage

AI tools were used only for conceptual understanding, including explanations of static
variables, memory management, and algorithm design.

No code was copied or generated directly. All implementation decisions and code were
written manually in accordance with the 42 learning objectives and rules.

---

## Notes

- Global variables are forbidden
- lseek() is forbidden
- libft is not allowed
- Undefined behavior may occur when reading binary files
- The function must work with any BUFFER_SIZE value

---

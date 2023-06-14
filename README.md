# get_next_line

this 42 school project aimed at reading a line from a file descriptor. 
If called in a loop, `get_next_line should` return the entire content one line at a time, until the end of the file is reached.
Wheen compiling it, we should be able to modify the buffer size.

# Status
Finished : 14-06-2023.  Grade : 125/100.

# Usage
### compiling Mandatory part
```shell
cc -Wall -Wextra -Werror get_next_line.c get_next_line.h get_next_line_utils.c main_for_test/main.c
```
### compiling Bonus part
```shell
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_bonus.h get_next_line_utils_bonus.c main_for_test/main_bonus.c
```
### compiling Mandatory part for manual input
```shell
cc -Wall -Wextra -Werror get_next_line.c get_next_line.h get_next_line_utils.c main_for_test/main_manual_input.c
```

`BUFFER_SIZE` can be changed at compilation using the command `-D BUFFER_SIZE for instance to read byte-by-byte:
```shell
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line.h get_next_line_utils.c main_for_test/main.c
```
### Execution 

in case of manual input test, you will need to execute with 
```shell
./a.out /dev/tty
```
and then entire your text - stop at any moment with `ctrc + c`

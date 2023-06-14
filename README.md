# get_next_line

this 42 school project aimed at reading a line from a file descriptor. 
If called in a loop, `get_next_line should` return the entire content one line at a time, until the end of the file is reached.
Wheen compiling it, we should be able to modify the buffer size.

## Status
Finished : 14-06-2023.  Grade : 125/100.

## Usage
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

In case of file testing, as it is alread in the main(s), classic `./a.out` to exectute. Otherwise in case of manual input test, you will need to execute with 
```shell
./a.out /dev/tty
```
and then entire your text - stop at any moment with `ctrc + c`

## Example of test result expected
here is result of the bonus expected : one line from each fd at a time.
![test resutls](/img/test.png)
## Explanation of the program
We are using linked lists as a static variable to read each `buffer_size` number of bytes from the file (mapped by the `fd`) into each node as long as there is text or we encounter a `\n`. we then handle the last node to only keep the characters placed after `\n` that were read in the last buffer. 
We then clear the list, make it match the new node with characters after the `\n`, so that next call of `get_next_line()` will build the next linked list on top of the previous call words happenign after the `\n` ... and so on until we reach end of file.

![flow chart](/img/flow_chart.png)




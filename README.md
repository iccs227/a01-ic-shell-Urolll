[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/WIXYXthJ)
# ICSH

MILESTONE 1
- echo should work in script mode, with redirection, with logical operators, and with appending
- !! should work in script mode, with redirection, wih logical operators, and with appending
- !! should work multiple times in a row
- !! should work even after empty command (it keeps the previous actual command)

MILESTONE 2
- After script mode is over, it would quit the shell
- The default exit code is 0, meaning echo $? should always give 0 after script mode ends
- Script mode handles redirection, external commands, and signal handling

MILESTONE 3
- Can run most external commands
- Can run apps like "firefox"
- Cannot run commands like "cd" or "z" (from zoxide)

MILESTONE 4
- Does not support handling some edge cases like python3
- Works perfectly fine with commands like "sleep"
- After CTRL+C or CTRL+Z, the behavior of "echo $?" is the same as that of a normal terminal

MILESTONE 5
- Running "ls -la > dog" should create a file dog if it does not exist

MILESTONE 6
- Process id should count from 1, but it also counts the ones that are not in jobs (completed normally)
- "jobs" does not necessarily print the job id in order
- Background process for "sleep" should work as intended in the milestone criteria (but may work differently for weird and unpredictable commands like closing "cmatrix")

MILESTONE 7 (Extra Features)
- The "otter" command which randomly prints out one of the otter ASCII arts
- The append operator ">>"

# Use-After-Free (CWE-416)

Use After Free Vulnerability, Attack and Fix

## Clone The Repository:

```
$ git clone https://github.com/NVombat/Use-After-Free.git
```

## Files:

- use_after_free.c -> Contains vulnerable code with the use-after-free vulnerability that can be exploited
- use_after_free_patched.c -> Contains the patched code where the use-after-free vulnerablity has been patched
- exploit1.sh -> Attack script 1
- exploit2.sh -> Attack script 2
- Makefile -> File for compiling the c files into their respective binaries
- heap_overflow.c -> An example of a heap overflow attack

## How to Run:

1. Run the Makefile:
```
$ make
```
2. Try to exploit the program yourself:
```
$ ./use_after_free
```
3. Run attack scripts to exploit the program:
```
$ ./exploit1.sh [OR] ./exploit2.sh
```
4. Try to exploit the patched version yourself:
```
$ ./use_after_free_patched
```
5. Clean up:
```
$ make clean
```

## Exploit Explained:

When memory is freed, the heap manager puts this memory into bins (Fast Bins and Regular Bins). Our code is concerned only with the Fast Bin which is used for smaller memory chunks. When memory is freed, it is put into the Fast Bin and is readily available for use by any other program or process however, if a memory chunk is freed and a request to allocate the same amount of memory is made after the freeing of the chunk, the freed memory is given to the program. The problem arises because the pointer to that freed memory chunk was never made NULL thus it still points to that memory chunk which has now been assigned to some other variable, program or process. The "dangling" pointer will take the value of whatever is stored in the newly allocated memory chunk.

## Fix Explained:

The easiest way to fix this vulnerability is to ensure that once memory is freed, the pointer to that memeory is made to be NULL. This does not allow for dangling pointers.

## How To Exploit The Code:

1. Select option 1 to allocate a chunk of memory to store the username
2. Select option 2 to allocate a chunk of memory to store the password
3. Free the chunks of memory using option 3.
4. Select option 2 to allocate a chunk of memory for the password so that it can rewrite the contents of the previously allocated username chunk too.
5. Use option 4 to log in and successfully exploit the vulnerability

OR

1. Select option 1 to allocate a chunk of memory to store the username
2. Select option 2 to allocate a chunk of memory to store the password
3. Free the chunks of memory using option 3.
4. Select option 4 to allocate the chunks of memory to temp_uname and temp_pwd and then enter "root" as the username

## Heap Overflow:
- A successful heap overflow can be performed using these commands:
```
$ make heap_overflow

$ ./heap_overflow AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAls

$ make clean
```
- This will execute the ```ls``` command however that can be replaced with any command of the attackers choice
- The ```uname``` and ```cmd``` variables are allocated 64 byte chunks next to each other in the heap.
- When executing the above mentioned command, the ```uname``` variable is filled with ```A's``` and these ```A's``` overflow to the next memory chunk which is ```cmd``` thus overwriting the hard-coded and intended command.
- This causes the program to execute the command injected by the attacker

# References:

- https://infosecwriteups.com/heap-exploitation-for-homo-sapiens-f166cd6a59fe
- https://infosecwriteups.com/arming-the-use-after-free-bc174a26c5f4

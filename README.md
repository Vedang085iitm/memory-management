
# Memory Management System

This is a C++ program for a simple Memory Management System that simulates memory allocation and management in a computer system. It allows users to load processes into main memory, perform memory operations (add, subtract, print, load), manage processes (kill, swap in/out), and view information about page tables.


This program implements a memory management system that handles paging and virtual memory. It allows users to load processes into memory, execute commands within those processes, manage processes, and view information about memory allocation.

## Input Format

The program takes the following input parameters:

- *Main Memory Size (M in KB):* Specifies the size of the main memory in kilobytes.

- *Virtual Memory Size (V in KB):* Specifies the size of virtual memory in kilobytes.

- *Page Size (P in bytes):* Specifies the size of each page in bytes.

- *Executable Files:* You can load executable files into memory. Each file contains:
  - Size (in KB): An assigned value for the executable's size, used for memory management.
  - A set of commands in the format:
    - `add x, y, z`: Add the contents of memory addresses x and y and store the result in memory address z.
    - `sub x, y, z`: Subtract the contents of memory address y from memory address x and store the result in memory address z.
    - `print x`: Print the value at memory address x.
    - `load a, y`: Store the value a in memory address y.

## System Commands

The system accepts the following commands:

- `load <filename1> <filename2> .. <filenameN>`: Load executable files into memory in order. Assign each executable a process id (pid). Print loading status messages.

- `run <pid>`: Execute the sequence of instructions in the program identified by its pid. Swaps processes between main memory and virtual memory using the LRU replacement algorithm.

- `kill <pid>`: Terminate a process identified by its pid and free its memory.

- `listpr`: Print the process identifiers (pids) of processes in main memory and virtual memory, sorted by pid.

- `pte <pid> <file>`: Print the page table entry information of a process to the specified output file. Include logical page numbers and physical page numbers.

- `pteall <file>`: Print page table entry information for all processes in ascending pid order.

- `swapout <pid>`: Swap out the process specified by pid into virtual memory.

- `swapin <pid>`: Swap in the process specified by pid into main memory. Swaps out the last run process(es) in main memory using the LRU replacement algorithm if necessary.

- `print <memloc> <length>`: Print the values stored in the physical memory locations from memloc through memloc + length - 1.

- `exit`: Exit the system and clean up allocated memory.

## Process Identifier (pid)

Each process is assigned a unique 32-bit process identifier (pid) starting from 1. Pids are used to identify and manage processes.

## Error Handling

The program handles invalid memory addresses and invalid pids by printing appropriate error messages and continuing to accept commands.

## Usage

Compile the program and run it with appropriate input parameters and commands.

## Author

This Memory Management System question was created by [
Prashanth L.A. (FOR IIT MADRAS COURSE CS3500)].

## Program Features

- Load Processes: You can load processes from input files into main memory or virtual memory, depending on available space.

- Page Table Entry Information: View information about the page table entries for a specific process.

- List Processes: List all processes currently in main memory and virtual memory.

- Page Table Entry Information for All Processes: View information about the page table entries for all processes.

- Swap Out Process: Move a process from main memory to virtual memory.

- Kill Process: Terminate a process and free its memory.

- Print Memory: Print the content of memory locations in main memory.

- Run Process Commands: Execute commands from a file associated with a process.

- Swap In Process: Move a process from virtual memory to main memory.
  
- all basic assumptions are considered.
- 
-  process identifier values will not wrap-around and hence pid reuse is not considered as given in the question.

## Usage()

### Compilation

Compile the program using a C++ compiler:

zsh
g++ -o memory_management memory_management.cpp


### Execution

Run the compiled program with the following command:

zsh
./memory_management -M <main_memory_size_KB> -V <virtual_memory_size_KB> -P <page_size_KB>


Replace <main_memory_size_KB>, <virtual_memory_size_KB>, and <page_size_KB> with the desired values. These values specify the sizes of main memory, virtual memory, and page size in kilobytes.

### Commands

Once the program is running, you can enter commands such as:

- load <filename>: Load a process from a file into memory.
- pte <pid> <filename>: View page table entry information for a specific process.
- listpr: List processes in main memory and virtual memory.
- pteall <filename>: View page table entry information for all processes.
- swapout <pid>: Swap out a process from main memory to virtual memory.
- kill <pid>: Terminate a process and free its memory.
- printmem <memloc> <length>: Print memory content starting at the specified location for a given length.
- run <pid>: Execute commands from a file associated with a process.
- swapin <pid>: Swap in a process from virtual memory to main memory.
- exit: Exit the program.

## Requirements

- C++ compiler (e.g., g++)
- Input files containing process commands

## Author

This Memory Management System was created by Vedang.

## License

This program is open-source software l.

Feel free to modify and use it for educational purposes or in your own projects. If you find any issues or have suggestions for improvements, please submit them in the repository's issue tracker.

---

Please note that you should adjust the README to include any additional details or specific instructions that might be necessary for your use case.

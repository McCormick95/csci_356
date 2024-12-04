# CPU Scheduler Implementation

This project implements a simple CPU scheduler that simulates different scheduling algorithms given a process trace. The scheduler handles process execution scheduling without dealing with I/O, system calls, or memory-related interrupts.

## Supported Scheduling Algorithms

1. **First Come First Serve (FCFS)**
   - Basic scheduling algorithm that executes processes in the order they arrive
   - Non-preemptive

2. **Preemptive Priority (PP) with Aging**
   - Priority-based scheduling with preemption
   - Includes aging mechanism to prevent starvation
   - Process priorities increase by 1 every 8ms of waiting time

## Project Structure

- `main.c`      - Main program entry point and input handling
- `scheduler.h` - Scheduler interface definitions
- `scheduler.c` - Implementation of scheduling algorithms
- `process.h`   - Process structure definition
- `my_queue.h`  - Queue interface definitions
- `my_queue.c`  - Queue implementation
- `Makefile`    - Build configuration

## Building the Project

To build the project, simply run:

```bash
make
```

This will compile all source files and create the executable named `scheduler`.

To clean the build files:

```bash
make clean
```

## Usage

The scheduler is invoked via command-line with the following syntax:

```bash
./scheduler [FCFS | PP]
```

Where:
- `FCFS` - First Come First Serve algorithm
- `PP` - Preemptive Priority with aging

## Input Format

The scheduler reads process information from standard input in the following format:

```
pid arrival_time cpu_time [priority]
```

Where:
- `pid` - Process ID (positive integer)
- `arrival_time` - Time at which process arrives (milliseconds)
- `cpu_time` - CPU time requested by the process
- `priority` - Process priority (only for PP scheduling, higher number = higher priority)

Input is terminated by a line containing all zeros.

### Example Input
```
1 0 12 5
2 0 9 5
3 3 6 6
4 7 4 7
0 0 0
```

## Output Format

The scheduler outputs scheduling events in real-time:
```
time pid event
```

Events include:
- Process running
- Process completing
- Process arriving
- Process aging (for PP scheduling)

After completion, it displays statistics:
- Average waiting time
- Average response time
- Average turnaround time
- Average CPU usage

## Implementation Details

- Maximum of 25 processes supported
- Uses custom queue implementation (`my_queue.c`)
- Process Control Block (PCB) structure maintains process state
- Time-driven simulation with clock ticks
- Priority aging implemented for PP scheduling


## Building and Testing Environment

The project is designed to compile and run using GCC. Ensure you have the following:

- GCC compiler
- Make build system

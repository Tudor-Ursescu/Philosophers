# 🧠 Philosophers

## ↕️Table of Contents
1.[Introduction](#-introduction)

2.[Features](#-features)

3.[Project Structure](#-project-structure)

4.[Installation](#installation)

5.[Usage](#-usage)

6.[Built-in Mechanisms](#-built-in-mechanisms)

7.[Contributors](#-contributors)

8.[License](#-license)

## 📖 Introduction
The Philosophers project is an implementation of the classic Dining Philosophers Problem, a synchronization challenge in concurrent programming. This project is designed to help understand threads, mutexes, and concurrency management in C using pthread.

## ✨ Features
- Multithreading: Utilizes pthreads for concurrent execution.

- Mutex-based synchronization: Ensures proper fork management and prevents deadlocks.

- Custom time management: Implements precise time tracking for philosopher actions.

- Fairness handling: Avoids starvation in an odd number of philosophers.

## 📂 Project Structure
```sh
Philosophers/
│── includes/
│   └── philo.h           # Header file with struct and function definitions
│── src/
│   ├── main.c            # Entry point of the program
│   ├── init.c            # Initialization of structures
│   ├── dinner.c          # Philosophers' routine execution
│   ├── monitor.c         # Death monitoring system
│   ├── utils.c           # Utility functions
│   ├── sync_utils.c      # Synchronization-related utilities
│   ├── write_status.c    # Output messages and status updates
│   ├── getters_setters.c # Thread-safe getters and setters
│── Makefile              # Compilation rules
```

## ⚙️ Installation
To install and compile philosophers, follow these steps:
```sh
#Clone the repository
git clone https://github.com/Tudor-Ursescu/Philosophers.git
#Navigate into the project directory
cd Philosophers
#Compile the project
make
```
This will generate an executable named `philo`

## 🚀 Usage
Run the program with the following arguments: 
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#Example:
./philo 5 800 200 200 5
```
- number_of_philosophers: Total philosophers at the table.
- time_to_die: Time (in ms) before a philosopher dies if they don’t eat.
- time_to_eat: Time (in ms) required for a philosopher to eat.
- time_to_sleep: Time (in ms) required for a philosopher to sleep.
- [number_of_times_each_philosopher_must_eat] (optional): Simulation stops when each philosopher eats this number of times.

## 🔧 Built-in Mechanisms
| Functionality              | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| **Mutex Synchronization**  | Prevents race conditions when philosophers access shared resources.        |
| **Thread Management**      | Each philosopher runs as a separate thread to simulate concurrency.         |
| **Fork Assignment**        | Ensures fair allocation of forks to prevent deadlocks and starvation.       |
| **Death Monitoring**       | Continuously checks if a philosopher has starved and stops the simulation. |
| **Logging System**         | Prints philosopher actions in real-time for better visualization.           |

## 👥 Contributors
[**Tudor Ursescu**](https://github.com/Tudor-Ursescu)

## 📜 License
This is an open-source project. Feel free to use, modify, and distribute it as needed!
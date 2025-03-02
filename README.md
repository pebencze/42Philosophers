# Philosophers

By solving this project, I have learned a lot about multithreading using pthreads.

## Overview

This repository contains a simulation of the classic ["Dining Philosophers"](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem. The simulation involves philosophers who sit at a round table with a large bowl of spaghetti. Each philosopher alternates between eating, thinking, and sleeping. The challenge is to manage resource sharing (forks) to ensure that no philosopher starves.

## Rules and Requirements

Philosophers can eat, think, or sleep. <br/>
While eating, philosophers hold two forks, one in each hand.<br/>
Philosophers put their forks back on the table after eating and then sleep.<br/>
Philosophers start thinking after sleeping.<br/>
The simulation stops when a philosopher dies of starvation.<br/>
Philosophers do not communicate with each other.<br/>
Philosophers do not know if another philosopher is about to die.<br/>
Philosophers should avoid dying at all costs.<br/>
    
## Concurrency and Safety

Each philosopher is represented by a thread.<br/>
Forks are shared resources protected by mutexes to prevent data races.<br/>
Global variables are forbidden.<br/>

## Program Arguments

number_of_philosophers: The number of philosophers and forks.<br/>
time_to_die (ms): Time after which a philosopher dies if they haven't eaten.<br/>
time_to_eat (ms): Time a philosopher spends eating.<br/>
time_to_sleep (ms): Time a philosopher spends sleeping.<br/>
number_of_times_each_philosopher_must_eat (optional): If specified, the simulation stops after each philosopher has eaten this many times. If not specified, the simulation stops when a philosopher dies.<br/>


## State Logging

    timestamp_in_ms X has taken a fork
    timestamp_in_ms X is eating
    timestamp_in_ms X is sleeping
    timestamp_in_ms X is thinking
    timestamp_in_ms X died

## Functions Used

    memset, printf, malloc, free, write
    usleep, gettimeofday
    pthread_create, pthread_join
    pthread_mutex_init, pthread_mutex_destroy
    pthread_mutex_lock, pthread_mutex_unlock

## Building and Running the Program

To compile the program, run:

    make

To run the simulation, execute the following command:

    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Example:

    ./philo 5 800 200 200

This command runs a simulation with 5 philosophers, where each philosopher will die if they haven't eaten within 800 ms, spends 200 ms eating, and 200 ms sleeping.

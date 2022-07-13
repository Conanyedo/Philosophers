# Philosophers

Philosophers is an introduction to the basics of process threading, and how work on the same memory space. 
And learn about mutexes, semaphores, and shared memory.

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

# About

The project consists of two part, the first one uses `Threads` and `Mutex` to organise philosophers. 
The second part uses `processes` and `semaphores` to share memory.

# Testing

To test the project, go to one of the folders and run `make`. Then, you can test the project using an executable.

- usage :

  * `./philo number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]` the last argument is optional.

- exemple :

  * `./philo 4 500 200 200`

# Visualization of the dinning philosophers problem

![image](https://user-images.githubusercontent.com/54075373/178767806-2aeeb572-d690-4533-b0be-bf49bbcac2c4.png)
![image](https://user-images.githubusercontent.com/54075373/178768411-86ba387e-4e0b-46d9-a433-5c122d4508b7.png)

# Philosophers

This repo provides a programm called "philo" that simulates the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in a slightly modified way using threads and mutexes.  

Tested on macOS Monterey.

## Installation

#### 1) Clone this repository 
```
git clone git@github.com:JL1709/Philosophers.git
```

#### 2) Run Makfile
```
cd Philosophers
make
```

#### 3)  Run program
```
$>./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat(optional)
```
- number_of_philosophers: number of philosophers and also the number of forks.
- time_to_die : if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.
- time_to_eat: time it takes for a philosopher to eat.
- time_to_sleep: time the philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.  

Example:
```
$>./philo 6 800 200 200 5
```

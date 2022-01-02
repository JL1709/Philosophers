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
$>./philo "number_of_philosophers" "time_to_die [ms]" "time_to_eat [ms]" "time_to_sleep [ms]" "number_of_times_each_philosopher_must_eat (optional)"
```
- number_of_philosophers: number of philosophers and also the number of forks.
- time_to_die : if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.
- time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.
- time_to_sleep: is the time the philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

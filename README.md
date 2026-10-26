# Philosophers

The goal of the "Philosophers" project is to simulate the classic "Dining Philosophers" problem, by using multithreading, processes, mutexes and atomic variables.

## 📝 The Simulation

*   Philosophers sit at a round table with a bowl of spaghetti.
*   They alternate between three states: **eating**, **thinking**, and **sleeping**.
*   There is one fork between each philosopher (Mandatory) or a pool of forks in the middle (Bonus).
*   A philosopher needs **two forks** to eat.
*   The simulation stops if a philosopher starves to death. The goal is to keep them all alive.

## 🚀 How to Run

### Mandatory Part (Threads & Mutexes)

Each philosopher is a thread. Forks are protected by mutexes.

```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
### Arguments Explained

Times are in milliseconds.

1.  `number_of_philosophers`: How many philosophers (and forks) are at the table.
2.  `time_to_die`: If a philosopher doesn't start eating within this time after their last meal (or the start of the simulation), they die.
3.  `time_to_eat`: How long it takes a philosopher to eat (they hold two forks during this time).
4.  `time_to_sleep`: How long a philosopher sleeps after eating.
5.  `[number_of_times_each_philosopher_must_eat]` (Optional): The simulation stops if everyone has eaten at least this many times. If left blank, the simulation only stops upon a death.

## 🛑 Rules & Constraints

*   No data races.
*   No global variables (except for one specific signal flag if needed, per the rules).
*   Death messages must print within 10ms of the actual death.

# 🍽️ Philosophers

Implementation of the dining philosophers problem using threads and mutexes.

## 🎯 Overview

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## ⚙️ Parameters

- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds until philosopher dies without eating
- `time_to_eat`: Time in milliseconds to eat
- `time_to_sleep`: Time in milliseconds to sleep
- `number_of_times_each_philosopher_must_eat`: Optional argument

## 🛠️ Implementation

### Key Functions
- Thread creation
- Mutex handling
- Time management
- Death checking
- Eating simulation

## 📋 Rules

- Philosophers sit at a round table
- Philosophers need two forks to eat
- Philosophers must eat, sleep, and think
- If a philosopher doesn't eat within time_to_die, they die
- Program stops when a philosopher dies

## 🚀 Installation

```bash
git clone https://github.com/fsantos23/philosophers.git
cd philosophers
make
```

## 🧪 Testing

```bash
# Basic test
./philo 4 800 200 200

# With meals limit
./philo 4 800 200 200 5

# Death test
./philo 4 310 200 200
```

## ⚠️ Error Handling

- Invalid arguments
- Thread creation failures
- Mutex initialization errors
- Memory allocation failures
- Timing issues

## 🔄 Program Flow

1. Parse arguments
2. Initialize mutexes
3. Create threads
4. Monitor philosophers
5. Clean resources

## ⭐ Show your support

Give a ⭐️ if this project helped you!

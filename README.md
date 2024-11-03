# 🍝 42 Philosophers – Dining with a Twist! 🍝

![github_philosophers_42](https://github.com/user-attachments/assets/d6ff7e7d-ba44-4e9d-92c8-fb29f2ae43cb)


Welcome to **42 Philosophers**, a project where classic problem-solving meets concurrent programming! Inspired by Edsger Dijkstra’s **Dining Philosophers Problem**, this project teaches us the art of managing shared resources and avoiding deadlock in a multi-threaded environment. Here’s everything you need to know to tackle this project and emerge victorious! 🏆

---

## 📜 Project Overview

Imagine philosophers sitting around a table with a single bowl of spaghetti. To eat, each philosopher needs two forks, yet there are only as many forks as philosophers. The challenge? Ensuring each philosopher can eat, sleep, and think without anyone starving or creating a deadlock.

**Objectives**:

1. **Mandatory Part**: Use **threads** and **mutexes** to manage shared resources.
2. **Bonus Part**: Implement with **processes** and **semaphores** for enhanced resource management.

---

## 🔧 Project Breakdown: How It Works

Each philosopher follows a cycle:
1. **Eating** 🍝 (if they have two forks),
2. **Sleeping** 🛏️,
3. **Thinking** 💭.

They repeat this loop until they either meet a set number of meals or tragically starve if they wait too long to eat. Philosophers can’t communicate with each other, so it’s all about careful resource management!

---

### 📐 Project Parameters

| Argument                             | Description                                                                                              |
|--------------------------------------|----------------------------------------------------------------------------------------------------------|
| `number_of_philosophers`             | Number of philosophers and forks at the table.                                                           |
| `time_to_die`                        | Maximum time (in ms) a philosopher can live without eating.                                              |
| `time_to_eat`                        | Time (in ms) a philosopher spends eating when holding two forks.                                         |
| `time_to_sleep`                      | Time (in ms) a philosopher spends sleeping after eating.                                                 |
| `number_of_times_each_philosopher_must_eat` (optional) | Stops the simulation once each philosopher has eaten this many times.                         |

---

### 📊 Example Run

```bash
# Run with 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, and each eating at least 3 times
./philo 5 800 200 200 3
```

Expected output:
```plaintext
[timestamp] [1] has taken a fork
[timestamp] [1] is eating
[timestamp] [2] has taken a fork
[timestamp] [2] is eating
...
[timestamp] [3] died
```

The program will log each action for every philosopher until they meet their dining requirements or one of them starves.

---

## 🎩 Mandatory Part: Threads & Mutexes

For the mandatory part:
1. **Each philosopher** is a **thread**, allowing concurrent actions.
2. **Each fork** is a **mutex**. Philosophers attempt to lock two mutexes (forks) to eat, releasing them when done.
3. **Deadlock Prevention**: Careful handling of mutexes ensures no philosopher is indefinitely blocked.

### Running the Program

1. Clone the repo:
   ```bash
   git clone https://github.com/DigitalPool/42-Philosophers.git
   ```
2. Navigate to the `philo` directory and compile:
   ```bash
   cd 42-Philosophers && make
   ```
3. Run the program:
   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

---

## 🌟 Bonus Part: Processes & Semaphores

For the bonus:
1. **Philosophers** are now **processes**, providing a fresh take on shared memory.
2. **Forks** are represented as **semaphores** in the center of the table. This allows any philosopher to access any fork, enhancing flexibility.
   
### Running the Bonus Program

1. Navigate to the `philo_bonus` directory and compile:
   ```bash
   cd 42-Philosophers/philo_bonus && make
   ```
2. Run the program:
   ```bash
   ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

---

## 💡 Tips to Ace the Project

1. **Understand Deadlock**: Recognize how deadlock forms in concurrent programming and take steps to prevent it by carefully managing mutex locks.
2. **Keep an Eye on Timing**: Use accurate timing functions to ensure philosophers eat and sleep as per the input parameters.
3. **Debug with Patience**: Testing concurrency can be tricky. Log each philosopher’s actions and use visual debugging tools if needed.
4. **Follow Norminette Rules**: Keep functions short, variables organized, and code clean.

---

## 🍜 There you have it, the dining philosophers problem!

Good luck, and may your philosophers dine in harmony! Keep each philosopher well-fed, rested, and thinking, all while sharpening your concurrency skills.

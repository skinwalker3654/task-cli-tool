# TASK_CLI_MANAGER (C)

A cli tool that works with 
commands in terminals that you can use it
to add delete change or complete your personal tasks.

---

## Features
- **adding** tasks
- **removing** tasks
- **renaming** tasks
- **changing** task status
- **listing** tasks
- **listing** by status
- **clear** tasks by status
- **reset** the task list
- **help** command menu

---

## examples of usage
```bash
./task add "buy groceries"
./task add "do programing"
./task set-status 1 done
./task clear done
./task list
```
---

## Requirments:
`gcc` compiler and `GNU MAKE`

### compile the program
```bash
make 
```
### when you want to delete the executable:
```bash
make clean
```
---

## Notes
- The task manager uses vectors for dynamic growth
- It auto saves and loads the tasks from a file so the program can remember the tasks youv added

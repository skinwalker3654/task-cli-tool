#ifndef TASK_TOOL_H
#define TASK_TOOL_H

#include <stdint.h>

typedef enum { 
    TODO,
    DOING,
    DONE, 
    EVERY_STATUS, /*This is used when we want to print all the list with every status
                  *bc in the print_list_of_tasks function you say what status you want to print specifically*/
} TaskStatus;

typedef struct Task_t {
    uint32_t taskId;
    char *taskName;
    TaskStatus taskStatus;    
} Task_t;

typedef struct TaskList {
    Task_t *tasks;
    uint32_t capacity;
    uint32_t counter;
} TaskList;

/*UTIL FUNCTIONS*/
void initialize_task_list(TaskList *listPtr);
void save_tasks_to_file(TaskList *listPtr);
void load_tasks_from_file(TaskList *listPtr);
void free_task_list(TaskList *listPtr);
void reset_task_list(TaskList *listPtr);
void help_show_commands(void);

/*MAIN FUNCTIONS*/
void add_task_to_list(TaskList *listPtr,char *givenTaskName);
void remove_task_from_list(TaskList *listPtr,int givenTaskId);
void print_list_of_tasks(TaskList *listPtr,TaskStatus givenStatu);
void change_task_status_by_id(TaskList *listPtr,int givenTaskId,TaskStatus givenStatu);
void rename_task_from_list(TaskList *listPtr,int givenTaskId,char *givenTaskName);
void clear_tasks_by_status(TaskList *listPtr,TaskStatus givenStatu);

#endif

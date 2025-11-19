#include <stdio.h>
#include <stdlib.h>
#include "tasktool.h"
#include <string.h>
#include <stdint.h>

void initialize_task_list(TaskList *listPtr) {
    /* The SIZE of the capacity if by default 2 and its going to double every
     * time the tasks fill the size of the array (VECTOR)*/
    listPtr->capacity = 2;
    listPtr->tasks = malloc(sizeof(Task_t)*listPtr->capacity);
    if(listPtr->tasks == NULL) {
        printf("[ERR] Task program initialization failed when started allocating memory for the task list\n");
        exit(EXIT_FAILURE);
        /* This runs in the start of the program so in case memory allocation fail
         * there is no other memory allocated before so we exit the program safely*/
    }

    listPtr->counter = 0;
}

void add_task_to_list(TaskList *listPtr,char *givenTaskName) {
    if(listPtr->counter >= listPtr->capacity) {
        /* We double the capacity when the tasks filled the current 
         * Task_t array size*/
        listPtr->capacity *= 2;
        Task_t *tempList = realloc(listPtr->tasks,sizeof(Task_t)*listPtr->capacity);
        if(tempList == NULL) {
            printf("[ERR] Failed to resize the task list with more memory for the new tasks\n");
            return;
        }

        /* We used temporary variable in case the reallocation failed
         * and now we add the values in the reall task list*/
        listPtr->tasks = tempList;
    }

    /*Checking if the givenTaskName already exists in the list*/
    int foundTaskWithSameName = -1;
    for(int i=0; i<listPtr->counter; i++) {
        if(strcmp(listPtr->tasks[i].taskName,givenTaskName)==0) {
            foundTaskWithSameName = 1;
            break;
        }
    }

    if(foundTaskWithSameName == 1) {
        printf("[ERR] Task with name '%s' already exists in the list\n",givenTaskName);
        return;
    }

    /* STRDUP function allocates memory exactly for the size of the string 
     * so make sure in future changes to keep freeying the task names at the end of the program*/
    listPtr->tasks[listPtr->counter].taskName = strdup(givenTaskName);
    if(listPtr->tasks[listPtr->counter].taskName == NULL) {
        printf("[ERR] Failed to allocate memory for the tasks name\n");
        return;
    }

    /*ID's are just numbers from 1 to INF so bc the task counter starts from zero we just add 1*/
    listPtr->tasks[listPtr->counter].taskId = listPtr->counter+1;
    listPtr->tasks[listPtr->counter].TaskStatu = TODO; //Default task status
    listPtr->counter++;

    /*Becauses we encresed the counter size before we now saying -1 to see the current task that added*/
    printf("[OK] task created succesfully with ID %d\n",listPtr->tasks[listPtr->counter-1].taskId);
}

void remove_task_from_list(TaskList *listPtr,int givenTaskId) {
    if(listPtr->counter == 0) {
        printf("[ERR] Task list is empty, there are no tasks to delete yet\n");
        return;
    }

    /*We checking if the task with the givenTaskId is existing in the list*/
    int foundTaskIndex = -1;
    for(int i=0; i<listPtr->counter; i++) {
        if(listPtr->tasks[i].taskId == givenTaskId) {
            foundTaskIndex = i;
            break;
        }
    }

    /* Deafault value of the foundTaskIndex is -1 so if it didnt find the task
     * with the given ID then the value will remain the same so we print
     * That the task does not exists*/
    if(foundTaskIndex == -1) {
        printf("[ERR] Task with ID %d does not found in the list\n",givenTaskId);
        return;
    }

    /* We keep the name of the task we are going to delete bc
     * we are going to use it on the message at the end*/
    char *deleted_task_name = strdup(listPtr->tasks[foundTaskIndex].taskName);
    free(listPtr->tasks[foundTaskIndex].taskName);

    /*Shifting method for deletion*/
    for(int i=foundTaskIndex; i<listPtr->counter-1; i++) 
        listPtr->tasks[i] = listPtr->tasks[i+1];
    listPtr->counter--; 

    /*We add the ID's in the specific order*/
    for(int i=0; i<listPtr->counter; i++) listPtr->tasks[i].taskId = i+1;
    printf("[OK] Task '%s' removed from the list succesfully\n",deleted_task_name);
    free(deleted_task_name);
}

void print_list_of_tasks(TaskList *listPtr,TaskStatus givenStatu) {
    if(listPtr->counter == 0) {
        printf("[ERR] Task list is empty, there are no tasks to print yet\n");
        return;
    }

    /* So this function gets a specific status and 
     * then it prints every task with that status
     * except in the case of the EVERY_STATU that
     * prints all the tasks*/
    if(givenStatu == TODO) {
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == TODO) {
                printf("%d | TODO | %s\n"
                        ,listPtr->tasks[i].taskId
                        ,listPtr->tasks[i].taskName);
            }
        }
    } else if(givenStatu == DONE) {
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == DONE) {
                printf("%d | DONE | %s\n"
                        ,listPtr->tasks[i].taskId
                        ,listPtr->tasks[i].taskName);
            }
        }
    } else if(givenStatu == DOING) {
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == DOING) {
                printf("%d | DOING | %s\n"
                        ,listPtr->tasks[i].taskId
                        ,listPtr->tasks[i].taskName);
            }
        }
    } else if(givenStatu == EVERY_STATU) {
        for(int i=0; i<listPtr->counter; i++) {
            /*All this is in the same line
             * but bc the status are difrent
             * we had to check manualy*/
            printf("%d |",listPtr->tasks[i].taskId);

            if(listPtr->tasks[i].TaskStatu == TODO) {
                printf(" TODO  |");
            } else if(listPtr->tasks[i].TaskStatu == DONE) {
                printf(" DONE  |");
            } else if(listPtr->tasks[i].TaskStatu == DOING) {
                printf(" DOING |");
            }

            printf(" %s\n",listPtr->tasks[i].taskName);
        }
    } else {
        printf("[ERR] You passed an invalid status format in the function \"print_list_of_tasks\"\n");
        return;
    }
}

void change_task_status_by_id(TaskList *listPtr,int givenTaskId,TaskStatus givenStatu) {
    if(listPtr->counter == 0) {
        printf("[ERR] The task list is empty, there are no tasks to change yet\n");
        return;
    }

    /*We check if the task with the givenTaskId exists*/
    int foundTaskIndex = -1;
    for(int i=0; i<listPtr->counter; i++) {
        if(listPtr->tasks[i].taskId == givenTaskId) {
            foundTaskIndex = i;
            break;
        }
    }

    /* The default value of the foundTaskIndex variable is -1 
     * so if we didnt find the task with the givenTaskId
     * then the variable will still be -1*/
    if(foundTaskIndex == -1) {
        printf("[ERR] Task with ID %d not found in the list\n",givenTaskId);
        return;
    }

    /*We check if the task with the givenTaskId has already the givenStatu*/
    if(listPtr->tasks[foundTaskIndex].TaskStatu == givenStatu) {
        printf("[ERR] Task with ID %d is already in the given status\n",givenTaskId);
        return;
    }
    
    listPtr->tasks[foundTaskIndex].TaskStatu = givenStatu;
    printf("[OK] Task '%s' has changed status succesfully\n",listPtr->tasks[foundTaskIndex].taskName);
}

void rename_task_from_list(TaskList *listPtr,int givenTaskId,char *givenTaskName) {
    if(listPtr->counter == 0) {
        printf("[ERR] Task list is empty, there are no tasks to rename yet\n");
        return;
    }

    /*We check if the task with the givenTaskId exists in the list*/
    int foundTaskIndex = -1;
    for(int i=0; i<listPtr->counter; i++) {
        if(listPtr->tasks[i].taskId == givenTaskId) {
            foundTaskIndex = i;
            break;
        }
    }

    /* The foundTaskIndex variable has by default the -1 value
     * so if the task havent found on the list nothing changed on the variable*/
    if(foundTaskIndex == -1) {
        printf("[ERR] Task with ID %d not found in the list\n",givenTaskId);
        return;
    }

    /*We check if the task is already named to the givenTaskName*/
    if(strcmp(listPtr->tasks[foundTaskIndex].taskName,givenTaskName)==0) {
        printf("[ERR] Task with ID %d is already named '%s'\n",givenTaskId,givenTaskName);
        return;
    }

    /* We keep the name of the task before the renaming so we can use
     * it on the message at the end*/
    char *task_before_rename = strdup(listPtr->tasks[foundTaskIndex].taskName);
    free(listPtr->tasks[foundTaskIndex].taskName);
    listPtr->tasks[foundTaskIndex].taskName = strdup(givenTaskName);

    printf("[OK] Task '%s' has renamed to '%s' succesfully\n",task_before_rename,givenTaskName);
    free(task_before_rename);
}

void clear_tasks_by_status(TaskList *listPtr,TaskStatus givenStatu) {
    /* This function clears every task with 
     * the given status by using the sifting method*/
    if(givenStatu == DOING) { //DOING_STATU
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == DOING) {
                free(listPtr->tasks[i].taskName);
                for(int j=i; j<listPtr->counter-1; j++) 
                    listPtr->tasks[j] = listPtr->tasks[j+1];
                listPtr->counter--;
                i--;
                for(int z=0; z<listPtr->counter; z++) listPtr->tasks[z].taskId = z+1;
            }
        }
    } else if(givenStatu == TODO) { //TODO_STATU
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == TODO) {
                free(listPtr->tasks[i].taskName);
                for(int j=i; j<listPtr->counter-1; j++) 
                    listPtr->tasks[j] = listPtr->tasks[j+1];
                listPtr->counter--;
                i--;
                for(int z=0; z<listPtr->counter; z++) listPtr->tasks[z].taskId = z+1;
            }
        }
    } else if(givenStatu == DONE) { //DONE_STATU
        for(int i=0; i<listPtr->counter; i++) {
            if(listPtr->tasks[i].TaskStatu == DONE) {
                free(listPtr->tasks[i].taskName);
                for(int j=i; j<listPtr->counter-1; j++) 
                    listPtr->tasks[j] = listPtr->tasks[j+1];
                listPtr->counter--;
                i--;
                for(int z=0; z<listPtr->counter; z++) listPtr->tasks[z].taskId = z+1;
            }
        }
    }

    printf("[OK] Tasks with the given status have been cleared succesfully\n");
}

void reset_task_list(TaskList *listPtr) {
    if(listPtr->counter == 0) {
        printf("[ERR] List is already empty, it cannot be reseted\n");
        return;
    }

    for(int i=0; i<listPtr->counter; i++)
        free(listPtr->tasks[i].taskName);

    free(listPtr->tasks);
    initialize_task_list(listPtr);

    printf("[OK] Task list has been reseted succesfully\n");
}

void save_tasks_to_file(TaskList *listPtr) {
    /* We save the tasks into a file with the name .tasksdb
     * with the format id|status|task name so we can load the data
     * every time we run the program so it nevers losts any tasks
     * except if you delete the file, NOTE in the status we are using numbers
     * for the parsing to make the job esier so 1 = TODO_STAT, 2 = DOING_STATU
     * and 3 is for DONE_STATU*/
    FILE *file = fopen(".tasksdb","w");
    if(file == NULL) { 
        printf("[ERR] Failed to save the tasks into the file\n");
        return;
    }
    
    for(int i=0; i<listPtr->counter; i++) {
        fprintf(file,"%d|",listPtr->tasks[i].taskId);
        if(listPtr->tasks[i].TaskStatu == TODO) fprintf(file,"1|");
        else if(listPtr->tasks[i].TaskStatu == DOING) fprintf(file,"2|");
        else if(listPtr->tasks[i].TaskStatu == DONE) fprintf(file,"3|");
        fprintf(file,"%s|\n",listPtr->tasks[i].taskName); 
        /*We are using | at the end so we can parse the spaces too!*/
    }

    fclose(file);
}

void load_tasks_from_file(TaskList *listPtr) {
    FILE *file = fopen(".tasksdb","r");
    if(file == NULL) {
        printf("[ERR] No data to load, make sure you have the .tasksdb file\n");
        return;
    }

    char buffer[256];

    int taskId;
    int whatStatue;
    char taskName[256];

    while(fgets(buffer,sizeof(buffer),file)) {
        if(sscanf(buffer,"%d|%d|%[^|]|",&taskId,&whatStatue,taskName)==3) {
            if(listPtr->counter >= listPtr->capacity) {
                /*If the array of tasks is filled then we double the size of it (VECTOR)*/
                listPtr->capacity *= 2;
                Task_t *tempList = realloc(listPtr->tasks,sizeof(Task_t)*listPtr->capacity);
                if(tempList == NULL) {
                    printf("[ERR] Task program initialization failed when started allocating memory for the task list\n");
                    return;
                }

                listPtr->tasks = tempList;
            }

            listPtr->tasks[listPtr->counter].taskName = strdup(taskName);
            if(listPtr->tasks[listPtr->counter].taskName == NULL) {
                printf("[ERR] Failed to allocate memory for the task name\n");
                return;
            }

            /* After we parse the status value we check what status to add
             * specifically, the values are explained in the save_tasks_to_file function*/
            listPtr->tasks[listPtr->counter].taskId = taskId;
            if(whatStatue == 1) {
                listPtr->tasks[listPtr->counter].TaskStatu = TODO;
            } else if(whatStatue == 2) {
                listPtr->tasks[listPtr->counter].TaskStatu = DOING;
            } else if(whatStatue == 3) {
                listPtr->tasks[listPtr->counter].TaskStatu = DONE;
            }

            listPtr->counter++;
        }
    }

    fclose(file);
}

void free_task_list(TaskList *listPtr) {
    /* If the list dosent have any task that mean
     * that there are no task names to free so we only 
     * free the listPtr->tasks that the initialize_task_list 
     * function allacated*/
    if(listPtr->counter == 0) {
        free(listPtr->tasks);
        listPtr->counter = 0;
        listPtr->capacity = 0;
        listPtr->tasks = NULL;
        return;
    }

    /* Otherwise we first free all the names
     * and then we free the listPtr->tasks*/
    for(int i=0; i<listPtr->counter; i++)
        free(listPtr->tasks[i].taskName);

    free(listPtr->tasks);
    listPtr->counter = 0;
    listPtr->capacity = 0;
    listPtr->tasks = NULL;
}

void help_show_commands() {
    /*This command prints a guid of how the program is used*/
    printf("Available commands:\n");
    printf("  ./task add \"taskName\"            - add tasks to the list\n");
    printf("  ./task remove <id>               - remove tasks from the list\n");
    printf("  ./task list                      - print all the tasks from the list\n");
    printf("  ./task list <status>              - print all the tasks with the same status\n");
    printf("  ./task set-status <id> <status>   - change the status from a task\n");
    printf("  ./task rename <id> \"newTaskName\" - change the name from a task\n");
    printf("  ./task clear <status>              - delete every task with the same status\n");
    printf("  ./task reset                      - deletes every task\n\n");
    printf("Available status:\n");
    printf("   todo    -   are the tasks that added and havent executed yet\n");
    printf("   doing   -   are the tasks that we are doing\n");
    printf("   done    -   are the tasks that have been completed\n");
}

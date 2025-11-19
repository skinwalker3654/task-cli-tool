#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tasktool.h"

int main(int argc,char **argv) {
    /* Thats because there are commands
     * with only 2, 3 or 4 arguments passed*/
    if(argc != 2 && argc != 3 && argc != 4) {
        printf("[ERR] Invalid arguments passed\n");
        printf("[INFO] Type: './task help' for more details\n");
    }

    /* We create the structure and load the data
     * from the file*/
    TaskList tasks;
    initialize_task_list(&tasks);

    load_tasks_from_file(&tasks);

    /*These are all the commands with 1 arguments passing the 2nd is the ./fileName*/
    if(argc == 2) {
        if(strcmp(argv[1],"list")==0) {
            print_list_of_tasks(&tasks,EVERY_STATU);
            goto exit_label;
        } else if(strcmp(argv[1],"help")==0) {
            help_show_commands();
            goto exit_label;
        } else if(strcmp(argv[1],"reset")==0) {
            reset_task_list(&tasks); 
            goto exit_label;
        } else {
            printf("[ERR] Invalid command '%s %s'\n",argv[0],argv[1]);
            printf("[INFO] Type: './task help' for more details\n");
            goto exit_label;
        }
    }

    /*There are all the commands with 2 arguments passed the 3rd is the ./fileName*/
    if(argc == 3) {
        if(strcmp(argv[1],"list")==0) {
            if(strcmp(argv[2],"done")==0) {
                print_list_of_tasks(&tasks,DONE);
                goto exit_label;
            } else if(strcmp(argv[2],"todo")==0) {
                print_list_of_tasks(&tasks,TODO);
                goto exit_label;
            } else if(strcmp(argv[2],"doing")==0) {
                print_list_of_tasks(&tasks,DOING);
                goto exit_label;
            } else {
                printf("[ERR] Invalid status '%s'\n",argv[2]);
                printf("[INFO] Type: './task help' for more details\n");
                goto exit_label;
            }
        } else if(strcmp(argv[1],"add")==0) {
            add_task_to_list(&tasks,argv[2]);
            goto exit_label;
        } else if(strcmp(argv[1],"clear")==0) {
            if(strcmp(argv[2],"done")==0) {
                clear_tasks_by_status(&tasks,DONE);
                goto exit_label;
            } else if(strcmp(argv[2],"todo")==0) {
                clear_tasks_by_status(&tasks,TODO);
                goto exit_label;
            } else if(strcmp(argv[2],"doing")==0) {
                clear_tasks_by_status(&tasks,DOING);
                goto exit_label;
            } else {
                printf("[ERR] Invalid status '%s'\n",argv[2]);
                printf("[INFO] Type: './task help' for more details\n");
            }
        } else if(strcmp(argv[1],"remove")==0) {
            char *endPtr;
            int idNumber = strtol(argv[2],&endPtr,10);
            if(*endPtr != '\0') {
                printf("[ERR] Invalid ID '%s'\n",argv[2]);
                printf("[INFO] Type: './task help' for more details\n");
                goto exit_label;
            }

            remove_task_from_list(&tasks,idNumber);
            goto exit_label;
        } else {
            printf("[ERR] Invalid command '%s %s %s'\n",argv[0],argv[1],argv[2]);
            printf("[INFO] Type: './task help' for more details\n");
            goto exit_label;
        }
    }

    /*There are all the commands that have 3 arguements passed the 4th is the ./fileName*/
    if(argc == 4) {
        if(strcmp(argv[1],"set-status")==0) {
            char *endPtr;
            int idNumber = strtol(argv[2],&endPtr,10);
            if(*endPtr != '\0') {
                printf("[ERR] Invalid ID '%s'\n",argv[2]);
                printf("[INFO] Type: './task help' for more details\n");
                goto exit_label;
            }

            if(strcmp(argv[3],"done")==0) {
                change_task_status_by_id(&tasks,idNumber,DONE);
                goto exit_label;
            } else if(strcmp(argv[3],"todo")==0) {
                change_task_status_by_id(&tasks,idNumber,TODO);
                goto exit_label;
            }  else if(strcmp(argv[3],"doing")==0) {
                change_task_status_by_id(&tasks,idNumber,DOING);
                goto exit_label;
            } else {
                printf("[ERR] Invalid status '%s'\n",argv[3]);
                printf("[INFO] Type: './task help' for more details\n");
                goto exit_label;
            }
        } else if(strcmp(argv[1],"rename")==0) {
            char *endPtr;
            int idNumber = strtol(argv[2],&endPtr,10);
            if(*endPtr != '\0') {
                printf("[ERR] Invalid ID '%s'\n",argv[2]);
                printf("[INFO] Type: './task help' for more details\n");
                goto exit_label;
            }

            rename_task_from_list(&tasks,idNumber,argv[3]);
            goto exit_label;
        } else {
            printf("[ERR] Invalid command '%s %s %s %s'\n",argv[0],argv[1],argv[2],argv[3]);
            printf("[INFO] Type: 'task help' for more details\n");
            goto exit_label;
        }
    }    

    exit_label:
        save_tasks_to_file(&tasks); 
        free_task_list(&tasks);

    return 0;
}

#include "todolist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct TaskList task_list;
  task_list.num_tasks = 0;

  if (argc < 2) {
    printf("Usage: ./app -flag\n");
    printf("ADD: -a\n");
    printf("REMOVE: -r\n");
    printf("LIST: -l\n");
    printf("MARK COMPLETE: -m\n");
    return 1;
  }
  printf("Before operations - num_tasks: %d\n", task_list.num_tasks);
  char *option = argv[1];

  switch (option[1]) {
  case 'a':
    add_task(&task_list, argc, argv);
    break;
  case 'l':
    list_tasks(&task_list);
    break;
  case 'r':
    if (argc < 3) {
      printf("Usagge: %s -r <task index>\n", argv[0]);
      return 1;
    }
    int task_index_r = atoi(argv[2]);
    remove_task(&task_list, task_index_r);
    break;
  case 'm':
    if (argc < 3) {
      printf("Usage: %s -m <task index>\n", argv[0]);
      return 1;
    }
    int task_index_m = atoi(argv[2]);
    mark_complete(&task_list, task_index_m);
    break;
  default:
    printf("invalid option %s\n", option);
    return 1;
  }
  printf("After operations - num_tasks: %d\n", task_list.num_tasks);
  return 0;
}

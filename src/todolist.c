#include "todolist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "tasks.txt"

void add_task(struct TaskList *task_list, int argc, char **argv) {
  char input[MAX_DESCRIPTION];
  printf("Add Task: ");
  if (scanf(" %[^\n]", input) == 1) {
    input[strcspn(input, "\n")] = '\0';

    FILE *file = fopen(FILENAME, "a+");

    if (file == NULL) {
      printf("Failed to load file");
      return;
    }
    fprintf(file, "0 %s\n", input);
    fclose(file);
    printf("Task added sucesfullly\n");
    task_list->num_tasks++;
  }
  return;
}

void list_tasks(struct TaskList *task_list) {
  load_tasks(task_list);
  FILE *file = fopen(FILENAME, "r");
  char buffer[MAX_DESCRIPTION];
  int completed;
  if (file == NULL) {
    printf("Failed to load file");
    return;
  }
  int task_index = 1;
  while (fscanf(file, "%d %[^\n]", &completed, buffer) == 2) {
    printf(" %d %s - %s \n", task_index, completed ? "[X]" : "[ ]", buffer);
    task_index++;
  }
  fclose(file);
}
void remove_task(struct TaskList *task_list, int task_index) {
  load_tasks(task_list);
  FILE *file = fopen(FILENAME, "r");
  if (file == NULL) {
    printf("Failed loading file");
    return;
  }
  FILE *temp_file = fopen("temp.txt", "w");
  if (temp_file == NULL) {
    printf("Failed to load temp file");
    return;
  }

  char buffer[MAX_DESCRIPTION];
  int current_index = 1;
  task_index = 1;

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    if (current_index != task_index) {
      fputs(buffer, temp_file);
    }
    current_index++;
  }
  fclose(file);
  fclose(temp_file);

  if (remove(FILENAME) != 0) {
    printf("failed to remove original file\n");
    return;
  }
  if (rename("temp.txt", FILENAME) != 0) {
    printf("failed to rename temp file \n");
    return;
  }
  printf("task %d removed\n", task_index);
  task_list->num_tasks--;
}

void mark_complete(struct TaskList *task_list, int task_index) {
  load_tasks(task_list);
  if (task_index >= 1 && task_index <= task_list->num_tasks) {
    task_list->tasks[task_index - 1].completed = 1;
    printf("Task %d marked as completed\n", task_index);
  } else {
    printf("invalid task index\n");
  }
  save_tasks(task_list);
}

void load_tasks(struct TaskList *task_list) {
  FILE *file = fopen(FILENAME, "r");

  while (fscanf(file, "%d %[^\n]",
                &task_list->tasks[task_list->num_tasks].completed,
                task_list->tasks[task_list->num_tasks].desciption) == 2) {
    task_list->num_tasks++;
    if (task_list->num_tasks >= MAX_TASKS) {
      printf("max tasks\n");
      break;
    }
  }
  fclose(file);
}

void save_tasks(struct TaskList *task_list) {
  FILE *file = fopen(FILENAME, "w");
  if (file == NULL) {
    printf("failed to load file");
    return;
  }
  for (int i = 0; i < task_list->num_tasks; i++) {
    fprintf(file, "%d %s\n", task_list->tasks[i].completed,
            task_list->tasks[i].desciption);
  }
  fclose(file);
}

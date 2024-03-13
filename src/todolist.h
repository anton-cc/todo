#ifndef TODOLIST_H
#define TODOLIST_H

#define MAX_DESCRIPTION 100
#define MAX_TASKS 15
#define FILENAME "tasks.txt"

struct Task {
  char desciption[MAX_DESCRIPTION];
  int completed;
  // mer information om uppgifter här
};

struct TaskList {
  struct Task tasks[MAX_TASKS];
  int num_tasks;
};

void add_task(struct TaskList *task_list, int argc, char *argv[]);
void list_tasks(struct TaskList *task_list);
void remove_task(struct TaskList *task_list, int task_index);
void mark_complete(struct TaskList *task_list, int task_index);
void load_tasks(struct TaskList *task_list);
void save_tasks(struct TaskList *task_list);
#endif

#include <stdlib.h>  // NULL
#include <string.h>  // strcmp()
#include "console_cmd.h"
#include "types.h"

#include <stdio.h>

/************************************************
 * Forward Declarations                         *
 ************************************************/
int cnsl_cmd_reg(const char *name, void (*routine)(int, const char *[]));
int cnsl_cmd_unreg(const char *name);
int cnsl_cmd_handle(const char *msg);
static struct cnsl_cmd_node *cnsl_cmd_find(const char *name);
static void list_table(void);

/************************************************
 * Globals                                      *
 ************************************************/
struct cnsl_cmd_node cmd_list[CONSOLE_CMD_CAP];
char *cmd_arg[CONSOLE_ARG_CAP];

/************************************************
 * APIs                                         *
 ************************************************/
/*
 * name: node name should be unique
 *       if name already exists, overwrite it
 * routine: node command routine function
 *
 * array approach: 
 *   traverse list, if exists: overwrite, if not: first empty node
 * linked-list approach:
 *   traverse list, if exists: overwrite, if not: new tail node
 */
int cnsl_cmd_reg(const char *name, void (*routine)(int, const char *[]))
{
  struct cnsl_cmd_node *thru;
  struct cnsl_cmd_node *empty = NULL;  /* first empty */

  /* input validation */
  if (NULL == name || NULL == routine)
    return FAILURE;

  /* traverse list if entry does not exist, then add it */
  for (thru = cmd_list; thru < &cmd_list[CONSOLE_CMD_CAP]; ++thru) {

    if (NULL != thru->name && !strcmp(name, thru->name)) {
      thru->routine = routine;
      return SUCCESS;
    }
    if (NULL == empty && NULL == thru->name)
      empty = thru;

  }

  if (NULL == empty)
    return FAILURE;  /* list full */
  else {
    empty->name = name;
    empty->routine = routine;
    return SUCCESS;
  }
}

/*
 * name: node name should be unique
 *       if name already exists, overwrite it
 * routine: node command routine function
 *
 * array approach: 
 *   traverse list, if exists: overwrite, if not: first empty node
 * linked-list approach:
 *   traverse list, if exists: overwrite, if not: new tail node
 */
int cnsl_cmd_unreg(const char *name)
{
  struct cnsl_cmd_node *target;

  /* input validation */
  if (NULL == name)
    return FAILURE;

  target = cnsl_cmd_find(name);
  if (NULL != target) {
    target->name = NULL;
    target->routine = NULL;
    return SUCCESS;
  } else {
    return FAILURE;
  }
}

int cnsl_cmd_handle(const char *msg)
{
  size_t argc = 0;
  const char *argv[CONSOLE_ARG_CAP];
  const char *thru;
  struct cnsl_cmd_node *target;

  /* input validation */
  if (NULL == msg)
    return FAILURE;

  /* split msg to token */
  thru = msg;
  while (NULL != (thru = strtok((char *)thru, " "))
         && argc < CONSOLE_ARG_CAP) {
    argv[argc++] = thru;
    thru = NULL;
  }

  if (0 == argc)
    return SUCCESS;

  target = cnsl_cmd_find(argv[0]);
  if (NULL != target) {
    target->routine(argc, argv);
    return SUCCESS;
  } else {
    return FAILURE;
  }
}
/************************************************
 * Private Methods                              *
 ************************************************/
static struct cnsl_cmd_node *cnsl_cmd_find(const char *name)
{
  struct cnsl_cmd_node *thru;
  
  for (thru = cmd_list; thru < &cmd_list[CONSOLE_CMD_CAP]; ++thru)
    if (NULL != thru->name && !strcmp(name, thru->name))
      return thru;

  return NULL;
}
/************************************************
 * Test                                         *
 ************************************************/
static void list_table(void)
{
  struct cnsl_cmd_node *thru;

  for (thru = cmd_list; thru < &cmd_list[CONSOLE_CMD_CAP]; ++thru)
    printf("name: %s\n", thru->name);
}

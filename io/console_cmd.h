#ifndef CONSOLE_CMD_H_
#define CONSOLE_CMD_H_

#define CONSOLE_CMD_CAP  64
#define CONSOLE_ARG_CAP  16

struct cnsl_cmd_node {
  const char *name;
  void (*routine)(int, const char *[]);
};

int cnsl_cmd_reg(const char *name, void (*routine)(int, const char *[]));
int cnsl_cmd_unreg(const char *name);
int cnsl_cmd_handle(const char *msg);

#endif  // CONSOLE_CMD_H_

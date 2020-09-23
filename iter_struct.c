#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define X_FIELDS \
    X(char *, field1) \
    X(char *, field2) \
    X(char *, field3) \
    X(char *, field4) \
    X(char *, field5)

typedef struct {
#define X(type, name) type name;
    X_FIELDS
#undef X
} mystruct;

void iterate(mystruct *a) {
#define X(type, name) \
         printf("mystruct.%s = %s\n", #name, a->name);
X_FIELDS
#undef X
}

int main(int argc, char *argv[]) {
    char year[5] = {0};

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int y = tm->tm_year + 1900;
    
    snprintf(year, sizeof(year), "%d", y);
    
    mystruct a = { year, "year", "of", "linux", "desktop"};
    iterate(&a);
    
    y++;
    snprintf(year, sizeof(year), "%d", y);
    a.field1 = strdup(year);
    printf("\nFixed it!\n\n");
    iterate(&a);
    
    free(a.field1);
    
    return 0;
}


/* #include <fcntl.h> */
/* #include <unistd.h> */
/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include "get_next_line.h" */
/**/

// main parte obligatoria
/* int main(void) */
/* { */
/*     int  fd; */
/*     char *line; */
/**/
/*     fd = open("text.txt", O_RDONLY); */
/*     if (fd < 0) */
/*         return (1); */
/*     while ((line = get_next_line(fd)) != NULL) */
/*     { */
/*         printf("%s", line); */
/*         free(line); */
/*     } */
/*     close(fd); */
/*     return (0); */
/* } */

// Main BONUS
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int   fd1;
    int   fd2;
    char  *line1;
    char  *line2;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
        return (1);

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    while (line1 || line2)
    {
        if (line1)
        {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("FD2: %s", line2);
            free(line2);
        }
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
    }

    close(fd1);
    close(fd2);
    return 0;
}


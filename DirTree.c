#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

typedef struct link_list{
  char path[PATH_MAX];
  struct link_list *next_link;
} link_list;

link_list * root_link;
link_list * curr;

void list_dir (const char * dir_name) {

  DIR * d;
  d = opendir (dir_name);

  if (!d) {
    fprintf (stderr, "Cannot open directory '%s': %s\n",
        dir_name, strerror (errno));
    exit (EXIT_FAILURE);
  }

  while (1) {
    struct dirent * entry;
    const char * d_name;

    entry = readdir(d);
    if (! entry) {
      break;
    }

    d_name = entry->d_name;

    /* Print the name of the file and directory that end with .java. */
    if(strstr(d_name, ".java")) {
        printf ("Adding: %s/%s\n", dir_name, d_name);

        curr = (link_list *)malloc(sizeof(link_list));
        strcpy(curr->path, dir_name);
        strcat(curr->path, "/");
        strcat(curr->path, d_name);
        curr->next_link = root_link;
        root_link = curr;
    }

    if (entry->d_type & DT_DIR) {
      if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
        int path_length;
        char path[PATH_MAX];

        path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);
        if (path_length >= PATH_MAX) {
          fprintf (stderr, "Path length has got too long.\n");
          exit (EXIT_FAILURE);
        }
        list_dir (path);
      }
    }
  }
  if (closedir (d)) {
    fprintf (stderr, "Could not close '%s': %s\n",
        dir_name, strerror (errno));
    exit (EXIT_FAILURE);
  }
}

void readFile() {
  FILE *file;
  char line[1024];
  file = fopen (curr->path, "rt");  /* open the file for reading */

  while(fgets(line, 1024, file) != NULL)
  {
    printf ("%s\n", line);
  }
  fclose(file);  /* close the file prior to exiting the routine */
}

int main ()
{
  root_link = NULL;
  list_dir (".");

    printf("Done Listing Dirs\n");
  curr = root_link;

  while(curr) {
    printf("Reading: %s\n", curr->path);
    readFile();
    curr = curr->next_link;
  }
  return 0;
}

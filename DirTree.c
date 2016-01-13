#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

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
      printf ("%s/%s\n", dir_name, d_name);
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

int main ()
{
  list_dir (".");
  return 0;
}

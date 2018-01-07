#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <gtk/gtk.h>
#include <math.h>
#include "compute.h"

int main (int argc, char **argv)
{
  DIR *dp;
  struct dirent *ep;
  char *file = malloc(42 * sizeof(char));

  dp = opendir("./IMAGES/");
  if (dp != NULL)
    {
      while (ep = readdir(dp))
	{
	  if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))
	    {
	      GError *gerror;
	      sprintf(file, "./IMAGES/%s", ep->d_name);
	      GdkPixbuf *ima_buf = gdk_pixbuf_new_from_file(file, NULL);
	      GdkPixbuf *ima_buf_res = gdk_pixbuf_copy(ima_buf);
	      guchar *ima = gdk_pixbuf_get_pixels(ima_buf);
	      guchar *ima_res = gdk_pixbuf_get_pixels(ima_buf_res);
	      ComputeImage(ima, gdk_pixbuf_get_width(ima_buf), gdk_pixbuf_get_height(ima_buf), ima_res);
	    }
	}
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}

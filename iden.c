/* EXIT_SUCCEESS if files are identical EXIT_FAILURE otherwise */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <err.h>

void
usage(const char *arg)
{
	printf("Usage: %s [ -h ] [ file1 file2 ]\n", arg);
}

int
main(int argc, char *argv[])
{
	struct stat buf1, buf2;
	FILE *f1, *f2;
	int opt, c1, c2;
	int hflag = 0;

	while ((opt = getopt(argc, argv, ":h")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		default:
			errx(1, "see %s -h", argv[0]);          
		}
	}

	if (hflag) {
		usage(argv[0]);
		return EXIT_SUCCESS;
	}
	if (argc != 3) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "r");
 	if (!f1)
		err(1, "%s ", argv[1]);
	if (!f2)
		err(1, "%s ", argv[2]);

	/* if ((fstat(fileno(f1), &buf1) != 0) || (fstat(fileno(f2), &buf2) != 0)) */
	if ((fstat(fileno(f1), &buf1) == -1) || (fstat(fileno(f2), &buf2) != 0))
		err(1, "fstat file\n");
	if (buf1.st_size != buf2.st_size) { /* files aren't identical */
		fclose(f1);
		fclose(f2);
		return EXIT_FAILURE;
	}

	/* if files have the same size */
	c1 = getc(f1);
	c2 = getc(f2);
	while((c1 != EOF) && (c2 != EOF) && (c1 == c2)) {
		c1 = getc(f1);
		c2 = getc(f2);
	}
	if (c1 == c2) {
		fclose (f1);
		fclose (f2);
		return EXIT_SUCCESS;
	} else {
		fclose (f1);
		fclose (f2);
		return EXIT_FAILURE;
	}
}

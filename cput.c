#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>

#define CPUTEMPFILE "/sys/devices/platform/coretemp.0/hwmon/hwmon1/temp2_input"

int
main (void)
{
	FILE *fp;
	char c[PATH_MAX];

	fp = fopen(CPUTEMPFILE, "r");
	if (!fp)
		err(1, "%s", CPUTEMPFILE);

	/* read file until fscanf reads a newline character store result to c */
	fscanf(fp,"%[^\n]", c);
	/* convert c to an int and divide with 1000 to get proper Celsius degrees */
	printf("%d\n", atoi(c) / 1000);
	return(EXIT_SUCCESS);
}
	

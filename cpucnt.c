#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

/* show the number of available cpus */
int
main(void)
{
	int nofcpus;

	nofcpus = sysconf(_SC_NPROCESSORS_ONLN);
	printf("%d core(s) found\n", nofcpus);
	return (EXIT_SUCCESS);
}

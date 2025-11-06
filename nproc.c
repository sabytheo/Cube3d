#include <unistd.h>
int main()
{
	long nb_cores = sysconf(_SC_NPROCESSORS_ONLN);
	printf("%ld", nb_cores);
	return(0);
}

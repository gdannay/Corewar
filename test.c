#include "op.h"
#include <sys/stat.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
# define BIT_2 16711680
# define BIT_3 65280
# define BIT_2_64 71776119061217280
# define BIT_3_64 280375465082880
# define BIT_4_64 1095216660480
# define BIT_5_64 4278190080
# define BIT_6_64 16711680
# define BIT_7_64 65280

uint16_t	swap_16_bytes(uint16_t nb)
{
	return (nb << 8 | nb >> 8);
}

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

uint64_t	swap_64_bytes(uint64_t nb)
{
	nb = (nb << 56) | ((nb << 48) & BIT_2_64)
		| ((nb << 40) & BIT_3_64) | ((nb << 32) & BIT_4_64)
		| ((nb >> 32) & BIT_5_64) | ((nb >> 40) & BIT_6_64)
		| ((nb >> 48) & BIT_7_64) | (nb >> 56);
	return (nb);
}

int	main(void)
{
	header_t	*head;
	struct stat	buf;
//	head = (header_t *)malloc(sizeof(header_t));
	int fd = open("champs/maxidef.cor", O_RDONLY);
	fstat(fd, &buf);
	head = (header_t *)mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	printf("ICI = %u\n", swap_32_bytes(head->prog_size));

/*	head->magic = swap_32_bytes((uint32_t)COREWAR_EXEC_MAGIC);
	strcpy(head->prog_name, "emtagueule");
	head->prog_size = swap_32_bytes(sizeof(head);
	strcpy(head->comment, "Tufaiclem");
	write(1, head, sizeof(*head));
	write(1, "\n", 1);
	char c;
	c = 1;
	write(1, &c, 1);
	c = 0;
	write(1, &c, 1);
	write(1, &c, 1);
	write(1, &c, 1);
	write(1, &c, 1);*/
}

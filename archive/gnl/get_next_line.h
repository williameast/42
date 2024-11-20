#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>



# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif



typedef struct s_node
{
	char			*data;
	struct s_node	*link;
} t_node;



#endif // GET_NEXT_LINE_H_

#include "vector.h"

t_vec3	vunit(t_vec3 vec)
{
	double	len = vlength(vec);

	if (len == 0)
	{
		perror("Error\nDevider is 0\n");
		exit(EXIT_FAILURE);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

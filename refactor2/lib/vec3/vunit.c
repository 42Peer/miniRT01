#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

t_vec3      vunit(t_vec3 vec)
{
    double len = vlength(vec);
    if (len == 0)
    {
        printf("Error\n:Devider is 0");
        exit(1);
    }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return (vec);
}

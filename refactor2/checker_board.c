#include "./include/minirt.h"
#include "include/structures.h"
#include "include/vector.h"
#include <stddef.h>

extern char ***mher;
extern char ***yubchoi;
extern char ***junkpark;

size_t	get_split_size(char **data) {
	size_t	ret = 0;

	while (data[ret])
		ret++;
	return (ret);
}

char ***get_ppm_file(char* filename)
{
	char **file = file_parser(filename);
	char ***ppm = malloc(sizeof(char **) * (get_split_size(file) + 1));

	size_t	i = 0;
	while (file[i])
	{
		size_t j = 0;
		ppm[i] = ft_split(file[i], ' ');;
		while (ppm[i][j]) {
			printf("%s ", ppm[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	ppm[i] = NULL;

	free_split(file);
	return (ppm);
}

void	free_ppm_file(char ***ppm_file)
{
	size_t	i = 0;
	while(ppm_file[i])
	{
		free_split(ppm_file[i]);
		i++;
	}
	free(ppm_file);
}

t_color3	get_color_from_file(t_plane *pl, t_point3 root, char ***ppm_file)
{
	(void ) ppm_file;
	t_color3	color;
	t_vec3	u = vunit(vcross(pl->normal, vec3(0, 1, 0)));
	t_vec3	v = vcross(pl->normal, u);
	t_vec3	tmp = vminus(root, pl->center);

	int	x = abs((int)vdot(u, tmp));
	int	y = abs((int)vdot(v, tmp));

	printf("x: %d y: %d\n", x, y);

	int	file_row = ft_atoi(yubchoi[1][0]);
	int	file_col = ft_atoi(yubchoi[1][1]);

	color.y = atoi(yubchoi[y % file_col + 3][(x % file_row) * 3 + 1]) / 255.999f;
	color.z = atoi(yubchoi[y % file_col + 3][(x % file_row) * 3 + 2]) / 255.999f;
	color.x = atoi(yubchoi[y % file_col + 3][(x % file_row) * 3]) / 255.999f;

	// printf("%lf %lf %lf\n", color.x, color.y, color.z);
	return (color);
}

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec, char ***ppm_file)
{
	t_plane	*pl;
	double	denominator;
	double	numerator;
	double	root;

	pl = pl_obj->element;

	denominator = vdot(pl->normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vdot(vminus(pl->center, ray->orig), pl->normal);
	root = numerator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->color = get_color_from_file(pl, rec->p, ppm_file);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	return (TRUE);
}

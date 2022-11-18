#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"
# include "wrap.h"
# include "vector.h"
# include "mlx.h"
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

/*
*				mlx
*/
int		mlx_exit(t_mlx *mlx);
int		mlx_esc_exit(int keycode, t_mlx *mlx);
void	set_mlx(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, t_color3 color);
void	pixel_put(t_scene *scene);

/*
*				util
*/
void		exit_with_error(char *msg);
int			get_file_size(char *filename);
void		free_split(char **data);

/*
*				util_libft
*/
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_atoi(const char *str);
int			ft_strcmp(char *line, char *c);
char		*ft_strrchr(const char *s, int c);
char		**ft_split(char const *s, char c);

/*
*				util_object
*/
t_vec3		str_to_vec3(char *s);
double		a_to_d(const char *str);
t_color3	parse_color(char *data);

/*
*				parser
*/
t_scene		parse(char *filename);
char		**file_parser(char *filename);
void		object_parser(char **line, t_scene *scene);


/*
*				object
*/
t_object	*object(void *object, int type);
void		oadd(t_object **list, t_object *new_obj);
void		sphere(t_scene *scene, char **data);
void		plane(t_scene *scene, char **data);
void		cylinder(t_scene *scene, char **data);
void		light(t_scene *scene, char **data);
void		ambient(t_scene *scene, char **data);
void		camera(t_scene *scene, char **data);

/*
*				trace
*/
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);
t_bool		hit(t_object *object_list, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *object_list, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);
t_bool		set_root(double a, double half_b, double c, t_hit_record *rec);
t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_circle(const t_cylinder *cy, t_ray *ray, t_hit_record *rec, int position);
t_color3	phong_lighting(t_scene *scene);
t_bool		in_shadow(t_scene *scene, t_vec3 light_vec);
t_color3	get_diffuse(t_scene *scene, t_light *light, t_vec3 light_dir);
t_color3	get_specular(t_scene *scene, t_light *light, t_vec3 light_dir);
t_color3	point_light_get(t_scene *scene, t_light *light);

/*
*				validate
*/
void		validate_rt(char *str);
void		check_invalid_char(char *str, char *valid_char);
void		parse_object(char *str);
void		check_object_position(char *str);
void		check_column_cnt(char **column, int column_cnt);
void		check_double(char *str, char *valid_char);
void		check_color3(char *str, char *valid_char);
void		check_vec3(char *str);
void		set_filter(int *filter, const char* valid_char);
void		check_object_sp(char *str);
void		check_object_pl(char *str);
void		check_object_cy(char *str);
int			check_cnt_A(void);
int			check_cnt_C(void);
int			check_cnt_L(void);
void		check_fov(char *str);
void		check_object_A(char *str);
void		check_object_C(char *str);
void		check_object_L(char *str);

#endif

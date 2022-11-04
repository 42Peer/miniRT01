#ifndef VEC_H
#define VEC_H

#include <math.h>
#include <unistd.h>

typedef struct s_vec3
{
  float        x;
  float        y;
  float        z;
}              t_vec3;

typedef t_vec3 t_point3;

typedef struct  s_ray
{
  t_point3      orig;
  t_vec3        dir;
}               t_ray;

t_vec3  *ft_vec3_add(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_sub(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_multi(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_div(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_multi_float(t_vec3 *target, float t, t_vec3 *v);
t_vec3  *ft_vec3_div_float(t_vec3 *target, float t, t_vec3 *v);
float   ft_vec3_dot(t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_cross(t_vec3 *target, t_vec3 *u, t_vec3 *v);
float   ft_vec3_len(t_vec3 *target);
float   ft_vec3_len_sqr(t_vec3 *target);
t_vec3  *ft_vec3_unit_vec(t_vec3 *target, t_vec3 *v);
t_vec3  *ft_vec3_set_xyz(t_vec3 *target, float x, float y, float z);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_ray *ft_ray_set(t_ray *target, t_point3 *origin, t_vec3 *direction);
t_point3 *ft_ray_at(t_point3 *target, t_ray *ray, float t);

t_ray *ft_ray_set(t_ray *target, t_point3 *origin, t_vec3 *direction)
{
  target->orig = *origin;
  target->dir = *direction;
  return (target);
}

t_point3  *ft_ray_at(t_point3 *target, t_ray *ray, float t)
{
  target->x = ray->orig.x + t * ray->dir.x;
  target->y = ray->orig.y + t * ray->dir.y;
  target->z = ray->orig.z + t * ray->dir.z;
  return (target);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long b;

	b = n;
	if (b < 0)
	{
		ft_putchar_fd('-', fd);
		b = b * -1;
	}
	if (b > 9)
	{
		ft_putnbr_fd(b / 10, fd);
		ft_putnbr_fd(b % 10, fd);
	}
	else
		ft_putchar_fd(b + '0', fd);
}

t_vec3  *ft_vec3_add(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x + v->x;
  target->y = u->y + v->y;
  target->z = u->z + v->z;
  return (target);
}

t_vec3  *ft_vec3_sub(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x - v->x;
  target->y = u->y - v->y;
  target->z = u->z - v->z;
  return (target);
}

t_vec3  *ft_vec3_multi(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x * v->x;
  target->y = u->y * v->y;
  target->z = u->z * v->z;
  return (target);
}

t_vec3  *ft_vec3_div(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x / v->x;
  target->y = u->y / v->y;
  target->z = u->z / v->z;
  return (target);
}

t_vec3  *ft_vec3_multi_float(t_vec3 *target, float t, t_vec3 *v)
{
  target->x = v->x * t;
  target->y = v->y * t;
  target->z = v->z * t;
  return (target);
}

t_vec3  *ft_vec3_div_float(t_vec3 *target, float t, t_vec3 *v)
{
  return (ft_vec3_multi_float(target, (1 / t), v));
}

float   ft_vec3_dot(t_vec3 *u, t_vec3 *v)
{
  return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_vec3  *ft_vec3_cross(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->y * v->z - u->z * v->y;
  target->y = u->z * v->x - u->x * v->z;
  target->z = u->x * v->y - u->y * v->x;
  return (target);
}

float   ft_vec3_len(t_vec3 *target)
{
  return (sqrt(ft_vec3_len_sqr(target)));
}

float   ft_vec3_len_sqr(t_vec3 *target)
{
  float result;

  result = pow(target->x, 2.0)
          + pow(target->y, 2.0)
          + pow(target->z, 2.0);
  return (result);
}

t_vec3  *ft_vec3_unit_vec(t_vec3 *target, t_vec3 *v)
{
  return (ft_vec3_div_float(target, ft_vec3_len(v), v));
}

t_vec3  *ft_vec3_set_xyz(t_vec3 *target, float x, float y, float z)
{
  target->x = x;
  target->y = y;
  target->z = z;
  return (target);
}

#endif
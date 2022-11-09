#include "trace.h"

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while(world)
	{
		// 오브젝트가 hit했다면
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;	// 어떤 오브젝트에 hit하면 t_max값을 해당 t값으로 바꿔주어서 더 멀리 있는 오브젝트는 히트가 안되게 함
			*rec = temp_rec;
		}
		world = world->next;	// 다음 오브젝트 검사
	}
	return (hit_anything);
}

// 오브젝트의 type에 맞추어 hit_type 함수 호출
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	return (hit_result);
}
#include "../include/minirt.h"

// hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	t_bool	front_face;
	
	// 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
	front_face = vdot(r->dir, rec->normal) < 0;
	// 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
	if (!front_face)
		rec->normal = vmult_k(rec->normal, -1);
}

t_bool	hit_obj(t_object *object_list, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if	(object_list->type == SP)
		hit_result = hit_sphere(object_list, ray, rec); 
		
	else if (object_list->type == PL)
		hit_result = hit_plane(object_list, ray, rec);
	return (hit_result);
}

t_bool	hit(t_object *object_list, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
	hit_anything = FALSE;
	while(object_list)
	{
		if (hit_obj(object_list, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		object_list = object_list->next;
	}
	return (hit_anything);
}

#include "trace.h"

// ray의 방향벡터와 교점의 법선벡터가 방향이 달라야함
// 만약 방향이 같다면 (= 내적 < 0) -> 카메라가 오브젝트의 내부에 있다는 뜻
// => 법선벡터의 방향을 뒤집어주자 (*-1)
void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}
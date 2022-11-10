#include "structures.h"
#include "utils.h"
#include "trace.h"

t_ray ray(t_point3 orig, t_vec3 dir) {
  t_ray ray;

  ray.orig = orig;
  ray.dir = vunit(dir);
  return (ray);
}

t_point3 ray_at(t_ray *ray, double t) {
  t_point3 at;

  at = vplus(ray->orig, vmult(ray->dir, t));
  return (at);
}

t_ray ray_primary(t_camera *cam, double u, double v) {
  t_ray ray;

  ray.orig = cam->orig;
  // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
  ray.dir =
	  vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)),
						 vmult(cam->vertical, v)),
				   cam->orig));
  return (ray);
}

t_color3    ray_color(t_scene *scene)
{

	//광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene)); //phong_lighting 함수는 8.4에서 설명한다. 이제 법선 벡터를 매핑해서 얻은 색이 아닌, 앞으로 작성할 phong_lighting 함수의 결과값을 반환한다!
	else
	{
		// double  t;
		//ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
		// t = 0.5 * (scene->ray.dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		// return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
		return (color3(0,0,0));
	}
}

t_bool          hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3  oc;
	double  a;
	//b를 half_b로 변경
	double  half_b;
	double  c;
	double  discriminant; //판별식
	double  sqrtd;
	double  root;
	t_sphere    *sp = sp_obj->element;

	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
	rec->albedo = sp_obj->albedo;
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}

t_bool          hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	double  root;
	t_plane    *pl = pl_obj->element;
	double     nu = vdot(ray->dir, pl->n);
	double     np = vdot(pl->n, pl->center);
	double     no = vdot(pl->n, ray->orig);
	// double		t = pl->center.z / ray->dir.z;

	if (!nu)
		return (FALSE);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (np - no) / nu;
	// root = t;
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->n;
	if (vdot(pl->n, ray->dir) < 0)
		rec->normal = vmult(pl->n, -1);
	rec->albedo = pl_obj->albedo;
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}

t_bool          hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	// t_vec3  oc;
	double  a;
	//b를 half_b로 변경
	double  half_b;
	double  c;
	double  discriminant; //판별식
	double  sqrtd;
	double  root;
	t_cylinder    *cy = cy_obj->element;

	t_vec3	dn_c = vcross(ray->dir,cy->n);
	t_vec3	deltaP = vminus(ray->orig, cy->center);
	t_vec3 deltaP_o_c = vcross(deltaP,cy->n);

	a = vlength2(dn_c);
	half_b = vdot(dn_c, deltaP_o_c);
	c = vlength2(deltaP_o_c) - cy->r2;

	// a = pow(vdot(ray->dir, cy->n), 2);
	// half_b = vdot(dn_c, deltaP_o_c);
	// c = vlength2(deltaP_o_c) - cy->r2;
	// discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	double	max_len2 = (cy->r2) + ((cy->h/2) * (cy->h/2));
	t_vec3 p = ray_at(ray, root);
	t_vec3 cp = vminus(p, cy->center);
	double	cp_len2 = vlength2(cp);
	if (cp_len2 > max_len2)
		return (FALSE);
	
	rec->t = root;
	rec->p = p;
	rec->normal = vminus(cp , vmult(cy->n, vdot(cp, cy->n))); // 정규화된 법선 벡터.
	rec->albedo = cy_obj->albedo;
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}

void    set_face_normal(t_ray *r, t_hit_record *rec)
{
	// 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	// 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
	rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}

t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool          hit_anything;
	t_hit_record    temp_rec;

	temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
	hit_anything = FALSE;
	while(world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}

// hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
t_bool      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool  hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec); 
	else if (world->type == PL)
		hit_result = hit_plane(world, ray, rec) || hit_result ? 1 : 0;
	else if (world->type == CY)
		hit_result = hit_plane(world, ray, rec) || hit_result ? 1 : 0;
	return (hit_result);
}

t_hit_record record_init(void)
{
	t_hit_record    record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_color3        phong_lighting(t_scene *scene)
{
	t_color3    light_color;
	t_object    *lights;

	light_color = color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
	lights = scene->light;
	while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
	{
		if(lights->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
	//모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

t_color3        point_light_get(t_scene *scene, t_light *light)
{
	t_color3    diffuse;
	t_vec3      light_dir;
	double      kd; // diffuse의 강도
	t_color3    specular;
	t_vec3      view_dir;
	t_vec3      reflect_dir;
	double      spec;
	double      ksn;
	double      ks;
	double      brightness;
	double      light_len;
    t_ray       light_ray;

	light_dir = vminus(light->origin, scene->rec.p);
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0,0,0));
		// return (scene->ambient);
    light_dir = vunit(light_dir);

	// cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
	diffuse = vmult(light->light_color, kd);
	// specular
	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ksn = 64; // shininess value
	ks = 0.5; // specular strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
	// return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
	return (vmult(vplus(diffuse, specular), brightness));
}

t_vec3          reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_bool          in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

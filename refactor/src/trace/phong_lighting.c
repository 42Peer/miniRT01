/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:23:31 by mher              #+#    #+#             */
/*   Updated: 2022/11/16 14:56:01 by jujeon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/trace.h"

t_bool          in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}

t_color3        phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

	// ambient 는 한번만 적용하기 때문에 초기화할때 한번만 해주면 된다.
    light_color = scene->ambient;
    lights = scene->light_list;
	//여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    while (lights) 
    {
        if(lights->type == LIGHT_POINT) 
            light_color = vplus(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 
	//그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
    return (vmin(vmult_(light_color, scene->rec.color), color3(1, 1, 1)));
}

t_vec3          reflect(t_vec3 v, t_vec3 n)
{
    //v - 2 * dot(v, n) * n;
    return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_color3        point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse;
    t_vec3      light_dir; 
	double      light_len; 
    t_ray       light_ray; 
    double      kd; 	   // diffuse의 강도
    t_color3    specular;
    t_vec3      view_dir;
    t_vec3      reflect_dir; // 반사된 광선의 단위벡터 
    double      spec;
    double      ksn;
    double      ks;
    double      brightness;

	// 오브젝트(hit point) -> 광원까지의 방향벡터
	light_dir = vminus(light->origin, scene->rec.p); 

	// 오브젝트(hit point) -> 광원까지의 거리
    light_len = vlength(light_dir); 

	// 오브젝트(hit point) -> 광원까지의 방향벡터.
	// hit_point 자체에 오차가 있을 수 있기 때문에 EPSILON 을 더해 줌으로써 오브젝트에서 위로 띄워준다.
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir); 

	// 광원이 물체에 의해 가려지는지 확인
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0,0,0));

	
	// 광원이 물체에 의해 가려지지 않는다면, 광원의 색깔을 가져온다.
	// 오브젝트(hit point) 에서 광원까지의 방향벡터를 정규화한다. 
    light_dir = vunit(light_dir);

	// diffuse의 강도
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	// 광원의 색깔에 diffuse의 강도를 곱해준다. 
    diffuse = vmult(light->light_color, kd);

	// 오브젝트->카메라(단위벡터) 
    view_dir = vunit(vmult(scene->ray.dir, -1));
	// 반사된 광선의 방향벡터 
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);

	// shininess value 재질의 광택도 (알루미늄 공, 테니스 공)
    ksn = 64; 
	// specular strength 반사율 (구겨진 알루미늄 공, 매끈한 알루미늄 공)
    ks = 0.5; 

	// 오브젝트->카메라 와 반사광 방향 벡터의 내적 값^ksn
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	// 광원의 색깔에 spec를 곱해준다.
    specular = vmult(vmult(light->light_color, ks), spec);

	// 기준 광속/광량을 정의한 매크로
	brightness = light->bright_ratio * LUMEN;
	// (diffuse + specular) * brightness
    return (vmult(vplus(diffuse, specular), brightness));
}

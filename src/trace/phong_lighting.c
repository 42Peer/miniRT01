#include "../../include/trace.h"

t_color3 phong_lighting(t_scene *scene) {
  t_color3 light_color;
  t_object *lights;

  light_color =
      color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
  lights = scene->light;
  while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular
                 //값을 모두 구해줘야 한다
  {
    if (lights->type == LIGHT_POINT)
      light_color = vplus(light_color, point_light_get(scene, lights->element));
    lights = lights->next;
  }
  light_color = vplus(light_color, scene->ambient);
  return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
  //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이
  //(1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

t_color3 point_light_get(t_scene *scene, t_light *light) {
  t_color3 diffuse;
  t_vec3 light_dir;
  double kd; // diffuse의 강도

  light_dir = vunit(
      vminus(light->orig,
             scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화 됨)
  // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은
  // 경우는 0.0으로 대체한다.
  kd = fmax(vdot(scene->rec.normal, light_dir),
            0.0); // (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의
                  // 법선벡터)의 내적값.
  diffuse = vmult(light->color, kd);
  return (diffuse);
}

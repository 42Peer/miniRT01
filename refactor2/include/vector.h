#ifndef VECTOR_H
# define VECTOR_H

#include <math.h>
#include "../include/structures.h"

t_vec3      vec3(double x, double y, double z);
t_point3    point3(double x, double y, double z);
t_point3    color3(double r, double g, double b);
void        vset(t_vec3 *vec, double x, double y, double z);
double      vlength2(t_vec3 vec);
double      vlength(t_vec3 vec);
// 벡터합
t_vec3      vplus(t_vec3 vec, t_vec3 vec2);
// 벡터차
t_vec3      vminus(t_vec3 vec, t_vec3 vec2);
// 벡터 * 스칼라 곱연산
t_vec3      vmult(t_vec3 vec, double t);
// 벡터 축 값끼리 곱연산
t_vec3      vmult_(t_vec3 vec, t_vec3 vec2);
// 벡터 스칼라 나누기
t_vec3      vdivide(t_vec3 vec, double t);
// 벡터 내적
double      vdot(t_vec3 vec, t_vec3 vec2);
// 벡터 외적
t_vec3      vcross(t_vec3 vec, t_vec3 vec2);
// 단위 벡터
t_vec3      vunit(t_vec3 vec);
// 두 벡터의 원소를 비교하여 작은 값들만 반환
t_vec3  vmin(t_vec3 vec1, t_vec3 vec2);

#endif
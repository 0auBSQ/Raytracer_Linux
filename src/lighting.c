/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:37:52 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 12:50:43 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static t_vec3	apply_point_light(t_instance *inst, t_light *l,
				t_shading_data p, t_vec3 color)
{
	t_scal	tmp;
	t_scal	t;
	t_ray	ray;

	ray.pos = p.pos;
	ray.dir = v3normalize(v3sub(l->pos, p.pos));
	if (v3dot(p.nor, ray.dir) <= 0.)
		return (color);
	tmp = v3dot(v3sub(l->pos, p.pos), v3sub(l->pos, p.pos));
	if (set_quadric_intersection(inst, ray, &t, p.rt->side) != -1
		&& t * t <= tmp)
		return (color);
	tmp = v3dot(v3sub(l->pos, p.pos), v3sub(l->pos, p.pos));
	color = v3add(color, v3mult(v3(p.col.x, p.col.y, p.col.z),
				v3dotf(l->col, v3dot(v3sub(l->pos, p.pos), p.nor) / tmp
					+ pow(fmax(0.0,
							v3dot(v3normalize(v3sub(l->pos, p.pos)),
								v3reflect(p.eye, p.nor))), p.m->alpha)
					* p.m->specular / tmp)));
	return (color);
}

t_vec4			bake_lighting(t_instance *inst, t_light *l,
				t_shading_data p)
{
	t_vec3	color;

	color = v3dotf(v3(p.col.x, p.col.y, p.col.z), 0.2);
	while (l != NULL)
	{
		if (l->type == light_point)
			color = apply_point_light(inst, l, p, color);
		l = l->next;
	}
	return (v4(color.x, color.y, color.z, p.col.w));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:05:11 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/07 10:05:49 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static t_scal	max3(t_vec3 c)
{
	if (c.x > c.y && c.x > c.z)
		return (c.x);
	else if (c.y > c.x && c.y > c.z)
		return (c.y);
	return (c.z);
}

static void		fcclamp(t_vec4 *color)
{
	if (color->x > 1.0)
		color->x = 1.0;
	if (color->y > 1.0)
		color->y = 1.0;
	if (color->z > 1.0)
		color->z = 1.0;
	if (color->x < 0.0)
		color->x = 0.0;
	if (color->y < 0.0)
		color->y = 0.0;
	if (color->z < 0.0)
		color->z = 0.0;
}

void			direct_light(t_vec4 *color, t_instance *inst, t_ray *ray)
{
	t_light		*l;
	t_vec3		oc;
	t_vec3		equ;
	t_scal		delta;
	t_scal		dist;

	l = inst->scn.light_list;
	while (l != NULL)
	{
		oc = v3sub(ray->pos, l->pos);
		equ.x = v3dot(ray->dir, ray->dir);
		equ.y = 2.0 * v3dot(oc, ray->dir);
		equ.z = v3dot(oc, oc) - 10 * max3(l->col) * max3(l->col);
		delta = equ.y * equ.y - 4 * equ.x * equ.z;
		dist = 999999999999999999999.;
		if (delta > 0 && equ.x != 0.)
			dist = (-equ.y - sqrt(delta)) / (2.0 * equ.x);
		if (dist <= 0)
			dist = 999999999999999999999.;
		color->x += (1 / dist) * l->col.x;
		color->y += (1 / dist) * l->col.y;
		color->z += (1 / dist) * l->col.z;
		fcclamp(color);
		l = l->next;
	}
}

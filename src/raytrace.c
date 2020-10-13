/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:31:53 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 12:25:27 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/*
** raytrace():
** Returns the color resulting from `ray` being raytraced with `n` reflexion.
*/

static t_vec4	ambiant(t_vec4 l, t_scal v)
{
	t_scal			brat;
	t_scal			rrat;
	t_scal			vrat;
	t_scal			tot;
	t_vec4			ret;

	tot = l.x + l.y + l.z;
	if (tot > 0 && tot < v)
	{
		rrat = l.x / tot;
		vrat = l.y / tot;
		brat = l.z / tot;
		ret = v4(v * rrat, v * vrat, v * brat, l.w);
		return (ret);
	}
	return (l);
}

static void		texture_transparency(t_material *m, t_shading_data *p,
	t_instance *inst)
{
	p->col.w = m->transparency;
	if (inst->cam.pf_filtre == black_to_alpha)
		if (p->col.x == 0. && p->col.y == 0. && p->col.z == 0.)
			p->col.w = 1;
}

static void		set_shading_data(t_instance *inst,
				t_raytrace_data rt, t_shading_data *p, ssize_t i)
{
	t_scal		*f;
	t_material	*m;

	f = inst->scn.c + i * 4;
	m = inst->scn.m + i;
	p->rt = &rt;
	p->pos = v3add(rt.ray.pos, v3dotf(rt.ray.dir, p->t));
	p->eye = v3dotf(rt.ray.dir, 1.0);
	p->nor = v3dotf(get_quadric_normal(inst->scn.v + i * 10, p->pos), rt.side);
	p->col = v4(f[0], f[1], f[2], 0.0);
	select_texture(inst, m, p->pos, &p->col);
	p->col = ambiant(p->col, inst->scn.ambiant);
	select_perturbation(p, m, &f);
	texture_transparency(m, p, inst);
	p->m = m;
	p->col = bake_lighting(inst, inst->scn.light_list, *p);
}

t_vec4			raytrace(t_instance *inst, t_raytrace_data rt, int n, int e)
{
	t_shading_data	p;
	ssize_t			i;
	t_material		*m;

	if ((i = set_quadric_intersection(inst, rt.ray, &p.t, rt.side)) == -1)
		return (inst->scn.background_color);
	m = inst->scn.m + i;
	set_shading_data(inst, rt, &p, i);
	rt.ray.pos = p.pos;
	if (n > 1 && m->refraction >= 0.1 && p.col.w > 0.)
	{
		rt.ray.dir = v3refract(rt.ray.dir, p.nor, pow(m->refraction, rt.side));
		rt.side = -rt.side;
		p.col = v4add(v4dotf(p.col, 1. - p.col.w),
				v4dotf(raytrace(inst, rt, n - 1, e), p.col.w));
		rt.side = -rt.side;
	}
	if (e > 1 && m->reflective > 0.)
	{
		rt.ray.dir = v3reflect(rt.ray.dir, p.nor);
		p.col = v4add(v4dotf(p.col, 1. - m->reflective),
				v4dotf(raytrace(inst, rt, n, e - 1), m->reflective));
	}
	return (inst->scn.mode_edit == ON && i == inst->scn.selected
		? v4add(v4dotf(p.col, .4), v4(.6, .6, .4, .5)) : p.col);
}

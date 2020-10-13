/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:07:16 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/07 10:07:38 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_raytrace_data	get_rt_data(t_instance *inst, int x, int y)
{
	t_raytrace_data	rt;
	t_scal			aspect_ratio;
	t_scal			aspect_width;
	t_scal			aspect_height;

	aspect_ratio = (t_scal)inst->win.w / (t_scal)inst->win.h;
	aspect_height = tan(inst->cam.yfov / 180. * M_PI / 2.0);
	aspect_width = aspect_height * aspect_ratio;
	rt.ray.dir = v3(1.0,
			(-2 * ((t_scal)x / (t_scal)inst->win.w) + 1) * aspect_width,
			(-2 * ((t_scal)y / (t_scal)inst->win.h) + 1) * aspect_height);
	rt.ray.dir = v3normalize(rt.ray.dir);
	rt.ray.dir = m3dotv3(inst->cam.rot_matrix, rt.ray.dir);
	rt.ray.pos = inst->cam.pos;
	rt.n = inst->win.nreflexions[1];
	rt.e = inst->win.nreflexions[0];
	rt.side = (out_of_bound(inst, rt.ray.pos) ? -1.0 : 1.0);
	return (rt);
}

void			process_stereoscopy(t_vec4 *color, t_raytrace_data rt,
	t_instance *i)
{
	t_ray			sray;
	t_vec4			color2;
	t_vec3			tmppos;

	sray = rt.ray;
	tmppos = v3dotf(v3normalize(v3cross(
				sray.dir, v3(0., 0., 1.))), 0.5);
	sray.pos = v3sub(sray.pos, tmppos);
	rt.ray = sray;
	color2 = raytrace(i, rt, rt.n, rt.e);
	color2.x = 0.;
	*color = v4add(*color, color2);
}

t_vec4			get_color(t_instance *inst, t_raytrace_data rt)
{
	t_vec4			color;

	color = raytrace(inst, rt, rt.n, rt.e);
	if (inst->cam.pf_filtre != NULL)
		color = inst->cam.pf_filtre(color);
	if (inst->cam.pf_filtre == filtre_stereoscopy)
		process_stereoscopy(&color, rt, inst);
	if (inst->cam.pf_filtre == filtre_do_nothing)
		direct_light(&color, inst, &rt.ray);
	return (color);
}

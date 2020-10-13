/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:43:25 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 08:57:09 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void			damier(t_shading_data *p, t_scal l)
{
	t_scal			d1;
	t_scal			d2;
	t_scal			d3;

	if (l <= 0)
		return ;
	d1 = p->pos.x / 2.0 / (t_scal)l + 0.00000000001;
	d2 = p->pos.y / 2.0 / (t_scal)l + 0.00000000001;
	d3 = p->pos.z / 2.0 / (t_scal)l + 0.00000000001;
	if (((d1 - floor(d1) < .5) != (d2 - floor(d2) < .5))
		!= (d3 - floor(d3) < .5))
		p->col = v4(0.0, 0.0, 0.0, 0.0);
}

void			perlin(t_shading_data *p, int l)
{
	t_scal			n;

	n = noise(p->pos.x, p->pos.y, p->pos.z) * l;
	if (n > 1.)
		n = 1.;
	if (n < 0.)
		n = 0.;
	p->col.x = p->col.x * n;
	p->col.y = p->col.y * n;
	p->col.z = p->col.z * n;
}

void			wood(t_shading_data *p, int l)
{
	t_scal			n;

	if (l <= 0)
		return ;
	n = 20 * noise(p->pos.x / l, p->pos.y / l, p->pos.z / l);
	n -= floor(n);
	if (n > 1.)
		n = 1.;
	if (n < 0.)
		n = 0.;
	p->col.x = p->col.x * n;
	p->col.y = p->col.y * n;
	p->col.z = p->col.z * n;
}

void			bump(t_shading_data *p, t_material *m, t_scal **f)
{
	t_vec3			v;
	t_scal			e;

	if (m->texture < 0 || m->texture > 5)
		e = m->coeff_perturbation;
	else
		e = ((*f)[0] + (*f)[1] + (*f)[2]) / 3;
	v.x = noise(p->pos.x - e, p->pos.y, p->pos.z)
		- noise(p->pos.x + e, p->pos.y, p->pos.z);
	v.y = noise(p->pos.x, p->pos.y - e, p->pos.z)
		- noise(p->pos.x, p->pos.y + e, p->pos.z);
	v.z = noise(p->pos.x, p->pos.y, p->pos.z - e)
		- noise(p->pos.x, p->pos.y, p->pos.z + e);
	p->nor = v3add(p->nor, v);
}

void			wave(t_shading_data *p, t_scal e)
{
	t_vec3			v;

	v.x = sin(e * p->pos.x);
	v.y = 0;
	v.z = 0;
	p->nor = v3add(p->nor, v);
}

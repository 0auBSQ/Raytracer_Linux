/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:24:47 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 14:13:59 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/*
** Sign should be 1.0 normally or -1.0 to invert the quadric.
** Returns 0 if the intersection is known to be occluded.
** Returns nonzero and sets i->t to the advancement if occlusion is not
** confirmed.
*/

static int		set_quadric_intersection_advancement(t_instance *inst,
				t_ray ray, t_intersection_data *i, t_scal sign)
{
	t_vec4		q;

	i->q = get_quadric_equation_coefficients(inst->scn.v + i->i * 10, ray);
	q = i->q;
	if (q.x == +0.0 || q.x == -0.0)
		if (sign * q.y < 0.0)
			i->t = -q.z / q.y;
		else
			return (0);
	else if (q.w >= 0.0)
		i->t = (-q.y - sign * sqrt(q.w)) / (2.0 * q.x);
	else
		return (0);
	if (i->t <= 0.0 || (i->inearest != -1 && i->tnearest <= i->t)
		|| (i->iclosest != -1 && i->tclosest <= i->t))
		return (0);
	return (1);
}

/*
** Unclearly named function used for refraction.
*/

static int		advancement_included_in_not_ranges(t_instance *inst,
				t_ray ray, t_intersection_data *i)
{
	t_vec4		q;

	i->jrange = -1;
	while (++i->jrange < inst->scn.nranges)
	{
		if (i->jrange == i->irange)
			continue ;
		i->j = inst->scn.offset[i->jrange] - 1;
		i->jend = inst->scn.offset[i->jrange] + inst->scn.count[i->jrange];
		while (++i->j < i->jend)
		{
			q = get_quadric_equation_coefficients(
					inst->scn.v + i->j * 10, ray);
			if (q.x * i->t * i->t + q.y * i->t + q.z >= -.0000000001)
				break ;
		}
		if (i->j == i->jend)
			return (0);
	}
	return (1);
}

/*
** Unclearly named function used for refraction.
*/

static ssize_t	set_not_quadric_intersection(
				t_instance *inst, t_ray ray, t_scal *tnearest)
{
	t_intersection_data		i;

	i.tnearest = 999999999999999999999.;
	i.inearest = -1;
	i.iclosest = -1;
	i.irange = -1;
	while (++i.irange < inst->scn.nranges)
	{
		i.i = inst->scn.offset[i.irange] - 1;
		while (++i.i < inst->scn.offset[i.irange] + inst->scn.count[i.irange])
		{
			if (!set_quadric_intersection_advancement(inst, ray, &i, -1.0))
				continue ;
			if (!advancement_included_in_not_ranges(inst, ray, &i))
				continue ;
			i.inearest = i.i;
			i.tnearest = i.t;
		}
	}
	*tnearest = i.tnearest;
	return (i.inearest);
}

static int		advancement_included_in_range(t_instance *inst,
				t_ray ray, t_intersection_data *i)
{
	t_vec4		q;

	i->j = inst->scn.offset[i->irange] - 1;
	while (++i->j < inst->scn.offset[i->irange] + inst->scn.count[i->irange])
	{
		if (i->j == i->i)
			continue ;
		q = get_quadric_equation_coefficients(
				inst->scn.v + i->j * 10, ray);
		if (q.x * i->t * i->t + q.y * i->t + q.z > 0.0)
			break ;
	}
	if (i->j < inst->scn.offset[i->irange] + inst->scn.count[i->irange])
		return (0);
	i->iclosest = i->i;
	i->tclosest = i->t;
	return (1);
}

ssize_t			set_quadric_intersection(t_instance *inst,
				t_ray ray, t_scal *tnearest, t_scal side)
{
	t_intersection_data		i;

	if (side <= 0.0)
		return (set_not_quadric_intersection(inst, ray, tnearest));
	i.inearest = -1;
	i.irange = -1;
	i.tnearest = 999999999999999999999.;
	while (++i.irange < inst->scn.nranges)
	{
		i.iclosest = -1;
		i.i = inst->scn.offset[i.irange] - 1;
		while (++i.i < inst->scn.offset[i.irange] + inst->scn.count[i.irange])
		{
			if (!set_quadric_intersection_advancement(inst, ray, &i, 1.0)
				|| !advancement_included_in_range(inst, ray, &i))
				continue ;
		}
		if (i.iclosest == -1)
			continue ;
		i.inearest = i.iclosest;
		i.tnearest = i.tclosest;
	}
	*tnearest = i.tnearest;
	return (i.inearest);
}

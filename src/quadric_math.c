/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:30:56 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 14:32:17 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec4			get_quadric_equation_coefficients(t_scal *q, t_ray r)
{
	t_vec4		eq;
	t_vec3		d;
	t_vec3		p;

	d = r.dir;
	p = r.pos;
	eq.x = q[0] * d.x * d.x + q[1] * d.y * d.y + q[2] * d.z * d.z
		+ q[3] * d.x * d.y + q[4] * d.x * d.z + q[5] * d.y * d.z;
	eq.y = 2.0 * (q[0] * p.x * d.x + q[1] * p.y * d.y + q[2] * p.z * d.z)
		+ q[3] * (p.x * d.y + p.y * d.x)
		+ q[4] * (p.x * d.z + p.z * d.x)
		+ q[5] * (p.y * d.z + p.z * d.y)
		+ q[6] * d.x + q[7] * d.y + q[8] * d.z;
	eq.z = q[0] * p.x * p.x + q[1] * p.y * p.y + q[2] * p.z * p.z
		+ q[3] * p.x * p.y + q[4] * p.x * p.z + q[5] * p.y * p.z
		+ q[6] * p.x + q[7] * p.y + q[8] * p.z + q[9];
	eq.w = eq.y * eq.y - 4.0 * eq.x * eq.z;
	return (eq);
}

t_scal			evaluate_quadric(t_scal *q, t_vec3 p)
{
	return (q[0] * p.x * p.x
		+ q[1] * p.y * p.y
		+ q[2] * p.z * p.z
		+ q[3] * p.x * p.y
		+ q[4] * p.x * p.z
		+ q[5] * p.y * p.z
		+ q[6] * p.x
		+ q[7] * p.y
		+ q[8] * p.z
		+ q[9]);
}

int				out_of_bound(t_instance *inst, t_vec3 pos)
{
	ssize_t		i;
	ssize_t		irange;

	irange = 0;
	while (irange < inst->scn.nranges)
	{
		i = inst->scn.offset[irange];
		while (i < inst->scn.offset[irange] + inst->scn.count[irange])
		{
			if (evaluate_quadric(inst->scn.v + i * 10, pos) >= 0)
				break ;
			i++;
		}
		if (i == inst->scn.offset[irange] + inst->scn.count[irange])
			return (1);
		irange++;
	}
	return (0);
}

t_vec3			get_quadric_normal(t_scal *q, t_vec3 p)
{
	t_vec3	ret;

	ret.x = 2. * q[0] * p.x + q[3] * p.y + q[4] * p.z + q[6];
	ret.y = 2. * q[1] * p.y + q[3] * p.x + q[5] * p.z + q[7];
	ret.z = 2. * q[2] * p.z + q[4] * p.x + q[5] * p.y + q[8];
	return (v3normalize(ret));
}

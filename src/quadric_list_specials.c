/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_list_specials.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:04:35 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/07 09:04:55 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_mat4			quadric_to_mat4(t_scal *q)
{
	t_mat4	out;

	out.m[0] = q[0];
	out.m[1] = q[3] / 2.0;
	out.m[2] = q[4] / 2.0;
	out.m[3] = q[6] / 2.0;
	out.m[4] = q[3] / 2.0;
	out.m[5] = q[1];
	out.m[6] = q[5] / 2.0;
	out.m[7] = q[7] / 2.0;
	out.m[8] = q[4] / 2.0;
	out.m[9] = q[5] / 2.0;
	out.m[10] = q[2];
	out.m[11] = q[8] / 2.0;
	out.m[12] = q[6] / 2.0;
	out.m[13] = q[7] / 2.0;
	out.m[14] = q[8] / 2.0;
	out.m[15] = q[9];
	return (out);
}

void			mat4_to_quadric(t_scal *q, t_mat4 m)
{
	q[0] = m.m[4 * 0 + 0];
	q[1] = m.m[4 * 1 + 1];
	q[2] = m.m[4 * 2 + 2];
	q[3] = m.m[4 * 0 + 1] + m.m[4 * 1 + 0];
	q[4] = m.m[4 * 0 + 2] + m.m[4 * 2 + 0];
	q[5] = m.m[4 * 1 + 2] + m.m[4 * 2 + 1];
	q[6] = m.m[4 * 0 + 3] + m.m[4 * 3 + 0];
	q[7] = m.m[4 * 1 + 3] + m.m[4 * 3 + 1];
	q[8] = m.m[4 * 2 + 3] + m.m[4 * 3 + 2];
	q[9] = m.m[4 * 3 + 3];
}

t_scal			iclamp(t_scal val)
{
	if (val > 1)
		return (1.);
	else if (val < 0)
		return (0.);
	return (val);
}

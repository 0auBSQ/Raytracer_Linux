/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:54:32 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 11:06:25 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_mat3			m3dot(t_mat3 a, t_mat3 b)
{
	t_mat3	r;
	t_scal	*m1;
	t_scal	*m2;
	t_scal	*m;

	m1 = a.m;
	m2 = b.m;
	m = r.m;
	m[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m[2];
	m[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m[2];
	m[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m[2];
	m[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m[5];
	m[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m[5];
	m[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m[5];
	m[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m[8];
	m[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m[8];
	m[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m[8];
	return (r);
}

t_mat3			m3scale(t_scal x, t_scal y, t_scal z)
{
	t_mat3		r;

	r.m[0] = x;
	r.m[1] = 0;
	r.m[2] = 0;
	r.m[3] = 0;
	r.m[4] = y;
	r.m[5] = 0;
	r.m[6] = 0;
	r.m[7] = 0;
	r.m[8] = z;
	return (r);
}

t_ivec2			ivec2(int x, int y)
{
	t_ivec2		out;

	out.x = x;
	out.y = y;
	return (out);
}

t_vec2			v2(t_scal x, t_scal y)
{
	t_vec2		out;

	out.x = x;
	out.y = y;
	return (out);
}

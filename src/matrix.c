/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:30:59 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/03 15:25:19 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec3	m3dotv3(t_mat3 m, t_vec3 v)
{
	t_vec3	r;

	r.x = m.m[0] * v.x + m.m[3] * v.y + m.m[6] * v.z;
	r.y = m.m[1] * v.x + m.m[4] * v.y + m.m[7] * v.z;
	r.z = m.m[2] * v.x + m.m[5] * v.y + m.m[8] * v.z;
	return (r);
}

t_mat3	m3yawpitchroll(t_scal yaw, t_scal pitch, t_scal roll)
{
	t_mat3	r;

	r.m[0] = cos(yaw) * cos(pitch);
	r.m[1] = sin(yaw) * cos(pitch);
	r.m[2] = -sin(pitch);
	r.m[3] = cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll);
	r.m[4] = sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll);
	r.m[5] = cos(pitch) * sin(roll);
	r.m[6] = cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll);
	r.m[7] = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
	r.m[8] = cos(pitch) * cos(roll);
	return (r);
}

t_mat4	m4dot(t_mat4 a, t_mat4 b)
{
	t_mat4	r;
	t_scal	*m1;
	t_scal	*m2;
	t_scal	*m;

	m1 = a.m;
	m2 = b.m;
	m = r.m;
	m[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	m[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	m[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	m[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];
	m[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	m[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	m[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	m[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];
	m[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	m[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	m[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	m[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];
	m[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	m[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	m[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	m[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
	return (r);
}

t_mat4	m4yawpitchroll(t_scal yaw, t_scal pitch, t_scal roll)
{
	t_mat4	r;

	r.m[0] = cos(yaw) * cos(pitch);
	r.m[1] = sin(yaw) * cos(pitch);
	r.m[2] = -sin(pitch);
	r.m[3] = 0.0;
	r.m[4] = cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll);
	r.m[5] = sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll);
	r.m[6] = cos(pitch) * sin(roll);
	r.m[7] = 0.0;
	r.m[8] = cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll);
	r.m[9] = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
	r.m[10] = cos(pitch) * cos(roll);
	r.m[11] = 0.0;
	r.m[12] = 0.0;
	r.m[13] = 0.0;
	r.m[14] = 0.0;
	r.m[15] = 1.0;
	return (r);
}

t_mat4	m4transpose(t_mat4 m)
{
	t_mat4	r;
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			r.m[j * 4 + i] = m.m[i * 4 + j];
			i++;
		}
		j++;
	}
	return (r);
}

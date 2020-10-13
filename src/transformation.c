/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:05:11 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/04 22:02:54 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void		translate_quad(t_scal *q, t_scal x, t_scal y, t_scal z)
{
	t_scal	r[10];

	r[0] = q[0];
	r[1] = q[1];
	r[2] = q[2];
	r[3] = q[3];
	r[4] = q[4];
	r[5] = q[5];
	r[6] = q[6] - 2.0 * q[0] * x - q[3] * y - q[4] * z;
	r[7] = q[7] - 2.0 * q[1] * y - q[3] * x - q[5] * z;
	r[8] = q[8] - 2.0 * q[2] * z - q[4] * x - q[5] * y;
	r[9] = q[0] * x * x + q[1] * y * y + q[2] * z * z
		+ q[3] * x * y + q[4] * x * z + q[5] * y * z
		- q[6] * x - q[7] * y - q[8] * z + q[9];
	ft_memcpy(q, r, sizeof(t_scal) * 10);
}

void		rotate_quad(t_scal *q, t_scal yaw, t_scal pitch, t_scal roll)
{
	t_mat4	mat;

	mat = quadric_to_mat4(q);
	mat = m4dot(m4yawpitchroll(yaw, pitch, roll), mat);
	mat = m4dot(mat, m4transpose(m4yawpitchroll(yaw, pitch, roll)));
	mat4_to_quadric(q, mat);
}

void		scale_quad(t_scal *q, t_scal x, t_scal y, t_scal z)
{
	q[0] = q[0] / (x * x);
	q[1] = q[1] / (y * y);
	q[2] = q[2] / (z * z);
	q[3] = q[3] / (x * y);
	q[4] = q[4] / (x * z);
	q[5] = q[5] / (y * z);
	q[6] = q[6] / x;
	q[7] = q[7] / y;
	q[8] = q[8] / z;
}

int			transformation(t_qunion *qunion, t_scal param[], int type_instr)
{
	t_quadric	*q;

	if (qunion == NULL)
		return (ERROR);
	if (type_instr == SPECULAR)
		while ((q = cycle_qunion(qunion)) != NULL)
		{
			q->param[13] = param[1];
			q->param[14] = param[0];
		}
	else if (type_instr == AMBIANT)
		while ((q = cycle_qunion(qunion)) != NULL)
			q->param[14] = param[0];
	else if (type_instr == TRANSLATE)
		while ((q = cycle_qunion(qunion)) != NULL)
			translate_quad(q->param, param[2], param[1], param[0]);
	else if (type_instr == ROTATE)
		while ((q = cycle_qunion(qunion)) != NULL)
			rotate_quad(q->param, param[2] * M_PI / 180.0,
				param[1] * M_PI / 180.0, param[0] * M_PI / 180.0);
	else if (type_instr == SCALE)
		while ((q = cycle_qunion(qunion)) != NULL)
			scale_quad(q->param, param[2], param[1], param[0]);
	return (SUCCESS);
}

int			perturbation(t_qunion *q, t_scal p[], int type)
{
	t_quadric		*quad;

	while ((quad = cycle_qunion(q)) != NULL)
	{
		quad->perturbation = type;
		quad->coeff_perturbation = p[0];
	}
	return (SUCCESS);
}

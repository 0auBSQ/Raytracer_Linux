/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:17:44 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 10:11:44 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void		plan_to_quad(t_scal param[], t_scal quad_param[], t_quadric *q)
{
	t_scal	yaw;
	t_scal	pitch;
	t_vec3	n;
	t_vec3	m;
	t_scal	d;

	ft_memset(quad_param, 0, sizeof(*quad_param) * 15);
	yaw = param[4] * M_PI / 180.0;
	pitch = param[3] * M_PI / 180.0;
	n = v3(cos(yaw) * cos(pitch), sin(yaw) * cos(pitch), -sin(pitch));
	m = v3(param[7], param[6], param[5]);
	d = -v3dot(n, m);
	quad_param[6] = cos(yaw) * cos(pitch);
	quad_param[7] = sin(yaw) * cos(pitch);
	quad_param[8] = -sin(pitch);
	quad_param[9] = d;
	quad_param[10] = param[2];
	quad_param[11] = param[1];
	quad_param[12] = param[0];
	q->material.rot = m3yawpitchroll(yaw, pitch, 0.0);
	q->material.pos = m;
	q->material.mapping = mapping_flat;
}

void		sphere_to_quad(t_scal param[], t_scal quad_param[], t_quadric *q)
{
	t_scal	a;
	t_scal	b;
	t_scal	c;
	t_scal	r;

	ft_memset(quad_param, 0, sizeof(*quad_param) * 15);
	a = param[6];
	b = param[5];
	c = param[4];
	r = param[3];
	quad_param[0] = 1 / r;
	quad_param[1] = 1 / r;
	quad_param[2] = 1 / r;
	quad_param[6] = -2 * a / r;
	quad_param[7] = -2 * b / r;
	quad_param[8] = -2 * c / r;
	quad_param[9] = a * a / r + b * b / r + c * c / r - r;
	quad_param[10] = param[2];
	quad_param[11] = param[1];
	quad_param[12] = param[0];
	q->material.rot = m3yawpitchroll(0.0, 0.0, 0.0);
	q->material.pos = v3(a, b, c);
	q->material.mapping = mapping_cube;
}

void		cylindre_to_quad(t_scal param[], t_scal quad_param[], t_quadric *q)
{
	ft_memset(quad_param, 0, sizeof(*quad_param) * 15);
	quad_param[1] = 1.0 / param[3];
	quad_param[2] = 1.0 / param[3];
	quad_param[9] = -param[3];
	quad_param[10] = param[2];
	quad_param[11] = param[1];
	quad_param[12] = param[0];
	rotate_quad(quad_param,
		param[5] * M_PI / 180., param[4] * M_PI / 180., 0.0);
	translate_quad(quad_param, param[8], param[7], param[6]);
	q->material.rot = m3yawpitchroll(param[5] * M_PI / 180.,
			param[4] * M_PI / 180., 0.0);
	q->material.pos = v3(param[8], param[7], param[6]);
	q->material.mapping = mapping_cone;
}

void		cone_to_quad(t_scal param[], t_scal quad_param[], t_quadric *q)
{
	t_scal	tangent;

	tangent = tan(param[3] * M_PI / 180. / 2.0);
	ft_memset(quad_param, 0, sizeof(*quad_param) * 15);
	quad_param[0] = -1.0 * tangent;
	quad_param[1] = 1.0 / tangent;
	quad_param[2] = 1.0 / tangent;
	quad_param[10] = param[2];
	quad_param[11] = param[1];
	quad_param[12] = param[0];
	rotate_quad(quad_param,
		param[5] * M_PI / 180., param[4] * M_PI / 180., 0.0);
	translate_quad(quad_param, param[8], param[7], param[6]);
	q->material.rot = m3yawpitchroll(param[5] * M_PI / 180.,
			param[4] * M_PI / 180., 0.0);
	q->material.pos = v3(param[8], param[7], param[6]);
	q->material.mapping = mapping_cone;
}

void		quadric_to_quad(t_scal param[], t_scal quad_param[], t_quadric *q)
{
	quad_param[0] = param[12];
	quad_param[1] = param[11];
	quad_param[2] = param[10];
	quad_param[3] = param[9];
	quad_param[4] = param[8];
	quad_param[5] = param[7];
	quad_param[6] = param[6];
	quad_param[7] = param[5];
	quad_param[8] = param[4];
	quad_param[9] = param[3];
	quad_param[10] = param[2];
	quad_param[11] = param[1];
	quad_param[12] = param[0];
	quad_param[13] = 0.0;
	quad_param[14] = 0.0;
	q->material.rot = m3yawpitchroll(0.0, 0.0, 0.0);
	q->material.pos = v3(param[8], param[7], param[6]);
	q->material.mapping = mapping_cone;
}

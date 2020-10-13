/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:07:54 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/06 18:02:16 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec3	v3mult(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return (r);
}

t_vec3	v3dotf(t_vec3 v, t_scal f)
{
	t_vec3	r;

	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	return (r);
}

t_scal	v3length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	v3normalize(t_vec3 v)
{
	t_scal	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return (v);
}

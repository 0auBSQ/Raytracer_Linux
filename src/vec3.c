/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:06:12 by cdittric          #+#    #+#             */
/*   Updated: 2019/01/14 22:06:33 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec3	v3(t_scal x, t_scal y, t_scal z)
{
	t_vec3	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_vec3	v3add(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec3	v3sub(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_scal	v3dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	v3cross(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}

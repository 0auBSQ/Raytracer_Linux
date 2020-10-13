/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:52 by cdittric          #+#    #+#             */
/*   Updated: 2019/01/14 22:10:24 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec4	v4(t_scal x, t_scal y, t_scal z, t_scal w)
{
	t_vec4	out;

	out.x = x;
	out.y = y;
	out.z = z;
	out.w = w;
	return (out);
}

t_scal	v4dot(t_vec4 a, t_vec4 b)
{
	return (a.x * b.x + a.y * b.y + a.z + b.z + a.w + b.w);
}

t_vec4	v4add(t_vec4 a, t_vec4 b)
{
	t_vec4	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	ret.w = a.w + b.w;
	return (ret);
}

t_vec4	v4dotf(t_vec4 v, t_scal f)
{
	t_vec4	r;

	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	r.w = v.w * f;
	return (r);
}

t_vec4	v4mult(t_vec4 a, t_vec4 b)
{
	t_vec4	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	r.w = a.w * b.w;
	return (r);
}

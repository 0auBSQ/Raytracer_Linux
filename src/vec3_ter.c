/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:01:58 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/06 18:02:13 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

/*
** v3reflect():
** Returns the reflexion of incident vector `i` against a surface of normal `n`.
** `n` should be normalized. `i` is pointed toward the surface and returned
** vector is pointing away from it.
*/

t_vec3	v3reflect(t_vec3 i, t_vec3 n)
{
	t_vec3	r;
	t_scal	double_dot;

	double_dot = 2. * (i.x * n.x + i.y * n.y + i.z * n.z);
	r.x = i.x - double_dot * n.x;
	r.y = i.y - double_dot * n.y;
	r.z = i.z - double_dot * n.z;
	return (r);
}

t_vec3	v3refract(t_vec3 i, t_vec3 n, t_scal indice)
{
	t_scal	cosi;
	t_scal	etai;
	t_scal	eta;
	t_scal	k;

	cosi = v3dot(i, n);
	cosi = (cosi > 1) ? 1 : cosi;
	cosi = (cosi < -1) ? -1 : cosi;
	etai = 1;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		indice = 1;
		etai = indice;
		n = v3dotf(n, -1);
	}
	if (indice <= 0.1)
		indice = 1.;
	eta = etai / indice;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return ((k < 0) ? v3(0, 0, 0)
		: v3add(v3dotf(i, eta), v3dotf(n, eta * cosi - sqrt(k))));
}

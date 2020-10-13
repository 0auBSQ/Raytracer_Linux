/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:36:33 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 11:13:34 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static int		index_texture(t_vec3 n)
{
	if (fabs(n.z) > fabs(n.y) && fabs(n.z) > fabs(n.x))
	{
		if (n.z < 0)
			return (NORD);
		else
			return (SUD);
	}
	else if (fabs(n.x) > fabs(n.y) && fabs(n.x) > fabs(n.z))
	{
		if (n.x < 0)
			return (OUEST);
		else
			return (EST);
	}
	else if (fabs(n.y) > fabs(n.x) && fabs(n.y) > fabs(n.z))
	{
		if (n.y < 0)
			return (BAS);
		else
			return (HAUT);
	}
	return (0);
}

static t_vec2	select_index(t_instance *inst, t_vec3 n, int select)
{
	t_vec2			p;

	p.x = 0;
	p.y = 0;
	if (select == NORD || select == SUD)
	{
		p.x = ((n.x / n.z + 1) / 2) * inst->scn.w[select];
		p.y = ((n.y / n.z + 1) / 2) * inst->scn.h[select];
	}
	else if (select == EST || select == OUEST)
	{
		p.x = ((n.y / n.x + 1) / 2) * inst->scn.w[select];
		p.y = ((n.z / n.x + 1) / 2) * inst->scn.h[select];
	}
	else if (select == HAUT || select == BAS)
	{
		p.x = ((n.x / n.y + 1) / 2) * inst->scn.w[select];
		p.y = ((n.z / n.y + 1) / 2) * inst->scn.h[select];
	}
	return (p);
}

t_vec2			cube_mapping(t_instance *inst,
				t_material *m, t_vec3 pos, int *select)
{
	t_vec3			n;

	n = v3normalize(v3sub(pos, m->pos));
	n = m3dotv3(m->rot, n);
	*select = index_texture(n);
	return (select_index(inst, n, *select));
}

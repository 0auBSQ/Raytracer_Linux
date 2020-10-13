/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:19:36 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 10:32:58 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_qunion		*struct_alloc_failed(t_quadric **q, t_qsection **s,
	t_qunion **u)
{
	ft_memdel((void**)q);
	ft_memdel((void**)s);
	ft_memdel((void**)u);
	return (NULL);
}

t_qunion		*add_quadric(t_qunion **q, t_scal quad_param[], t_quadric *qua)
{
	t_quadric	*quadric;
	t_qsection	*qsection;
	t_qunion	*qunion;

	quadric = ft_memalloc(sizeof(t_quadric));
	qsection = ft_memalloc(sizeof(t_qsection));
	qunion = ft_memalloc(sizeof(t_qunion));
	if (quadric == NULL || qsection == NULL || qunion == NULL)
		return (struct_alloc_failed(&quadric, &qsection, &qunion));
	ft_memcpy(quadric->param, quad_param, sizeof(quadric->param));
	quadric->material = qua->material;
	quadric->material.texture = -1;
	quadric->material_active = OFF;
	quadric->perturbation = 0;
	quadric->next = NULL;
	qsection->list = quadric;
	qsection->next = NULL;
	qunion->name = NULL;
	qunion->list = qsection;
	qunion->next = *q;
	*q = qunion;
	return (qunion);
}

void			free_qunion_list(t_qunion *q)
{
	t_qsection	*qsection;
	t_quadric	*quadric;
	void		*tmp;

	while (q != NULL)
	{
		qsection = q->list;
		while (qsection != NULL)
		{
			quadric = qsection->list;
			while (quadric != NULL)
			{
				tmp = quadric;
				quadric = quadric->next;
				ft_memdel((void**)&tmp);
			}
			tmp = qsection;
			qsection = qsection->next;
			ft_memdel((void**)&tmp);
		}
		ft_memdel((void**)&q->name);
		tmp = q;
		q = q->next;
		ft_memdel((void**)&tmp);
	}
}

static void		fill_quadric(t_instance *i,
	t_quadric *quadric, ssize_t n, ssize_t nranges)
{
	ft_memcpy(i->scn.v + 10 * n, quadric->param + 0, sizeof(t_scal) * 10);
	ft_memcpy(i->scn.c + 4 * n, quadric->param + 10, sizeof(t_scal) * 3);
	i->scn.c[4 * n + 3] = 1.0;
	i->scn.m[n] = quadric->material;
	i->scn.m[n].ambiant = 1.0;
	i->scn.m[n].diffuse = 1.0;
	i->scn.m[n].specular = quadric->param[13];
	i->scn.m[n].alpha = quadric->param[14];
	i->scn.m[n].reflective = 0.;
	i->scn.m[n].transparency = 0.;
	i->scn.m[n].refraction = 1.0;
	i->scn.offset[nranges] = n;
	i->scn.count[nranges] += 1;
	i->scn.m[n].tex_zoom = quadric->tex_zoom;
	i->scn.m[n].tex_offset = quadric->tex_offset;
	if (quadric->material_active == ON)
	{
		i->scn.m[n].reflective = iclamp(quadric->reflective);
		i->scn.m[n].transparency = iclamp(quadric->transparency);
		i->scn.m[n].refraction = quadric->refraction;
	}
	if (quadric->perturbation == 0)
		return ;
	i->scn.m[n].perturbation = quadric->perturbation;
	i->scn.m[n].coeff_perturbation = quadric->coeff_perturbation;
}

void			fill_instance(t_instance *i, t_qunion *q)
{
	t_qsection		*qsection;
	t_quadric		*quadric;
	ssize_t			n;
	ssize_t			nranges;

	allocate_instance_values(i, q);
	n = i->scn.n - 1;
	nranges = i->scn.nranges - 1;
	while (q != NULL)
	{
		qsection = q->list;
		while (qsection != NULL)
		{
			quadric = qsection->list;
			while (quadric != NULL)
			{
				fill_quadric(i, quadric, n--, nranges);
				quadric = quadric->next;
			}
			nranges--;
			qsection = qsection->next;
		}
		q = q->next;
	}
}

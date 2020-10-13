/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:42:10 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 13:21:24 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void			remove_qunion(t_qunion **q)
{
	t_qsection	*qsection;
	t_quadric	*quadric;
	void		*tmp;

	qsection = (*q)->list;
	while (qsection != NULL)
	{
		quadric = qsection->list;
		while (quadric != NULL)
		{
			tmp = quadric;
			quadric = quadric->next;
			ft_memdel(&tmp);
		}
		tmp = qsection;
		qsection = qsection->next;
		ft_memdel(&tmp);
	}
	ft_memdel((void**)&(*q)->name);
	tmp = *q;
	*q = (*q)->next;
	ft_memdel(&tmp);
}

t_qsection		*merge_qsection(t_quadric *a, t_quadric *b)
{
	t_quadric	**q;
	t_qsection	*out;

	out = (t_qsection *)ft_memalloc(sizeof(t_qsection));
	if (out == NULL)
		return (NULL);
	out->next = NULL;
	out->list = NULL;
	q = &out->list;
	while (a != NULL && (*q = ft_memalloc(sizeof(t_quadric))) != NULL)
	{
		**q = *a;
		q = &(*q)->next;
		a = a->next;
	}
	while (b != NULL && (*q = ft_memalloc(sizeof(t_quadric))) != NULL)
	{
		**q = *b;
		q = &(*q)->next;
		b = b->next;
	}
	*q = NULL;
	if (a != NULL || b != NULL)
		remove_qsection(&out);
	return (out);
}

void			insert_qsection(t_qsection **list, t_qsection *node)
{
	node->next = *list;
	*list = node;
}

void			remove_qsection(t_qsection **q)
{
	t_quadric	*quadric;
	void		*tmp;

	quadric = (*q)->list;
	while (quadric != NULL)
	{
		tmp = quadric;
		quadric = quadric->next;
		ft_memdel(&tmp);
	}
	tmp = *q;
	*q = (*q)->next;
	ft_memdel(&tmp);
}

int				count_qsection(t_qsection *q)
{
	int			ret;

	ret = 0;
	while (q != NULL)
	{
		ret++;
		q = q->next;
	}
	return (ret);
}

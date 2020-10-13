/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qunion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:54:00 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 14:38:03 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static int		intersect_qunion_ext(t_qunion **q,
				t_qsection *tmp, ssize_t *nqsection, ssize_t *nquadric)
{
	t_quadric	*quadric;
	t_qunion	qunion;

	if (nquadric)
	{
		while ((quadric = cycle_qunion(*q)) != NULL)
			++*nquadric;
		qunion.list = tmp;
		while ((quadric = cycle_qunion(&qunion)) != NULL)
			--*nquadric;
		while ((quadric = cycle_qunion((*q)->next)) != NULL)
			--*nquadric;
	}
	if (nqsection)
		*nqsection += count_qsection((*q)->list)
			- count_qsection(tmp) - count_qsection((*q)->next->list);
	while (tmp != NULL)
		remove_qsection(&tmp);
	remove_qunion(&(*q)->next);
	return (0);
}

int				intersect_qunion(t_qunion **q,
				int n, ssize_t *nqsection, ssize_t *nquadric)
{
	t_qsection	*a;
	t_qsection	*b;
	t_qsection	*tmp;
	void		*p;

	while (--n > 0 && *q != NULL && (*q)->next != NULL)
	{
		a = (*q)->list;
		tmp = (*q)->list;
		(*q)->list = NULL;
		while (a != NULL)
		{
			b = (*q)->next->list;
			while (b != NULL && (p = merge_qsection(b->list, a->list)) != NULL)
			{
				insert_qsection(&(*q)->list, p);
				b = b->next;
			}
			if (b != NULL)
				return (intersect_qunion_ext(q, tmp, nqsection, nquadric));
			a = a->next;
		}
		intersect_qunion_ext(q, tmp, nqsection, nquadric);
	}
	return (1);
}

static t_qunion	*add_qsection_as_qunion(t_qunion **q, t_qsection *qsection,
	ssize_t *nqsection, ssize_t *nquadric)
{
	t_qunion	*qunion;
	t_qsection	**end_list;
	t_quadric	*quadric;

	if (!(qunion = (t_qunion *)ft_memalloc(sizeof(t_qunion))))
		return (NULL);
	end_list = &qunion->list;
	quadric = qsection->list;
	while (quadric != NULL)
	{
		if ((*end_list = (t_qsection *)malloc(sizeof(t_qsection))) == NULL
			|| ((*end_list)->list = malloc(sizeof(t_quadric))) == NULL)
			return (qunion_failm(&qunion, &end_list));
		*(*end_list)->list = *quadric;
		(*end_list)->list->next = NULL;
		end_list = &(*end_list)->next;
		quadric = quadric->next;
		if (nquadric)
			++*nquadric;
	}
	*end_list = NULL;
	if (nqsection)
		*nqsection += count_qsection(qunion->list);
	qunion->next = *q;
	return ((*q = qunion));
}

int				invert_qunion(t_qunion **q,
	ssize_t *nqsection, ssize_t *nquadric)
{
	t_quadric	*quadric;
	t_qsection	*qsection;
	int			count;

	if (*q == NULL)
		return (0);
	while ((quadric = cycle_qunion(*q)) != NULL)
		invert_quadric(quadric);
	count = 0;
	qsection = (*q)->list;
	while (qsection != NULL)
	{
		if (add_qsection_as_qunion(&(*q)->next,
				qsection, nqsection, nquadric) == NULL)
			return (0);
		count++;
		qsection = qsection->next;
	}
	if (nqsection)
		*nqsection -= count;
	if (nquadric)
		while ((quadric = cycle_qunion(*q)) != NULL)
			--*nquadric;
	remove_qunion(q);
	return (intersect_qunion(q, count, nqsection, nquadric));
}

int				manipulate_qunion(t_instance *inst,
				t_qunion **q, t_scal *param, int instr)
{
	if (instr == UNION)
		unite_qunion(q, (int)param[0]);
	else if (instr == SECTION)
	{
		if (!intersect_qunion(q, (int)*param, &inst->scn.nranges, &inst->scn.n))
			return (ERROR);
	}
	else if (instr == INVERT && q != NULL)
	{
		if (!invert_qunion(q, &inst->scn.nranges, &inst->scn.n))
			return (ERROR);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

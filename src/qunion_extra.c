/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qunion_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:31:02 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/07 09:32:17 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_quadric		*cycle_qunion(t_qunion *q)
{
	static t_qsection	*qsection;
	static t_quadric	*quadric;

	if (quadric == NULL)
	{
		if (q != NULL && q->list != NULL && q->list->list != NULL)
		{
			qsection = q->list;
			quadric = q->list->list;
		}
	}
	else
	{
		quadric = quadric->next;
		if (quadric == NULL)
		{
			qsection = qsection->next;
			if (qsection != NULL && qsection->list != NULL)
				quadric = qsection->list;
			else
				quadric = NULL;
		}
	}
	return (quadric);
}

int				unite_qunion(t_qunion **q, int n)
{
	int			ret;
	t_qsection	**qsection;
	t_qunion	*tmp;

	ret = 0;
	while (ret + 1 < n && *q != NULL && (*q)->next != NULL)
	{
		qsection = &(*q)->list;
		while (*qsection != NULL)
			qsection = &(*qsection)->next;
		*qsection = (*q)->next->list;
		(*q)->next->list = (*q)->list;
		tmp = *q;
		*q = (*q)->next;
		ft_memdel((void**)&tmp->name);
		ft_memdel((void**)&tmp);
		ret++;
	}
	return (ret);
}

void			invert_quadric(t_quadric *quadric)
{
	quadric->param[0] = -quadric->param[0];
	quadric->param[1] = -quadric->param[1];
	quadric->param[2] = -quadric->param[2];
	quadric->param[3] = -quadric->param[3];
	quadric->param[4] = -quadric->param[4];
	quadric->param[5] = -quadric->param[5];
	quadric->param[6] = -quadric->param[6];
	quadric->param[7] = -quadric->param[7];
	quadric->param[8] = -quadric->param[8];
	quadric->param[9] = -quadric->param[9];
}

t_qunion		*qunion_failm(t_qunion **q, t_qsection ***s)
{
	free(*s);
	(*q)->next = NULL;
	free_qunion_list(*q);
	return (NULL);
}

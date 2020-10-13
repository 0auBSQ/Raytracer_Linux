/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:59:06 by mbenjell          #+#    #+#             */
/*   Updated: 2019/03/28 18:59:35 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int				add_light(t_light **l, t_scal param[])
{
	t_light		*new;

	new = malloc(sizeof(t_light));
	if (new == NULL)
		return (ERROR);
	new->type = light_point;
	new->pos.x = param[5];
	new->pos.y = param[4];
	new->pos.z = param[3];
	new->col.x = param[2];
	new->col.y = param[1];
	new->col.z = param[0];
	new->next = *l;
	*l = new;
	return (SUCCESS);
}

void			remove_light(t_light **l)
{
	t_light		*tmp;

	tmp = *l;
	*l = (*l)->next;
	free(tmp);
}

void			allocate_instance_values(t_instance *i, t_qunion *q)
{
	if ((i->scn.v = malloc(sizeof(t_scal) * i->scn.n * 10)) == NULL
		|| (i->scn.c = malloc(sizeof(t_scal) * i->scn.n * 4)) == NULL
		|| (i->scn.m = malloc(sizeof(t_material) * i->scn.n)) == NULL
		|| (i->scn.offset = malloc(sizeof(ssize_t) * i->scn.nranges)) == NULL
		|| (i->scn.count = malloc(sizeof(ssize_t) * i->scn.nranges)) == NULL)
	{
		free_qunion_list(q);
		print_error(i->env, "Erreur allocation de la scene\n");
	}
	ft_memset(i->scn.count, 0, sizeof(ssize_t) * i->scn.nranges);
}

int				log2i(int n)
{
	int		out;

	out = 0;
	while (n != 0)
	{
		n >>= 1;
		out++;
	}
	return (out);
}

void			print_error(t_environment *env, const char *format)
{
	write(1, format, ft_strlen(format));
	end_environment(env, EXIT_FAILURE);
}

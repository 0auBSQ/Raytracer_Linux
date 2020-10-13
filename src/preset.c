/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:17:58 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/06 20:58:53 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static void	set_components(t_instance *i, t_qunion **q, t_scal *param)
{
	create_quadric(i, q, SPHERE, param);
	param[3] = -90;
	param[5] = 2;
	create_quadric(i, q, PLANE, param);
	param[3] = 90;
	param[5] = -2;
	create_quadric(i, q, PLANE, param);
	param[3] = 0;
	param[4] = 90;
	param[5] = 0;
	param[6] = 2;
	create_quadric(i, q, PLANE, param);
	param[4] = -90;
	param[6] = -2;
	create_quadric(i, q, PLANE, param);
	param[4] = 0;
	param[6] = 0;
	param[7] = 2;
	create_quadric(i, q, PLANE, param);
	param[4] = 180;
	param[7] = -2;
	create_quadric(i, q, PLANE, param);
}

static int	create_dice(t_instance *i, t_qunion **q, t_scal *param_preset)
{
	t_scal	param[13];

	param[0] = param_preset[0];
	param[1] = param_preset[1];
	param[2] = param_preset[2];
	param[3] = 3;
	ft_memset(&param[4], 0, 4 * sizeof(t_scal));
	set_components(i, q, param);
	if (!intersect_qunion(q, 7, &i->scn.nranges, &i->scn.n))
		return (ERROR);
	return (SUCCESS);
}

int			store_preset(t_instance *i, t_qunion **q, t_stream *s, int ins)
{
	int		ret;
	int		nb;
	t_scal	pos_param[13];

	nb = nb_param(ins);
	ft_memset(&pos_param, 0, sizeof(pos_param));
	while (nb)
	{
		skip_space(s);
		ret = extract_param(s, &pos_param[--nb]);
		if (ret == ERROR)
			return (ERROR);
	}
	if (ins == DICE)
		ret = create_dice(i, q, pos_param);
	return (ret);
}

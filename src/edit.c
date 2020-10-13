/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 23:28:58 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 01:30:47 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void		edit_object(int k, t_instance *inst)
{
	if (k == KEY_NUMPLUS && inst->scn.mode_edit == ON)
	{
		inst->scn.v[inst->scn.selected * 10 + 9]++;
		inst->win.redraw_required = 1;
	}
	if (k == KEY_NUMMINUS && inst->scn.mode_edit == ON)
	{
		inst->scn.v[inst->scn.selected * 10 + 9]--;
		inst->win.redraw_required = 1;
	}
	if (k == KEY_P && inst->scn.mode_edit == ON)
	{
		if (inst->scn.m[inst->scn.selected].perturbation == 0)
			inst->scn.m[inst->scn.selected].perturbation = DAMIER;
		else if (inst->scn.m[inst->scn.selected].perturbation > WAVE)
			inst->scn.m[inst->scn.selected].perturbation = 0;
		else
			inst->scn.m[inst->scn.selected].perturbation++;
		inst->scn.m[inst->scn.selected].coeff_perturbation = 1.0;
		inst->win.redraw_required = 1;
	}
	if (k == KEY_O && inst->scn.mode_edit == ON)
		inst->scn.m[inst->scn.selected].coeff_perturbation++;
	if (k == KEY_L && inst->scn.mode_edit == ON)
		inst->scn.m[inst->scn.selected].coeff_perturbation--;
}

int			event_edition(int k, t_instance *inst)
{
	if (k == KEY_E)
	{
		inst->scn.mode_edit = !(inst->scn.mode_edit);
		inst->scn.selected = 0;
		inst->win.redraw_required = 1;
	}
	if (k == KEY_N)
		inst->scn.selected = (inst->scn.selected + 1) % inst->scn.n;
	if (k == KEY_B)
		inst->scn.selected = (inst->scn.selected - 1) % inst->scn.n;
	if (inst->scn.mode_edit == ON && (k == KEY_B || k == KEY_N))
		inst->win.redraw_required = 1;
	edit_object(k, inst);
	return (0);
}

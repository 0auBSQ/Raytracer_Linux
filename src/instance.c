/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:42:54 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/03 21:43:58 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_instance		*add_instance(t_environment *env, char *name)
{
	t_instance	*inst;

	inst = malloc(sizeof(*inst));
	if (inst == NULL)
		return (NULL);
	ft_memset(inst, 0, sizeof(*inst));
	inst->env = env;
	inst->name = name;
	inst->win.w = DEFAULT_WINDOW_WIDTH;
	inst->win.h = DEFAULT_WINDOW_HEIGHT;
	inst->win.dxsample = DEFAULT_DXSAMPLE;
	inst->win.dysample = DEFAULT_DYSAMPLE;
	inst->win.nreflexions[0] = DEFAULT_NREFLEXIONS;
	inst->win.nreflexions[1] = DEFAULT_NTRANSPARENCY;
	inst->cam.velocity = DEFAULT_VELOCITY;
	inst->cam.velocity_modifier = DEFAULT_VELOCITY_MODIFIER;
	inst->cam.yfov = DEFAULT_YFOV;
	inst->next = env->inst_list;
	inst->self = &env->inst_list;
	if (env->inst_list != NULL)
		env->inst_list->self = &inst->next;
	env->inst_list = inst;
	inst->scn.mode_edit = OFF;
	return (inst);
}

void			remove_instance(t_instance *inst)
{
	*inst->self = inst->next;
	if (inst->next != NULL)
		inst->next->self = inst->self;
	if (inst->self_current != NULL)
		*inst->self_current = inst->next_current;
	if (inst->next_current != NULL)
		inst->next_current->self_current = inst->self_current;
	if (inst->win.img != NULL)
		mlx_destroy_image(inst->env->mlx, inst->win.img);
	if (inst->win.win != NULL)
		mlx_destroy_window(inst->env->mlx, inst->win.win);
	free(inst->win.rbuf);
	free(inst->scn.v);
	free(inst->scn.c);
	free(inst->scn.m);
	free(inst->scn.offset);
	free(inst->scn.count);
	while (inst->scn.light_list != NULL)
		remove_light(&inst->scn.light_list);
	free_qunion_list(inst->scn.templates);
	free(inst);
}

void			make_instance_current(t_instance *inst)
{
	if (inst->self_current != NULL)
		*inst->self_current = inst->next_current;
	if (inst->next_current != NULL)
		inst->next_current->self_current = inst->self_current;
	inst->next_current = inst->env->inst_current;
	inst->self_current = &inst->env->inst_current;
	if (inst->env->inst_current != NULL)
		inst->env->inst_current->self_current = &inst->next_current;
	inst->env->inst_current = inst;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:22:38 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 11:34:56 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int		expose_event(t_instance *inst)
{
	make_instance_current(inst);
	mlx_clear_window(inst->env->mlx, inst->win.win);
	mlx_put_image_to_window(inst->env->mlx, inst->win.win,
		inst->win.img, 0, 0);
	return (0);
}

int		close_event(t_instance *inst)
{
	t_environment	*env;

	env = inst->env;
	remove_instance(inst);
	if (env->inst_list == NULL)
		end_environment(env, EXIT_SUCCESS);
	return (0);
}

void	update_camera(t_instance *inst)
{
	t_camera	*c;
	t_scal		speed;

	c = &inst->cam;
	speed = c->velocity * (c->move_faster ? c->velocity_modifier : 1.0)
		/ (c->move_slower ? c->velocity_modifier : 1.0);
	inst->cam.rot_matrix = m3yawpitchroll(
			c->rot.x / 180. * M_PI,
			c->rot.y / 180. * M_PI,
			c->rot.z / 180. * M_PI);
	c->spd = v3(
			(c->move_forward ? speed : 0.) - (c->move_backward ? speed : 0.),
			(c->move_left ? speed : 0.) - (c->move_right ? speed : 0.),
			(c->move_up ? speed : 0.) - (c->move_down ? speed : 0.));
	c->spd = m3dotv3(c->rot_matrix, c->spd);
	if (c->move_forward != c->move_backward
		|| c->move_left != c->move_right
		|| c->move_up != c->move_down)
	{
		c->pos = v3add(c->pos, c->spd);
		inst->win.redraw_required = 1;
	}
}

int		loop_event(t_environment *env)
{
	t_instance	*p;
	t_instance	*target;
	int			nsample;

	target = NULL;
	p = env->inst_current;
	while (p != NULL)
	{
		nsample = (1 << p->win.dxsample) * (1 << p->win.dysample);
		update_camera(p);
		if ((p->win.redraw_required || p->win.isample < nsample)
			&& (target == NULL || (!target->win.redraw_required
					&& p->win.redraw_required)))
			target = p;
		p = p->next_current;
	}
	if (target == NULL)
		return (0);
	if (target->win.redraw_required)
		target->win.isample = 0;
	mlx_clear_window(env->mlx, target->win.win);
	render(target);
	mlx_put_image_to_window(env->mlx, target->win.win, target->win.img, 0, 0);
	target->win.redraw_required = 0;
	return (0);
}

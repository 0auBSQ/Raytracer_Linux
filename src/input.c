/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:26:43 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 01:31:28 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int		key_press(int k, t_instance *inst)
{
	if (k == KEY_ESCAPE)
		return (close_event(inst));
	inst->cam.move_right |= (k == KEY_RIGHT || k == KEY_D);
	inst->cam.move_forward |= (k == KEY_UP || k == KEY_W || k == KEY_Z);
	inst->cam.move_left |= (k == KEY_LEFT || k == KEY_A || k == KEY_Q);
	inst->cam.move_backward |= (k == KEY_DOWN || k == KEY_S);
	inst->cam.move_up |= (k == KEY_SPACE);
	inst->cam.move_down |= (k == KEY_LSHIFT || k == KEY_RSHIFT);
	inst->cam.move_slower |= (k == KEY_LCONTROL || k == KEY_RCONTROL);
	inst->cam.move_faster |= (k == KEY_LALT || k == KEY_RALT);
	event_filtre(k, inst);
	if (inst->scn.n > 0)
		event_edition(k, inst);
	return (0);
}

int		key_release(int k, t_instance *inst)
{
	inst->cam.move_right &= !(k == KEY_RIGHT || k == KEY_D);
	inst->cam.move_forward &= !(k == KEY_UP || k == KEY_W || k == KEY_Z);
	inst->cam.move_left &= !(k == KEY_LEFT || k == KEY_A || k == KEY_Q);
	inst->cam.move_backward &= !(k == KEY_DOWN || k == KEY_S);
	inst->cam.move_up &= !(k == KEY_SPACE);
	inst->cam.move_down &= !(k == KEY_LSHIFT || k == KEY_RSHIFT);
	inst->cam.move_slower &= !(k == KEY_LCONTROL || k == KEY_RCONTROL);
	inst->cam.move_faster &= !(k == KEY_LALT || k == KEY_RALT);
	return (0);
}

int		mouse_press(int button, int x, int y, t_instance *inst)
{
	make_instance_current(inst);
	if (y < 0)
		return (0);
	inst->win.held_buttons |= (1 << button);
	inst->win.held_x = x;
	inst->win.held_y = y;
	return (0);
}

int		mouse_release(int button, int x, int y, t_instance *inst)
{
	(void)x;
	(void)y;
	inst->win.held_buttons &= ~(1 << button);
	return (0);
}

int		mouse_move(int x, int y, t_instance *inst)
{
	t_scal	sensibility;

	sensibility = 2. * inst->cam.yfov
		* (2. * tan((inst->cam.yfov / 180. * M_PI) / 2.))
		/ (t_scal)inst->win.h;
	if (inst->win.held_buttons & (1 << BUTTON_LEFT)
		&& (inst->win.held_x != x || inst->win.held_y != y))
	{
		inst->cam.rot.x -= (t_scal)(x - inst->win.held_x) * sensibility;
		inst->cam.rot.y += (t_scal)(y - inst->win.held_y) * sensibility;
		inst->cam.rot.y = fmin(fmax(inst->cam.rot.y, -90.), 90.);
		inst->win.redraw_required = 1;
	}
	inst->win.held_x = x;
	inst->win.held_y = y;
	return (0);
}

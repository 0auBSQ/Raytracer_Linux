/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:39:26 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/02 15:15:05 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void			end_environment(t_environment *env, int status)
{
	while (env->inst_list != NULL)
		remove_instance(env->inst_list);
	exit(status);
}

void			init_environment(t_environment *env)
{
	ft_memset(env, 0, sizeof(*env));
	env->error_callback = end_environment;
}

void			init_view(t_environment *env)
{
	t_instance	*pinst;

	if (env->inst_list == NULL)
		print_error(env, "Could not open any window.\n");
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		print_error(env, "Failed to initialize mlx.\n");
	pinst = env->inst_list;
	while (pinst != NULL)
	{
		pinst->win.win = mlx_new_window(pinst->env->mlx,
				pinst->win.w, pinst->win.h,
				pinst->name);
		pinst->win.img = mlx_new_image(pinst->env->mlx,
				pinst->win.w, pinst->win.h);
		if (pinst->win.win == NULL || pinst->win.img == NULL)
			print_error(env, "Failed to initialize a window.\n");
		pinst->win.buf = mlx_get_data_addr(pinst->win.img, &pinst->win.bpp,
				&pinst->win.s_l, &pinst->win.endian);
		pinst->win.redraw_required = 1;
		if (init_textures(pinst) == ERROR)
			print_error(env, "Failed to load textures.\n");
		make_instance_current(pinst);
		pinst = pinst->next;
	}
}

void			init_hooks(t_environment *env)
{
	t_instance	*pinst;

	pinst = env->inst_list;
	while (pinst != NULL)
	{
		pinst->win.rbuf = malloc(sizeof(char) * pinst->win.h * pinst->win.s_l);
		if (pinst->win.rbuf == NULL)
			print_error(pinst->env, "Failed to allocate render buffer");
		mlx_hook(pinst->win.win, KEY_PRESS, (1L << 0), key_press, pinst);
		mlx_hook(pinst->win.win, KEY_RELEASE, (1L << 1), key_release, pinst);
		mlx_hook(pinst->win.win, MOUSE_PRESS, (1L << 2), mouse_press, pinst);
		mlx_hook(pinst->win.win, MOUSE_RELEASE, (1L << 3), mouse_release, pinst);
		mlx_hook(pinst->win.win, MOUSE_MOVE, (1L << 6), mouse_move, pinst);
		mlx_hook(pinst->win.win, EXPOSE_EVENT, (1L << 15), expose_event, pinst);
		mlx_hook(pinst->win.win, CLOSE_EVENT, (1L << 17), close_event, pinst);
		pinst = pinst->next;
	}
	mlx_loop_hook(env->mlx, loop_event, env);
}

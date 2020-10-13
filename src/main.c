/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:26:00 by cdittric          #+#    #+#             */
/*   Updated: 2019/03/27 15:44:40 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int				main(int argc, char *argv[])
{
	t_environment	env;

	init_environment(&env);
	if (argc < 2)
		print_error(&env, "usage: rtv1 <scene path> ...\n");
	parse_files(&env, argc, argv);
	init_view(&env);
	init_hooks(&env);
	mlx_loop(env.mlx);
}

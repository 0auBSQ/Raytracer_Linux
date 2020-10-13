/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:18:17 by rmarracc          #+#    #+#             */
/*   Updated: 2019/04/06 17:19:32 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_vec4		filtre_do_nothing(t_vec4 color)
{
	return (color);
}

t_vec4		black_to_alpha(t_vec4 color)
{
	return (color);
}

t_vec4		filtre_stereoscopy(t_vec4 color)
{
	t_vec4			new;

	new.x = 0.393 * color.x + 0.769 * color.y + 0.189 * color.z;
	new.y = 0.;
	new.z = 0.;
	if (new.x > 255)
		new.x = 255;
	return (new);
}

t_vec4		filtre_sepia(t_vec4 color)
{
	t_vec4			new;

	new.x = 0.393 * color.x + 0.769 * color.y + 0.189 * color.z;
	new.y = 0.349 * color.x + 0.686 * color.y + 0.168 * color.z;
	new.z = 0.272 * color.x + 0.534 * color.y + 0.131 * color.z;
	if (new.x > 255)
		new.x = 255;
	if (new.y > 255)
		new.y = 255;
	if (new.z > 255)
		new.z = 255;
	return (new);
}

t_vec4		filtre_cell(t_vec4 color)
{
	t_vec4			new;

	new.x = floor(9. * color.x) / 8.;
	new.y = floor(9. * color.y) / 8.;
	new.z = floor(9. * color.z) / 8.;
	return (new);
}

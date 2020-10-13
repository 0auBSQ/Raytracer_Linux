/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:45:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 14:42:19 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int				init_textures(t_instance *inst)
{
	t_environment	*env;
	int				k;
	int				d[3];
	t_scene			*s;

	k = 0;
	env = inst->env;
	s = &inst->scn;
	s->tex[0] = mlx_xpm_file_to_image(env->mlx, "tex/nord.xpm", s->w + 0, s->h + 0);
	s->tex[1] = mlx_xpm_file_to_image(env->mlx, "tex/sud.xpm", s->w + 1, s->h + 1);
	s->tex[2] = mlx_xpm_file_to_image(env->mlx, "tex/est.xpm", s->w + 2, s->h + 2);
	s->tex[3] = mlx_xpm_file_to_image(env->mlx, "tex/ou.xpm", s->w + 3, s->h + 3);
	s->tex[4] = mlx_xpm_file_to_image(env->mlx, "tex/haut.xpm", s->w + 4, s->h + 4);
	s->tex[5] = mlx_xpm_file_to_image(env->mlx, "tex/bas.xpm", s->w + 5, s->h + 5);
	while (k < 6)
		if (s->tex[k++] == NULL)
			return (ERROR);
	s->c_tex[0] = (int*)mlx_get_data_addr(s->tex[0], &d[0], &d[1], &d[2]);
	s->c_tex[1] = (int*)mlx_get_data_addr(s->tex[1], &d[0], &d[1], &d[2]);
	s->c_tex[2] = (int*)mlx_get_data_addr(s->tex[2], &d[0], &d[1], &d[2]);
	s->c_tex[3] = (int*)mlx_get_data_addr(s->tex[3], &d[0], &d[1], &d[2]);
	s->c_tex[4] = (int*)mlx_get_data_addr(s->tex[4], &d[0], &d[1], &d[2]);
	s->c_tex[5] = (int*)mlx_get_data_addr(s->tex[5], &d[0], &d[1], &d[2]);
	return (SUCCESS);
}

int				store_texture(t_qunion *qunion, t_scal param[13])
{
	t_quadric		*quad;

	if (param[2] < 0 || param[2] > 5)
		return (ERROR);
	while ((quad = cycle_qunion(qunion)) != NULL)
	{
		quad->material.texture = param[2];
		quad->tex_zoom = param[1];
		quad->tex_offset = param[0];
	}
	return (SUCCESS);
}

void			store_material(t_qunion *qunion, t_scal param[13])
{
	t_quadric		*quad;

	while ((quad = cycle_qunion(qunion)) != NULL)
	{
		quad->reflective = param[2];
		quad->transparency = param[1];
		quad->refraction = param[0];
		quad->material_active = ON;
	}
}

t_vec2			select_texture(t_instance *i,
					t_material *m, t_vec3 pos, t_vec4 *c)
{
	int				select;
	t_vec2			coords;
	t_ivec2			t;
	unsigned char	*tex;

	if (m->texture >= 0 && m->texture < 6 && m->mapping == mapping_cube)
		coords = cube_mapping(i, m, pos, &select);
	else
		return (v2(0.0, 0.0));
	tex = (unsigned char*)i->scn.c_tex[m->texture];
	t.x = (coords.x * m->tex_zoom + m->tex_offset);
	t.x = t.x % i->scn.w[select];
	t.y = (coords.y * m->tex_zoom + m->tex_offset);
	t.y = t.y % i->scn.h[select];
	if (c != NULL)
		*c = v4((t_scal)tex[2 + t.x * 4 + t.y * 4 * i->scn.w[select]] / 255.,
				(t_scal)tex[1 + t.x * 4 + t.y * 4 * i->scn.w[select]] / 255.,
				(t_scal)tex[0 + t.x * 4 + t.y * 4 * i->scn.w[select]] / 255.,
				0.);
	return (coords);
}

void			select_perturbation(t_shading_data *p, t_material *m,
	t_scal **f)
{
	if (m->perturbation == DAMIER)
		damier(p, m->coeff_perturbation);
	else if (m->perturbation == PERLIN)
		perlin(p, m->coeff_perturbation);
	else if (m->perturbation == WOOD)
		wood(p, m->coeff_perturbation);
	else if (m->perturbation == BUMP)
		bump(p, m, f);
	else if (m->perturbation == WAVE)
		wave(p, m->coeff_perturbation);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:32:43 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 12:24:21 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "defaults.h"
# include "types.h"
# include "../minilibx_macos/mlx.h"

t_vec3			v3(t_scal x, t_scal y, t_scal z);
t_vec3			v3add(t_vec3 a, t_vec3 b);
t_vec3			v3sub(t_vec3 a, t_vec3 b);
t_scal			v3dot(t_vec3 a, t_vec3 b);
t_vec3			v3cross(t_vec3 a, t_vec3 b);

t_vec3			v3mult(t_vec3 a, t_vec3 b);
t_vec3			v3dotf(t_vec3 v, t_scal f);
t_scal			v3length(t_vec3 v);
t_vec3			v3normalize(t_vec3 v);
t_vec3			v3reflect(t_vec3 i, t_vec3 n);
t_vec3			v3refract(t_vec3 i, t_vec3 n, t_scal indice);

t_vec4			v4(t_scal x, t_scal y, t_scal z, t_scal w);
t_scal			v4dot(t_vec4 a, t_vec4 b);
t_vec4			v4add(t_vec4 a, t_vec4 b);
t_vec4			v4dotf(t_vec4 v, t_scal f);
t_vec4			v4mult(t_vec4 a, t_vec4 b);

t_vec3			m3dotv3(t_mat3 m, t_vec3 v);
t_mat4			m4dot(t_mat4 a, t_mat4 b);
t_mat3			m3yawpitchroll(t_scal yaw, t_scal pitch, t_scal roll);
t_mat4			m4yawpitchroll(t_scal yaw, t_scal pitch, t_scal roll);
t_mat4			m4transpose(t_mat4 m);

t_mat3			m3dot(t_mat3 a, t_mat3 b);
t_mat3			m3scale(t_scal x, t_scal y, t_scal z);
t_ivec2			ivec2(int x, int y);
t_vec2			v2(t_scal x, t_scal y);

int				init_stream(t_stream *st, int fd);
int				ft_getchar(t_stream *s);
int				ft_getc(t_stream *s);
int				flusher(t_stream *s);
int				skip_space(t_stream *s);
int				store_obj(t_instance *i, t_qunion **q,
				t_stream *s, int type_instr);
int				store_preset(t_instance *i, t_qunion **q, t_stream *s, int ins);

void			parse_files(t_environment *env, int argc, char *argv[]);

void			end_environment(t_environment *env, int status);
void			init_environment(t_environment *env);
void			init_view(t_environment *env);
void			init_hooks(t_environment *env);

int				transformation(t_qunion *q, t_scal param[], int type_instr);

t_qunion		*add_quadric(t_qunion **q, t_scal quad_param[], t_quadric *qua);
void			free_qunion_list(t_qunion *q);
void			fill_instance(t_instance *i, t_qunion *q);
t_mat4			quadric_to_mat4(t_scal *q);
void			mat4_to_quadric(t_scal *q, t_mat4 m);
t_scal			iclamp(t_scal val);

t_instance		*add_instance(t_environment *env, char *name);
void			remove_instance(t_instance *inst);
void			make_instance_current(t_instance *inst);

int				add_light(t_light **l, t_scal param[]);
void			remove_light(t_light **l);
void			allocate_instance_values(t_instance *i, t_qunion *q);
int				log2i(int n);
void			print_error(t_environment *env, const char *format);

void			plan_to_quad(t_scal param[],
				t_scal quad_param[], t_quadric *q);
void			sphere_to_quad(t_scal param[],
				t_scal quad_param[], t_quadric *q);
void			cylindre_to_quad(t_scal param[],
				t_scal quad_param[], t_quadric *q);
void			cone_to_quad(t_scal param[],
				t_scal quad_param[], t_quadric *q);
void			quadric_to_quad(t_scal param[],
				t_scal quad_param[], t_quadric *q);

void			translate_quad(t_scal *q, t_scal x, t_scal y, t_scal z);
void			rotate_quad(t_scal *q, t_scal yaw, t_scal pitch, t_scal roll);

int				key_press(int keycode, t_instance *inst);
int				key_release(int keycode, t_instance *inst);
int				mouse_press(int button, int x, int y, t_instance *inst);
int				mouse_release(int button, int x, int y, t_instance *inst);
int				mouse_move(int x, int y, t_instance *inst);

int				expose_event(t_instance *inst);
int				close_event(t_instance *inst);
int				loop_event(t_environment *env);

void			render(t_instance *inst);

int				out_of_bound(t_instance *inst, t_vec3 pos);
t_vec4			raytrace(t_instance *inst, t_raytrace_data rt, int n, int e);

void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
int				ft_strequ(const char *s1, const char *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);

int				event_filtre(int k, t_instance *inst);
t_vec4			filtre_sepia(t_vec4 color);
t_vec4			filtre_cartoon(t_vec4 color);
t_vec4			filtre_stereoscopy(t_vec4 color);
t_vec4			filtre_cell(t_vec4 color);
t_vec4			filtre_do_nothing(t_vec4 color);

void			remove_qunion(t_qunion **q);
t_qsection		*merge_qsection(t_quadric *a, t_quadric *b);
void			insert_qsection(t_qsection **list, t_qsection *node);
void			remove_qsection(t_qsection **q);
int				count_qsection(t_qsection *q);
int				create_quadric(t_instance *inst, t_qunion **q, int type_instr,
				t_scal param[]);

t_quadric		*cycle_qunion(t_qunion *q);
int				unite_qunion(t_qunion **q, int n);
int				intersect_qunion(t_qunion **q,
				int n, ssize_t *nqsection, ssize_t *nquadric);
int				invert_qunion(t_qunion **q,
				ssize_t *nqsection, ssize_t *nquadric);
int				manipulate_qunion(t_instance *inst,
				t_qunion **q, t_scal *param, int instr);
void			invert_quadric(t_quadric *quadric);
t_qunion		*qunion_failm(t_qunion **q, t_qsection ***s);

int				init_textures(t_instance *inst);
t_vec2			cube_mapping(t_instance *inst,
				t_material *m, t_vec3 pos, int *select);
int				store_texture(t_qunion *qunion, t_scal param[13]);
t_vec2			select_texture(t_instance *i,
				t_material *m, t_vec3 pos, t_vec4 *c);
void			store_material(t_qunion *qunion, t_scal param[13]);
int				perturbation(t_qunion *q, t_scal p[], int type);
int				store_preset(t_instance *i, t_qunion **q, t_stream *s,
				int ins);

void			damier(t_shading_data *p, t_scal l);
void			perlin(t_shading_data *p, int l);
void			wood(t_shading_data *p, int l);
void			bump(t_shading_data *p, t_material *m, t_scal **f);
void			wave(t_shading_data *p, t_scal e);
void			select_perturbation(t_shading_data *p, t_material *m,
				t_scal **f);

t_vec4			black_to_alpha(t_vec4 color);

int				event_edition(int k, t_instance *inst);

t_scal			noise(t_scal x, t_scal y, t_scal z);

ssize_t			set_quadric_intersection(t_instance *inst,
				t_ray ray, t_scal *tnearest, t_scal side);

int				nb_param(int type_instr);
int				extract_param(t_stream *s, t_scal *n);

void			direct_light(t_vec4 *color, t_instance *inst, t_ray *ray);
t_raytrace_data	get_rt_data(t_instance *inst, int x, int y);
void			process_stereoscopy(t_vec4 *color, t_raytrace_data rt,
				t_instance *i);
t_vec4			get_color(t_instance *inst, t_raytrace_data rt);

t_vec4			get_quadric_equation_coefficients(t_scal *q, t_ray r);
t_scal			evaluate_quadric(t_scal *q, t_vec3 p);
int				out_of_bound(t_instance *inst, t_vec3 pos);
t_vec3			get_quadric_normal(t_scal *q, t_vec3 p);

t_vec4			bake_lighting(t_instance *inst, t_light *l, t_shading_data p);

#endif

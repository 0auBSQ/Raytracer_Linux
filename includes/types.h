/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:30:53 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 12:07:50 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "defaults.h"

typedef double					t_scal;

typedef struct					s_vec2 {
	t_scal						x;
	t_scal						y;
}								t_vec2;

typedef struct					s_mat2 {
	t_scal						m[4];
}								t_mat2;

typedef struct					s_vec3 {
	t_scal						x;
	t_scal						y;
	t_scal						z;
}								t_vec3;

typedef struct					s_mat3 {
	t_scal						m[9];
}								t_mat3;

typedef struct					s_vec4 {
	t_scal						x;
	t_scal						y;
	t_scal						z;
	t_scal						w;
}								t_vec4;

typedef struct					s_mat4 {
	t_scal						m[16];
}								t_mat4;

typedef struct					s_ivec2 {
	int							x;
	int							y;
}								t_ivec2;

typedef enum					e_mapping_type {
	mapping_flat,
	mapping_cube,
	mapping_cone
}								t_mapping_type;

typedef struct					s_material {
	t_scal						ambiant;
	t_scal						diffuse;
	t_scal						specular;
	t_scal						alpha;
	t_scal						reflective;
	t_scal						transparency;
	t_scal						refraction;
	int							texture;
	t_scal						tex_offset;
	t_scal						tex_zoom;
	int							perturbation;
	t_scal						coeff_perturbation;
	t_mat3						rot;
	t_vec3						pos;
	t_mapping_type				mapping;
}								t_material;

/*
** t_quadric:
** Quadric surface of the form
** a*x^2 + b*y^2 + c*z^2 + d*x*y + e*x*z + f*y*z + g*x + h*y + i*z + j < 0
*/

typedef struct					s_quadric {
	t_scal						param[15];
	t_scal						reflective;
	t_scal						transparency;
	t_scal						refraction;
	t_material					material;
	t_scal						material_active;
	t_scal						tex_offset;
	t_scal						tex_zoom;
	int							perturbation;
	t_scal						coeff_perturbation;
	struct s_quadric			*next;
}								t_quadric;

/*
** t_qsection:
** The section of a list of quadrics.
*/

typedef struct					s_qsection {
	t_quadric					*list;
	struct s_qsection			*next;
}								t_qsection;

/*
** t_qunion:
** The union of a list of sections of quadrics.
** Fundamental object required for Constructive Solid Geometry with quadrics.
*/

typedef struct					s_qunion {
	char						*name;
	t_qsection					*list;
	struct s_qunion				*next;
}								t_qunion;

typedef struct					s_ray {
	t_vec3						pos;
	t_vec3						dir;
}								t_ray;

/*
** side: 1.0 if the origin of the ray is outside any object.
** -1.0 otherwise (Out of bound). Used for refraction and object traversal.
*/

typedef struct					s_raytrace_data {
	t_ray						ray;
	int							n;
	int							e;
	t_scal						side;
}								t_raytrace_data;

typedef struct					s_shading_data {
	t_scal						t;
	t_raytrace_data				*rt;
	t_vec4						col;
	t_vec3						pos;
	t_vec3						eye;
	t_vec3						nor;
	t_material					*m;
}								t_shading_data;

typedef struct					s_flags {
	int							w;
	int							h;
	t_scal						x;
	t_scal						y;
	t_scal						z;
}								t_flags;

typedef struct					s_intersection_data {
	ssize_t						inearest;
	t_scal						tnearest;
	ssize_t						iclosest;
	t_scal						tclosest;
	ssize_t						jrange;
	ssize_t						j;
	ssize_t						jend;
	ssize_t						irange;
	ssize_t						i;
	t_scal						t;
	t_vec4						q;
}								t_intersection_data;

/*
** t_primitive:
** Indexes fundamental geometrical objects (not t_object) that are of the same
** type and contiguous in memory
*/

typedef enum					e_primitive_type {
	primitive_quadric,
	primitive_type_count
}								t_primitive_type;

typedef struct					s_primitive {
	t_primitive_type			type;
	size_t						offset;
	size_t						count;
	struct s_object				*next;
}								t_primitive;

typedef struct					s_object {
	char						*name;
	t_primitive					*plist;
	struct s_object				*next;
}								t_object;

/*
** t_light: Simple light for phong shading.
** - type: (light_<...>)
**  | ambiant:		requires `col`.
**  | point:		requires `col`, `pos`.               + attenuation
**  | directional:	requires `col`, `dir`.
**  | spot:			requires `col`, `pos`, `dir`, `cos`. + attenuation
** - col: color of the light.
** - pos: position of the light.
** - dir: direction of the light.
** - cos: cosine of half the angle of aperture of a spotlight.
*/

typedef enum					e_light_type {
	light_ambiant,
	light_point,
	light_directional,
	light_spot,
	light_type_count
}								t_light_type;

typedef struct					s_light {
	t_light_type				type;
	t_vec3						col;
	t_vec3						pos;
	t_vec3						dir;
	t_vec3						cos;
	t_scal						constant_attenuation;
	t_scal						linear_attenuation;
	t_scal						quadratic_attenuation;
	struct s_light				*next;
}								t_light;

/*
** t_window:
** Contains data associated to the mlx window and its mlx image.
** - buf:		Buffer of the mlx image associated with the window.
** - rbuf:		Formated like `buf` but only a subset of it's pixels are
** rendered. Content of `buf` is extrapolated from that subset before display.
** - isample:	Iterates over the subsets of `rbuf` to be rendered. One is
** rendered for each call to the functions render().
** - dxsample:	Bit depth of the samples number of a subdivision on the x-axis.
** - dysample:	Bit depth of the samples number of a subdivision on the y-axis.
** The number of different subsets before before `rbuf` is completely
** rendered is `2^dxsample * 2^dysample`. `isample` will iterate from 0 to that.
** - held_<*>:	Used by the mouse motion event to know the mouse state after the
** previous mouse event. `held_button` is a bit field.
*/

typedef struct					s_window {
	void						*win;
	void						*img;
	char						*buf;
	char						*rbuf;
	int							isample;
	int							dxsample;
	int							dysample;
	int							nreflexions[2];
	int							bpp;
	int							s_l;
	int							endian;
	int							w;
	int							h;
	int							held_x;
	int							held_y;
	int							held_buttons;
	int							redraw_required;
}								t_window;

/*
** t_camera:
** - rot:				yaw, pitch and roll of the camera.
** - move_<direction>:	whether the key to move in said direction is pressed.
*/

typedef struct					s_camera {
	t_vec3						pos;
	t_vec3						rot;
	t_vec3						spd;
	t_mat3						rot_matrix;
	t_scal						yfov;
	t_scal						velocity;
	t_scal						velocity_modifier;
	int							move_right;
	int							move_forward;
	int							move_left;
	int							move_backward;
	int							move_up;
	int							move_down;
	int							move_faster;
	int							move_slower;
	t_vec4						(*pf_filtre)(t_vec4 color);
}								t_camera;

/*
** t_scene:
** - v:			geometry buffer per primitive type.
** - t:			texture geometry buffer per primitive type.
** - c:			color buffer per primitive type.
** - tex:		texture index for each primitive per primitive type.
** - offset:	offset of which primitive to start drawing at per primitive type
** - count:		count of how many primitives to draw per primitive type.
** - light_list:chained list of lights to apply.
** - obj_list:	optional chained list of object for manipulation by the user.
*/

typedef struct					s_scene {
	t_scal						*v;
	t_scal						*c;
	t_material					*m;
	int							*tex[6];
	int							w[6];
	int							h[6];
	int							*c_tex[6];
	ssize_t						*offset;
	ssize_t						*count;
	ssize_t						nranges;
	ssize_t						n;
	t_light						*light_list;
	t_scal						ambiant;
	t_vec4						background_color;
	t_qunion					*templates;
	int							mode_edit;
	ssize_t						selected;
}								t_scene;

typedef struct s_environment	t_environment;

typedef struct					s_instance {
	t_environment				*env;
	char						*name;
	t_window					win;
	t_camera					cam;
	t_scene						scn;
	struct s_instance			**self_current;
	struct s_instance			*next_current;
	struct s_instance			**self;
	struct s_instance			*next;
	t_scal						ambiante;
}								t_instance;

struct							s_environment {
	void						*mlx;
	t_instance					*inst_list;
	t_instance					*inst_current;
	void						(*error_callback)(t_environment *, int);
};

typedef struct					s_stream {
	int							fd;
	char						buff[BUFFER_SIZE];
	int							i;
	int							nread;
}								t_stream;

#endif

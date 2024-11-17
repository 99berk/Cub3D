/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:29:45 by aaltinto          #+#    #+#             */
/*   Updated: 2024/09/23 14:34:35 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ARG "Error! Invalid arguments.\nUsage: './cub3d *.cub'"

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define ARROW_L 123
# define ARROW_R 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define SHIFT 257
# define SPACE 49

# define M_PI 3.14159265358979323846

# define TILE_SIZE 40
# define PLAYER_SPEED 1.5f
# define CAMERA_DISTANCE 10

# define X 0
# define Y 1
# define TOP 0
# define BOT 1

# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_render
{
	int		sc_width;
	int		sc_height;
	double	ray_angle;
	double	ray_dist;
	int		flag;
}	t_render;

typedef struct s_player
{
	double	pos[2];
	double	camera[2];
	double	fov;
	double	p_angle;
	double	running;
}	t_player;

typedef struct s_textures
{
	char	*walls[5];
	char	*floor;
	int		floor_rgb[3];
	char	*ceiling;
	int		ceiling_rgb[3];
}	t_textures;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_keys
{
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_la;
	int		key_ra;
}	t_keys;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	t_textures	textures;
	t_mlx		mlx;
	t_data		img;
	t_data		xpm[4];
	t_player	player;
	t_render	render;
	t_keys		keys;
	char		**map;
	int			map_w;
	int			map_h;
	char		*raw_map;
	int			fov_angle;
}	t_vars;

typedef struct s_ray
{
	double	side_dist[2];
	double	raydir[2];
	double	delta_dist[2];
	int		step[2];
	int		side;
}	t_ray;

//error
int		err(char *str);
int		null_free(void *ptr);
void	abort_mission(t_vars *vars);
int		read_map(char **argv, t_vars *vars);
int		double_counter(char **str);
char	**reallocate_double(char **str);
int		find_longest_line(char **str);
int		free_doubles(char **str);
int		parse_init(t_vars *vars, char *map);
int		init_textures(t_textures *textures, char *tmp);
int		extract_rgb(t_vars *vars);
int		color_init(t_vars *vars, char *tmp);
int		cast_rays(t_vars *vars);
int		rgb_to_hex(int r, int g, int b);
void	pixel_put(t_data *data, int x, int y, int color);
double	nor_angle(double angle);
int		key_capture(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		move_player(t_vars *vars, double x, double y);
int		close_windows(t_vars *vars);
char	*strip(char *str);
int		get_color(t_vars *vars, int flag, int x, int y);
int		render(void *ptr);
int		fill_variable(t_vars *vars, t_ray *ray);
int		detect_player(t_vars *vars);
int		texture_color(t_data *data, int x, int y);
int		detect_player(t_vars *vars);
int		get_textures(t_vars *vars);

#endif
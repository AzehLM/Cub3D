/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:14 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:15 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

typedef struct s_main_struct		t_main_struct;
typedef struct s_scene				t_scene;
typedef struct s_object_door		t_object_door;
typedef struct s_object_collectible	t_object_collectible;
typedef bool						(*t_parser_func)(t_scene *scene,
										char *line);

# define BUFFER_SIZE 512
# define CLEAR_BUFFER -42

# define TEXTURE_NO	"NO"
# define TEXTURE_SO	"SO"
# define TEXTURE_WE	"WE"
# define TEXTURE_EA	"EA"
# define COLOR_F	"F"
# define COLOR_C	"C"

# define HORIZONTAL 0
# define VERTICAL 1
# define ENCLOSED 2

# define CUB_FORMAT ".cub"
# define XPM_FORMAT ".xpm"

# define _ERROR "Error: %s\n"

# define ERR_NB_PARAMS "Error\nWrong number of parameters\n"
# define ERR_EXTENSION "Error\nWrong file format extension\n"

# define ERR_COLOR_INVALID "Invalid color format\n"
# define ERR_DUPLICATE "Error\nDuplicate %s identifier\n"
# define ERR_EMPTY_FILE "Error\nEmpty file\n"

# define ERR_INCOMPLETE_SCENE "Error\nScene incomplete before map start\n"
# define ERR_INVALID_CHAR "Error\nInvalid character encountered\n"
# define ERR_MISSING_ELEMENT "Error\nMissing required scene elements\n"
# define ERR_NO_MAP "Error\nNo map in file"
# define ERR_PARSING_ELEMENT "Error\nParsing element: %s"
# define ERR_SCENE_INVALID "Error\nInvalid scene configuration\n"
# define ERR_TOO_MANY_PLAYER "Error\nToo many player found in map\n"
# define ERR_NO_PLAYER "Error\nNo player found in map\n"
# define ERR_ENTITY "Error\nEntity is not properly enclosed ([%d,%d])\n"
# define ERR_NB_MONSTER "Error\nMore than one monster entity\n"

# define DEBUG_INITIAL_MAP "INITIAL MAP"
# define DEBUG_MAP_AFTER_SPACE "MAP AFTER SPACES INCLUSING"
# define DEBUG_PLAYER_COUNT "\n--- ERROR: INVALID NUMBER OF PLAYER (%d) ---\n"
# define DEBUG_SEPARATOR "\n--- %s ---\n"
# define DEBUG_UNCLOSED_MAP "\n--- ERROR: UNCLOSED MAP ---\n"
# define DEBUG_VALID_MAP "MAP SUCCESSFULLY VALIDATED"

typedef struct s_color_parse
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	char			*line;
}	t_color_parse;

typedef struct s_scene
{
	t_color_parse	*floor_color;
	t_color_parse	*ceiling_color;
	char			*we_texture;
	char			*so_texture;
	char			*no_texture;
	char			*ea_texture;
	int				pos[3];
	int				collectible_count;
	int				door_count;
	int				monster_count;
	int				collectible_positions[100][3];
	int				door_positions[100][4];
	int				monster_positions[2];
}	t_scene;

typedef struct s_parsing
{
	ssize_t	count;
	ssize_t	capacity;
	int		fd;
	char	*line;
	char	**new_lines;
	char	**lines;
}	t_parsing;

typedef struct s_infos
{
	t_parsing	*data;
	t_scene		*scene;
	int			map_start;
}	t_infos;

bool					check_extension(char *map, int fd, char *extension);
bool					is_scene_complete(t_scene *scene);
bool					is_texture_valid(char *path);
bool					parse_ceiling_color(t_scene *scene, char *line);
bool					parse_ea_texture(t_scene *scene, char *line);
bool					parse_floor_color(t_scene *scene, char *line);
bool					parse_no_texture(t_scene *scene, char *line);
bool					parse_so_texture(t_scene *scene, char *line);
bool					parse_we_texture(t_scene *scene, char *line);
bool					read_line_check(int fd, char *buffer);

char					**clear_read_lines(t_parsing *data);
char					**read_all_lines(t_parsing *data);
char					*extract_line(char **buffer);
char					*extract_texture_path(char *line, int id_len);
char					*join_and_free(char *s1, char *s2);
char					*read_line(int fd);

int						check_scene_validity(t_infos *infos);
int						get_element_type(char *line);

t_object_collectible	*create_object_map_item(int item[2]);
t_object_door			*create_object_map_door(int doors[4]);

void					check_map_validity(t_infos *infos, int map_start);
void					cleanup_parsing(t_infos *infos);
void					exit_error(char *message);
void					free_array(char **array);
void					free_extended_map(char **extended_map, int height);
void					free_map_item_i(t_main_struct *main_struct, int i);
void					free_scene(t_scene *scene);
void					init_data(t_infos *infos, char **av);
void					init_data(t_infos *infos, char **av);
void					init_parsing(t_infos *infos, char **av);
void					parsing(int ac, char **av, t_infos *infos);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:11:23 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/14 17:16:34 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../Library/Libft/libft.h"
# include "../Library/Minilibx/mlx.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <stdarg.h>
# include <fcntl.h>

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define ESC_KEY 65307
# define Q_KEY 113

# define EVT_KEY_PRESS 2
# define EVT_DESTROY_NOTIFY 17
# define EVT_FOCUS 9

# define SPRITE_SIZE 64
# define BUFFER_GNL 10

# define IMG_WALL "assets/1.xpm"
# define IMG_COLLECT "assets/C.xpm"
# define IMG_SPACE "assets/0.xpm"
# define IMG_GOAL_OFF "assets/E_off.xpm"
# define IMG_GOAL_ON "assets/E_on.xpm"
# define IMG_PLAYER "assets/P_init.xpm"

# define PLAYER_UP "assets/P_up.xpm"
# define PLAYER_LEFT "assets/P_left.xpm"
# define PLAYER_DOWN "assets/P_down.xpm"
# define PLAYER_RIGHT "assets/P_right.xpm"

# define DEBUG_INFO 1

/**
 * @brief Is used to hold all pertinent data of the game.
 */
typedef struct s_game_data
{
	void	*mlx;
	void	*window;
	char	**game_map;
	void	*sprite_space;
	void	*sprite_obstacle;
	void	*sprite_collectable;
	void	*sprite_goal_on;
	void	*sprite_goal_off;
	void	*sprite_player_init;
	void	*s_player_up;
	void	*s_player_left;
	void	*s_player_down;
	void	*s_player_right;
	int		goal_x;
	int		goal_y;
	int		p_pos_x;
	int		p_pos_y;
	int		p_direction;
	int		sprite_width;
	int		sprite_height;
	int		window_width;
	int		window_height;
	int		n_moves;
	int		n_collected;
	int		collectable;
	int		game_end;
}	t_game_data;

typedef struct s_map_data
{
	int	collum;
	int	line;
	int	goal_count;
	int	player_count;
	int	collectable_count;
}	t_map_data;

//___get_next_line ======================================================

/**
 * @brief Get the next line object
 * 
 * @param fd 
 * @return char* 
 */
char		*get_next_line(int fd);

//___so_long ============================================================

//int	main(int argc, char **argv)

/**
 * @brief Function used to receive the map data, read it 
 * and make sense of it
 * 
 * @param map_path The map that is being read this instance
 * @return A char** that is the map interpreted for code use
 */
char		**generate_map(char *map_path);

/**
 * @brief starts the process of the game functioning
 * 
 * @param game_data the data package of the game
 */
void		start_game(t_game_data *game_data);

/**
 * @brief Start the most basic part of the game
 * 
 * @param game_data the data package of the game
 */
void		start_data(t_game_data *game_data);

/**
 * @brief Initializes all the sprites that will be used
 * 
 * @param game_data the data package of the game
 */
void		start_sprites(t_game_data *game_data);

//___so_long_utils ========================================================

/**
 * @brief Free's the memory of the void pointer received and puts 
 * it's contents to zero
 * 
 * @param ptr The pointer to free
 */
void		free_ptr(void **ptr);

/**
 * @brief Using the map data stored it gets the size that the 
 * window of the game should be
 * 
 * @param game_data the data package of the game
 */
void		get_window_size(t_game_data *game_data);

/**
 * @brief validates the image for game use 
 * 
 * @param sprite the image you will be putting in the game
 * @param game_data the data package of the game
 * @return the image ready to use 
 */
void		*start_sprite(char *sprite, t_game_data *game_data);

/**
 * @brief Initializes the data of the map
 * 
 * @param data The map data used for validation
 */
void		map_data_init(t_map_data *data);

/**
 * @brief 
 * 
 * @param game the data package of the game
 * @return int 
 */
int			display_info(t_game_data *game);

//___map_validation =====================================================

/**
 * @brief Checks if all the parameters passed by the map are correct 
 * according to the rules of the game
 * 
 * @param map The map already in the format that will be used to make it
 * @param map_file The original file used for the map
 * @return If the map is valid for the game 
 */
int			validate_map(char **map, char *map_file);

/**
 * @brief Checks if the quantity of certain things in the map and
 * if the numbers are valid
 * 
 * @param map The map in the format to be used
 * @param data The map data used for validation
 * @return If is valid 
 */
int			valid_count(char **map, t_map_data *data);

/**
 * @brief Check if the walls of the game are in the right place
 * 
 * @param map The map in the format to be used
 * @param data The map data used for validation
 * @return If is valid  
 */
int			valid_walls(char **map, t_map_data *data);

/**
 * @brief Checks if the characters used to build the map are 
 * valid and if nothing extra was used
 * 
 * @param map The map in the format to be used
 * @return If is valid  
 */
int			valid_characters(char **map);

/**
 * @brief Checks if the file used the correct extension
 * 
 * @param map_file The original file of the map
 * @return If is valid  
 */
int			valid_extension(char *map_file);

//___map_use =============================================================

/**
 * @brief Start the process of putting the map and objects on the game window
 * 
 * @param data The data package of the game
 */
void		start_map(t_game_data *data);

/**
 * @brief "Draws" the sprite on the window screen on the set of 
 * coordinates passed
 * 
 * @param game The data package of the game
 * @param sprite The specific sprite you want drawn 
 * @param x Coordinate X on the map
 * @param y Coordinate Y on the map
 */
void		sprite_draw(t_game_data *game, void *sprite, int x, int y);

/**
 * @brief "Draws" the collectable and counts them
 * 
 * @param game The data package of the game
 * @param horizontal Coordinate X on the map
 * @param vertical Coordinate Y on the map
 */
void		map_hook_collet(t_game_data *game, int horizontal, int vertical);

/**
 * @brief "Draws" the goal and saves it's position
 * 
 * @param game The data package of the game
 * @param goal_x Coordinate X on the map to save
 * @param goal_y Coordinate Y on the map to save
 */
void		map_hook_goal(t_game_data *game, int goal_x, int goal_y);

/**
 * @brief "Draws" the player and saves it's initial position
 * 
 * @param game The data package of the game
 * @param player_x Coordinate X on the map to save
 * @param player_y Coordinate Y on the map to save
 */
void		map_hook_player(t_game_data *game, int player_x, int player_y);

//___hook_set =============================================================

/**
 * @brief Calls all the different types of events that happen
 * during the game
 * 
 * @param g_data The data package of the game
 */
void		hooks_in_game(t_game_data *g_data);

/**
 * @brief Knows what key was pressed and call functions accordingly
 * 
 * @param key_pressed The key that was pressed
 * @param game_data The data package of the game
 * @return 0
 */
int			key_press(int key_pressed, t_game_data *game_data);

/**
 * @brief Starts the process of quitting the game
 * 
 * @param game_data The data package of the game
 * @return 0
 */
int			quit_game(t_game_data *game_data);

/**
 * @brief Start the procces of updating the map acoording to your movement
 * 
 * @param keycode The key pressed
 * @param game_data The data package of the game
 */
void		map_update(int keycode, t_game_data *game_data);

/**
 * @brief Part of map updating procces
 * 
 * @param data The data package of the game
 */
void		map_updater(t_game_data *data);

//___hook_utils_quit ==========================================================

/**
 * @brief Free all the pointers used to hold the map
 * 
 * @param game_map The stored map of the game
 */
void		free_map(char **game_map);

/**
 * @brief Free the memory used to store the images, the window, the display 
 * and then frees the mlx
 * 
 * @param g_data The data package of the game
 */
void		free_game(t_game_data *g_data);

//___hook_utils_map ===========================================================

/**
 * @brief Updates the direction the player is facing
 * 
 * @param player_direction The directional key that was pressed 
 * @param g_data The data package of the game
 */
void		update_direction(int player_direction, t_game_data *g_data);

/**
 * @brief Updates the position of the player on the map 
 * 
 * @param keycode The directional key that was pressed 
 * @param g_data The data package of the game
 */
void		update_player(int keycode, t_game_data *g_data);

/**
 * @brief Handles the player behavior when moving and interacting with 
 * things in the map
 * 
 * @param game_data The data package of the game
 * @param new_y Player new Y position on the map
 * @param new_x Player new X position on the map
 */
void		hold_key(t_game_data *game_data, int new_y, int new_x);

/**
 * @brief Handles the goal sprite update (it is updated together with 
 * the others sprites)
 * 
 * @param data The data package of the game
 * @param x The X on the map
 * @param y The Y on the map
 */
void		goal_updater(t_game_data *data, int x, int y);

/**
 * @brief Resumes the map on the screen
 * 
 * @param game The data package of the game
 * @return 0
 */
int			map_resume(t_game_data *game);

//___hook_utils_hold_key =====================================================

/**
 * @brief Changes the value of two positions on the map
 * 
 * @param pos Position in the present
 * @param new_pos New position
 * @param val Value to be put in the old position
 * @param new_val Value to be put in the new position
 */
void		change_position(char *pos, char *new_pos, char val, char new_val);

/**
 * @brief Handles the player moving to an empty space
 * 
 * @param g_data The data package of the game
 * @param new_y The Y position you are moving to
 * @param new_x The X position you are moving to
 */
void		handle_space(t_game_data *g_data, int new_y, int new_x);

/**
 * @brief Handles the player moving to a collectable
 * 
 * @param g_data The data package of the game
 * @param new_y The Y position you are moving to
 * @param new_x The X position you are moving to
 */
void		handle_collectable(t_game_data *g_data, int new_y, int new_x);

/**
 * @brief Handles the player moving to an activated Goal
 * 
 * @param g_data The data package of the game
 * @param new_y The Y position you are moving to
 * @param new_x The X position you are moving to
 */
void		handle_goal_on(t_game_data *g_data, int new_y, int new_x);

/**
 * @brief Handles the player moving to an deactivated Goal
 * 
 * @param g_data The data package of the game
 * @param new_y The Y position you are moving to
 * @param new_x The X position you are moving to
 */
void		handle_goal_off(t_game_data *g_data, int new_y, int new_x);

//___hook_utils_update

/**
 * @brief Sraws the player in the position that hee is and direction 
 * that he is facing
 * 
 * @param g_data The data package of the game
 * @param player_x Coordinate X on the map to save
 * @param player_y Coordinate Y on the map to save
 */
void		update_hook_player(t_game_data *g_data, int player_x, int player_y);

#endif

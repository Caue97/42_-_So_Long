# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 18:30:16 by felcaue-          #+#    #+#              #
#    Updated: 2022/01/14 17:07:50 by felcaue-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= solong

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -lXext -lX11
LIB			= ar -rcs
RM			= /bin/rm -rf

LIBFT			=	Library/Libft/libft.a
LIBFT_PATH		=	Library/Libft
MINILIBX		=	Library/Minilibx/libmlx.a
MINILIBX_PATH	=	Library/Minilibx

DIRECTORY	=	Objs_solong

INCLUDE		=	source_code/so_long.h 
SRCS		=	get_next_line.c hook_set.c hook_utils_hold_key.c hook_utils_map.c \
				hook_utils_quit.c map_use.c map_validation.c so_long_utils.c \
				so_long.c hook_utils_update.c
				
ADD_ARG		=	$(addprefix source_code/,$(SRCS))
				

OBJS		= $(addprefix ./$(DIRECTORY)/,$(SRCS:.c=.o))

all:		$(NAME)

$(DIRECTORY)/%.o:	source_code/%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(DIRECTORY) $(OBJS) $(INCLUDE) $(LIBFT) $(MINILIBX)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(LDFLAGS) -o $@

$(LIBFT):	
			make -C Library/Libft

$(MINILIBX):
			make -C Library/Minilibx

$(DIRECTORY):	
				mkdir -p $(DIRECTORY)

git:
			clear
			git add .
			git commit -m "make git update"
			git push origin			

clean:
			$(RM) $(DIRECTORY)
			make -C $(LIBFT_PATH) clean
			make -C $(MINILIBX_PATH) clean

fclean:		clean
			$(RM) $(NAME)
			make -C $(LIBFT_PATH) fclean
			make -C $(MINILIBX_PATH) clean

my_clean:	clean
			$(RM) $(NAME)
			make -C $(LIBFT_PATH) fclean
			make -C $(MINILIBX_PATH) clean
			clear

re:			fclean all

.PHONY:		all clean fclean re
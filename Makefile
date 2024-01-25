# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 00:10:23 by doriani           #+#    #+#              #
#    Updated: 2024/01/24 04:28:51 by doriani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
## Variables ##
###############
NAME		= cub3d
UNAME_S := $(shell uname -s)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes/ -I./libft/includes/
RM			= rm -f
LIBFT_DIR	= ./libft/
LIBFT_NAME	= libft.a
LIBFT		= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
## Base sources section ##
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
SOURCES   = $(patsubst %.c,%,$(notdir $(wildcard $(SRC_DIR)*.c)))
## MLX utils sources section ##
MLXUTILS_SRC_DIR= ./src/mlx_utils/
MLXUTILS_OBJ_DIR= ./obj/mlx_utils/
MLXUTILS_SOURCES= $(patsubst %.c,%,$(notdir $(wildcard $(MLXUTILS_SRC_DIR)*.c)))
SRCS		= $(addsuffix .c, $(addprefix $(SRC_DIR), $(SOURCES)))           \
$(addsuffix .c, $(addprefix $(MLXUTILS_SRC_DIR), $(MLXUTILS_SOURCES)))
OBJS		= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(SOURCES)))           \
$(addsuffix .o, $(addprefix $(MLXUTILS_OBJ_DIR), $(MLXUTILS_SOURCES)))
HEADERS = $(wildcard ./includes/*.h)
LIBRARIES = -L./libft -L./libmlx -lft -lmlx -lm -lXext -lX11


#############
## Targets ##
#############
usage:
	@echo "Usage: make [usage | all | $(NAME) | clean | fclean | re]"
	@echo
	@echo "-- Usage --"
	@echo "\tusage: displays this message"
	@echo
	@echo "-- $(NAME) build targets --"
	@echo "\tall: compiles client and server"
	@echo "\t$(NAME): compiles $(NAME) program"
	@echo "\tclean: remove object files"
	@echo "\tfclean: remove object files and programs"
	@echo "\tre: combines fclean and all"

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBRARIES)

$(OBJS): $(SRCS)

$(LIBFT):
	(cd $(LIBFT_DIR) && make)

$(OBJ_DIR)%o: $(SRC_DIR)%c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(MLXUTILS_OBJ_DIR)%o: $(MLXUTILS_DIR)%c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	(cd $(LIBFT_DIR) && make clean)
	$(RM) $(OBJS)

fclean: clean
	(cd $(LIBFT_DIR) && make fclean)
	$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re $(NAME) usage

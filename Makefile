# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/09/29 11:28:40 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all bonus clean fclean re re_bonus run lib

YELLOW	:= \033[0;33m
RED	:= \033[31m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:=		main.c \
					parse_map.c \
					parse_texture.c \
					reef.c \
					debug.c

#SRCS_BONUS	:=

#*------------------------------------------------------------------------------*

SRCS_D		:=	sources/

#SRCS_B		:=	sources/bonus/

OBJS_D		:=	objs/

#OBJS_B_D	:=	objs_bonus/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

#OBJS_B		:=	$(SRCS_BONUS:%.c=$(OBJS_B_D)%.o)

#*------------------------------------------------------------------------------*

HEAD		:=	includes/cube.h \

#HEAD_BONUS	:=	includes/minishell_bonus.h \

HEAD_D		:=	.

#*------------------------------------------------------------------------------*

CFLAGS		:=	-Wall -Wextra -Werror -g3

#*------------------------------------------------------------------------------*

NAME		:=	cube

VFLAGS		=	--leak-check=full --show-leak-kinds=all

#NAME_B		:=	minishell_bonus

#*------------------------------------------------------------------------------*

LIBFT		=	Libft/

LIBFT_A		=	$(addprefix $(LIBFT), libft_ex.a)

#*------------------------------------------------------------------------------*

MLX			:=	libmlx.a

MLX_D		:=	mlx_linux/

MLX_F		:=	-L$(MLX_D) -L/usr/lib -lmlx -lXext -lX11 -lm -lz

MLX_H		:=	$(MLX_D)mlx.h

MLX_A		:=	$(addprefix $(MLX_D), $(MLX))

#*------------------------------------------------------------------------------*


all			:	lib
				@$(MAKE) --no-print-directory $(NAME)

lib			:
				$(MAKE) --no-print-directory -C $(MLX_D)

#bonus		:
#				@$(MAKE) --no-print-directory $(NAME_B)

#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS_D) $(OBJS) $(MLX_A) $(LIBFT_A) $(HEAD)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_A) $(MLX_F) -Lft_ex $(LIBFT_A) -lreadline
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"

#$(NAME_B)	:	$(OBJS_B_D) $(OBJS_B) $(LIBFT_A) $(HEAD_BONUS)
#				@$(CC)  -o $(NAME_B) $(OBJS_B)  -Lft_ex $(LIBFT_A)
#				@echo "$(YELLOW)$(NAME_B) successfully built!$(NC)"

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD) $(MLX_H)
				@echo "$(YELLOW)Compiling $<, depends on $(HEAD)...$(NC)"
				@$(CC) $(CFLAGS) -Iincludes -I$(LIBFT)/includes -c $< -o $@

#$(OBJS_B)	:	$(OBJS_B_D)%.o: $(SRCS_B)%.c $(HEAD_BONUS)
#				@echo "$(YELLOW)Compiling $<, depends on $(HEAD_BONUS)...$(NC)"
#				@$(CC) $(CFLAGS) -Iincludes -I$(LIBFT)/includes -c $< -o $@

$(LIBFT_A):
				@$(MAKE) -s --no-print-directory -C $(LIBFT)

$(OBJS_D)	:
				@mkdir -p $(dir $(OBJS))

#$(OBJS_B_D)	:
#				@mkdir -p $(OBJS_B_D)

#*------------------------------------------------------------------------------*

clean		:
				@$(RM) -r $(OBJS) $(OBJS_D) $(OBJS_B) $(OBJS_B_D)
				@$(MAKE) clean -s --no-print-directory -C $(LIBFT)
				@$(MAKE) clean -C mlx_linux
				@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)
				@$(MAKE) fclean -s --no-print-directory -C $(LIBFT)
				@$(MAKE) clean -C mlx_linux
				@echo "$(YELLOW)Full clean complete$(NC)"

re			:	fclean all


valgrind	:
				make && valgrind $(VFLAGS) ./$(NAME) maps/map.cub

run:
				make && ./$(NAME) maps/map.cub

#re_bonus	:	fclean bonus



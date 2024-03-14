# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 18:52:03 by mel-meka          #+#    #+#              #
#    Updated: 2024/03/14 01:23:43 by mel-meka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar rc
RM = rm -f

LIBFT_SRCS = libft/ft_isalpha.c		libft/ft_toupper.c		\
			 libft/ft_isdigit.c		libft/ft_tolower.c		\
			 libft/ft_isalnum.c		libft/ft_strchr.c		\
			 libft/ft_isascii.c		libft/ft_strrchr.c		\
			 libft/ft_isprint.c		libft/ft_strncmp.c		\
			 libft/ft_strlen.c		libft/ft_memchr.c		\
			 libft/ft_memset.c		libft/ft_memcmp.c		\
			 libft/ft_bzero.c		libft/ft_strnstr.c		\
			 libft/ft_memcpy.c		libft/ft_atoi.c			\
			 libft/ft_memmove.c								\
			 libft/ft_strlcpy.c		libft/ft_calloc.c		\
			 libft/ft_strlcat.c		libft/ft_strdup.c		\
			 \
			 libft/ft_substr.c			\
			 libft/ft_strjoin.c			\
			 libft/ft_strtrim.c			\
			 libft/ft_split.c			\
			 libft/ft_itoa.c			\
			 libft/ft_strmapi.c			\
			 libft/ft_striteri.c		\
			 libft/ft_putchar_fd.c		\
			 libft/ft_putstr_fd.c		\
			 libft/ft_putendl_fd.c		\
			 libft/ft_putnbr_fd.c		\
			   libft/ft_lstnew_bonus.c			\
			   libft/ft_lstadd_front_bonus.c	\
			   libft/ft_lstsize_bonus.c			\
			   libft/ft_lstlast_bonus.c			\
			   libft/ft_lstadd_back_bonus.c		\
			   libft/ft_lstdelone_bonus.c		\
			   libft/ft_lstclear_bonus.c		\
			   libft/ft_lstiter_bonus.c			\
			   libft/ft_lstmap_bonus.c			\

GNL_SRCS = ./get_next_line/get_next_line.c \

FT_PRINTF_SRCS = ./ft_printf/ft_printf.c	\
				 ./ft_printf/ft_put_hex.c	\
				 ./ft_printf/ft_put_str.c	\
				 ./ft_printf/put_int.c		\
				 ./ft_printf/ft_putchar.c	\

FDF_SRCS = fdf.c			\
		   fdf_err.c		\
		   fdf_clean.c		\
		   load_map.c		\
		   load_map_utils.c	\
		   draw_map.c		\
		   draw_line.c		\
		   draw_utils.c		\
		   draw_point.c		\
		   transform.c		\
		   input.c

BONUS_SRCS=bonus/fdf_bonus.c			\
		   bonus/fdf_err_bonus.c		\
		   bonus/fdf_clean_bonus.c		\
		   bonus/load_map_bonus.c		\
		   bonus/load_map_utils_bonus.c	\
		   bonus/draw_map_bonus.c		\
		   bonus/draw_line_bonus.c		\
		   bonus/draw_utils_bonus.c		\
		   bonus/draw_point_bonus.c		\
		   bonus/transform_bonus.c		\
		   bonus/input_bonus.c			\
		   bonus/animation_bonus.c

FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
FDF_OBJS = $(FDF_SRCS:.c=.o)
SRCS = $(GNL_SRCS) $(LIBFT_SRCS) $(FT_PRINTF_SRCS)
OBJS = $(SRCS:.c=.o)
FDF_OBJS = $(FDF_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCLUDES = -I libft -I minilibx-linux -I get_next_line


NAME = fdf

BONUS = fdf_bonus

LIBS = -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror -O3 $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(FDF_OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)


$(FDF_OBJS): $(FDF_SRCS)
	$(CC) $(CFLAGS) $(FDF_SRCS) -c $(INCLUDES)

bonus: $(BONUS)


$(BONUS): $(OBJS) $(MLX) $(BONUS_OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)


clean:
	$(RM) $(OBJS) $(FDF_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

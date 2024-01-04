# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 18:52:03 by mel-meka          #+#    #+#              #
#    Updated: 2023/12/22 21:57:50 by mel-meka         ###   ########.fr        #
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

FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
FDF_OBJS = $(FDF_SRCS:.c=.o)
SRCS = $(GNL_SRCS) $(LIBFT_SRCS) $(FT_PRINTF_SRCS)
OBJS = $(SRCS:.c=.o)
FDF_OBJS = $(FDF_SRCS:.c=.o)

INCLUDES = -I libft -I minilibX_macos -I get_next_line


NAME = fdf

MLX = minilibX_macos/libmlx.a
FRAMEWORKS = -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror -O2

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(FDF_OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(FRAMEWORKS)

$(MLX): minilibX_macos/*.c minilibX_macos/*.m
	(cd minilibX_macos && make)

$(FDF_OBJS): $(FDF_SRCS)
	$(CC) $(CFLAGS) $(FDF_SRCS) -c $(INCLUDES)



clean:
	$(RM) $(OBJS) $(FDF_OBJS)
	(cd minilibX_macos && make clean)

fclean: clean
	$(RM) $(NAME)

re: fclean all

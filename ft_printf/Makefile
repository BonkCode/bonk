# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/10 19:04:19 by rtrant            #+#    #+#              #
#    Updated: 2020/05/24 19:03:25 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_HEADER = -I libft
SRCS = ft_directive.c ft_get_char_print.c ft_get_int_print.c ft_get_pointer_print.c ft_get_string_print.c ft_get_unsigned_int_print.c ft_printfutils.c main.c
OBJS = ft_directive.o ft_get_char_print.o ft_get_int_print.o ft_get_pointer_print.o ft_get_string_print.o ft_get_unsigned_int_print.o ft_printfutils.o main.o
LIBFT_OBJS =  ft_atoi.o ft_bzero.o ft_isalpha.o ft_isascii.o \
        ft_isdigit.o ft_isprint.o ft_memcmp.o ft_memcpy.o ft_memmove.o \
        ft_memset.o ft_strlcpy.o ft_strlen.o ft_tolower.o ft_toupper.o \
        ft_strnstr.o ft_isalnum.o ft_memccpy.o ft_strrchr.o ft_strchr.o \
        ft_memchr.o ft_calloc.o ft_strdup.o ft_strncmp.o ft_strlcat.o \
        ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o \
        ft_strmapi.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o

all: $(NAME)

$(NAME):
	@echo "Compiling libft..."
	@make -C $(LIBFT_PATH) > /dev/null
	@echo "Copying libft ---> root..."
	@cp $(LIBFT_PATH)$(LIBFT_NAME) .
	@cp $(LIBFT_PATH)/*.o .
	@echo "Compiling project with libft..."
	@gcc -Wall -Wextra -Werror -c $(SRCS) $(LIBFT_HEADER)
	@ar rcs $(NAME) $(OBJS) $(LIBFT_OBJS)
	@make clean > /dev/null
	@echo "Project compilation complete!"

clean:
	@rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	@rm -f $(NAME) $(LIBFT_NAME)

re: fclean all
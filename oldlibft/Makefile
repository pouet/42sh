# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 10:58:46 by nchrupal          #+#    #+#              #
#    Updated: 2016/01/25 14:15:53 by nchrupal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	   ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c\
	   ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c\
	   ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c\
	   ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c\
	   ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c\
	   ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c\
	   ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c\
	   ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c\
	   ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c\
	   ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c\
	   ft_tolower.c ft_toupper.c ft_isblank.c ft_islower.c ft_ispunct.c\
	   ft_isspace.c ft_isupper.c ft_isxdigit.c ft_lstpushback.c\
	   ft_lstpushfront.c ft_lstclear.c ft_qsort.c ft_lstsort.c\
	   dll_createnode.c dll_dellist.c dll_delnode.c dll_insertat.c\
	   dll_newlist.c dll_pushback.c dll_pushfront.c
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIB_NAME = libft.a
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%-50s" "linking library $@..."
	@$(AR) rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "%-50s" "compiling "$(notdir $<)...
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\e[1;32m[OK]\e[0m\n"

clean:
	@printf "%-50s" "deleting objects..." 
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_PATH)
	@printf "\e[1;32m[OK]\e[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@$(RM) $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

re: fclean all

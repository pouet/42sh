# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 10:58:46 by nchrupal          #+#    #+#              #
#    Updated: 2016/02/04 10:20:03 by nchrupal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = dou_p_args.c ft_printf.c int_args.c int_form.c s_args.c subfmt.c\
		   treat_args.c colors.c fd.c
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/ ./libft/includes/
LIB_PATH = ./libft/
LIB_NAME = libft.a
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra
NAME = libftprintf.a

.PHONY: all clean fclean re libft

all: libft $(NAME)

libft:
	@printf "/--------------- creating library \e[1;36m$@\e[0m... ----------/\n"
	@make -C $(LIB_PATH)
	@printf "%-50s\n" "/---------------- library $@ created... ----------/"

$(NAME): $(OBJ)
	@printf "%-50s" "linking library $@..."
	@$(AR) rc tmp $(OBJ)
	@libtool -static -o $(NAME) $(LIB) tmp
	@$(RM) tmp
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

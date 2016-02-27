# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 10:58:46 by nchrupal          #+#    #+#              #
#    Updated: 2016/02/25 10:46:27 by nchrupal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = $(sort main.c lexer.c parser.c ft_env.c expand.c error.c\
		   process_cmd.c get_opts.c ft_setenv.c ft_cd.c ft_exit.c\
		   redirections.c events.c xmalloc.c colors.c initterms.c tty.c\
		   print.c read_line.c history.c clipboard.c)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
PRINTF_PATH = ./ft_printf/
INC_PATH = ./includes/ $(LIBFT_PATH)includes/ $(PRINTF_PATH)includes/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = $(addprefix -L,$(LIBFT_PATH) $(PRINTF_PATH))
LDLIBS = -lft -lftprintf -ltermcap
NAME = 42sh

.PHONY: all clean fclean re libft ft_printf

all: libft ft_printf $(NAME)

libft:
	@printf "/--------------- creating library \e[1;36m$@\e[0m... ----------/\n"
	@make -C $(LIBFT_PATH)
	@printf "/---------------- library $@ created... ----------/\n"

ft_printf:
	@printf "/------------- creating library \e[1;36m$@\e[0m... --------/\n"
	@make -C $(PRINTF_PATH)
	@printf "/-------------- library $@ created... --------/\n"

$(NAME): $(OBJ)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME) -g3 -gdwarf-2 -O0
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

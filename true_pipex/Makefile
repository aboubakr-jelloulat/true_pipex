NAME         = pipex
BONUS_NAME   = pipex_bonus


CC           = cc
CFLAGS       = -Wall -Wextra -Werror -fsanitize=address
RM           = rm -f

HEADER       = ./includes/pipex.h
BONUS_HEADER = ./includes/pipex_bonus.h


LIBFT        = ./includes/libft/libft.a


SRCS         = src/pipex.c 		src/pipex_utils.c 		src/main.c
BONUS        = bonus_src/main_bonus.c 		bonus_src/pipex_bonus.c 	bonus_src/pipex_utils_bonus.c 	bonus_src/get_next_line_bonus.c


OBJ_SRCS     = $(SRCS:.c=.o)
OBJ_BONUS    = $(BONUS:.c=.o)


all: $(NAME)


$(NAME): $(OBJ_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT) -o $(NAME)


bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(BONUS_NAME)


%.o: %.c $(HEADER) $(BONUS_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
	
	@$(MAKE) -C ./includes/libft

clean:
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJ_SRCS) $(OBJ_BONUS)


fclean: clean
	@$(MAKE) fclean -C ./includes/libft
	@$(RM) $(NAME) $(BONUS_NAME)


re: fclean all

re_bonus: fclean bonus


.PHONY: all bonus clean fclean re re_bonus

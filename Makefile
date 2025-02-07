CC = cc
CFLAGS = -Wall -Werror -Wextra
file = pipex.c \
	   pipex_utls.c
Bfile = pipex_bonus.c \
		pipex_utls_bonus.c \
		pipex_utls_bonus2.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJ = $(file:.c=.o)
BOBJ = $(Bfile:.c=.o)
NAME = pipex

all: $(NAME)
	
$(NAME): $(OBJ) libft/libft.h
	@make -s -C libft
	cc $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

bonus : $(BOBJ) libft/libft.h get_next_line/get_next_line.h
	@make -s -C libft
	cc $(CFLAGS) $(BOBJ) libft/libft.a  -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ) $(BOBJ)
	@make -s fclean -C libft

fclean: clean
	rm -f $(NAME)
	@make -s fclean -C libft 

re: fclean all

.PHONY : clean
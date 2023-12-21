all:
	cc -Wall -Wextra -Werror -o ft_printf.o -c ft_printf.c
	ar rcs libftprintf.a ft_printf.o
clean:
	rm -rf ft_printf.o
fclean:
	rm -rf ft_printf.o libftprintf.a
re: fclean all
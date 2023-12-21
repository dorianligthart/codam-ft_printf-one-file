/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:17:50 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/21 19:26:15 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RESET "\033[0m"		//4
#define BLACK "\033[0;30m"	//7
#define RED "\033[0;31m"	//7
#define GREEN "\033[0;32m"	//7
#define YELLOW "\033[0;33m"	//7
#define BLUE "\033[0;34m"	//7
#define MAGENTA "\033[0;35m"//7
#define CYAN "\033[0;36m"	//7
#define WHITE "\033[0;37m"	//7

// https://patorjk.com/software/taag/
#define PRINTF_ASCII_ART \
"###########################################################################\n"\
"#     ____       ____                     _   _       _____     _____     #\n"\
"#  h |  _\"\\ e y |  _\"\\  !      ___       | \\ |\"|     |_ \" _|   |\" ___|    #\n"\
"#   \\| |_) |/  \\| |_) |/      |_\"_|     <|  \\| |>      | |    i| |_  th   #\n"\
"#    |  __/     |  _ <         | |      v| |\\  |e     /| |\\   \\|  _|/     #\n"\
"#    |_|        |_| \\_\\      h/| |\\a     |_| \\_|     f |_| a   |_|        #\n"\
"#    ||>>_      //   \\\\_  .-,_|___|_,-.  ||   \\\\,-.  _// \\\\_   )(\\\\,-     #\n"\
"#   (__)__)    (__)  (__)  \\_)-' '-(_/   (_\")  (_/  (__) (__) (__)(_/     #\n"\
"#                                                                         #\n"\
"#     _____   y _____ o   ____       _____   l _____ f    ____            #\n"\
"#    |_ \" _|  \\| ___\"|/  / __\"| r   |_ \" _|  \\| ___\"|/ ! |  _\"\\ !         #\n"\
"#      | |     |  _|\"   <\\___ \\/      | |     |  _|\"    \\| |_) |/         #\n"\
"#     /| |\\    | |___    u___) |     /| |\\    | |___     |  _ <           #\n"\
"#    i |_|n    |_____|   |____/>>   s |_|e    |_____|    |_| \\_\\          #\n"\
"#    _// \\\\_   <<   >>    )(  (__)  _// \\\\_   <<   >>    //   \\\\_         #\n"\
"#   (__) (__) (__) (__)  (__)      (__) (__) (__) (__)  (__)  (__)        #\n"\
"#                                                                         #\n"\
"#  simple main that checks return values.      by: github/dorianligthart  #\n"\
"#                   and prints output.                                    #\n"\
"###########################################################################"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include "ft_printf.h"
#include <string.h>
#include <unistd.h>

static int	ft_putint(int nbr)
{
	char	basestr[] = "0123456789";
	int		divider;
	char	put[21];
	int		y;

	if (nbr == INT_MIN)
		return(write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	divider = 1;
	while (divider <= nbr / 10)
		divider = divider * 10;
	y = 0;
	while (divider)
	{
		put[y] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / 10;
		y++;
	}
	put[y] = '\0';
	y = write(1, put, y);
	return (-1 + (y >= 0) * (y + 1));
}

static void	print10argdiff(char *form,
	void *arg1, void *arg2, void *arg3, void *arg4, void *arg5,
	void *arg6, void *arg7, void *arg8, void *arg9, void *arg10)
{
	write(1, "\'"YELLOW, 9);
	if (form)
		write(1, form, strlen(form));
	write(1, RESET"\':", 6);
		
		write(1, "\nprintf:    \'", 13);
		int x = printf(form, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		fflush(stdout);
		write(1, "\'-->", 4);
		ft_putint(x);
		
		write(1, "\nft_printf: \'", 13);
		int y = ft_printf(form, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		fflush(stdout);
		write(1, "\'-->", 4);
		ft_putint(y);

		if (x != y)
			write(1, RED"\t\tdifference!"RESET"\n\n", 26);
		else
			write(1, "\t\t"GREEN"OK."RESET"\n\n", 17);
}

static void	print1argdiff(char *form, void *arg)
{
	write(1, "\'"YELLOW, 9);
	if (form)
		write(1, form, strlen(form));
	write(1, RESET"\':", 6);
		
		write(1, "\nprintf:    \'", 13);
		int x = printf(form, arg);
		fflush(stdout);
		write(1, "\'-->", 4);
		ft_putint(x);
		
		write(1, "\nft_printf: \'", 13);
		int y = ft_printf(form, arg);
		fflush(stdout);
		write(1, "\'-->", 4);
		ft_putint(y);

		if (x != y)
			write(1, RED"\t\tdifference!"RESET"\n", 26);
		else
			write(1, "\t\t"GREEN"OK."RESET"\n", 17);
}

//TESTER:
int	main(void)
{
printf(CYAN PRINTF_ASCII_ART RESET"\n\n");
write(1, "\n"BLUE"[format string test]"RESET"\n", 34);
//UB segfault check:
	print1argdiff("%zbcd", NULL);
	print1argdiff("%", NULL);
	print1argdiff("abcd%", NULL);
	print1argdiff("%%%", NULL);
	print1argdiff("abcd%%%", NULL);
	print1argdiff("%%%abcd", NULL);
//no UB check:
	print1argdiff("", NULL);
	print1argdiff("\0", NULL);
	print1argdiff(NULL, NULL);
	print1argdiff("6", NULL);
	print1argdiff("abcd", NULL);
	print1argdiff("%%", NULL);
	print1argdiff("%%abcd", NULL);
	print1argdiff("abcd%%", NULL);
	
	int	i = 0;
//c: flags="-", fieldwidth.
write(1, "\n"BLUE"[c conversion]"RESET"\n", 28);
	while (++i < 128)
		print1argdiff("%c", (void *)i);

//s: flags="-", fieldwidth, precision.
write(1, "\n"BLUE"[s conversion]"RESET"\n", 28);
	print1argdiff("%s", (void *)"");
	print1argdiff("%s", (void *)"\0");
	print1argdiff("%s", (void *)NULL);
	print1argdiff("%s", (void *)"6");
	print1argdiff("%s", (void *)"abcd");

//p: flags="-", fieldwidth, precision==0.
write(1, "\n"BLUE"[p conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 20)
		print1argdiff("%p", (void *)(ULONG_MAX - 10 + i));

//di: flags="-+ 0", fieldwidth, precision.
write(1, "\n"BLUE"[di conversion]"RESET"\n", 29);
	print1argdiff("%i", (void *)-1);
	print1argdiff("%i", (void *)0);
	print1argdiff("%i", (void *)1);
	print1argdiff("%i", (void *)10);
	i = -1;
	while (++i < 20)
		print1argdiff("%i", (void *)(INT_MAX - 10 + i));

//u: flags="-0", fieldwidth, precision.
write(1, "\n"BLUE"[u conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 20)
		print1argdiff("%u", (void *)(UINT_MAX - 10 + i));

//x: flags="-#0", fieldwidth, precision.
write(1, "\n"BLUE"[x conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 20)
		print1argdiff("%x", (void *)(ULONG_MAX - 10 + i));
	
//X: flags="-#0", fieldwidth, precision.
write(1, "\n"BLUE"[X conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 20)
		print1argdiff("%X", (void *)(ULONG_MAX - 10 + i));
	
	print10argdiff("evaluator try 10 args here for fun :)"
		"%d %d %d %d %d %d %d %d %d %d",
		(void *)42, (void *)442, (void *)42, (void *)42, (void *)42, (void *)42, (void *)42, (void *)42, (void *)42, (void *)42);
	return (0);
}
/*
make re && cc tester.c libftprintf.a -o printf && ./printf
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:44:30 by dligthar          #+#    #+#             */
/*   Updated: 2023/12/21 17:21:13 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static char *ft_strchr(const char *str, char c, int i)
{
	while (str && str[++i])
		if (str[i] == (unsigned char)c)
			return ((char *)(str + i));
	if (str && (unsigned char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

static int	puint(int fd, unsigned long nbr, char *basestr)
{
	unsigned long	divider;
	int				base;
	int				i;
	char			put[64];

	base = 0;
	while (basestr && basestr[base])
	if (base < 2)
		return (-1);
	divider = 1;
	while (divider <= nbr / base)
		divider = divider * base;
	i = 0;
	while (divider)
	{
		put[i] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / base;
		i++;
	}
	put[i] = '\0';
	return (write(fd, put, i));
}

static int	newformat2(int fd, const char **format, va_list *list, int tmp)
{
	int	nbr;

	if (**format == 'p' && *format++)
	{
		tmp = write(fd, "0x", 2);
		if (tmp < 2)
			return (-1);
		return (tmp	+ puint(fd, va_arg(*list, long), "0123456789abcdef"));
	}
	else if ((**format == 'd' || **format == 'i') && *format++)
	{
		nbr = va_arg(*list, int);
		if (nbr < 0)
		{
			tmp = write(fd, "-", 1);
			nbr *= -1;
		}
		nbr = puint(fd, nbr, "0123456789");
		return (-1 + (tmp >= 0 && nbr >= 0) * (tmp + nbr + 1));
	}
	else if (**format == 'u' && *format++)
		return (puint(fd, va_arg(*list, unsigned int), "0123456789"));
	return (0);
}

static int	newformat(int fd, const char **format, va_list *list, int tmp)
{
	char	*s;

	if (!ft_strchr("cspdiuxX%", **format, -1))
		return (0);
	if (**format == '%' && *format++)
		return (write(fd, "%", 1));
	else if (**format == 'c' && *format++)
	{
		tmp = va_arg(*list, int);
		return (write(fd, &tmp, 1));
	}
	else if (**format == 's' && *format++)
	{
		s = va_arg(*list, char *);
		if (!s)
			return (write(fd, "(null)", 6));
		while (s[tmp])
			tmp++;
		return (write(fd, s, tmp));
	}
	else if (**format == 'x' && *format++)
		return (puint(fd, va_arg(*list, unsigned int), "0123456789abcdef"));
	else if (**format == 'X' && *format++)
		return (puint(fd, va_arg(*list, unsigned int), "0123456789ABCDEF"));
	return (newformat2(fd, format, list, 0));
}

int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			printed;
	int			x;
	int			y;
	const char	*tmp;

	if (!format)
		return (-1);
	va_start(list, format);
	printed = 0;
	while (*format)
	{
		tmp = format;
		while (*format && *format != '%')
			format++;
		x = write(1, tmp, format - tmp);
		y = 0;
		if (*format == '%' && format++)
			y = newformat(1, &format, &list, 0);
		if (y < 0 || x < 0)
			return (-1);
		printed = printed + x + y;
	}
	va_end(list);
	return (printed);
}

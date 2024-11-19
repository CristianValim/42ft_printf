/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:26:49 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/11/19 14:32:49 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_arguments(const char *format_string, va_list args);
int	print_arguments(long n, long base, int uppercase, int is_pointer);
int	ft_putstr(char *s);

/* Processes a format string and a variable number of
arguments, printing the formatted output to the standard output.
(const char *format_string)	> The format string.
return (count)				> The total number of characters written. */
int	ft_printf(const char *format_string, ...)
{
	va_list	args;
	int		count;

	va_start(args, format_string);
	count = 0;
	while (*format_string)
	{
		if (*format_string == '%')
		{
			format_string++;
			count += parse_arguments(format_string, args);
		}
		else
		{
			count += write(1, format_string, 1);
		}
		format_string++;
	}
	va_end(args);
	return (count);
}

/* Parses the arguments based on the format specifier.
(const char *type)	> The format specifier.
(va_list args)		> The list of arguments.
return (count)		> The number of characters written. */
int	parse_arguments(const char *type, va_list args)
{
	int	count;
	int	c;

	count = 0;
	if (*type == 'c')
	{
		c = va_arg(args, int);
		count += write(1, &c, 1);
	}
	else if (*type == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*type == 'p')
		count += print_arguments((unsigned long)va_arg(args, void *), 16, 0, 1);
	else if (*type == 'd' || *type == 'i')
		count += print_arguments(va_arg(args, int), 10, 0, 0);
	else if (*type == 'u')
		count += print_arguments(va_arg(args, unsigned int), 10, 0, 0);
	else if (*type == 'x')
		count += print_arguments(va_arg(args, unsigned int), 16, 0, 0);
	else if (*type == 'X')
		count += print_arguments(va_arg(args, unsigned int), 16, 1, 0);
	else if (*type == '%')
		count += write(1, "%", 1);
	return (count);
}

/* Converts argument to the specified base and writes it to the standard
output.
(long n)		> The number to be converted
(long base)		> The base
(int uppercase)	> The flag to convert to uppercase
(int is_pointer)> The flag to convert to a pointer
return (count)	> The number of characters written. */
int	print_arguments(long n, long base, int uppercase, int is_pointer)
{
	char			*base_str;
	int				count;
	unsigned long	nbr;

	count = 0;
	nbr = (unsigned long)n;
	if (!n && is_pointer)
		return (ft_putstr("(nil)"));
	if (n < 0 && base == 10)
	{
		count += write(1, "-", 1);
		nbr = -n;
	}
	if (is_pointer)
		count += write(1, "0x", 2);
	if (uppercase)
		base_str = "0123456789ABCDEF";
	else
		base_str = "0123456789abcdef";
	if (nbr >= (unsigned long)base)
		count += print_arguments(nbr / base, base, uppercase, 0);
	count += write(1, &base_str[nbr % base], 1);
	return (count);
}

/* Writes the string s to the standard output.
(char *s)		> The string to be written.
return 			> The number of characters written. */
int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
		count += write(1, s++, 1);
	return (count);
}

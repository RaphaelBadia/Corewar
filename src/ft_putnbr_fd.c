/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 17:57:36 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/05 18:35:21 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
	return ;
}

void	ft_putstr_fd(int fd, const char *s)
{
	while (*s)
		ft_putchar_fd(fd, *s++);
}

void	ft_putnbr_fd(int fd, int n)
{
	if (n > 9)
	{
		ft_putnbr_fd(fd, n / 10);
		ft_putchar_fd(fd, n % 10 + 0x30);
	}
	else if (n == -2147483648)
		ft_putstr_fd(fd, "-2147483648");
	else if (n < 0)
	{
		ft_putchar_fd(fd, '-');
		ft_putnbr_fd(fd, -n);
	}
	else if (n < 10)
		ft_putchar_fd(fd, n % 10 + 0x30);
}

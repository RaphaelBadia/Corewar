/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:50:26 by jye               #+#    #+#             */
/*   Updated: 2017/03/14 22:45:07 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

static int	get_to_stack(char **stack, char *buff)
{
	char	*ptr;

	if ((ptr = *stack))
	{
		if ((*stack = ft_strjoin(ptr, buff)) == NULL)
			return (1);
		free(ptr);
	}
	else
	{
		if ((*stack = ft_strnew(ft_strlen(buff))) == NULL)
			return (1);
		ft_strcpy(*stack, buff);
	}
	return (0);
}

static int	line__(char **line, char **stack)
{
	char			*ptr;
	unsigned long	llen;
	unsigned long	slen;

	if (*stack == NULL)
		return (0);
	if ((ptr = ft_strchr(*stack, 0xa)) == NULL)
		return (0);
	llen = ptr - *stack;
	slen = ft_strlen(*stack);
	if ((*line = ft_strnew(llen)) == NULL)
		return (1);
	ft_memcpy(*line, *stack, llen);
	ptr = *stack;
	if ((*stack = ft_strnew(slen - llen)) == NULL)
	{
		*stack = ptr;
		return (1);
	}
	ft_memcpy(*stack, ptr + llen + 1, slen - llen);
	free(ptr);
	return (1);
}

static int	ret_val(char **stack, char **line)
{
	if (*stack == NULL)
		return (0);
	if (**stack)
	{
		*line = *stack;
		*stack = NULL;
		return (1);
	}
	else
	{
		free(*stack);
		return (0);
	}
}

int			get_next_line(const int fd, char **line)
{
	static char	*stack = NULL;
	char		buff[BUFF_SIZE + 1];
	int			ret;

	if (line__(line, &stack))
	{
		if (line == NULL)
			return (-1);
		return (1);
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		if (get_to_stack(&stack, buff))
			return (-1);
		if (line__(line, &stack))
			return (1);
	}
	return (ret_val(&stack, line));
}

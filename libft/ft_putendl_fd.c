/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:26:11 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:44:12 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Output the string ’s’ with a newline to the specified file descriptor. */
void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	write(fd, "\n", 1);
}

/* int	main(void)
{
	ft_putendl_fd("ABCdef", 1);
	return (0);
} */

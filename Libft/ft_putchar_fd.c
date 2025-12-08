/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:00:48 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/26 13:18:18 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Output the character ’c’ to the specified file descriptor. */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* 
// To see differences in fd, redirect stdout and stderr to different locations:
// ./a.out > output.txt 2> error.txt
int	main(void)
{
	ft_putchar_fd('A', 1);  // Writes 'A' to standard output
    ft_putchar_fd('B', 2);  // Writes 'B' to standard error
	return (0);
} 
*/

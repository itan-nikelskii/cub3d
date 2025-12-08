/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:33 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 14:11:12 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Set the first n bytes of a block of memory pointed to by ptr to 0. */
void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)ptr;
	while (n > 0)
	{
		*byte_ptr = 0;
		byte_ptr++;
		n--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:07:08 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/09 14:19:44 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Convert a string pointed to by nptr into its whole numeric representation. 
The number can be preceded by any amount of whitespace (gets discarded) and an
optional single positive or negative sign. If a non-digit is encountered after
a digit, the rest is ignored and the integer up until that point is returned.
Return 0 on error. 
Undefined behavior if the would-be-represented value is out of the int range. */
int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + sign * (*nptr - '0');
		nptr++;
	}
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	int	result = ft_atoi(" --+--+1234ab567");
	printf("%d\n", result);
	return (0);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:15:46 by inikelsk          #+#    #+#             */
/*   Updated: 2025/05/06 13:51:21 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count the number of digits of n by repeatedly dividing it by base. Note that
count = 1 account for all single-digit numbers. */
static int	count_digits(long long n, int base)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
	}
	while (n >= base)
	{
		n /= base;
		count++;
	}
	return (count);
}

/* Convert a long long into a number of a specified base (up to base-16) and
return a string representation of that number. NOTE: overflow is NOT handled. */
char	*ft_basetoa(long long n, int base, int uppercase)
{
    int		is_negative;
	int		len;
    char	*symbols;
	char	*result;

    if (uppercase)
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	is_negative = (n < 0);
    len = count_digits(n, base) + is_negative;
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
	result[len] = '\0';
	if (n < 0)
		n = -n;
    while (len-- > is_negative)
    {
        result[len] = symbols[n % base];
        n /= base;
    }
	if (is_negative)
		result[0] = '-';
    return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:26:41 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/23 12:19:30 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Check whether c is an uppercase letter (A-Z). */
static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

/* Check whether c is a lowercase letter (a-z). */
static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

/* Check whether c is an alphabetic character. */
int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

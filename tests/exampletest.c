/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exampletest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:37 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/24 17:52:40 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

// Test(misc, failing) {
// 	cr_assert(0);
// }

Test(misc, passing) {
	cr_assert(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:38:56 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/31 14:26:08 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define W_KEY 13
#  define ESC_KEY 53
# endif

# ifdef __linux__
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define W_KEY 119
#  define ESC_KEY 65307
# endif

#endif // KEYS_H

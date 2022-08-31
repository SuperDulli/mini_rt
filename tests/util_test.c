/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:25:07 by chelmerd          #+#    #+#             */
/*   Updated: 2022/08/30 19:30:35 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/theories.h>
#include <criterion/new/assert.h>
#include <limits.h>

#include "../mini_rt.h"

#define ULP_UNITS 4

#define GARBAGE_STRINGS "--", "++", "abc", "0+0", "1e6", "-2,0", "2."
#define INTS_AS_STRINGS "0", "1", "2", "255", "-1", "-2", "-255"
#define FLOATS_AS_STRINGS "0.0", "0.333", "0.5", "1.0", "255.0", "-1.0", "-255.0", "-255.1"

TheoryDataPoints(numbers, check_int_success) =
{
	DataPoints(char *, INTS_AS_STRINGS)
};

Theory((char * str), numbers, check_int_success)
{
	int	is_int;
	int	result;

	is_int = check_int(str);
	cr_expect(zero(int, is_int), "is_int: false negative for %s.", str);
	result = ft_atoi(str);
	cr_expect(eq(int, result, atoi(str)), "ft_atoi should give the same result as atoi.");
}

TheoryDataPoints(numbers, check_int_fail) =
{
	DataPoints(char *, FLOATS_AS_STRINGS, GARBAGE_STRINGS)
};

Theory((char * str), numbers, check_int_fail)
{
	int	is_int;

	is_int = check_int(str);
	cr_expect(not(zero(int, is_int)), "is_int: false positive for %s.", str);
}

TheoryDataPoints(numbers, check_float_success) =
{
	DataPoints(char *, FLOATS_AS_STRINGS)
};

Theory((char * str), numbers, check_float_success)
{
	int	is_float;

	is_float = check_float(str);
	cr_expect(zero(int, is_float), "is_float: false negative for %s.", str);
}

TheoryDataPoints(numbers, check_float_fail) =
{
	DataPoints(char *, INTS_AS_STRINGS, GARBAGE_STRINGS)
};

Theory((char * str), numbers, check_float_fail)
{
	int		is_float;

	is_float = check_float(str);
	cr_expect(not(zero(int, is_float)), "is_float: false positive for %s.", str);
}

TheoryDataPoints(numbers, str_to_float_success) =
{
	DataPoints(char *, FLOATS_AS_STRINGS, INTS_AS_STRINGS)
};

Theory((char * str), numbers, str_to_float_success)
{
	float	result;
	float	expected;
	int		is_float;
	int		is_int;

	is_float = !check_float(str);
	is_int = !check_int(str);
	if (!is_float && !is_int)
		cr_fatal("string is neither int or float. %s -> %d || %d", str, is_float, is_int);
	// cr_assert(any(zero(int, is_float), zero(int, is_int)), "%s -> %d || %d", str, is_float, is_int);
	result = ft_atof(str);
	expected = atof(str);
	// cr_log_info("ft_atof(%s)=%f == %f", str, result, expected);
	cr_expect(ieee_ulp_eq(flt, result, expected, ULP_UNITS), "ft_atof should give the same result as atof.");
}

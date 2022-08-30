#include <criterion/criterion.h>

#include "../mini_rt.h"

t_obj	*sphere;

void sphere_suite_setup(void)
{
	float	pos[VEC3_SIZE];

	printf("setup\n");
	vec3(0, 0, 0, pos);
	sphere = new_sphere(pos, 0, 1.f);
}

void sphere_suite_teardown(void)
{
	printf("teardown\n");
	// destroy_object(sphere);
}

TestSuite(sphere, .init=sphere_suite_setup, .fini=sphere_suite_teardown);

Test(sphere, create)
{
	printf("test start\n");
	cr_assert(sphere != NULL, "new_sphere should not return NULL");
	printf("test end\n");
}

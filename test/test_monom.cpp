#include "polynom.h"

#include <gtest.h>

TEST(Monom, can_create_empty_monom)
{
	ASSERT_NO_THROW(Monom());
}

TEST(Monom, created_monom_is_empty)
{
	Monom m;
	ASSERT_EQ(m.get_coef(), 0);
	ASSERT_EQ(m.get_deg(), 0);
}

TEST(Monom, can_create_monom_with_deg)
{
	ASSERT_NO_THROW(Monom(1, 123));
}

TEST(Monom, created_monom_is_correct)
{
	Monom m(1, 234);
	ASSERT_EQ(m.get_coef(), 1);
	ASSERT_EQ(m.get_deg(), 234);
}

TEST(Monom, can_create_monom_without_deg)
{
	ASSERT_NO_THROW(Monom(1));
}

TEST(Monom, created_monom_without_deg_is_correct)
{
	Monom m(1);
	ASSERT_EQ(m.get_coef(), 1);
}

TEST(Monom, can_create_monom_with_x_y_z)
{
	ASSERT_NO_THROW(Monom(1, 2, 3, 4));
}

TEST(Monom, created_monom_with_x_y_z_is_correct)
{
	Monom m(1, 2, 3, 4);
	ASSERT_EQ(m.get_coef(), 1);
	ASSERT_EQ(m.get_deg(), 234);
}

TEST(Monom, can_get_coef)
{
	Monom m(1, 234);

	EXPECT_EQ(1, m.get_coef());
}

TEST(Monom, can_get_deg_of_x)
{
	Monom m(1, 234);

	EXPECT_EQ(2, m.deg_x());
}
TEST(Monom, can_get_deg_of_y)
{
	Monom m(1, 234);

	EXPECT_EQ(3, m.deg_y());
}

TEST(Monom, can_get_deg_of_z)
{
	Monom m(1, 234);

	EXPECT_EQ(4, m.deg_z());
}

TEST(Monom, can_get_deg)
{
	Monom m(1, 234);

	EXPECT_EQ(234, m.get_deg());
}


TEST(Monom, can_add_monoms)
{
	Monom m1(1, 234);
	Monom m2(5, 234);

	EXPECT_EQ(Monom(6, 234), m1+m2);
}

TEST(Monom, cant_add_monoms_with_different_degs)
{
	Monom m1(1, 234);
	Monom m2(5, 123);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(Monom, can_sub_monoms)
{
	Monom m1(1, 234);
	Monom m2(5, 234);

	EXPECT_EQ(Monom(-4, 234), m1 - m2);
}

TEST(Monom, cant_sub_monoms_with_different_degs)
{
	Monom m1(1, 234);
	Monom m2(5, 123);

	ASSERT_ANY_THROW(m1 + m2);
}






TEST(Monom, can_calculate_value_at_point)
{
	Monom m(0.5, 234);

	EXPECT_EQ(324, m.point(1, 2, 3));
}

TEST(Monom, can_print_polynom)
{
	Polynom p1(Monom(1, 2, 3, 4));
	Polynom p2(Monom(1, 5, 3, 4));
	p1.add_monom(Monom(1, 2, 3, 4));
	p1.add_monom(Monom(7, 1, 1, 1));
	p1.add_monom(Monom(8, 1, 1, 0));
	p1.print();
	Polynom p = p1 + p2;
	p.print();
	Polynom p3 = p - p2;
	p3.print();
}

//TEST(Monom, can_addmonom)
//{
//	Polynom p;
//	//p.add_monom(Monom(1, 2, 3, 4));
//	p.print();
//}

TEST(Monom, can_addmonom)
{
	Polynom p;
	p.add_monom(Monom(1, 2, 3, 4));
	p.erase_zero();
	p.print();
}

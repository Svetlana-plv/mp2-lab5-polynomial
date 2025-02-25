#include "polynom.h"

#include <gtest.h>

TEST(Polynom, can_create_empty_polynom)
{
	ASSERT_NO_THROW(Polynom());
}

TEST(Polynom, can_create_polynom_by_monom)
{
	ASSERT_NO_THROW(Polynom(Monom(1, 123)));
}

TEST(Polynom, can_addmonom)
{
	Polynom p;
	ASSERT_NO_THROW(p.add_monom(Monom(1,123)));
}

TEST(Polynom, can_addmonom_in_different_way)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 234));
	p1.add_monom(Monom(1, 123));

	ASSERT_EQ(p1, p);
}

TEST(Polynom, can_addmonom_that_already_exist)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(2, 234));
	
	ASSERT_EQ(p1, p);
}

TEST(Polynom, can_erase_zero)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));
	ASSERT_NO_THROW(p.erase_zero());
}

TEST(Polynom, can_mul_monom_by_const)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(2, 234));
	ASSERT_EQ(p1, p*2);
}

TEST(Polynom, can_friend_mul_monom_by_const)
{
	Polynom p;
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(2, 234));
	ASSERT_EQ(p1, 2 * p);
}

TEST(Polynom, can_add_monom_and_deg_not_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 123));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(2, 234));
	ASSERT_EQ(p1, p + Monom(2, 234));
}

TEST(Polynom, can_sub_monom_and_deg_not_in_polynom)
{
	Polynom p;
	p.add_monom(Monom(1, 123));

	Polynom p1;
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(-2, 234));
	ASSERT_EQ(p1, p - Monom(2, 234));
}

TEST(Polynom, can_add_monom_and_deg_in_polynom_left)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(2, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(3, 123));
	p1.add_monom(Monom(2, 234));

	ASSERT_EQ(p1, p + Monom(2, 123));

}

TEST(Polynom, can_sub_monom_and_deg_in_polynom_left)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(5, 123));
	p.add_monom(Monom(2, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(2, 123));
	p1.add_monom(Monom(2, 234));

	ASSERT_EQ(p1, p - Monom(3, 123));

}

TEST(Polynom, can_add_monom_and_deg_in_polynom_right)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(1, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(3, 234));

	ASSERT_EQ(p1, p + Monom(2, 234));

}

TEST(Polynom, can_sub_monom_and_deg_in_polynom_right)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(1, 123));
	p.add_monom(Monom(3, 234));

	Polynom p1;
	p1.add_monom(Monom(1, 111));
	p1.add_monom(Monom(1, 123));
	p1.add_monom(Monom(1, 234));

	ASSERT_EQ(p1, p - Monom(2, 234));

}

TEST(Polynom, can_mul_monom)
{
	Polynom p1(Monom(1, 234));
	p1.add_monom(Monom(3, 111));

	Polynom p(Monom(2, 465));
	p.add_monom(Monom(6, 342));

	ASSERT_EQ(p, p1 * Monom(2, 231));
}


TEST(Polynom, can_calculate_value_at_point)
{
	Polynom p;
	p.add_monom(Monom(1, 111));
	p.add_monom(Monom(5, 222));

	EXPECT_EQ(186, p.point(1, 2, 3));
}

TEST(Polynom, can_calculate_value_at_point_in_empty_polynom)
{
	Polynom p;

	EXPECT_EQ(0, p.point(1, 2, 3));
}
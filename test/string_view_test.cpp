#include <iostream>
#include "string_view.hpp"
#include <cstring>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Compare with std string", "[string_view]")
{

	std::string s = "This is a string";
	std_backport::string_view v(s);

	CHECK(v.substr(0) == s.substr(0));
	CHECK(v.substr(0, 5) == s.substr(0, 5));
	CHECK(v.substr(1, 5) == s.substr(1, 5));
	CHECK(v.substr(4, 5) == s.substr(4, 5));
	CHECK(v.substr(0, 322) == s.substr(0, 322));

#define FIND_TEST_FUNCTION(FNAME)                            \
	CHECK(s.FNAME("is") == v.FNAME("is"));                   \
	CHECK(s.FNAME("is", 4) == v.FNAME("is", 4));             \
	CHECK(s.FNAME("s", 4) == v.FNAME("s", 4));               \
	CHECK(s.FNAME("s", 4, 1) == v.FNAME("s", 4, 1));         \
	CHECK(s.FNAME("s") == v.FNAME("s"));                     \
	CHECK(s.FNAME('q') == v.FNAME('q'));                     \
	CHECK(s.FNAME('q') == v.FNAME('q'));                     \
	CHECK(s.FNAME('q', s.size()) == v.FNAME('q', v.size())); \
	CHECK(s.FNAME('q', s.size() + 1) == v.FNAME('q', v.size() + 1));

	FIND_TEST_FUNCTION(find);
	FIND_TEST_FUNCTION(rfind);
	FIND_TEST_FUNCTION(find_first_of);
	FIND_TEST_FUNCTION(find_last_of);
	FIND_TEST_FUNCTION(find_first_not_of);
	FIND_TEST_FUNCTION(find_last_not_of);

#undef FIND_TEST_FUNCTION

	CHECK(v.find('q') == std_backport::string_view::npos);
	CHECK(v.rfind('q') == std_backport::string_view::npos);
	CHECK(v.rfind("is", 4) == 2);
	CHECK(v.rfind("s") == 10);

	CHECK(v.find_first_of('q') == std_backport::string_view::npos);
	CHECK(v.find_last_of('q') == std_backport::string_view::npos);
	CHECK(v.find_first_not_of('q') == 0);
	CHECK(v.find_last_not_of('q') == v.size() - 1);

	{
		std_backport::string_view view;
		CHECK((view = "test") == std::string("test"));
		CHECK((view = "") == std::string(""));
		CHECK((view = "") == std::string());
	}

	{
		std_backport::string_view view = "test";
		char buffer[5] = {};
		;
		CHECK(view.copy(buffer, 5) == 4);
		CHECK(strcmp(buffer, "test") == 0);
	}
	{
		std_backport::string_view view = "test";
		CHECK(view.to_string() == "test");
	}

	CHECK((v == s));
	CHECK((v <= s));
	CHECK((v >= s));
	CHECK(!(v != s));
	CHECK(!(v < s));
	CHECK(!(v > s));

	CHECK(!(v == ""));
	CHECK(!(v <= ""));
	CHECK((v >= ""));
	CHECK((v != ""));
	CHECK(!(v < ""));
	CHECK((v > ""));

	CHECK(!(v == "a"));
	CHECK((v <= "a"));
	CHECK(!(v >= "a"));
	CHECK((v != "a"));
	CHECK((v < "a"));
	CHECK(!(v > "a"));

	bool catch_except = false;
	try
	{
		v.substr(v.size(), 1);
	}
	catch (std::exception &)
	{
		catch_except = true;
	}
	CHECK(catch_except);

	{
		std_backport::string_view view("test");

		std::string str("test2");
		std_backport::string_view view2(str);
		CHECK(view.substr(1) == "est");
		CHECK(view.substr(1, 1) == "e");
		CHECK(view2.substr(1) == "est2");

		CHECK(view.compare(view2) < 0);
		CHECK(view2.compare(view) > 0);
		CHECK(view.compare(view2.substr(0, 4)) == 0);

		CHECK(view2.substr(1, 3) == "est");
	}

	{
		std::string empty_str;
		std_backport::string_view empty_view(empty_str);
		CHECK(empty_view == empty_str);

		std_backport::string_view editview("test");
		editview.remove_prefix(2);
		CHECK(editview == "st");
		editview = "test";
		editview.remove_suffix(2);
		CHECK(editview == "te");
	}
}

#ifdef STD_BACKPORT_USE_CONSTEXPR
TEST_CASE("constexpr", "[string_view]")
{

	constexpr std_backport::string_view constexpr_view;
	constexpr std_backport::string_view constexpr_view2 = constexpr_view;
	CHECK(constexpr_view2 == constexpr_view);
	CHECK(constexpr_view2 == "");
	constexpr std_backport::string_view constexpr_view3("test");
	constexpr std_backport::string_view constexpr_view4 = constexpr_view3;
	CHECK(constexpr_view4 == constexpr_view3);
	CHECK(constexpr_view4 == std_backport::string_view("test"));
	CHECK(constexpr_view4 == "test");
}
#endif
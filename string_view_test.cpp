#include <iostream>
#include "string_view.hpp"
#include <cassert>
#include <cstring>


void compare_with_std_string_test()
{
	std::string s = "This is a string";
	std_backport::string_view v(s);


	assert(v.substr(0) == s.substr(0));
	assert(v.substr(0, 5) == s.substr(0, 5));
	assert(v.substr(1, 5) == s.substr(1, 5));
	assert(v.substr(4, 5) == s.substr(4, 5));
	assert(v.substr(0, 322) == s.substr(0, 322));


#define FIND_TEST_FUNCTION(FNAME)\
assert(s.FNAME("is") == v.FNAME("is"));\
assert(s.FNAME("is", 4) == v.FNAME("is", 4));\
assert(s.FNAME("s", 4) == v.FNAME("s", 4));\
assert(s.FNAME("s", 4 , 1) == v.FNAME("s", 4 , 1));\
assert(s.FNAME("s") == v.FNAME("s"));\
assert(s.FNAME('q') == v.FNAME('q'));\
assert(s.FNAME('q') == v.FNAME('q'));\
assert(s.FNAME('q', s.size()) == v.FNAME('q', v.size()));\
assert(s.FNAME('q', s.size() + 1) == v.FNAME('q', v.size() + 1));

	FIND_TEST_FUNCTION(find);
	FIND_TEST_FUNCTION(rfind);
	FIND_TEST_FUNCTION(find_first_of);
	FIND_TEST_FUNCTION(find_last_of);
	FIND_TEST_FUNCTION(find_first_not_of);
	FIND_TEST_FUNCTION(find_last_not_of);

#undef FIND_TEST_FUNCTION
	
	assert(v.find('q') == std_backport::string_view::npos);	
	assert(v.rfind('q') == std_backport::string_view::npos);
	assert(v.rfind("is", 4) == 2);
	assert(v.rfind("s") == 10);

	assert(v.find_first_of('q') == std_backport::string_view::npos);
	assert(v.find_last_of('q') == std_backport::string_view::npos);
	assert(v.find_first_not_of('q') == 0);
	assert(v.find_last_not_of('q') == v.size() - 1);

	{
		std_backport::string_view view;
		assert((view = "test") == std::string("test"));
		assert((view = "") == std::string(""));
		assert((view = "") == std::string());
	}

	{
		std_backport::string_view view="test";
		char buffer[5] = {};
		;
		assert(view.copy(buffer, 5) == 4);
		assert(strcmp(buffer, "test") == 0);
	}
	{
		std_backport::string_view view = "test";
		assert(view.to_string() == "test");
	}



	assert((v == s));
	assert((v <= s));
	assert((v >= s));
	assert(!(v != s));
	assert(!(v < s));
	assert(!(v > s));


	assert(!(v == ""));
	assert(!(v <= ""));
	assert((v >= ""));
	assert((v != ""));
	assert(!(v < ""));
	assert((v > ""));

	assert(!(v == "a"));
	assert((v <= "a"));
	assert(!(v >= "a"));
	assert((v != "a"));
	assert((v < "a"));
	assert(!(v > "a"));

	bool catch_except = false;
	try
	{
		v.substr(v.size(), 1);
	}
	catch (std::exception&)
	{
		catch_except = true;
	}
	assert(catch_except);
}


int main()
{

#ifdef STD_BACKPORT_USE_CONSTEXPR
	constexpr std_backport::string_view constexpr_view;
	constexpr std_backport::string_view constexpr_view2 = constexpr_view;
	assert(constexpr_view2 == constexpr_view);
	assert(constexpr_view2 == "");
	constexpr std_backport::string_view constexpr_view3("test");
	constexpr std_backport::string_view constexpr_view4 = constexpr_view3;
	assert(constexpr_view4 == constexpr_view3);
	assert(constexpr_view4 == "test");
#endif

	std_backport::string_view view("test");

	std::string str("test2");
	std_backport::string_view view2(str);

	{
		assert(view.substr(1) == "est");
		assert(view.substr(1, 1) == "e");
		assert(view2.substr(1) == "est2");

		assert(view.compare(view2) < 0);
		assert(view2.compare(view) > 0);
		assert(view.compare(view2.substr(0, 4)) == 0);

		assert(view2.substr(1, 3) == "est");
	}
	compare_with_std_string_test();

	std::string empty_str;
	std_backport::string_view empty_view(empty_str);
	assert(empty_view == empty_str);

	std_backport::string_view editview("test");
	editview.remove_prefix(2);
	assert(editview == "st");
	editview = "test";
	editview.remove_suffix(2);
	assert(editview == "te");
	return 0;
}


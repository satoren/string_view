#include <iostream>
#include "string_view.hpp"
#include <cassert>

int main()
{
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


	{
		std::string s("This is a string");
		std_backport::string_view v(s);

		assert(s.find("is") == v.find("is"));
		assert(s.find("is", 4) == v.find("is", 4));
		assert(s.find("s", 4) == v.find("s", 4));
		assert(s.find("s") == v.find("s"));
		assert(s.find('q') == v.find('q'));
		assert(s.find('q') == v.find('q'));

		assert(v.find('q') == std_backport::string_view::npos);
	}

	{
		std::string s("This is a string");
		std_backport::string_view v(s);


		assert(s.rfind("is") == v.rfind("is"));
		assert(s.rfind("is", 4) == v.rfind("is", 4));
		assert(s.rfind("s", 4) == v.rfind("s", 4));
		assert(s.rfind("s") == v.rfind("s"));
		assert(s.rfind('q') == v.rfind('q'));
		assert(s.rfind('q') == v.rfind('q'));

		assert(s.rfind("is") == 5);

		assert(s.rfind("is", 4) == 2);

		assert(s.rfind("s") == 10);

		assert(s.rfind('q') == std_backport::string_view::npos);
	}

	
	{
		std::string s("This is a string");
		std_backport::string_view v(s);

		assert(s.find_first_of("is") == v.find_first_of("is"));
		assert(s.find_first_of("is", 4) == v.find_first_of("is", 4));
		assert(s.find_first_of("s", 4) == v.find_first_of("s", 4));
		assert(s.find_first_of("s") == v.find_first_of("s"));
		assert(s.find_first_of('q') == v.find_first_of('q'));
		assert(s.find_first_of('q') == v.find_first_of('q'));

		assert(v.find_first_of('q') == std_backport::string_view::npos);
	}
	{
		std::string s("This is a string");
		std_backport::string_view v(s);

		assert(s.find_last_of("is") == v.find_last_of("is"));
		assert(s.find_last_of("is", 4) == v.find_last_of("is", 4));
		assert(s.find_last_of("s", 4) == v.find_last_of("s", 4));
		assert(s.find_last_of("s") == v.find_last_of("s"));
		assert(s.find_last_of('q') == v.find_last_of('q'));
		assert(s.find_last_of('q') == v.find_last_of('q'));

		assert(v.find_last_of('q') == std_backport::string_view::npos);
	}


	{
		std::string s("This is a string");
		std_backport::string_view v(s);

		assert(s.find_last_of("is") == v.find_last_of("is"));
		assert(s.find_last_of("is", 4) == v.find_last_of("is", 4));
		assert(s.find_last_of("s", 4) == v.find_last_of("s", 4));
		assert(s.find_last_of("s") == v.find_last_of("s"));
		assert(s.find_last_of('q') == v.find_last_of('q'));
		assert(s.find_last_of('q') == v.find_last_of('q'));

		assert(v.find_last_of('q') == std_backport::string_view::npos);
	}

	{
		std::string s("This is a string");
		std_backport::string_view v(s);

		assert(s.find_first_not_of("is") == v.find_first_not_of("is"));
		assert(s.find_first_not_of("is", 4) == v.find_first_not_of("is", 4));
		assert(s.find_first_not_of("s", 4) == v.find_first_not_of("s", 4));
		assert(s.find_first_not_of("s") == v.find_first_not_of("s"));
		assert(s.find_first_not_of('q') == v.find_first_not_of('q'));
		assert(s.find_first_not_of('q') == v.find_first_not_of('q'));

		assert(v.find_first_not_of('q') == 0);
	}

	{
		std::string s("This is a string");
		std_backport::string_view v(s);
		assert(s.find_last_not_of("is") == v.find_last_not_of("is"));
		assert(s.find_last_not_of("is", 4) == v.find_last_not_of("is", 4));
		assert(s.find_last_not_of("s", 4) == v.find_last_not_of("s", 4));
		assert(s.find_last_not_of("s") == v.find_last_not_of("s"));
		assert(s.find_last_not_of('q') == v.find_last_not_of('q'));
		assert(s.find_last_not_of('q') == v.find_last_not_of('q'));

		assert(v.find_last_not_of('q') == v.size()-1);
	}


	/*
	{
    // the test string
    std_backport::string_view hello("Hello World!");
 
    // strings and chars to search for
    std::string search_str = std::string("o");
    const char* search_cstr = "Good Bye!";
    assert(hello.find_first_of(search_str) == 4);
    assert(hello.find_first_of(search_str, 5) == 7);
    assert(hello.find_first_of(search_cstr) == 1);
    assert(hello.find_first_of(search_cstr, 0, 4) == 4);
    assert(hello.find_first_of('x') == std::string_view::npos);
	}*/
    return 0;
}


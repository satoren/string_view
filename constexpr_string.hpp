#pragma once
/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include <string>
#include <utility>

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
namespace compiletime {
template <typename CharT, std::size_t N>
struct basic_constexpr_string {
  typedef CharT value_type;
  typedef CharT* pointer;
  typedef const CharT* const_pointer;
  typedef CharT& reference;
  typedef const CharT& const_reference;
  typedef std::size_t size_type;

  constexpr const_pointer c_str() const { return buffer; }
  std::basic_string<CharT> to_string() const {
    return std::basic_string<CharT>(buffer);
  }

  constexpr CharT operator[](size_type pos) const { return buffer[pos]; }

  constexpr int compare(const basic_constexpr_string<CharT, N>& v) const;

  constexpr bool operator==(const basic_constexpr_string& rhs) const {
    return compare(rhs) == 0;
  }
  constexpr bool operator!=(const basic_constexpr_string& rhs) const {
    return compare(rhs) != 0;
  }
  constexpr bool operator<(const basic_constexpr_string& rhs) const {
    return compare(rhs) < 0;
  }
  constexpr bool operator>(const basic_constexpr_string& rhs) const {
    return rhs < *this;
  }
  constexpr bool operator<=(const basic_constexpr_string& rhs) const {
    return !(*this > rhs);
  }
  constexpr bool operator>=(const basic_constexpr_string& rhs) const {
    return !(*this < rhs);
  }

  constexpr size_type size() const { return N; }

  CharT buffer[N + 1];
};

#if __cplusplus >= 201402L || (defined(_MSC_VER) && _MSC_VER >= 1900)
using std::make_index_sequence;
using std::index_sequence;
#else
template <std::size_t... Indices>
struct index_sequence {};
template <std::size_t first, std::size_t last, class result = index_sequence<>,
          bool flag = first >= last>
struct make_index_sequence_t {
  using type = result;
};
template <std::size_t step, std::size_t last, std::size_t... Indices>
struct make_index_sequence_t<step, last, index_sequence<Indices...>, false>
    : make_index_sequence_t<step + 1, last, index_sequence<Indices..., step> > {
};
template <std::size_t N>
using make_index_sequence = typename make_index_sequence_t<0, N>::type;
#endif

namespace detail {
template <typename CharT, std::size_t... Indices>
constexpr basic_constexpr_string<CharT, sizeof...(Indices)> build_string(
    const CharT* str, index_sequence<Indices...>) {
  return basic_constexpr_string<CharT, sizeof...(Indices)>{str[Indices]...};
}
template <typename CharT, std::size_t... Indices, std::size_t... Indices2>
constexpr basic_constexpr_string<CharT,
                                 sizeof...(Indices) + sizeof...(Indices2)>
append_string(const CharT* str, index_sequence<Indices...>, const CharT* str2,
              index_sequence<Indices2...>) {
  return basic_constexpr_string<CharT,
                                sizeof...(Indices) + sizeof...(Indices2)>{
      str[Indices]..., str2[Indices2]...};
}
template <typename CharT>
constexpr int compare(const CharT* str, const CharT* str2, std::size_t len) {
  return len == 0 ? 0
                  : (*str) != (*str2) ? (*str) - (*str2)
                                      : compare(str + 1, str2 + 1, len - 1);
}
}

template <typename CharT, std::size_t N>
constexpr int basic_constexpr_string<CharT, N>::compare(
    const basic_constexpr_string<CharT, N>& n) const {
  return detail::compare(&buffer[0], &n.buffer[0], N);
}

template <typename CharT, std::size_t N1, std::size_t N2>
constexpr basic_constexpr_string<CharT, N1 + N2> operator+(
    const basic_constexpr_string<CharT, N1>& cstr1,
    const basic_constexpr_string<CharT, N2>& cstr2) {
  return detail::append_string(&cstr1.buffer[0], make_index_sequence<N1>(),
                               &cstr2.buffer[0], make_index_sequence<N2>());
}
template <typename CharT, std::size_t N>
std::basic_string<CharT> operator+(
    const std::basic_string<CharT>& str,
    const basic_constexpr_string<CharT, N>& cstr) {
  std::string ret;
  ret.reserve(str.size() + N);
  ret.append(str);
  ret.append(cstr.buffer);
  return ret;
}
template <typename CharT, std::size_t N>
std::basic_string<CharT> operator+(const basic_constexpr_string<CharT, N>& cstr,
                                   const std::basic_string<CharT>& str) {
  std::string ret;
  ret.reserve(str.size() + N);
  ret.append(cstr.buffer);
  ret.append(str);
  return ret;
}

template <typename CharT, std::size_t N>
constexpr basic_constexpr_string<CharT, N - 1> to_constexpr_string(
    const CharT (&str)[N]) {
  return detail::build_string(str, make_index_sequence<N - 1>());
}

template <std::size_t N>
using constexpr_string = basic_constexpr_string<char, N>;
template <std::size_t N>
using constexpr_wstring = basic_constexpr_string<wchar_t, N>;

#if defined(_HAS_CONSTEXPR) || __cplusplus >= 201103L || \
    (defined(_MSC_VER) && _MSC_VER >= 1800)
template <std::size_t N>
using constexpr_u16string = basic_constexpr_string<char16_t, N>;
template <std::size_t N>
using constexpr_u32string = basic_constexpr_string<char32_t, N>;
#endif
}
#else
#error Needs at least a C++11 compiler
#endif
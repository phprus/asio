//
// detail/type_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_TYPE_TRAITS_HPP
#define ASIO_DETAIL_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#include <type_traits>

namespace asio {

using std::add_const;
using std::add_lvalue_reference;
using std::aligned_storage;
using std::alignment_of;
using std::conditional;
using std::decay;
using std::declval;
using std::enable_if;
using std::false_type;
using std::integral_constant;
using std::is_base_of;
using std::is_class;
using std::is_const;
using std::is_constructible;
using std::is_convertible;
using std::is_copy_constructible;
using std::is_destructible;
using std::is_function;
using std::is_move_constructible;
using std::is_nothrow_copy_constructible;
using std::is_nothrow_destructible;
using std::is_object;
using std::is_reference;
using std::is_same;
using std::is_scalar;
using std::remove_cv;
template <typename T>
struct remove_cvref : remove_cv<typename std::remove_reference<T>::type> {};
using std::remove_pointer;
using std::remove_reference;
#if defined(ASIO_HAS_STD_INVOKE_RESULT)
template <typename> struct result_of;
template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};
#else // defined(ASIO_HAS_STD_INVOKE_RESULT)
using std::result_of;
#endif // defined(ASIO_HAS_STD_INVOKE_RESULT)
using std::true_type;

template <typename> struct void_type { typedef void type; };

template <typename...> struct conjunction : true_type {};
template <typename T> struct conjunction<T> : T {};
template <typename Head, typename... Tail> struct conjunction<Head, Tail...> :
  conditional<Head::value, conjunction<Tail...>, Head>::type {};

struct defaulted_constraint
{
  ASIO_CONSTEXPR defaulted_constraint() {}
};

template <bool Condition, typename Type = int>
struct constraint : enable_if<Condition, Type> {};

} // namespace asio

#endif // ASIO_DETAIL_TYPE_TRAITS_HPP

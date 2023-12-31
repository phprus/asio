//
// detail/type_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

using std::add_const_t;

template <std::size_t N, std::size_t A>
struct aligned_storage
{
  struct type
  {
    alignas(A) unsigned char data[N];
  };
};

template <std::size_t N, std::size_t A>
using aligned_storage_t = typename aligned_storage<N, A>::type;

using std::alignment_of;

using std::conditional;

using std::conditional_t;

using std::decay;

using std::decay_t;

using std::declval;

using std::enable_if;

using std::enable_if_t;

using std::false_type;

using std::integral_constant;

using std::is_base_of;

using std::is_class;

using std::is_const;

using std::is_constructible;

using std::is_convertible;

using std::is_function;

using std::is_move_constructible;

using std::is_nothrow_copy_constructible;

using std::is_nothrow_destructible;

using std::is_pointer;

using std::is_reference;

using std::is_same;

using std::is_scalar;

using std::remove_cvref_t;

using std::remove_pointer_t;

using std::remove_reference_t;

template <typename> struct result_of;

template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};

template <typename T>
using result_of_t = typename result_of<T>::type;

using std::true_type;

using std::void_t;

using std::conjunction;

struct defaulted_constraint
{
  constexpr defaulted_constraint() {}
};

template <bool Condition, typename Type = int>
struct constraint : std::enable_if<Condition, Type> {};

template <bool Condition, typename Type = int>
using constraint_t = typename constraint<Condition, Type>::type;

using std::type_identity_t;

} // namespace asio

#endif // ASIO_DETAIL_TYPE_TRAITS_HPP

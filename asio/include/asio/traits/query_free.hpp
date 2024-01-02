//
// traits/query_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_QUERY_FREE_HPP
#define ASIO_TRAITS_QUERY_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename Property, typename = void>
struct query_free_default;

template <typename T, typename Property, typename = void>
struct query_free;

} // namespace traits
namespace detail {

struct no_query_free
{
  static constexpr bool is_valid = false;
  static constexpr bool is_noexcept = false;
};

template <typename T, typename Property, typename = void>
struct query_free_trait : no_query_free
{
};

template <typename T, typename Property>
struct query_free_trait<T, Property,
  void_t<
    decltype(query(declval<T>(), declval<Property>()))
  >>
{
  static constexpr bool is_valid = true;

  using result_type = decltype(
    query(declval<T>(), declval<Property>()));

  static constexpr bool is_noexcept =
    noexcept(query(declval<T>(), declval<Property>()));
};

} // namespace detail
namespace traits {

template <typename T, typename Property, typename>
struct query_free_default :
  detail::query_free_trait<T, Property>
{
};

template <typename T, typename Property, typename>
struct query_free :
  query_free_default<T, Property>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_QUERY_FREE_HPP

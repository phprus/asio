//
// traits/prefer_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_PREFER_FREE_HPP
#define ASIO_TRAITS_PREFER_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename Property, typename = void>
struct prefer_free_default;

template <typename T, typename Property, typename = void>
struct prefer_free;

} // namespace traits
namespace detail {

struct no_prefer_free
{
  static constexpr bool is_valid = false;
  static constexpr bool is_noexcept = false;
};

template <typename T, typename Property, typename = void>
struct prefer_free_trait : no_prefer_free
{
};

template <typename T, typename Property>
struct prefer_free_trait<T, Property,
  void_t<
    decltype(prefer(declval<T>(), declval<Property>()))
  >>
{
  static constexpr bool is_valid = true;

  using result_type = decltype(
    prefer(declval<T>(), declval<Property>()));

  static constexpr bool is_noexcept =
    noexcept(prefer(declval<T>(), declval<Property>()));
};

} // namespace detail
namespace traits {

template <typename T, typename Property, typename>
struct prefer_free_default :
  detail::prefer_free_trait<T, Property>
{
};

template <typename T, typename Property, typename>
struct prefer_free :
  prefer_free_default<T, Property>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_PREFER_FREE_HPP

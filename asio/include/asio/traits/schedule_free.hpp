//
// traits/schedule_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_SCHEDULE_FREE_HPP
#define ASIO_TRAITS_SCHEDULE_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#define ASIO_HAS_DEDUCED_SCHEDULE_FREE_TRAIT 1

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename = void>
struct schedule_free_default;

template <typename T, typename = void>
struct schedule_free;

} // namespace traits
namespace detail {

struct no_schedule_free
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

template <typename T, typename = void>
struct schedule_free_trait : no_schedule_free
{
};

template <typename T>
struct schedule_free_trait<T,
  typename void_type<
    decltype(schedule(declval<T>()))
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(schedule(declval<T>()));

  ASIO_STATIC_CONSTEXPR(bool,
    is_noexcept = noexcept(schedule(declval<T>())));
};

} // namespace detail
namespace traits {

template <typename T, typename>
struct schedule_free_default :
  detail::schedule_free_trait<T>
{
};

template <typename T, typename>
struct schedule_free :
  schedule_free_default<T>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_SCHEDULE_FREE_HPP

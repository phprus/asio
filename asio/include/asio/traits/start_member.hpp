//
// traits/start_member.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_START_MEMBER_HPP
#define ASIO_TRAITS_START_MEMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#define ASIO_HAS_DEDUCED_START_MEMBER_TRAIT 1

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename = void>
struct start_member_default;

template <typename T, typename = void>
struct start_member;

} // namespace traits
namespace detail {

struct no_start_member
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

template <typename T, typename = void>
struct start_member_trait : no_start_member
{
};

template <typename T>
struct start_member_trait<T,
  typename void_type<
    decltype(declval<T>().start())
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(declval<T>().start());

  ASIO_STATIC_CONSTEXPR(bool,
    is_noexcept = noexcept(declval<T>().start()));
};

} // namespace detail
namespace traits {

template <typename T, typename>
struct start_member_default :
  detail::start_member_trait<T>
{
};

template <typename T, typename>
struct start_member :
  start_member_default<T>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_START_MEMBER_HPP

//
// traits/require_concept_member.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_REQUIRE_CONCEPT_MEMBER_HPP
#define ASIO_TRAITS_REQUIRE_CONCEPT_MEMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#define ASIO_HAS_DEDUCED_REQUIRE_CONCEPT_MEMBER_TRAIT 1

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename Property, typename = void>
struct require_concept_member_default;

template <typename T, typename Property, typename = void>
struct require_concept_member;

} // namespace traits
namespace detail {

struct no_require_concept_member
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

template <typename T, typename Property, typename = void>
struct require_concept_member_trait : no_require_concept_member
{
};

template <typename T, typename Property>
struct require_concept_member_trait<T, Property,
  typename void_type<
    decltype(declval<T>().require_concept(declval<Property>()))
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    declval<T>().require_concept(declval<Property>()));

  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    declval<T>().require_concept(declval<Property>())));
};

} // namespace detail
namespace traits {

template <typename T, typename Property, typename>
struct require_concept_member_default :
  detail::require_concept_member_trait<T, Property>
{
};

template <typename T, typename Property, typename>
struct require_concept_member :
  require_concept_member_default<T, Property>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_REQUIRE_CONCEPT_MEMBER_HPP

//
// traits/set_value_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_SET_VALUE_FREE_HPP
#define ASIO_TRAITS_SET_VALUE_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

#if defined(ASIO_HAS_DECLTYPE) \
  && defined(ASIO_HAS_NOEXCEPT) \
  && defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT 1
#endif // defined(ASIO_HAS_DECLTYPE)
       //   && defined(ASIO_HAS_NOEXCEPT)
       //   && defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace traits {

template <typename T, typename Vs, typename = void>
struct set_value_free_default;

template <typename T, typename Vs, typename = void>
struct set_value_free;

} // namespace traits
namespace detail {

struct no_set_value_free
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_free_trait : no_set_value_free
{
};

template <typename T, typename... Vs>
struct set_value_free_trait<T, void(Vs...),
  typename void_type<
    decltype(set_value(declval<T>(), declval<Vs>()...))
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    set_value(declval<T>(), declval<Vs>()...));

  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    set_value(declval<T>(), declval<Vs>()...)));
};

#else // defined(ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_free_trait;

template <typename T, typename... Vs>
struct set_value_free_trait<T, void(Vs...)> :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value
      && conjunction<is_same<Vs, typename decay<Vs>::type>...>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_set_value_free,
      traits::set_value_free<typename add_const<T>::type, void(Vs...)>
    >::type,
    traits::set_value_free<
      typename remove_reference<T>::type,
      void(typename decay<Vs>::type...)>
  >::type
{
};

#endif // defined(ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename Vs, typename>
struct set_value_free_default :
  detail::set_value_free_trait<T, Vs>
{
};

template <typename T, typename Vs, typename>
struct set_value_free :
  set_value_free_default<T, Vs>
{
};

} // namespace traits
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_TRAITS_SET_VALUE_FREE_HPP

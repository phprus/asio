//
// error_traits.hpp
// ~~~~~~~~~~~~~~~~
//
//
// Copyright (c) 2024 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_ERROR_TRAITS_HPP
#define ASIO_ERROR_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#include <exception>
#include <system_error>
#include <type_traits>

#include "asio/detail/push_options.hpp"

namespace asio {

/// Error traits to automatically convert error values into exceptions.
template<typename Error>
struct error_traits;

template<>
struct error_traits<std::error_code>
{
  typedef std::error_code type;

  [[noreturn]]
  static void throw_error(
      const std::error_code& ec
      ASIO_SOURCE_LOCATION_DEFAULTED_PARAM)
  {
    detail::do_throw_error(ec ASIO_SOURCE_LOCATION_ARG);
  }

  [[nodiscard]]
  static std::exception_ptr make_exception_ptr(
      const std::error_code &ec) noexcept
  {
    return std::make_exception_ptr(std::system_error(ec));
    //try
    //{
    //  throw_error(ec);
    //}
    //catch(...)
    //{
    //  return std::current_exception();
    //}
  }

  [[nodiscard]]
  static bool is_failure(
      const std::error_code &ec) noexcept
  {
     return !!ec;
  }
};


template<>
struct error_traits<std::exception_ptr>
{
  typedef std::exception_ptr type;

  [[noreturn]]
  static void throw_error(
      std::exception_ptr e)
  {
    std::rethrow_exception(e);
  }

  [[nodiscard]]
  static std::exception_ptr make_exception_ptr(
      std::exception_ptr e) noexcept
  {
    return e;
  }

  [[nodiscard]]
  static bool is_failure(
      const std::exception_ptr &e) noexcept
  {
    return !!e;
  }
};

template<typename Error, typename = Error>
struct is_error : std::false_type {};

template<typename Error>
struct is_error<Error, typename error_traits<Error>::type> : std::true_type {};

template<>
struct is_error<std::exception_ptr, std::exception_ptr> : std::true_type {};

template<>
struct is_error<std::error_code, std::error_code> : std::true_type {};

template<typename T>
struct signature_has_error : std::false_type {};

template<>
struct signature_has_error<void()> : std::false_type {};

template<typename T>
struct signature_has_error<void(T)> : is_error<T> {};


template<typename T, typename ... Ts>
struct signature_has_error<void(T, Ts...)> : is_error<T> {};


}

#include "asio/detail/pop_options.hpp"


#endif //ASIO_ERROR_TRAITS_HPP

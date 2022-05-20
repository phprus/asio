//
// ip/address.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IP_ADDRESS_HPP
#define ASIO_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <string>
#include "asio/detail/throw_exception.hpp"
#include "asio/detail/string_view.hpp"
#include "asio/detail/type_traits.hpp"
#include <system_error>
#include "asio/ip/address_v4.hpp"
#include "asio/ip/address_v6.hpp"
#include "asio/ip/bad_address_cast.hpp"

#include <functional>
#include <iosfwd>

#include "asio/detail/push_options.hpp"

namespace asio {
namespace ip {

/// Implements version-independent IP addresses.
/**
 * The asio::ip::address class provides the ability to use either IP
 * version 4 or version 6 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address
{
public:
  /// Default constructor.
  ASIO_DECL address() noexcept(true);

  /// Construct an address from an IPv4 address.
  ASIO_DECL address(
      const asio::ip::address_v4& ipv4_address) noexcept(true);

  /// Construct an address from an IPv6 address.
  ASIO_DECL address(
      const asio::ip::address_v6& ipv6_address) noexcept(true);

  /// Copy constructor.
  ASIO_DECL address(const address& other) noexcept(true);

  /// Move constructor.
  ASIO_DECL address(address&& other) noexcept(true);

  /// Assign from another address.
  ASIO_DECL address& operator=(const address& other) noexcept(true);

  /// Move-assign from another address.
  ASIO_DECL address& operator=(address&& other) noexcept(true);

  /// Assign from an IPv4 address.
  ASIO_DECL address& operator=(
      const asio::ip::address_v4& ipv4_address) noexcept(true);

  /// Assign from an IPv6 address.
  ASIO_DECL address& operator=(
      const asio::ip::address_v6& ipv6_address) noexcept(true);

  /// Get whether the address is an IP version 4 address.
  bool is_v4() const noexcept(true)
  {
    return type_ == ipv4;
  }

  /// Get whether the address is an IP version 6 address.
  bool is_v6() const noexcept(true)
  {
    return type_ == ipv6;
  }

  /// Get the address as an IP version 4 address.
  ASIO_DECL asio::ip::address_v4 to_v4() const;

  /// Get the address as an IP version 6 address.
  ASIO_DECL asio::ip::address_v6 to_v6() const;

  /// Get the address as a string.
  ASIO_DECL std::string to_string() const;

  /// Determine whether the address is a loopback address.
  ASIO_DECL bool is_loopback() const noexcept(true);

  /// Determine whether the address is unspecified.
  ASIO_DECL bool is_unspecified() const noexcept(true);

  /// Determine whether the address is a multicast address.
  ASIO_DECL bool is_multicast() const noexcept(true);

  /// Compare two addresses for equality.
  ASIO_DECL friend bool operator==(const address& a1,
      const address& a2) noexcept(true);

  /// Compare two addresses for inequality.
  friend bool operator!=(const address& a1,
      const address& a2) noexcept(true)
  {
    return !(a1 == a2);
  }

  /// Compare addresses for ordering.
  ASIO_DECL friend bool operator<(const address& a1,
      const address& a2) noexcept(true);

  /// Compare addresses for ordering.
  friend bool operator>(const address& a1,
      const address& a2) noexcept(true)
  {
    return a2 < a1;
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const address& a1,
      const address& a2) noexcept(true)
  {
    return !(a2 < a1);
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const address& a1,
      const address& a2) noexcept(true)
  {
    return !(a1 < a2);
  }

private:
  // The type of the address.
  enum { ipv4, ipv6 } type_;

  // The underlying IPv4 address.
  asio::ip::address_v4 ipv4_address_;

  // The underlying IPv6 address.
  asio::ip::address_v6 ipv6_address_;
};

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(const char* str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(const char* str,
    std::error_code& ec) noexcept(true);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(const std::string& str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(const std::string& str,
    std::error_code& ec) noexcept(true);

#if defined(ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(string_view str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
ASIO_DECL address make_address(string_view str,
    std::error_code& ec) noexcept(true);

#endif // defined(ASIO_HAS_STRING_VIEW)
       //  || defined(GENERATING_DOCUMENTATION)

/// Output an address as a string.
/**
 * Used to output a human-readable string for a specified address.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param addr The address to be written.
 *
 * @return The output stream.
 *
 * @relates asio::ip::address
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address& addr);

} // namespace ip
} // namespace asio

namespace std {

template <>
struct hash<asio::ip::address>
{
  std::size_t operator()(const asio::ip::address& addr)
    const noexcept(true)
  {
    return addr.is_v4()
      ? std::hash<asio::ip::address_v4>()(addr.to_v4())
      : std::hash<asio::ip::address_v6>()(addr.to_v6());
  }
};

} // namespace std

#include "asio/detail/pop_options.hpp"

#include "asio/ip/impl/address.hpp"
#if defined(ASIO_HEADER_ONLY)
# include "asio/ip/impl/address.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_IP_ADDRESS_HPP

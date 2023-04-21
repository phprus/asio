//
// schedule.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include "asio/execution/schedule.hpp"

#include <system_error>
#include "asio/execution/sender.hpp"
#include "asio/execution/submit.hpp"
#include "asio/traits/connect_member.hpp"
#include "asio/traits/start_member.hpp"
#include "asio/traits/submit_member.hpp"
#include "../unit_test.hpp"

#if !defined(ASIO_NO_DEPRECATED)

namespace exec = asio::execution;

struct operation_state
{
  void start() noexcept(true)
  {
  }
};

struct sender : exec::sender_base
{
  sender()
  {
  }

  template <typename R>
  operation_state connect(ASIO_MOVE_ARG(R) r) const
  {
    (void)r;
    return operation_state();
  }

  template <typename R>
  void submit(ASIO_MOVE_ARG(R) r) const
  {
    typename asio::decay<R>::type tmp(ASIO_MOVE_CAST(R)(r));
    exec::set_value(tmp);
  }
};

struct no_schedule
{
};

struct const_member_schedule
{
  sender schedule() const noexcept(true)
  {
    return sender();
  }
};

struct free_schedule_const_receiver
{
  friend sender schedule(
      const free_schedule_const_receiver&) noexcept(true)
  {
    return sender();
  }
};

struct non_const_member_schedule
{
  sender schedule() noexcept(true)
  {
    return sender();
  }
};

struct free_schedule_non_const_receiver
{
  friend sender schedule(
      free_schedule_non_const_receiver&) noexcept(true)
  {
    return sender();
  }
};

struct executor
{
  executor()
  {
  }

  executor(const executor&) noexcept(true)
  {
  }

  executor(executor&&) noexcept(true)
  {
  }

  template <typename F>
  void execute(ASIO_MOVE_ARG(F) f) const noexcept(true)
  {
    typename asio::decay<F>::type tmp(ASIO_MOVE_CAST(F)(f));
    tmp();
  }

  bool operator==(const executor&) const noexcept(true)
  {
    return true;
  }

  bool operator!=(const executor&) const noexcept(true)
  {
    return false;
  }
};

void test_can_schedule()
{
  constexpr bool b1 = exec::can_schedule<
      no_schedule&>::value;
  ASIO_CHECK(b1 == false);

  constexpr bool b2 = exec::can_schedule<
      const no_schedule&>::value;
  ASIO_CHECK(b2 == false);

  constexpr bool b3 = exec::can_schedule<
      const_member_schedule&>::value;
  ASIO_CHECK(b3 == true);

  constexpr bool b4 = exec::can_schedule<
      const const_member_schedule&>::value;
  ASIO_CHECK(b4 == true);

  constexpr bool b5 = exec::can_schedule<
      free_schedule_const_receiver&>::value;
  ASIO_CHECK(b5 == true);

  constexpr bool b6 = exec::can_schedule<
      const free_schedule_const_receiver&>::value;
  ASIO_CHECK(b6 == true);

  constexpr bool b7 = exec::can_schedule<
      non_const_member_schedule&>::value;
  ASIO_CHECK(b7 == true);

  constexpr bool b8 = exec::can_schedule<
      const non_const_member_schedule&>::value;
  ASIO_CHECK(b8 == false);

  constexpr bool b9 = exec::can_schedule<
      free_schedule_non_const_receiver&>::value;
  ASIO_CHECK(b9 == true);

  constexpr bool b10 = exec::can_schedule<
      const free_schedule_non_const_receiver&>::value;
  ASIO_CHECK(b10 == false);

  constexpr bool b11 = exec::can_schedule<
      executor&>::value;
  ASIO_CHECK(b11 == true);

  constexpr bool b12 = exec::can_schedule<
      const executor&>::value;
  ASIO_CHECK(b12 == true);
}

struct receiver
{
  int* count_;

  receiver(int* count)
    : count_(count)
  {
  }

  receiver(const receiver& other) noexcept(true)
    : count_(other.count_)
  {
  }

  receiver(receiver&& other) noexcept(true)
    : count_(other.count_)
  {
    other.count_ = 0;
  }

  void set_value() noexcept(true)
  {
    ++(*count_);
  }

  template <typename E>
  void set_error(ASIO_MOVE_ARG(E) e) noexcept(true)
  {
    (void)e;
  }

  void set_done() noexcept(true)
  {
  }
};

void test_schedule()
{
  int count = 0;
  const_member_schedule ex1 = {};
  exec::submit(
      exec::schedule(ex1),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  const const_member_schedule ex2 = {};
  exec::submit(
      exec::schedule(ex2),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  exec::submit(
      exec::schedule(const_member_schedule()),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  free_schedule_const_receiver ex3 = {};
  exec::submit(
      exec::schedule(ex3),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  const free_schedule_const_receiver ex4 = {};
  exec::submit(
      exec::schedule(ex4),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  exec::submit(
      exec::schedule(free_schedule_const_receiver()),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  non_const_member_schedule ex5 = {};
  exec::submit(
      exec::schedule(ex5),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  free_schedule_non_const_receiver ex6 = {};
  exec::submit(
      exec::schedule(ex6),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  executor ex7;
  exec::submit(
      exec::schedule(ex7),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  const executor ex8;
  exec::submit(
      exec::schedule(ex8),
      receiver(&count));
  ASIO_CHECK(count == 1);

  count = 0;
  exec::submit(
      exec::schedule(executor()),
      receiver(&count));
  ASIO_CHECK(count == 1);
}

ASIO_TEST_SUITE
(
  "schedule",
  ASIO_TEST_CASE(test_can_schedule)
  ASIO_TEST_CASE(test_schedule)
)

#else // !defined(ASIO_NO_DEPRECATED)

ASIO_TEST_SUITE
(
  "schedule",
  ASIO_TEST_CASE(null_test)
)

#endif // !defined(ASIO_NO_DEPRECATED)

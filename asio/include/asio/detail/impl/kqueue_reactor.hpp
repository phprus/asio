//
// detail/impl/kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2005 Stefan Arentz (stefan at soze dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP
#define ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_KQUEUE)

#include "asio/detail/scheduler.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

inline void kqueue_reactor::post_immediate_completion(
    operation* op, bool is_continuation) const
{
  scheduler_.post_immediate_completion(op, is_continuation);
}

template <typename TimeTraits, typename Allocator>
void kqueue_reactor::add_timer_queue(timer_queue<TimeTraits, Allocator>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename TimeTraits, typename Allocator>
void kqueue_reactor::remove_timer_queue(
    timer_queue<TimeTraits, Allocator>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename TimeTraits, typename Allocator>
void kqueue_reactor::schedule_timer(timer_queue<TimeTraits, Allocator>& queue,
    const typename TimeTraits::time_type& time,
    typename timer_queue<TimeTraits, Allocator>::per_timer_data& timer,
    wait_op* op)
{
  mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    interrupt();
}

template <typename TimeTraits, typename Allocator>
std::size_t kqueue_reactor::cancel_timer(
    timer_queue<TimeTraits, Allocator>& queue,
    typename timer_queue<TimeTraits, Allocator>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename TimeTraits, typename Allocator>
void kqueue_reactor::cancel_timer_by_key(
    timer_queue<TimeTraits, Allocator>& queue,
    typename timer_queue<TimeTraits, Allocator>::per_timer_data* timer,
    void* cancellation_key)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer_by_key(timer, ops, cancellation_key);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

template <typename TimeTraits, typename Allocator>
void kqueue_reactor::move_timer(timer_queue<TimeTraits, Allocator>& queue,
    typename timer_queue<TimeTraits, Allocator>::per_timer_data& target,
    typename timer_queue<TimeTraits, Allocator>::per_timer_data& source)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(target, ops);
  queue.move_timer(target, source);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // defined(ASIO_HAS_KQUEUE)

#endif // ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

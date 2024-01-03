//
// overlapped_handle.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Test that header file is self-contained.
#include "asio/windows/overlapped_handle.hpp"

#include "asio.hpp"
#include "../unit_test.hpp"

ASIO_TEST_SUITE
(
  "windows/overlapped_handle",
  ASIO_TEST_CASE(null_test)
)

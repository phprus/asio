//
// tcp_client.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/ip/tcp.hpp>
#include <asio/read.hpp>
#include <asio/write.hpp>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include "high_res_clock.hpp"

using asio::ip::tcp;

const int num_samples = 100000;

struct transfer_all
{
  typedef std::size_t result_type;
  std::size_t operator()(const asio::error_code& ec, std::size_t)
  {
    return (ec && ec != asio::error::would_block) ? 0 : ~0;
  }
};

int main(int argc, char* argv[])
{
  if (argc != 6)
  {
    std::fprintf(stderr,
        "Usage: tcp_client <ip> <port> "
        "<nconns> <bufsize> {spin|block}\n");
    return 1;
  }

  const char* ip = argv[1];
  unsigned short port = static_cast<unsigned short>(std::atoi(argv[2]));
  int num_connections = std::atoi(argv[3]);
  std::size_t buf_size = static_cast<std::size_t>(std::atoi(argv[4]));
  bool spin = (std::strcmp(argv[5], "spin") == 0);

  asio::io_context io_context;
  std::vector<std::shared_ptr<tcp::socket> > sockets;

  for (int i = 0; i < num_connections; ++i)
  {
    std::shared_ptr<tcp::socket> s(new tcp::socket(io_context));

    tcp::endpoint target(asio::ip::make_address(ip), port);
    s->connect(target);

    s->set_option(tcp::no_delay(true));

    if (spin)
    {
      s->non_blocking(true);
    }

    sockets.push_back(s);
  }

  std::vector<unsigned char> write_buf(buf_size);
  std::vector<unsigned char> read_buf(buf_size);

  auto start = std::chrono::high_resolution_clock::now();
  std::uint64_t start_hr = high_res_clock();

  std::uint64_t samples[num_samples];
  for (int i = 0; i < num_samples; ++i)
  {
    tcp::socket& socket = *sockets[i % num_connections];

    std::uint64_t t = high_res_clock();

    asio::error_code ec;
    asio::write(socket,
        asio::buffer(write_buf),
        transfer_all(), ec);

    asio::read(socket,
        asio::buffer(read_buf),
        transfer_all(), ec);

    samples[i] = high_res_clock() - t;
  }

  auto stop = std::chrono::high_resolution_clock::now();
  std::uint64_t stop_hr = high_res_clock();
  std::uint64_t elapsed_usec = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  std::uint64_t elapsed_hr = stop_hr - start_hr;
  double scale = 1.0 * elapsed_usec / elapsed_hr;

  std::sort(samples, samples + num_samples);
  std::printf("  0.0%%\t%f\n", samples[0] * scale);
  std::printf("  0.1%%\t%f\n", samples[num_samples / 1000 - 1] * scale);
  std::printf("  1.0%%\t%f\n", samples[num_samples / 100 - 1] * scale);
  std::printf(" 10.0%%\t%f\n", samples[num_samples / 10 - 1] * scale);
  std::printf(" 20.0%%\t%f\n", samples[num_samples * 2 / 10 - 1] * scale);
  std::printf(" 30.0%%\t%f\n", samples[num_samples * 3 / 10 - 1] * scale);
  std::printf(" 40.0%%\t%f\n", samples[num_samples * 4 / 10 - 1] * scale);
  std::printf(" 50.0%%\t%f\n", samples[num_samples * 5 / 10 - 1] * scale);
  std::printf(" 60.0%%\t%f\n", samples[num_samples * 6 / 10 - 1] * scale);
  std::printf(" 70.0%%\t%f\n", samples[num_samples * 7 / 10 - 1] * scale);
  std::printf(" 80.0%%\t%f\n", samples[num_samples * 8 / 10 - 1] * scale);
  std::printf(" 90.0%%\t%f\n", samples[num_samples * 9 / 10 - 1] * scale);
  std::printf(" 99.0%%\t%f\n", samples[num_samples * 99 / 100 - 1] * scale);
  std::printf(" 99.9%%\t%f\n", samples[num_samples * 999 / 1000 - 1] * scale);
  std::printf("100.0%%\t%f\n", samples[num_samples - 1] * scale);

  double total = 0.0;
  for (int i = 0; i < num_samples; ++i) total += samples[i] * scale;
  std::printf("  mean\t%f\n", total / num_samples);
}

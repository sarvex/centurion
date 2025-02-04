/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include "centurion/detail/stdlib.hpp"

TEST(FromString, IntegerBase10)
{
  ASSERT_FALSE(cen::detail::stoi("foo"));

  ASSERT_EQ(42, cen::detail::stoi("42"));
  ASSERT_EQ(123, cen::detail::stoi("123"));
  ASSERT_EQ(-834, cen::detail::stoi("-834"));
}

TEST(FromString, IntegerBase16)
{
  ASSERT_FALSE(cen::detail::stoi("foo", 16));

  ASSERT_EQ(0xB7, cen::detail::stoi("B7", 16));
  ASSERT_EQ(0x123, cen::detail::stoi("123", 16));
  ASSERT_EQ(0xE9A, cen::detail::stoi("E9A", 16));
}

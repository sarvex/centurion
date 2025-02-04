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

#include <iostream>  // cout

#include "centurion/controller.hpp"

using bind_type = cen::controller_bind_type;

TEST(ControllerBindType, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_AXIS, to_underlying(bind_type::axis));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_BUTTON, to_underlying(bind_type::button));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_NONE, to_underlying(bind_type::none));
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_HAT, to_underlying(bind_type::hat));
}

TEST(ControllerBindType, ToString)
{
  ASSERT_THROW(to_string(static_cast<bind_type>(100)), cen::exception);

  ASSERT_EQ("none", to_string(bind_type::none));
  ASSERT_EQ("button", to_string(bind_type::button));
  ASSERT_EQ("axis", to_string(bind_type::axis));
  ASSERT_EQ("hat", to_string(bind_type::hat));

  std::cout << "controller_bind_type::button == " << bind_type::button << '\n';
}

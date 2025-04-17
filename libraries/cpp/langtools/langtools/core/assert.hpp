// Copyright 2025 Sophie Lund
//
// This file is part of Forge.
//
// Forge is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Forge is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Forge. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <iostream>
#include <termcolor/termcolor.hpp>

#define LT_ABORT(message)                                                   \
  {                                                                         \
    ::std::cerr << ::termcolor::bright_blue << __FILE__ << ":" << __LINE__  \
                << ::termcolor::reset << ::termcolor::red                   \
                << ": aborted: " << ::termcolor::reset << ::termcolor::bold \
                << message << ::termcolor::reset << ::std::endl             \
                << ::std::endl;                                             \
    ::std::abort();                                                         \
  }

#define LT_TODO()                                                          \
  {                                                                        \
    ::std::cerr << ::termcolor::bright_blue << __FILE__ << ":" << __LINE__ \
                << ::termcolor::reset << ::termcolor::red << ": todo"      \
                << ::termcolor::reset << ::std::endl                       \
                << ::std::endl;                                            \
    ::std::abort();                                                        \
  }

#ifdef NDEBUG
#define LT_ASSERT(condition, message) \
  {                                   \
  }
#else
#define LT_ASSERT(condition, message)                                        \
  {                                                                          \
    if (!(condition)) {                                                      \
      ::std::cerr << ::termcolor::bright_blue << __FILE__ << ":" << __LINE__ \
                  << ": " << ::termcolor::reset << ::termcolor::red          \
                  << "assertion failed" << ::termcolor::reset << ::std::endl \
                  << ::termcolor::bright_grey                                \
                  << "   expression: " << ::termcolor::reset                 \
                  << ::termcolor::yellow << #condition << ::std::endl        \
                  << ::termcolor::bright_grey                                \
                  << "  description: " << ::termcolor::reset                 \
                  << ::termcolor::reset << ::termcolor::bold << message      \
                  << ::termcolor::reset << ::std::endl                       \
                  << ::std::endl;                                            \
      ::std::abort();                                                        \
    }                                                                        \
  }
#endif

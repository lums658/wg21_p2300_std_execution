/*
 * Copyright (c) Lucian Radu Teodorescu
 *
 * Licensed under the Apache License Version 2.0 with LLVM Exceptions
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *   https://llvm.org/LICENSE.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <execution.hpp>

namespace ex = std::execution;

//! Used for debugging, to generate errors to the console
template <typename T>
struct type_printer;

//! Used in various sender types queries
template <typename... Ts>
struct type_array {};

//! Used as a default empty context
struct empty_env {};

//! Check that the value_types of a sender matches the expected type
template <typename ExpectedValType, typename Env = empty_env, typename S>
inline void check_val_types(S snd) {
  using t = typename ex::completion_signatures_of_t<S, Env>::template value_types<type_array, type_array>;
  static_assert(std::is_same<t, ExpectedValType>::value);
}

//! Check that the error_types of a sender matches the expected type
template <typename ExpectedValType, typename Env = empty_env, typename S>
inline void check_err_types(S snd) {
  using t = typename ex::completion_signatures_of_t<S, Env>::template error_types<type_array>;
  static_assert(std::is_same<t, ExpectedValType>::value);
}

//! Check that the sends_stopped of a sender matches the expected value
template <bool Expected, typename Env = empty_env, typename S>
inline void check_sends_stopped(S snd) {
  constexpr bool val = ex::completion_signatures_of_t<S, Env>::sends_stopped;
  static_assert(val == Expected);
}

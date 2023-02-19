#pragma once
#include <exception>
#include <iostream>

// This file contains a package of ad-hoc error handling routines

enum class Error_action {
  ignore,
  throwing,
  terminating,
  logging,
};

constexpr Error_action default_error_action = Error_action::throwing;

enum class Error_code {
  range_error,
  length_error,
};

std::string error_code_name[]{
    "range error",
    "length error",
};

template <Error_action action = default_error_action, class C>
constexpr void expect(C cond, Error_code x) {
  if constexpr (action == Error_action::logging)
    if (!cond())
      std::cerr << "expect() failure: " << int(x) << ' '
                << error_code_name[int(x)] << '\n';
  if constexpr (action == Error_action::throwing)
    if(!cond()) throw x;
  if constexpr (action == Error_action::terminating)
    if(!cond()) std::terminate();
}

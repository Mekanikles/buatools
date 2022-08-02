#pragma once

#include <gsl/pointers>

namespace bua
{

using uint = unsigned int;
using u64 = unsigned long long;
using u32 = unsigned int;
using s64 = long long;
using s32 = int;
using u8 = unsigned char;
using s8 = char;

template<typename T>
using not_null = gsl::not_null<T>;

}

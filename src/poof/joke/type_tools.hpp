#pragma once

#include <utility>

template <class T1, class T2>
using SumType = decltype(std::declval<T1>() + std::declval<T2>());

template <class T1, class T2>
using DiffType = decltype(std::declval<T1>() - std::declval<T2>());

template <class T1, class T2>
using ProdType = decltype(std::declval<T1>() * std::declval<T2>());

template <class T1, class T2>
using DivType = decltype(std::declval<T1>() / std::declval<T2>());

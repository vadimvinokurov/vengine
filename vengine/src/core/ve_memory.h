﻿#pragma once

#include <memory>

namespace VE {
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;
}
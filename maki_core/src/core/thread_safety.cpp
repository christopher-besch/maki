#include "pch.h"

#include "thread_safety.h"

namespace Maki {

#ifndef NDEBUG
thread_local ThreadType g_thread_type {};
#endif

} // namespace Maki

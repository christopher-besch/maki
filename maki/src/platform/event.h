#pragma once

#include <functional>

#include "platform/keys.h"

namespace Maki {

struct EventHandler {
    // return true when event handled and not to be passed to next layer
    std::function<bool(double pos_x, double pos_y)>       on_mouse_move {nullptr};
    std::function<bool(double offset_x, double offset_y)> on_scroll {nullptr};
    std::function<bool(MouseBtn btn)>                     on_mouse_btn_press {nullptr};
    std::function<bool(MouseBtn btn)>                     on_mouse_btn_release {nullptr};
    std::function<bool(Key key)>                          on_key_press {nullptr};
    std::function<bool(Key key)>                          on_key_repeat {nullptr};
    std::function<bool(Key key)>                          on_key_release {nullptr};
    std::function<bool(int width, int height)>            on_window_resize {nullptr};
    // these might also be worth implementing:
    // on_window_close
    // on_window_lose_focus
    // on_window_gain_focus
    // on_window_minimize
    // on_window_unminimize
};

} // namespace Maki

#pragma once

#include <memory>   // for allocator, make_shared, __shared_ptr_access
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Collapsible, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                  // for text, hbox, Element

#include "key_input.hpp"
#include "grid_container.hpp"
#include "../../include/mage_const.h"
#include "../keycode.h"
#include "../serial.h"


void run_tui(int SERIAL_USB, uint8_t* config_keycodes);

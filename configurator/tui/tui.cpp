#include "tui.h"

using namespace ftxui;

void run_tui(uint8_t* config_keycodes) {
	std::string config[(mage_const::NUMBER_OF_KEYS_IN_PLANK * 3) + 8];

	std::vector<std::vector<Component>> grid;
	grid.emplace_back();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < mage_const::NUMBER_OF_KEYS_IN_COLUMN; j++) {
			for (int k = 0; k < mage_const::NUMBER_OF_KEYS_IN_ROW; k++) {
				uint8_t index = (mage_const::NUMBER_OF_KEYS_IN_PLANK * i) + (j * mage_const::NUMBER_OF_KEYS_IN_ROW) + k;
				config[index] = mage::keycode_names[config_keycodes[index]];
				grid.back().push_back(mage::MakeKeyInput(config[index], k, j, i, config_keycodes));
			}
			grid.emplace_back();
		}
		for (int k = 0; k < mage_const::NUMBER_OF_KEYS_IN_ROW; k++) {
			grid.back().push_back(mage::MakeDisabledKeyInput());
		}
		grid.emplace_back();
	}

	for (int k = 0; k < 3; k++) {
		grid.back().push_back(mage::MakeDisabledKeyInput());
	}
	for (int k = 0; k < mage_const::NUMBER_OF_KEYS_IN_CONTROL_GROUP * 2; k++) {
		uint8_t index = (mage_const::NUMBER_OF_KEYS_IN_PLANK * 3) + k;
		config[index] = mage::keycode_names[config_keycodes[index]];
		grid.back().push_back(mage::MakeKeyInput(config[index], k / 4, k % 4, 3, config_keycodes));
	}
	for (int k = 0; k < 3; k++) {
		grid.back().push_back(mage::MakeDisabledKeyInput());
	}


	auto component = MakeGridContainer(grid);

	auto screen = ScreenInteractive::TerminalOutput();

	component |= CatchEvent([&](Event event) {
		if (component->ActiveChild() && component->ActiveChild()->OnEvent(event)) {
			return true;
		}
		/// Allow leaving the tui
		if (event == Event::Character('q') || event == Event::Escape) {
			screen.ExitLoopClosure()();
			return true;
		}

		return false;
	});

	screen.Loop(component);
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

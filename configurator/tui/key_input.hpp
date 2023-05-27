#pragma once
#include <stdint.h>    // for uint32_t
#include <algorithm>   // for max, min
#include <cstddef>     // for size_t
#include <functional>  // for function
#include <memory>   // for allocator, shared_ptr, allocator_traits<>::value_type
#include <sstream>  // for basic_istream, stringstream
#include <string>   // for string, basic_string, operator==, getline
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/captured_mouse.hpp"     // for CapturedMouse
#include "ftxui/component/component.hpp"          // for Make, Input
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/event.hpp"  // for Event, Event::ArrowDown, Event::ArrowLeft, Event::ArrowLeftCtrl, Event::ArrowRight, Event::ArrowRightCtrl, Event::ArrowUp, Event::Backspace, Event::Delete, Event::End, Event::Home, Event::Return
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Pressed
#include "ftxui/component/screen_interactive.hpp"  // for Component
#include "ftxui/dom/elements.hpp"  // for operator|, reflect, text, Element, xflex, hbox, Elements, frame, operator|=, vbox, focus, focusCursorBarBlinking, select
#include "ftxui/screen/box.hpp"    // for Box
#include "ftxui/screen/string.hpp"           // for string_width
#include "ftxui/util/ref.hpp"                // for StringRef, Ref
#include "ftxui/../../src/ftxui/screen/string_internal.hpp" // This is terrible and I am so sorry you had to look at it. However, I have no idea how to access this file other than this so you can blame Arthur Sonzogni for how he designed this library.


namespace mage {

using namespace ftxui;

template <typename T>
inline T clamp(T value, T min, T max) {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	return value;
}

// An input box. The user can type text into it.
class KeyInput : public ComponentBase {
	public:
	// NOLINTNEXTLINE
	KeyInput(StringRef content, const std::string& start = "", bool disabled = false, Ref<InputOption> option = {})
		: content_(std::move(content)), option_(std::move(option)), disabled(disabled) {
		if (start != "") {
			option_->cursor_position = start.length();
			*content_ = start;
		}
		else {
			option_->cursor_position = content_->length();
		}
	}

	KeyInput()
		: content_(""), option_({}), disabled(true) {
	}

	private:
	bool taking_input = false;
	bool disabled = false;
	// Component implementation:
	Element Render() override {
		const bool is_focused = Focused();

		auto transform = option_->transform ? option_->transform
										 : InputOption::Default().transform;


		if (!this->taking_input) {
			// Just output text if the box is no selected
			Element element;
			if (disabled) {
				element = text("");
			}
			else {
				element = text(*content_);
			}

			element = element | flex | frame;

			return transform({
				std::move(element), hovered_, is_focused,
				true}) | reflect(box_);
		}


		const auto focused =
		  (is_focused || hovered_) ? focusCursorBarBlinking : ftxui::select;

		int& cursor_position = option_->cursor_position();
		cursor_position = clamp(cursor_position, 0, (int)content_->size());

		Element element;
		const std::string& content_text = *content_;
		if (cursor_position == (int)content_->size()) {
			element = hbox({
				Text(content_text),
				text("|") | focused
			  }) |
			xflex;
		}
		else {
			const int glyph_start = cursor_position;
			const int glyph_end = GlyphNext(content_text, glyph_start);
			const std::string part_before_cursor = content_text.substr(0, glyph_start);
			const std::string part_at_cursor = content_text.substr(glyph_start, glyph_end - glyph_start);
			const std::string part_after_cursor = content_text.substr(glyph_end);
			element = hbox({
				Text(part_before_cursor),
				Text("|" + part_at_cursor) | focused | reflect(cursor_box_),
				Text(part_after_cursor),
			  }) | xflex;
		}

		if (is_focused) {
			element |= focus;
		}

		if (this->taking_input) {
			element |= color(Color::BlueLight);
		}

		return transform({
			std::move(element), hovered_, is_focused,
			false
		  }) |
		  xflex | reflect(box_);
	}

	Element Text(const std::string& input) {
		return text(input);
	}

	bool HandleReturn() {
		if (this->disabled) {
			return false;
		}
		this->taking_input = !this->taking_input;
		return true;
	}

	bool HandleEscape() {
		if (this->disabled) {
			return false;
		}
		if (this->taking_input) {
			this->taking_input = false;
			return true;
		}
		return false;
	}

	bool HandleCharacter(std::string character) {
		if (character == "\n") {
			option_->on_enter();
			return false;
		}

		if (this->taking_input) {
			int& cursor_position = option_->cursor_position();
			content_->insert(cursor_position, character);
			cursor_position += character.size();
			option_->on_change();
		}

		return true;
	}

	bool HandleArrowLeft() {
		if (!this->taking_input) {
			return false;
		}
		int& cursor_position = option_->cursor_position();
		if (cursor_position == 0) {
			return true;
		}

		cursor_position = GlyphPrevious(content_(), cursor_position);
		return true;
	}

	bool HandleArrowRight() {
		if (!this->taking_input) {
			return false;
		}
		int& cursor_position = option_->cursor_position();
		if (cursor_position == (int)content_->size()) {
			return true;
		}

		cursor_position = GlyphNext(content_(), cursor_position);
		return true;
	}

	bool HandleBackspace() {
		int& cursor_position = option_->cursor_position();
		if (cursor_position == 0) {
			return false;
		}
		const size_t start = GlyphPrevious(content_(), cursor_position);
		const size_t end = cursor_position;
		content_->erase(start, end - start);
		cursor_position = start;
		return true;
	}

	bool HandleDelete() {
		int& cursor_position = option_->cursor_position();
		if (cursor_position == (int)content_->size()) {
			return false;
		}
		const size_t start = cursor_position;
		const size_t end = GlyphNext(content_(), cursor_position);
		content_->erase(start, end - start);
		return true;
	}


	bool OnEvent(Event event) override {
		int& cursor_position = option_->cursor_position();
		cursor_position = clamp(cursor_position, 0, (int)content_->size());


		if (event.is_mouse()) {
			return HandleMouse(event);
		}
		if (event == Event::Return) {
			return HandleReturn();
		}
		if (event == Event::Escape) {
			return HandleEscape();
		}
		if (event.is_character()) {
			return HandleCharacter(event.character());
		}

		if (!this->taking_input) {
			return false;
		}


		if (event == Event::Backspace) {
			return HandleBackspace();
		}
		if (event == Event::Delete) {
			return HandleDelete();
		}
		if (event == Event::ArrowLeft) {
			return HandleArrowLeft();
		}
		if (event == Event::ArrowRight) {
			return HandleArrowRight();
		}
		if (event == Event::ArrowLeftCtrl) {
			return HandleLeftCtrl();
		}
		if (event == Event::ArrowRightCtrl) {
			return HandleRightCtrl();
		}

		return false;
	}

	bool HandleLeftCtrl() {
		// TODO: Handle Left CTRL
		return true;
	}

	bool HandleRightCtrl() {
		// TODO: Handle Right CTRL
		return true;
	}

	bool HandleMouse(Event event) {
		hovered_ = box_.Contain(event.mouse().x,	//
								event.mouse().y) &&
		CaptureMouse(event);
		if (!hovered_) {
			return false;
		}

		if (event.mouse().button != Mouse::Left ||
			event.mouse().motion != Mouse::Pressed) {
			return false;
		}

		TakeFocus();

		if (content_->empty()) {
			option_->cursor_position() = 0;
			return true;
		}

		// Find the line and index of the cursor.
		std::string& text = *content_;
		int& cursor_position = option_->cursor_position();

		int cursor_column = cursor_position;

		int new_cursor_column = cursor_column + event.mouse().x - cursor_box_.x_min;

		new_cursor_column = clamp(new_cursor_column, 0, (int)text.length());

		if (new_cursor_column == cursor_column) {
			return false;
		}

		return true;
	}

	bool Focusable() const final { return true; }

	bool hovered_ = false;
	StringRef content_;

	Box box_;
	Box cursor_box_;
	Ref<InputOption> option_;
};

  inline ftxui::Component MakeKeyInput(ftxui::StringRef content, const std::string& start = "", ftxui::Ref<ftxui::InputOption> option = {}) {
	return Make<KeyInput>(content, start, false, option);
  }

  inline ftxui::Component MakeDisabledKeyInput() {
	return Make<KeyInput>();
  }

}	// namespace mage

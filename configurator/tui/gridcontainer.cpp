#include "gridcontainer.hpp"
#include "key_input.hpp"

using namespace ftxui;

class ContainerBase : public ComponentBase {
public:
  ContainerBase(Components children, int* selector)
	: selector_(selector ? selector : &selected_) {
	for (Component& child : children) {
	  Add(std::move(child));
	}
  }

  // Component override.
  bool OnEvent(Event event) override {
	if (event.is_mouse()) {
	  return OnMouseEvent(event);
	}

	if (!Focused()) {
	  return false;
	}

	if (ActiveChild() && ActiveChild()->OnEvent(event)) {
	  return true;
	}

	return EventHandler(event);
  }

  Component ActiveChild() override {
	if (children_.empty()) {
	  return nullptr;
	}

	return children_[static_cast<size_t>(*selector_) % children_.size()];
  }

  void SetActiveChild(ComponentBase* child) override {
	for (size_t i = 0; i < children_.size(); ++i) {
	  if (children_[i].get() == child) {
		*selector_ = static_cast<int>(i);
		return;
	  }
	}
  }

protected:
  // Handlers
  virtual bool EventHandler(Event /*unused*/) { return false; }  // NOLINT

  virtual bool OnMouseEvent(Event event) {
	return ComponentBase::OnEvent(std::move(event));
  }

  int selected_ = 0;
  int* selector_ = nullptr;

  void MoveSelector(int dir) {
	for (int i = *selector_ + dir; i >= 0 && i < int(children_.size());
		 i += dir) {
	  if (children_[i]->Focusable()) {
		*selector_ = i;
		return;
	  }
	}
  }

  void MoveSelectorWrap(int dir) {
	if (children_.empty()) {
	  return;
	}
	for (size_t offset = 1; offset < children_.size(); ++offset) {
	  const size_t i = ((size_t(*selector_ + offset * dir + children_.size())) %
						children_.size());
	  if (children_[i]->Focusable()) {
		*selector_ = int(i);
		return;
	  }
	}
  }
};


std::vector<Component> squash_vec_vec(const std::vector<std::vector<Component>>& vec_vec) {
  std::vector<Component> out;
  for (auto& line : vec_vec) {
	for (auto& elem : line) {
	  out.push_back(elem);
	}
  }
  return out;
}

class GridContainer : public ContainerBase {
public:

  std::ofstream log_file;
  std::vector<std::vector<Component>> lines;
  int selectorx, selectory, dummy_selector;

	GridContainer(std::vector<std::vector<Component>> component_lines, int selectorx = 0, int selectory = 0) : ContainerBase(squash_vec_vec(component_lines), &dummy_selector), lines(std::move(component_lines)), selectorx(selectorx), selectory(selectory) {
		log_file.open("log.log");
		dummy_selector = 0;
	}

	void clamp_selectors() {
		if (selectory < 0) {
			selectory = 0;
		}
		else if (selectory >= (int)lines.size()) {
			selectory = lines.size() - 1;
		}
		if (selectorx < 0) {
			selectorx = 0;
		}
		else if (selectorx >= (int)lines[selectory].size()) {
			selectorx = lines[selectory].size() - 1;
		}
	}

  Element Render() override {
	std::vector<Elements> elements;
	for (auto& line : lines) {
	  elements.emplace_back();
	  for (auto& it : line) {
		elements.back().push_back(it->Render());
	  }
	}
	if (elements.empty()) {
	  return text("Empty container");
	}
	return gridbox(std::move(elements));
  }


  Component ActiveChild() override {
	if (lines.empty()) {
	  return nullptr;
	}

	clamp_selectors();
	return lines[selectory][selectorx];
  }

  void SetActiveChild(ComponentBase* child) override {
	for (size_t i = 0; i < lines.size(); i++) {
	  for (size_t j = 0; i < lines[i].size(); ++j) {
		if (lines[i][j].get() == child) {
		  selectory = i;
		  selectorx = j;
		  return;
		}
	  }
	}
  }

  void MoveSelectorX(int dir) {
	auto& line = lines[selectory];
	for (int i = selectorx + dir; i >= 0 && i < int(line.size());
		 i += dir) {
	  if (line[i]->Focusable()) {
		selectorx = i;
		return;
	  }
	}
  }

  void MoveSelectorWrapX(int dir) {
	auto& line = lines[selectory];
	if (line.empty()) {
	  return;
	}
	for (size_t offset = 1; offset < line.size(); ++offset) {
	  const size_t i = ((size_t(selectorx + offset * dir + line.size())) %
						line.size());
	  if (line[i]->Focusable()) {
		selectorx = int(i);
		return;
	  }
	}
  }

  void MoveSelectorY(int dir) {
	for (int i = selectory + dir; i >= 0 && i < int(lines.size());
		 i += dir) {
	  if (lines[i][selectorx]->Focusable()) {
		selectory = i;
		return;
	  }
	}
  }

  void MoveSelectorWrapY(int dir) {
	if (lines.empty()) {
	  return;
	}
	for (size_t offset = 1; offset < lines.size(); ++offset) {
	  const size_t i = ((size_t(selectory + offset * dir + lines.size())) %
						lines.size());
	  if (lines[i][selectorx]->Focusable()) {
		selectory = int(i);
		return;
	  }
	}
  }

  void MoveSelectorWrapXandY(int dir) {
	auto& line = lines[selectory];
	if (line.empty()) {
	  return;
	}
	for (size_t offset = 1; offset < line.size(); ++offset) {
	  size_t i = (size_t(selectorx + offset * dir + line.size()));
	  if (i > line.size()) {
		MoveSelectorWrapY(+1);
	  }
	  if (i < 0) {
		MoveSelectorWrapY(-1);
	  }

	  i = i % line.size();
	  if (line[i]->Focusable()) {
		selectorx = int(i);
		return;
	  }
	}
  }

  bool EventHandler(Event event) override {
	const int old_selected_x = selectorx;
	const int old_selected_y = selectory;
	if (event == Event::ArrowUp || event.character() == "k") {
	  MoveSelectorY(-1);
	}
	if (event == Event::ArrowDown || event == Event::Character('j')) {
	  MoveSelectorY(+1);
	}
	if (event == Event::ArrowLeft || event == Event::Character('h')) {
	  MoveSelectorX(-1);
	}
	if (event == Event::ArrowRight || event == Event::Character('l')) {
	  MoveSelectorX(+1);
	}

	if (event == Event::PageUp) {
	  for (int i = 0; i < box_.y_max - box_.y_min; ++i) {
		MoveSelectorY(-1);
	  }
	}
	if (event == Event::PageDown) {
	  for (int i = 0; i < box_.y_max - box_.y_min; ++i) {
		MoveSelectorY(1);
	  }
	}
	if (event == Event::Home) {
	  for (size_t i = 0; i < children_.size(); ++i) {
		MoveSelectorX(-1);
	  }
	}
	if (event == Event::End) {
	  for (size_t i = 0; i < children_.size(); ++i) {
		MoveSelectorX(1);
	  }
	}
	if (event == Event::Tab) {
	  MoveSelectorWrapXandY(+1);
	}
	if (event == Event::TabReverse) {
	  MoveSelectorWrapXandY(-1);
	}

	clamp_selectors();
	return old_selected_x != selectorx || old_selected_y != selectory;
  }

  bool OnMouseEvent(Event event) override {
	if (ContainerBase::OnMouseEvent(event)) {
	  return true;
	}

	if (event.mouse().button != Mouse::WheelUp &&
		event.mouse().button != Mouse::WheelDown) {
	  return false;
	}

	if (!box_.Contain(event.mouse().x, event.mouse().y)) {
	  return false;
	}

	if (event.mouse().button == Mouse::WheelUp) {
	  MoveSelectorY(-1);
	}
	if (event.mouse().button == Mouse::WheelDown) {
	  MoveSelectorY(+1);
	}

	clamp_selectors();
	return true;
  }



  Box box_;
};


Component MakeGridContainer(const std::vector<std::vector<Component>>& lines, int selectorx, int selectory) {
   return std::make_shared<GridContainer>(lines, selectorx, selectory);
}

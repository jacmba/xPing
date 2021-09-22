#pragma once

#include <imgwindow.h>

class AcarsWindow : public ImgWindow {
public:
	explicit AcarsWindow(ImFontAtlas* fontAtlas = nullptr);
	~AcarsWindow() final = default;

protected:
	void BuildInterface() override;
};


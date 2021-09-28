#pragma once

#include <imgwindow.h>
#include <string>

class AcarsWindow : public ImgWindow {
public:
	explicit AcarsWindow(ImFontAtlas* fontAtlas = nullptr);
	~AcarsWindow() final = default;

protected:
	void BuildInterface() override;

private:
	std::string globalText;
};


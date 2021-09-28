#pragma once

#include <imgwindow.h>
#include <string>

#define GREEN ImVec4(0, 1, 0, 1)
#define BLUE ImVec4(0.68, 0.85, 0.9, 1)

class AcarsWindow : public ImgWindow {
public:
	explicit AcarsWindow(ImFontAtlas* fontAtlas = nullptr);
	~AcarsWindow() final = default;

protected:
	void BuildInterface() override;

private:
	std::string globalText;
	char scratchBuff[128] = "";
	std::string lText[4];
	std::string rText[4];
};


#include "AcarsWindow.h"
#include <cstring>

AcarsWindow::AcarsWindow(ImFontAtlas* fontAtlas) : ImgWindow(fontAtlas) {
	globalText = "xPing CPDLC ACARS - Jacinto Mba 2021";
	Init(600, 300, 200, 500);
}

void AcarsWindow::BuildInterface() {

	ImGui::BeginGroup();
	for (int i = 0; i < 4; i++) {
		ImGui::PushID(100 + i);
		if (ImGui::Button(">")) {
			lText[i] = scratchBuff;
		}
		ImGui::PopID();
	}
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginChild("Screen", ImVec2(525, 200), true);
	for (int i = 0; i < 4; i++) {
		ImGui::TextColored(BLUE, lText[i].c_str());
		ImGui::SameLine();
		ImGui::TextColored(BLUE, rText[i].c_str());
	}
	ImGui::TextColored(GREEN, globalText.c_str());
	ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginGroup();
	for (int i = 0; i < 4; i++) {
		ImGui::PushID(200 + i);
		if (ImGui::Button("<")) {
			rText[i] = scratchBuff;
		}
		ImGui::PopID();
	}
	ImGui::EndGroup();
	
	ImVec2 pos = ImGui::GetCursorPos();
	pos.x += 50;
	ImGui::SetCursorPos(pos);
	ImGui::InputText("", scratchBuff, IM_ARRAYSIZE(scratchBuff));
}

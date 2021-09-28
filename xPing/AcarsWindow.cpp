#include "AcarsWindow.h"
#include <cstring>

AcarsWindow::AcarsWindow(ImFontAtlas* fontAtlas) : ImgWindow(fontAtlas) {
	globalText = "";
	Init(600, 300, 200, 500);
}

void AcarsWindow::BuildInterface() {
	ImGui::BeginGroup();
	for (int i = 1; i <= 4; i++) {
		ImGui::PushID(100 + i);
		if (ImGui::Button(">")) {
			globalText = "L" + std::to_string(i);
		}
		ImGui::PopID();
	}
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginChild("Screen", ImVec2(525, 200), true);
	ImGui::TextColored(ImVec4(0, 1, 0, 1), globalText.c_str());
	ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginGroup();
	for (int i = 1; i <= 4; i++) {
		ImGui::PushID(200 + i);
		if (ImGui::Button("<")) {
			globalText = "R" + std::to_string(i);
		}
		ImGui::PopID();
	}
	ImGui::EndGroup();
}

#include "AcarsWindow.h"

AcarsWindow::AcarsWindow(ImFontAtlas* fontAtlas) : ImgWindow(fontAtlas) {
	Init(600, 400, 200, 200);
}

void AcarsWindow::BuildInterface() {
	ImGui::Text("Hello imgui!!");
	ImGui::Text("This is gonna be an awesome ACARS window");
	ImGui::Text("By Jacinto Mba");
}

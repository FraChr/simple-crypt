#include "RenderCmd.h"
#include <iostream>

void RenderCmd::WriteOut(const std::string_view &text) {
    WriteOutMaster(text);
}

void RenderCmd::WriteError(const std::string_view &text) {
    WriteOutMaster(text);
}

void RenderCmd::WriteOutMaster(const std::string_view &text) {
    if (text.empty()) return;
    std::cout << text << std::endl;
}
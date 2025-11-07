#pragma once
#include <string>

class RenderCmd {
    public:
        static void WriteOut(const std::string_view &text);
        static void WriteError(const std::string_view &text);
    private:
        static void WriteOutMaster(const std::string_view &text);
};

#pragma once

#include <functional>
/*#include "POD/file.h"*/
struct FileInfo;
using CommandFunc = std::function<void( FileInfo&)>;

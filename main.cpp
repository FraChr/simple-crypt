#include "Builder/Builder.h"
#include "SimpleCrypt.h"

int main(const int argc, char *argv[]) {
    Builder builder(argc, argv);
    const auto app = builder.Build();
    app.Run();
    return 0;
}
#include <iostream>
#include <spdlog/spdlog.h>
#include "pushdeer.h"

int main() {
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    spdlog::set_level(spdlog::level::info);

    auto pushdeer =
        Pushdeer::Pushdeer("PDU1549TDgJhw6oNVKBSzvBeVGOSJkrRn8ynXfA4");
    pushdeer.send_text("hello world", "optional description");
    pushdeer.send_markdown("# hello world", "**optional** description in markdown");
    pushdeer.send_image("https://github.com/easychen/pushdeer/raw/main/doc/image/clipcode.png");
    pushdeer.send_image(
        "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVQYV2NgYAAAAAMAAWgmWQ0AAAAASUVORK5CYII=");
}
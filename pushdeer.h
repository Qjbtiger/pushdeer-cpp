#ifndef INCLUDE_PUSHDEER_H
#define INCLUDE_PUSHDEER_H

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Pushdeer {
class Pushdeer {
    public:
        std::string server;
        std::string endpoint;
        std::string pushkey;

    private:
        bool _push(std::string text, std::string desp = "",
                 std::string server = "", std::string pushkey = "",
                 std::string textType = "");

    public:
        Pushdeer();
        Pushdeer(std::string pushkey);
        Pushdeer(std::string server, std::string pushkey);

        ~Pushdeer();

        bool send_text(std::string text, std::string desp = "",
                       std::string server = "", std::string pushkey = "");
        bool send_markdown(std::string text, std::string desp = "",
                           std::string server = "", std::string pushkey = "");
        bool send_image(std::string imageSrc, std::string desp = "",
                        std::string server = "", std::string pushkey = "");
};

inline bool Pushdeer::_push(std::string text, std::string desp,
                            std::string server, std::string pushkey,
                            std::string textType) {
    if (server.empty()) {
        if (this->server.empty()) {
            spdlog::warn("PushDeer: server is empty, skip sending text");
            return false;
        } else {
            server = this->server;
        }
    }

    if (pushkey.empty()) {
        if (this->pushkey.empty()) {
            spdlog::warn("PushDeer: pushkey is empty, skip sending text");
            return false;
        } else {
            pushkey = this->pushkey;
        }
    }
    cpr::Response r = cpr::Post(cpr::Url{server + this->endpoint},
                                cpr::Parameters{
                                    {"pushkey", pushkey},
                                    {"text", text},
                                    {"type", textType},
                                    {"desp", desp}
                                });

    if (r.status_code != 200) {
        spdlog::warn("PushDeer: send text failed, status code: {}", r.status_code);
        return false;
    }

    spdlog::info("PushDeer: send text successfully");
    return true;
}

inline Pushdeer::Pushdeer(std::string server, std::string pushkey) {
    this->server = "https://api2.pushdeer.com";
    this->endpoint = "/message/push";

    if (!server.empty()) {
        this->server = server;
    } else {
        spdlog::warn("PushDeer: server is empty, use default server: {}", this->server);
    }

    if (!pushkey.empty()) {
        this->pushkey = pushkey;
    } else {
        spdlog::warn("PushDeer: pushkey is empty, use default pushdeer: {}", this->pushkey);
    }
}

inline Pushdeer::Pushdeer(std::string pushkey)
    :Pushdeer("", pushkey) {}

inline Pushdeer::Pushdeer()
    :Pushdeer("", "") {}

inline Pushdeer::~Pushdeer() {
}

inline bool Pushdeer::send_text(std::string text, std::string desp,
                                std::string server, std::string pushkey) {
    return this->_push(text, desp, server, pushkey, "text");
}

inline bool Pushdeer::send_markdown(std::string text, std::string desp,
                                    std::string server, std::string pushkey) {
    return this->_push(text, desp, server, pushkey, "markdown");
}

inline bool Pushdeer::send_image(std::string imageSrc, std::string desp,
                                 std::string server, std::string pushkey) {
    return this->_push(imageSrc, desp, server, pushkey, "image");
}

} // namespace Pushdeer
#endif // INCLUDE_PUSHDEER_H
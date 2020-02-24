#include <rpc/server.h>
#include <spdlog/logger.h>

#include <nlohmann/json.hpp>

#include "backends/aria2/aria2fetcher.h"
#include "downserver.h"
#include "fetcher.hpp"

std::shared_ptr<spdlog::logger> kDefaultLogger;

int main(int argc, char* argv[]) {
    rpc::server srv(8080);

#if BACKEND == ARIA2
    DownServer server{std::make_unique<AriaFetcher>()};
#endif
    srv.bind("list", [&server]() -> std::string {
        nlohmann::json obj;
        return obj.dump();
    });
    srv.bind("add", [&server](const std::string& url) -> bool {
        return server.add(url);
    });
    server.start();
    srv.run();
    server.stop();
    return 0;
}

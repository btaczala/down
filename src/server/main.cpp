#include <rpc/server.h>

#include <nlohmann/json.hpp>

#include "downserver.h"
#include "fetcher.hpp"

class DummyFetcher : public IFetcher {
    virtual void start(const std::string& url) override {}
};

int main(int argc, char* argv[]) {
    rpc::server srv(8080);

    DownServer server{std::make_unique<DummyFetcher>()};
    srv.bind("list", [&server]() -> std::string {
        nlohmann::json obj;
        return obj.dump();
    });
    srv.bind(
        "add",
        [&server](const std::string& url, const std::string& path) -> bool {
            return server.add(url, path);
        });
    server.start();
    srv.run();
    server.stop();
    return 0;
}

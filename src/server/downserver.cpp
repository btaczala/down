#include "downserver.h"

#include <filesystem>

#include "fetcher.hpp"
#include "log.h"

namespace {
const std::string kDefaultPath = std::filesystem::current_path();
}

DownServer::DownServer(std::unique_ptr<IFetcher> &&fetcher)
    : _fetcher(std::move(fetcher)) {}

DownServer::~DownServer() { stop(); }

void DownServer::start() {
    dm_info("Starting server");
    _fetcher->run();
}
void DownServer::stop() {
    dm_info("Stopping server");
    _fetcher->stop();
}

bool DownServer::add(const std::string &uri, const std::string &path) {
    const std::string localPath = path.empty() ? kDefaultPath : path;
    dm_info("Adding {}", uri);
    const auto id = _fetcher->add(uri, path);
    dm_debug("Added id={}", id);

    return !id.empty();
}

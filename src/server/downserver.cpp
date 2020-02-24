#include "downserver.h"

#include "fetcher.hpp"

namespace {
const std::string kDefaultPath = "/downloads";
}

DownServer::DownServer(std::unique_ptr<IFetcher> &&fetcher)
    : _fetcher(std::move(fetcher)) {}

void DownServer::start() {}
void DownServer::stop() {}

bool DownServer::add(const std::string &where, const std::string &path) {
    const std::string localPath = path.empty() ? kDefaultPath : path;

    return false;
}

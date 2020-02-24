#include "aria2fetcher.h"

#include <iostream>

#include "log.h"

namespace {
void deleteSession(aria2::Session* s) { aria2::sessionFinal(s); }
int downloadEventCallback(aria2::Session* session, aria2::DownloadEvent event,
                          aria2::A2Gid gid, void* userData) {
    dm_debug("downloadEventCallback");
    AriaFetcher* aria = static_cast<AriaFetcher*>(userData);
    switch (event) {
        case aria2::EVENT_ON_DOWNLOAD_COMPLETE:
            dm_info("Download {} completed", aria2::gidToHex(gid));
            aria->triggerCallback(aria2::gidToHex(gid),
                                  DownloadState::Finished);
            break;
        case aria2::EVENT_ON_DOWNLOAD_ERROR:
            dm_info("Download {} error", gid);
            break;
        default:
            return 0;
    }
    dm_info("{}", aria2::gidToHex(gid));
    return 1;
}

aria2::Session* createSession(AriaFetcher* thiz) {
    aria2::libraryInit();
    aria2::SessionConfig config;
    // Add event callback
    config.downloadEventCallback = downloadEventCallback;
    config.userData = static_cast<void*>(thiz);
    return aria2::sessionNew(aria2::KeyVals(), config);
}

}  // namespace

AriaFetcher::AriaFetcher() : _session(createSession(this), deleteSession) {
    _running.store(false);
}
AriaFetcher::~AriaFetcher() { stop(); }

void AriaFetcher::run() {
    dm_info("AriaFetcher::run()");
    if (_running.load() == true) {
        dm_warn("Aria2 already running");
        return;
    }

    _running.store(true);
    _ariaThread = std::move(std::thread{[this]() {
        dm_debug("Staring aria2 thread");
        int rv{0};
        while (_running.load()) {
            {
                std::lock_guard<std::mutex> lock{_ariaMutex};
                rv = aria2::run(_session.get(), aria2::RUN_ONCE);
            }
            dm_debug("loop {}", rv);
            if (rv < 0) {
                dm_error("aria2 error");
                break;
            } else if (rv == 0) {
                // sleep and wait for next downloads
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }
        dm_debug("bye bye");
    }});
}

void AriaFetcher::stop() {
    dm_debug("AriaFetcher::stop()");
    _running.store(false);
    if (_ariaThread.joinable()) {
        _ariaThread.join();
    }
}

std::string AriaFetcher::add(const std::string& url, const std::string& path) {
    dm_debug("Adding uri {} path={}", url, path);
    aria2::KeyVals options{std::make_pair("dir", path)};
    std::vector<std::string> urls;
    urls.push_back(url);
    aria2::A2Gid id;
    aria2::addUri(_session.get(), &id, urls, options);
    dm_debug("Added download uri={}, gid={}", url, aria2::gidToHex(id));
    return aria2::gidToHex(id);
}

DownloadEntry AriaFetcher::entry(const std::string& id) {
    {
        std::lock_guard<std::mutex> lock{_ariaMutex};
        const auto gid = aria2::hexToGid(id);
        const auto handle = aria2::getDownloadHandle(_session.get(), gid);

        if (!handle) {
            dm_error("Unable to find {}", gid);
            return DownloadEntry{};
        }

        if (handle->getFiles().size() == 0) {
            dm_warn("Info for file {} not available", gid);
        }

        for (const auto& f : handle->getFiles()) {
            dm_debug("File path{}, index={}, completed = {}", f.path, f.index,
                     f.completedLength);
        }
        aria2::deleteDownloadHandle(handle);
    }

    DownloadEntry entry{};

    return entry;
}

void AriaFetcher::triggerCallback(std::string id, DownloadState state) {
    if (_cb) {
        dm_debug("Triggering id = {}", id);
        _cb(id, state);
    }
}

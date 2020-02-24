#define CATCH_CONFIG_RUNNER

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <filesystem>

#include "aria2fetcher.h"
#include "catch.hpp"
#include "downserver.h"

std::shared_ptr<spdlog::logger> kDefaultLogger;

namespace {
const std::string kDefaultPath = std::filesystem::current_path();
}

TEST_CASE("start download server", "[aria2]") {
    AriaFetcher aria;
    aria.run();
}

TEST_CASE("double start", "[aria2]") {
    AriaFetcher aria;
    aria.run();
    aria.run();
    aria.run();
}

TEST_CASE("add uri", "[aria2]") {
    AriaFetcher aria;
    REQUIRE(!aria.add("http://www.google.com", kDefaultPath).empty());
}

TEST_CASE("add and run", "[aria2]") {
    AriaFetcher aria;
    const std::string id =
        aria.add("http://www.google.com/index.html", kDefaultPath);
    REQUIRE(!id.empty());

    bool finished = false;
    DownloadState localState = DownloadState::Stopped;

    aria.setCallback(
        [&finished, &localState](std::string id, DownloadState state) {
            finished = true;
            localState = state;
        });

    aria.run();

    while (!finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    REQUIRE(localState == DownloadState::Finished);
}

TEST_CASE("add and list", "[aria2]") {
    AriaFetcher aria;
    const std::string id =
        aria.add("http://www.google.com/index.html", kDefaultPath);
    REQUIRE(!id.empty());

    bool finished = false;
    DownloadState localState = DownloadState::Stopped;

    aria.setCallback(
        [&finished, &localState](std::string id, DownloadState state) {
            finished = true;
            localState = state;
        });

    aria.run();

    int counter = 0;

    while (!finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto info = aria.entry(id);
        counter++;
        if (counter > 5) break;
    }
    REQUIRE(localState == DownloadState::Finished);
    REQUIRE(counter < 5);
}

int main(int argc, char *argv[]) {
    bool haveDebug = std::getenv("DM_DEBUG") != nullptr;
    kDefaultLogger = spdlog::stdout_color_mt("download");
    if (haveDebug) {
        kDefaultLogger->set_level(spdlog::level::debug);
    }
    return Catch::Session().run(argc, argv);
}

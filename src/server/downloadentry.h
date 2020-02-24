
#ifndef DOWNLOADENTRY_H_Z8OE5CPO
#define DOWNLOADENTRY_H_Z8OE5CPO

#include <string>

enum class DownloadState { Stopped = 0, Running = 1, Finished = 2 };

struct DownloadEntry {
    bool isRunning;
    std::string url;
    std::string path;
};

#endif /* end of include guard: DOWNLOADENTRY_H_Z8OE5CPO */

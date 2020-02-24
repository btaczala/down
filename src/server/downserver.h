#ifndef DOWNSERVER_H_5GO61T2Y
#define DOWNSERVER_H_5GO61T2Y

#include <memory>

#include "downloadqueue.h"

class IFetcher;

struct DownServer {
    DownServer(std::unique_ptr<IFetcher>&& fetcher);
    ~DownServer();

    bool add(const std::string& where, const std::string& path = "");

    void start();
    void pause();
    void stop();

    void list();

   private:
    DownloadQueue _queue;
    const std::unique_ptr<IFetcher> _fetcher;
};

#endif /* end of include guard: DOWNSERVER_H_5GO61T2Y */

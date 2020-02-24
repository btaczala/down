
#ifndef ARIA2FETCHER_H_5TF2YWM4
#define ARIA2FETCHER_H_5TF2YWM4

#include <aria2/aria2.h>

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include "downloadentry.h"
#include "fetcher.hpp"
namespace aria2 {
struct Session;
}

using DownloadCallback = std::function<void(std::string, DownloadState)>;

class AriaFetcher : public IFetcher {
   public:
    AriaFetcher();
    virtual ~AriaFetcher();
    virtual void run() override;
    virtual void stop() override;
    virtual std::string add(const std::string& url,
                            const std::string& path) override;

    void setCallback(const DownloadCallback& cb) { _cb = cb; }
    void triggerCallback(std::string id, DownloadState state);
    DownloadEntry entry(const std::string& id);

   private:
    const std::unique_ptr<aria2::Session, void (*)(aria2::Session*)> _session;
    std::thread _ariaThread;
    std::mutex _ariaMutex;
    std::atomic_bool _running;
    DownloadCallback _cb;
};

#endif /* end of include guard: ARIA2FETCHER_H_5TF2YWM4 */

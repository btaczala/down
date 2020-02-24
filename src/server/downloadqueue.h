
#ifndef DOWNLOADQUEUE_H_9C6PFLP1
#define DOWNLOADQUEUE_H_9C6PFLP1

#include <vector>

#include "downloadentry.h"

struct DownloadQueue {
   private:
    std::vector<DownloadEntry> downloads;
};

#endif /* end of include guard: DOWNLOADQUEUE_H_9C6PFLP1 */

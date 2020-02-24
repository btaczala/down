#ifndef FETCHER_HPP_GIKL5QC6
#define FETCHER_HPP_GIKL5QC6

#include <string>

class IFetcher {
   public:
    virtual ~IFetcher() = default;
    virtual void run() = 0;
    virtual void stop() = 0;

    virtual std::string add(const std::string& url,
                            const std::string& path) = 0;
};

#endif /* end of include guard: FETCHER_HPP_GIKL5QC6 */

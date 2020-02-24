#ifndef FETCHER_HPP_GIKL5QC6
#define FETCHER_HPP_GIKL5QC6

#include <string>

class IFetcher {
   public:
    virtual ~IFetcher() = default;

    virtual void start(const std::string& url) = 0;
};

#endif /* end of include guard: FETCHER_HPP_GIKL5QC6 */

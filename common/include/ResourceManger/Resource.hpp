#pragma once

#include <string>

class Resource {
public:
    Resource() = delete;
    Resource(const std::string& path);
    virtual ~Resource() = default;

    const std::string& getPath() const;

    virtual void* getResource() = 0;

protected:
    std::string path;
};

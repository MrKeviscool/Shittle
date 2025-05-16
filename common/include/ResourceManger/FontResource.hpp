#include "Resource.hpp"

#include <SFML/Graphics/Font.hpp>

class FontResource : public Resource {
public:
    FontResource(const std::string& path);
    void* getResource() override;

protected:
    sf::Font font;
};
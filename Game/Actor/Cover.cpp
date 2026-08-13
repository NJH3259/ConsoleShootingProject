#include "Cover.h"

using namespace Craft;
Cover::Cover(const Craft::Vector2 position)
    :Actor("#", position, Color::Bright)
{
    typeId = 2; //type id 3 = Cover type
    sortingOrder = 5;
}

Cover::Cover(std::string& image, Craft::Vector2& position)
    :Actor(image, position, Color::Red)
{
    typeId = 3;
    sortingOrder = 5;
}

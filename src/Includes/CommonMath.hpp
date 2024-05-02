#ifndef CommonMath
#define CommonMath

#include <cmath> 
#include <SFML/System.hpp>
#include <vector>
#define M_PI           3.14159265358979323846  /* pi */


//handles applying rotations to objects, and formating data.
class WorldHelper {
public:
    //TYPES
    typedef std::vector<sf::Vector2f> T_PrimitiveShape;
    typedef std::vector<T_PrimitiveShape> T_WorldObjects;
    
    T_WorldObjects worldObjects;
    //funcitons

    WorldHelper();
};
sf::Vector2f* calc_hit(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);

#endif // M_PI

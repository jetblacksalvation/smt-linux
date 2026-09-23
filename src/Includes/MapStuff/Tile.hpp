#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <sfml/Graphics.hpp>
class Tile
{
public:
    Tile() = default;

    Tile(const nlohmann::json& json)
    {
        deserialize(json);
    }

    void deserialize(const nlohmann::json& json)
    {
        id = json.at("id").get<std::string>();
        value = json.at("int").get<int>();
        walkable = json.value("walkable", false);
		if (json.contains("texture_path") && !json.at("texture_path").is_null())
		{
			texturePath = json.at("texture_path").get<std::string>();
		}
        else
        {
			texturePath = std::nullopt;
        }
    }
    static std::vector<Tile> parseTiles(const std::string& path)
    {
        std::ifstream file(path);

        if (!file)
            throw std::runtime_error("Failed to open: " + path);

        nlohmann::json data;
        file >> data;

        std::vector<Tile> result;

        for (const auto& object : data.at("static_objects"))
            result.emplace_back(object);

        return result;
    }
	static std::unordered_map<int, sf::Texture> getTileTextureMap(const std::string& path)
	{
		std::ifstream file(path);
		if (!file)
			throw std::runtime_error("Failed to open: " + path);
		nlohmann::json data;
		file >> data;
		std::unordered_map<int, sf::Texture> result;
		for (const auto& object : data.at("static_objects"))
		{
			Tile tile(object);
            if (tile.getOptionalTexturePath().has_value())
			{
                result[tile.getValue()] = sf::Texture();
                result[tile.getValue()].loadFromFile(path + tile.getOptionalTexturePath().value_or(""));

            }
		}
		return result;
	}
    const std::string& getId() const
    {
        return id;
    }

    int getValue() const
    {
        return value;
    }

    bool isWalkable() const
    {
        return walkable;
    }
	std::optional<std::string> getOptionalTexturePath() const
	{
		return texturePath;
	}
private:
    std::string id;
    int value = 0;
    bool walkable = false;
	std::optional<std::string> texturePath; 
};

#endif
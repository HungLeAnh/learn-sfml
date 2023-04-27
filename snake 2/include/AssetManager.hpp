#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include<memory>
#include<map>

#include<SFML/Graphics.hpp>

namespace Engine{
    class AssetManager
    {
        public:
            AssetManager();
            ~AssetManager();

            void AddTexture(int id,const std::string& filePath,bool wantRepeat =false );
            void AddFont(int id,const std::string& filePath);

            const sf::Font &GetFont(int id) const;
            const sf::Texture &GetTexture(int id) const;
        private:
            std::map<int,std::unique_ptr<sf::Texture>> m_textures;
            std::map<int,std::unique_ptr<sf::Font>> m_fonts;
    };
}

#endif // ASSETMANAGER_HPP

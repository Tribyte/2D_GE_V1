#ifndef GE_HPP
#define GE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "state/state.hpp"
#include "resource/resource.hpp"
#include "resource/texture.hpp"

namespace ge {
    struct Data {
        sf::RenderWindow window;
        sf::Clock clock;
        unsigned int width;
        unsigned int height;
        state::Handler state;
        resource::Texture texture;
        resource::Resource<sf::Font> font;
    };

    inline void Load(Data *data, std::string filepath){
        std::filebuf fb;
        if(fb.open(filepath, std::ios::in)){
            std::istream is(&fb);
            while(is){
                std::string temp;
                std::getline(is, temp);
                if(temp.find(':') == std::string::npos){ continue; }

                std::string first = temp.substr(0, temp.find(':'));
                std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);
                std::string root = filepath.substr(0, filepath.find_last_of("/") + 1);

                if(first == "texture"){ data->texture.read(root + second); continue; }
                if(first == "font"){    data->font.read(   root + second); continue; }
            }

            fb.close();
        }
    }

    inline void CreateWindow(Data *data, unsigned int width, unsigned int height, const char *title){
        data->width = width;
        data->height = height;
        data->window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
    }

    inline void Run(Data *data, float UPS = 1.0f / 60.0f){
        float dt = data->clock.getElapsedTime().asSeconds();
        float new_dt = 0.0f, elapsed = 0.0f;

        while(data->window.isOpen()){
            new_dt = data->clock.getElapsedTime().asSeconds();
            elapsed += new_dt - dt;
            dt = new_dt;

            if(elapsed >= UPS){
                data->state.update();
                elapsed -= UPS;
            }

            //render
            data->window.clear();
            data->state.render();
            data->window.display();
        }
    }
}

#endif // !GE_HPP
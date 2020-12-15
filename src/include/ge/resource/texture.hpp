#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "resource.hpp"

namespace ge {
    namespace resource {
        class Texture : public Resource<sf::Texture> {
        public:
            void read(std::string filepath){
                std::filebuf fb;
                if(fb.open(filepath, std::ios::in)){
                    std::istream is(&fb);
                    bool multi = false;
                    sf::Image img;
                    std::vector<std::string> rect;
                    std::string rectName;
    
                    while(is){
                        std::string temp;
                        std::getline(is, temp);
                        if(temp.find(']') != std::string::npos){
                            spritesheet(img, rectName, rect);
                            multi = false;
                            rect.clear();
                            continue;
                        }
                        if(temp.find(':') == std::string::npos && !multi){ continue; }

                        std::string first = temp.substr(0, temp.find(':'));
                        std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);
                        std::string root = filepath.substr(0, filepath.find_last_of("/") + 1);

                        if(first == "spritesheet"){ read(root + second); continue; }
                        if(first == "ssimg"){
                            if(!img.loadFromFile(root + second)){
                                std::cout << "Error: filepath '" << filepath << "' failed to load" << std::endl;
                                std::exit(-1);
                            }
                        }
                        if(second == "["){ multi = true; rectName = first; continue; }

                        (multi)? rect.push_back(temp) : load(root + second, first);
                    }

                    fb.close();
                }
            }

            void spritesheet(sf::Image &img, std::string &name, std::vector<std::string> &rect){
                unsigned int size = rect.size();
                sf::Texture *tex = new sf::Texture[size];

                for(unsigned int i = 0; i < size; i++){
                    std::string temp = rect.at(i).substr(4, rect.at(i).size() - 1);
                    int w = std::stoi(temp.substr(0, temp.find(' ')));

                    temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                    int h = std::stoi(temp.substr(0, temp.find(' ')));

                    temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                    int x = std::stoi(temp.substr(0, temp.find(' ')));

                    temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                    int y = std::stoi(temp);

                    sf::IntRect selectionArea(x, y, w, h);
                    if(!tex[i].loadFromImage(img, selectionArea)){
                        std::cout << "error in loading '" << name << "' spritesheet";
                        std::exit(-1);
                    }
                }

                objs[name] = new ResourceObjArr<sf::Texture>(tex, size);
            }
        };
    }
}
#endif // !TEXTURE_HPP
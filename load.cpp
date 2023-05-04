#include <filesystem>
#include <iostream>
#include <map>

#include "load.h"
#include "tinyxml2/tinyxml2.h"

void readPath(std::shared_ptr<std::map<std::string, std::string>> path) {

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile("paths.xml");

    if(result != tinyxml2::XML_SUCCESS) {
        std::cout<<"Archivo paths.xml no existe en "<<std::filesystem::current_path()<<std::endl;
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Path");

    for( ; root != nullptr; root = root->NextSiblingElement()) {
        std::string key = root->Attribute("id");
        std::string value = root->GetText();
        path->emplace(key,value);
    }
    doc.Clear();
}

void readGames(std::shared_ptr<std::map<std::string, std::string>> games) {

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile("info.xml");

    if(result != tinyxml2::XML_SUCCESS) {
        std::cout<<"Archivo paths.xml no existe en "<<std::filesystem::current_path()<<std::endl;
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Games")->FirstChildElement("Game");

    for ( ; root != NULL ; root = root->NextSiblingElement()) {
        std::string key = root->Attribute("id");
        std::string value = root->GetText();

        games->emplace(key,value);
    }
    doc.Clear();
}

void readProg(std::shared_ptr<std::map<std::string, std::string>> prog) {

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile("info.xml");

    if(result != tinyxml2::XML_SUCCESS) {
        std::cout<<"Archivo paths.xml no existe en "<<std::filesystem::current_path()<<std::endl;
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Progressive")->FirstChildElement("Prog");

    for( ; root != NULL ;root = root->NextSiblingElement()){
        std::string key = root->Attribute("id");
        std::string value = root->GetText();

        prog->emplace(key,value);
    }
    doc.Clear();
}

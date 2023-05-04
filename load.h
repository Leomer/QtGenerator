#ifndef LOAD_H
#define LOAD_H

#include <map>
#include <memory>
#include <string>

void readPath(std::shared_ptr<std::map<std::string, std::string>>);
void readGames(std::shared_ptr<std::map<std::string, std::string>>);
void readProg(std::shared_ptr<std::map<std::string, std::string>>);

#endif // LOAD_H

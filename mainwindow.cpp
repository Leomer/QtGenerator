#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "load.h"
#include "release.h"

//Lista de variables para la UI
std::shared_ptr<std::map<std::string, std::string>> branchesList;
std::shared_ptr<std::map<std::string, std::string>> gamesList;
std::shared_ptr<std::map<std::string, std::string>> progList;

//Lista de variables para generar descarga
std::shared_ptr<std::vector<std::string>> games;
std::shared_ptr<std::vector<std::string>> display;
std::shared_ptr<std::vector<std::string>> progressive;

std::string path, revision;

//Direccion de carpeta destino
const std::string RELEASE_DIRECTORY = "..\\Release";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    //Inicializacion de las variables
    branchesList    = std::make_shared<std::map<std::string, std::string>>();
    gamesList       = std::make_shared<std::map<std::string, std::string>>();
    progList        = std::make_shared<std::map<std::string, std::string>>();

    display     = std::make_shared<std::vector<std::string>>();
    games       = std::make_shared<std::vector<std::string>>();
    progressive = std::make_shared<std::vector<std::string>>();

    //Lectura de archivos
    readPath(branchesList);
    readGames(gamesList);
    readProg(progList);

    //Variables UI
    QComboBox* branchesUI       = ui->branchList;
    QListWidget* gamesUI        = ui->games;
    QListWidget* progressiveUI  = ui->progressive;

    //Muestra la lista de datos
    for(const auto& [key, value] : *branchesList)
        branchesUI->addItem(key.c_str());

    for(const auto& [key, value] : *gamesList)
        gamesUI->addItem(key.c_str());

    for(const auto& [key, value] : *progList)
        progressiveUI->addItem(key.c_str());

    //Conecciones
    connect(ui->btnExit, &QPushButton::clicked, this, &close);
    connect(ui->btnClear, &QPushButton::clicked, this, &clearWidgets);
    connect(ui->btnStart, &QPushButton::clicked, this, &start);

    connect(gamesUI, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
        actionWidgetGame(item, gamesList, games, ui->gameList);
    });

    connect(progressiveUI, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
       actionWidgetGame(item, progList, progressive, ui->progressiveList);
    });

    ui->btnStart->setDisabled(true);

}

void MainWindow::actionWidgetGame(QListWidgetItem *item, std::shared_ptr<std::map<std::string, std::string>> list,
                                  std::shared_ptr<std::vector<std::string>> vec, QListWidget* widget) {

    std::string tmpKey, tmpDisplay;

    for (const auto& [key,display] : *list) {
        if(key.c_str() == item->text()) {
            tmpKey = key.c_str();
            tmpDisplay = display.c_str();
        }
    }

    insert(tmpKey, vec, widget);
    insert(tmpDisplay, display, ui->displayList);

    if(!display->empty() and !games->empty() and !progressive->empty())
        ui->btnStart->setEnabled(true);

}

void MainWindow::insert(std::string tmp, std::shared_ptr<std::vector<std::string>> tmpVec, QListWidget* widget) {

    bool duplicate = false;

    if(!tmpVec->empty()) {
        for(auto& g : *tmpVec){
            if(g.compare(tmp) == 0){
                duplicate = true;
            }
        }
    }

    if(!duplicate and tmp != "0") {
        tmpVec->emplace_back(tmp);
        sort(tmpVec->begin(), tmpVec->end());

        widget->clear();

        for(auto& g: *tmpVec)
            widget->addItem(g.c_str());
    }

}


void MainWindow::clearWidgets() {

    //Se limpia los vectores
    display->clear();
    games->clear();
    progressive->clear();

    //Se limpia los widgets
    ui->displayList->clear();
    ui->gameList->clear();
    ui->progressiveList->clear();

    ui->btnStart->setDisabled(true);

}

void MainWindow::start() {

    for(const auto& [key, value] : *branchesList)
        if(key == ui->branchList->currentText().toStdString()) {
            path = value;
            break;
        }

    revision = ui->txtRev->text().toStdString();

    //Genera nueva carpeta para la descarga
    createDirectories(RELEASE_DIRECTORY);

}

MainWindow::~MainWindow() {
    delete ui;
}


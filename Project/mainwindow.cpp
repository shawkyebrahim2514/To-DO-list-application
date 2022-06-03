#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editnote.h"
#include "ui_editnote.h"

//QMap<QString, QString>allNotes;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // make this file if doesn't exist
    QDir notesDir;
    notesDir.mkpath("notes");

    // upload style sheet to listwidget
    QFile stylefile(":/essential files/stylesheet.qss");
    stylefile.open(QFile::ReadOnly);
    QString style = stylefile.readAll();
    stylefile.close();
    ui->listWidget->setStyleSheet(style);
    // loop over each note and append it in listwidget
    QDir dir("notes");
    foreach(QFileInfo val, dir.entryInfoList()){
        QFile file(val.filePath());
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QString fileName = val.fileName().mid(0,val.fileName().size()-4);
            allNotes[fileName] = file.readAll();
        }
        file.close();
    }

    // append each note title from allNotes to listwidget
    auto item = allNotes.begin();
    while(item != allNotes.end()){
        ui->listWidget->addItem(item.key());
        item ++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // if this note is opened before, active its tab
    for(int i = 0;i < ui->tabWidget->count(); i++){
        if(ui->tabWidget->tabText(i) == item->text()){
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    // add new editNote widget to the tabwidget
    editNote *screen = new editNote(item->text());
    screen->ui->noteParagraph->setText(allNotes[item->text()]);
    ui->tabWidget->addTab(screen,item->text());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}


void MainWindow::on_addNew_clicked()
{
    // get new note title and check its validation
    QString tabName = QInputDialog::getText(this,"New tab","Enter new tab name");
    if(tabName.isEmpty()){
        QMessageBox::warning(this,"Error","Don't enter empty title");
        return;
    }
    for(auto& letter : tabName){
        if(!letter.isLetterOrNumber() && letter != ' '){
            QMessageBox::warning(this,"Error","Enter valid tab name\n( only alphabets or digits )");
            return;
        }
    }

    // add new widget to tabwidgets
    editNote *screen = new editNote(tabName);
    ui->tabWidget->addTab(screen,tabName);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

    // add item with the new note title
    ui->listWidget->addItem(tabName);
    ui->listWidget->item(ui->listWidget->count() - 1)->setSelected(1);
    allNotes[tabName] = "";

    // create this new note
    QFile file("notes/" + tabName + ".txt");
    file.open(QFile::WriteOnly);
    file.close();
}


void MainWindow::on_saveNote_clicked()
{
    // if tabwidgets does not contain any tab, return without doing anything
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Choose a note first");
        return;
    }


    // save current note file with its new content
    editNote *currentNote = (editNote*)ui->tabWidget->currentWidget();
    //editNote *currentNote = (editNote*)ui->tabWidget->widget(ui->tabWidget->currentIndex());
    QString tabName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    allNotes[tabName] = currentNote->ui->noteParagraph->toHtml();
    QFile file("notes/" + tabName + ".txt");
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    out << allNotes[tabName];
    file.flush();
    file.close();
}


void MainWindow::on_deleteNoteBtn_clicked()
{
    // if tabwidgets does not contain any tab, return without doing anything
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Choose a note first");
        return;
    }

    // reomve this note file
    QString tabName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    QFile file("notes/" + tabName + ".txt");
    file.remove();
    file.close();

    // remove this note from listwidget and from tabwidget
    qDeleteAll(ui->listWidget->selectedItems());
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}


void MainWindow::on_changeNoteTitleBtn_clicked()
{
    // change current tab title
    if(!ui->tabWidget->count()){
        QMessageBox::warning(this,"Error","Choose a note first");
        return;
    }
    editNote *currentNote = (editNote*)ui->tabWidget->currentWidget();
    QString curTabName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());

    // take new note title and check its validation
    QString newTabName = QInputDialog::getText(this,"change tab title","Enter new title");
    if(newTabName.isEmpty()){
        QMessageBox::warning(this,"Error","note can not be with empty title");
        return;
    }
    for(auto& letter : newTabName){
        if(!letter.isLetterOrNumber() && letter != ' '){
            QMessageBox::warning(this,"Error","Enter valid tab name\n( only alphabets or digits )");
            return;
        }
    }

    // update note title in its class
    currentNote->noteTitle = newTabName;

    // erase this note from the map and from listwidget, then add the new one
    allNotes.erase(allNotes.find(curTabName));
    qDeleteAll(ui->listWidget->selectedItems());
    ui->listWidget->addItem(newTabName);

    // rename note file
    QFile::rename("notes/" + curTabName + ".txt", "notes/" + newTabName + ".txt");

    // update tab text title
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), newTabName);
    allNotes[newTabName] = curTabName;
    on_tabWidget_currentChanged(0);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{

    QString tarList = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(ui->listWidget->item(i)->text() == tarList){
            ui->listWidget->setCurrentItem(ui->listWidget->item(i));
            return;
        }
    }
}


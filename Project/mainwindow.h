#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <bits/stdc++.h>
#include <QListWidget>
#include <QTextStream>
#include <QDir>
#include <QInputDialog>

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    map<string,string>allNotes;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_addNew_clicked();

    void on_saveNote_clicked();

    void on_deleteNoteBtn_clicked();

    void on_changeNoteTitleBtn_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

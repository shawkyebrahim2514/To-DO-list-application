#ifndef EDITNOTE_H
#define EDITNOTE_H

#include <QWidget>
#include <QTextEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
namespace Ui {
class editNote;
}

class editNote : public QWidget
{
    Q_OBJECT

public:
    QString noteTitle = "";
    explicit editNote(QString title, QWidget *parent = nullptr);
    ~editNote();

private slots:
    void on_noteParagraph_textChanged();

    void on_copyBtn_clicked();

    void on_pasteBtn_clicked();

    void on_cutBtn_clicked();

    void on_clearBtn_clicked();

    void on_undoBtn_clicked();

    void on_redoBtn_clicked();

    void on_changeFontBtn_clicked();

    void on_alignLeftBtn_clicked();

    void on_alignCenterBtn_clicked();

    void on_alignRightBtn_clicked();

    void on_colorBtn_clicked();

    void on_smalizeBtn_clicked();

    void on_capitalizeBtn_clicked();

public:
    Ui::editNote *ui;
};

#endif // EDITNOTE_H

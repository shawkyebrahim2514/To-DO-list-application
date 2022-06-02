#include "editnote.h"
#include "ui_editnote.h"
editNote::editNote(QString title, QString paragraph, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editNote)
{
    ui->setupUi(this);
    ui->noteParagraph->setText(paragraph);
    noteTitle = title;
}

editNote::~editNote()
{
    delete ui;
}


void editNote::on_noteParagraph_textChanged()
{
    allParagraph = ui->noteParagraph->toHtml();
}


void editNote::on_copyBtn_clicked()
{
    ui->noteParagraph->copy();
}


void editNote::on_pasteBtn_clicked()
{
    ui->noteParagraph->paste();
}


void editNote::on_cutBtn_clicked()
{
    ui->noteParagraph->cut();
}


void editNote::on_clearBtn_clicked()
{
    ui->noteParagraph->clear();
}


void editNote::on_undoBtn_clicked()
{
    ui->noteParagraph->undo();
}


void editNote::on_redoBtn_clicked()
{
    ui->noteParagraph->redo();
}


void editNote::on_changeFontBtn_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->noteParagraph->setCurrentFont(font);
    }else return;
}


void editNote::on_changeColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this, "choose font color");
    if(color.isValid()){
        ui->noteParagraph->setTextColor(color);
    }
}


void editNote::on_alignLeftBtn_clicked()
{
    ui->noteParagraph->setAlignment(Qt::AlignLeft);
}


void editNote::on_alignCenterBtn_clicked()
{
    ui->noteParagraph->setAlignment(Qt::AlignCenter);
}


void editNote::on_alignRightBtn_clicked()
{
    ui->noteParagraph->setAlignment(Qt::AlignRight);
}


void editNote::on_colorBtn_clicked()
{
    QColor color = QColorDialog::getColor("#d3506a",this, "choose font color");
    if(color.isValid()){
        ui->noteParagraph->setTextColor(color);
    }

}


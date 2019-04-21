#include "find_window.h"
#include "ui_find_window.h"
#include "redit.h"
#include <QMessageBox>

find_window::find_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::find_window)
{
    ui->setupUi(this);
}

find_window::~find_window()
{
    delete ui;
}

void find_window::undo_changes()
{
    QTextCursor cursor(document);
    cursor.beginEditBlock();

    QTextCharFormat plainFormat(cursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setBackground(Qt::white);

    while(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::WordRight,
                                    QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(colorFormat);
    }
    cursor.endEditBlock();
}

void find_window::receive_data(QTextDocument* document)
{
   this->document = document;
}

QString find_window::on_pushButton_clicked()
{
    QString searchString = ui->lineEdit->text();

    bool found = false;

    // undo previous change (if any)
    this->undo_changes();


    if (searchString.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Search Field"),
                                tr("The search field is empty. "
                                   "Please enter a word and click Find."));
    }
    else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setBackground(Qt::yellow);

        int cnt = 0;
        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(searchString, highlightCursor);

            if (!highlightCursor.isNull())
            {
                found = true;
                for(int i = 0; i < searchString.size(); i++)
                {
                    highlightCursor.movePosition(QTextCursor::NextCell,
                                                QTextCursor::KeepAnchor);
                    highlightCursor.mergeCharFormat(colorFormat);
                }

            }
            //QMessageBox::information(this, tr(std::to_string(cnt).c_str()), tr(std::to_string(cnt).c_str()));
            cnt++;
        }

        cursor.endEditBlock();

        if (found == false)
        {
                QMessageBox::information(this, tr("Word Not Found"),
                                         tr("Sorry, the word cannot be found."));
        }
    }

    return searchString;
}

void find_window::on_pushButton_2_clicked()
{
    this->undo_changes();
    this->hide();
}

void find_window::reject()
{
    this->undo_changes();
    QDialog::reject();
}

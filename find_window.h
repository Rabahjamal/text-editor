#ifndef FIND_WINDOW_H
#define FIND_WINDOW_H

#include <QDialog>
#include <QTextDocument>

namespace Ui {
class find_window;
}

class find_window : public QDialog
{
    Q_OBJECT

public:
    explicit find_window(QWidget *parent = nullptr);
    ~find_window();

    void undo_changes();
private slots:
    QString on_pushButton_clicked();

    void receive_data(QTextDocument*);

    void on_pushButton_2_clicked();

private:
    Ui::find_window *ui;
    QTextDocument* document;

    void reject();
};

#endif // FIND_WINDOW_H

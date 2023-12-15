#ifndef CALDAT_H
#define CALDAT_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class CalDat;
}

class CalDat : public QDialog
{
    Q_OBJECT

public:
    explicit CalDat(QWidget *parent = nullptr);
    ~CalDat();

private slots:
    void on_difButton_clicked();

    void on_sumDays_clicked();

    void on_checkYear_clicked();

private:
    Ui::CalDat *ui;
};

#endif // CALDAT_H

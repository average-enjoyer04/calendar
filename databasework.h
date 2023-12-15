#ifndef DATABASEWORK_H
#define DATABASEWORK_H
#include <QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>
#include <QCryptographicHash>
#include <set>

class DatabaseWork
{
public:
    DatabaseWork();
    ~DatabaseWork();
    QString authorization(QString& username, QString& password);
    QString registration(QString& username, QString& password);
    QString updateSpecDatData(int day, int month, QString& event);
    QString deleteSpecDatData(int day, int month);
    QString getEventData(int day, int month);
    QString fillTable();
    QString addSpecDatData(int day, int month, QString& event);
    std::set<int> datesArray[12];
private:
    QSqlDatabase* db;
    void hashMake(QString& username, QString& password, QString& result);
    int userId;
    bool isOpen = false;
};

#endif // DATABASEWORK_H

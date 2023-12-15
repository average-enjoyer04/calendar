#include "databasework.h"

DatabaseWork::DatabaseWork()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QDir databasePath;
    QString path = databasePath.currentPath()+"/myDb10.db"; // Not "myDb.db"
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(path);
    if(db->open()){
        isOpen = true;
    }
    if (!db->tables().contains("users")) {
        QSqlQuery query2;
        query2.exec("CREATE TABLE users ("
                    "ID       INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT,"
                    "password TEXT);");
        query2.exec("CREATE TABLE specDat ("
                   "id     INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                   "userId INTEGER REFERENCES users (ID),"
                   "day    INTEGER,"
                   "month  INTEGER,"
                   "event  TEXT);");
    }

}

DatabaseWork::~DatabaseWork()
{
    db->close();
    delete db;
}

void DatabaseWork::hashMake(QString& username, QString& password, QString& result){
    QByteArray salt = QCryptographicHash::hash(username.toUtf8(), QCryptographicHash::Md5); // Generate salt using username hash
    QByteArray saltedPassword = password.toUtf8() + salt; // Append salt to password

    QByteArray hashedPassword = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha512);
    result = hashedPassword.toHex();
}
QString DatabaseWork::authorization(QString& username, QString& password){
    if (isOpen) {
        QString result;
        QSqlQuery query(QSqlDatabase::database());
        query.prepare(QString("SELECT *FROM users WHERE username = :username AND password = :password"));
        hashMake(username, password, result);
        query.bindValue(":username", username);
        query.bindValue(":password", result);

        if (!query.exec()) {
            return "Возникли некоторые проблемы";

        }
        else {
            if(query.next()){
                userId = query.value(0).toInt();
                qDebug()<<userId;
                return "Вы авторизовались";
            }

            else{
                return "Непраильный пароль или логин";
            }

        }
    }
    else{
        return "Нет соединения с базой данных";
    }
}

QString DatabaseWork::registration(QString& username, QString& password){
    if (isOpen) {
        QString result;
        // Проверка уникальности логина
        QSqlQuery checkQuery(QSqlDatabase::database());
        checkQuery.prepare("SELECT username FROM users WHERE username = :username");
        checkQuery.bindValue(":username", username);
        if (checkQuery.exec() && checkQuery.next()) {
            // Запись с таким логином уже существует
            return "Логин уже занят";
        } else {
            // Логин уникален, добавляем новую запись
            hashMake(username, password, result);
            QSqlQuery insertQuery(QSqlDatabase::database());
            insertQuery.prepare("INSERT INTO users (username, password)"
                                "VALUES (:username, :password)");
            insertQuery.bindValue(":username", username);
            insertQuery.bindValue(":password", result);
            if (insertQuery.exec()) {
                userId = insertQuery.lastInsertId().toInt();
                //qDebug()<<userId;
                return "Данные добавлены";

            }
            else {
                return "Данные не добавлены";
            }
        }
    }
    else{
        return "Нет соединения с базой данных";
    }
}
QString DatabaseWork::fillTable(){
    if (isOpen) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("SELECT day, month FROM specDat WHERE userId = :userId");
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            return "Возникли некоторые проблемы";
        }

        while (query.next()) {
            int day = query.value(0).toInt();
            int month = query.value(1).toInt();

            if (month >= 1 && month <= 12) {
                datesArray[month - 1].insert(day);
            }

        }
        return "good";
    }
    else{
        return "Нет соединения с базой данных";
    }
}
QString DatabaseWork::addSpecDatData(int day, int month, QString& event) {
    if (isOpen) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("INSERT INTO specDat (userId, day, month, event) VALUES (:userId, :day, :month, :event)");
        query.bindValue(":userId", userId);
        query.bindValue(":day", day);
        query.bindValue(":month", month);
        query.bindValue(":event", event);
        if (!query.exec()) {
            return "Возникли некоторые проблемы";
        } else {
            datesArray[month - 1].insert(day);
            return "Событие было успешно добавлено";
        }
    } else {
        return "Нет соединения с базой данных";
    }
}

QString DatabaseWork::updateSpecDatData(int day, int month, QString& event) {
    if (isOpen) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("UPDATE specDat SET event = :event WHERE day = :day AND month = :month");
        query.bindValue(":userId", userId);
        query.bindValue(":day", day);
        query.bindValue(":month", month);
        query.bindValue(":event", event);
        if (!query.exec()) {
            return "Возникли некоторые проблемы";
        } else {
            return "Событие было успешно перезаписано";
        }
    } else {
        return "Нет соединения с базой данных";
    }
}

QString DatabaseWork::deleteSpecDatData(int day, int month) {
    if (isOpen) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("DELETE FROM specDat WHERE userId = :userId AND day = :day AND month = :month");
        query.bindValue(":userId", userId);
        query.bindValue(":day", day);
        query.bindValue(":month", month);
        if (!query.exec()) {
            return "Возникли некоторые проблемы";
        } else {
            datesArray[month - 1].erase(day);
            return "Событие было успешно удалено";
        }
    } else {
        return "Нет соединения с базой данных";
    }
}
QString DatabaseWork::getEventData(int day, int month) {
    if (isOpen) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("SELECT event FROM specDat WHERE userId = :userId AND day = :day AND month = :month");
        query.bindValue(":userId", userId);
        query.bindValue(":day", day);
        query.bindValue(":month", month);
        if (!query.exec()) {
            return "Возникли некоторые проблемы";
        } else {
            if (query.next()) {
                return query.value(0).toString();
            } else {
                return "В базе данных не найдено событие с указанными значениями";
            }
        }
    } else {
        return "Нет соединения с базой данных";
    }
}

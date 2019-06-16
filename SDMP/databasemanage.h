#ifndef DATABASEMANAGE_H
#define DATABASEMANAGE_H

#include<QString>
#include<QDebug>
#include<QImage>
#include<memory>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>

class DataBaseManage
{
public:
    DataBaseManage();
    explicit DataBaseManage(const QString &dataBaseName, const QString &driverDB);
    virtual bool conectDataBase(const QString &hostName,
                                const QString &userName,
                                const QString &pasword);
    virtual bool addTable(const QString &nameTable) = 0;

    virtual bool deleteTable(const  QString &nameTable) = 0;
    virtual bool saveAll();
    virtual~DataBaseManage();

private:
    std::shared_ptr<QString> dataBaseName;
    std::shared_ptr<QString> driverDB;
protected:
    QSqlDatabase dataBase;
};

#endif // DATABASEMANAGE_H

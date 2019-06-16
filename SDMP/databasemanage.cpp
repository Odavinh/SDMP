#include "databasemanage.h"
#include<QSqlRecord>

//#define DEBUG


DataBaseManage::DataBaseManage(const QString &dataBaseName, const QString &driverDB)
{
    this->dataBaseName = std::make_shared<QString>(dataBaseName);
    this->driverDB = std::make_shared<QString>(driverDB);
}

bool DataBaseManage::conectDataBase(const QString &hostName,
                                    const QString &userName,
                                    const QString &pasword)
{
    dataBase = QSqlDatabase::addDatabase(*this->driverDB.get());
    dataBase.setDatabaseName("DRIVER={SQL Server};"
                             "Server="+hostName+";"
                             "Database="+*this->dataBaseName.get()+";"
                             "Trusted_Connection=True");
    if(userName.isEmpty())
        dataBase.setUserName(userName);
    if(pasword.isEmpty())
        dataBase.setPassword(pasword);
    if(!dataBase.open()){
#ifndef DEBUG
        qDebug() << dataBase.lastError().text();
#endif // DEBUG
        return false;
    }else {
#ifndef DEBUG
        qDebug() << "open Database!!";
#endif // DEBUG
        return true;
    }
}

bool DataBaseManage::saveAll()
{
    return this->dataBase.commit();
}



DataBaseManage::~DataBaseManage()
{
    dataBase.close();
}

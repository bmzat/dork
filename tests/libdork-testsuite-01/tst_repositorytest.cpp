#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QUrl>
#include <stdio.h>


#include "../../src/dorkcore/repository.h"

class RepositoryTest : public QObject
{
    Q_OBJECT

public:
    RepositoryTest();

private:
    QDir trd;
    void delRecursive(QDir d,int rec=0);
    QString urlstring;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNewInstanceRepo();
    void testRepoOpenUnsupp();
    void testRepoOpenRemote();
    void testRepoOpenUninitialized();
    void testRepoInitDirectory();
};

RepositoryTest::RepositoryTest()
{
}

void RepositoryTest::initTestCase()
{
    trd=QDir(".");
    if(!trd.mkpath("trepo/vault")){
        QFAIL("Cannot create test Repo");
    }
    trd.cd("trepo");
    QString rdir = trd.absolutePath();
    QUrl u(rdir);
    u.setScheme("file");
    u.setHost("localhost");
    urlstring = u.toString();
    qDebug() << "URLSTRING:" << urlstring;
    //trd.setCurrent(trd.absolutePath());

}

void RepositoryTest::cleanupTestCase()
{
    qDebug() << "trd:" << trd.currentPath() << " ## " << trd.absolutePath();
    //trd.cdUp();

   delRecursive(trd);
   trd.cdUp();
   trd.rmdir("trepo");
    //QDir d("C:\\");
   // d.setCurrent("C:\\");
    //delRecursive(d);

}

void RepositoryTest::testNewInstanceRepo()
{
    dork::Repository *repo = new dork::Repository();

    if(repo==NULL){
        QFAIL("new dork::Repository() failed");
    }
    delete repo;
}

void RepositoryTest::testRepoOpenUnsupp()
{
    dork::Repository *repo = new dork::Repository();
    dork::Repository::RepoError re;

    if(repo==NULL){
        QFAIL("new dork::Repository() failed");
    }
    re = repo->repoOpen("quagga://user:pass@host/path");
    delete repo;
    QVERIFY(re==repo->errTransportNotSupported);
}
void RepositoryTest::testRepoOpenRemote()
{
    dork::Repository *repo = new dork::Repository();
    dork::Repository::RepoError re;

    if(repo==NULL){
        QFAIL("new dork::Repository() failed");
    }
    re = repo->repoOpen("file://user:pass@host/path");
    delete repo;
    QVERIFY(re==repo->errOpNotSupported);
}


QTEST_MAIN(RepositoryTest);

#define DEL_REC_LOG 0 //0x09
void RepositoryTest::delRecursive(QDir d,int rec)
{
#if DEL_REC_LOG&0x01
    qDebug() << "[" << rec << "]>>>>>" << d.absolutePath();
#endif
    d.setSorting( QDir::Name );
    d.setFilter( QDir::AllEntries|QDir::NoDotAndDotDot);
    d.refresh();
    //QStringList qsl = d.entryList();
    QFileInfoList qsl = d.entryInfoList();
    for(QList<QFileInfo>::iterator iter = qsl.begin();iter!=qsl.end();iter++){
        QFileInfo finfo(*iter);
        if ( finfo.isSymLink () ){
           qDebug() << "LINK:" << finfo.absoluteFilePath();
           continue;
        }
        if ( finfo.isDir() ) {
#if DEL_REC_LOG&0x02
            qDebug() << "[" << rec << "] DIR:" << finfo.filePath();
#endif
            QString dirname = finfo.fileName();
            if ((dirname==".") || (dirname == ".."))
                continue;
            QDir sd(finfo.absoluteFilePath());
            //sd.cd(finfo.filePath());
          //  sd.setCurrent(finfo.filePath());
//            if (skipDir(sd))
//                continue;

            delRecursive(sd,(rec+1));
            if(!d.rmdir(finfo.absoluteFilePath())){
                qDebug() << "RMDIR FAILED:" << finfo.absoluteFilePath();
            }
        } else {
#if DEL_REC_LOG&0x04
            qDebug() << "[" << rec << "] FILE:" << finfo.filePath();
#endif
            QFile f(finfo.absoluteFilePath());
            //QString ap = finfo.absoluteFilePath();
            if(!f.exists()){
               qDebug() << "DOES NOT EXITS?:" << finfo.absoluteFilePath();
            }
            if(!f.setPermissions(QFile::ReadOwner|QFile::WriteOwner)){
                 qDebug() << "SETPRM FAILED ["<< f.errorString() <<"] - " << finfo.absoluteFilePath();
            }
            if(!f.remove()){
                qDebug() << "REMOVE FAILED ["<< f.errorString() <<"] - " << finfo.absoluteFilePath();
            }
        }
    }
#if DEL_REC_LOG&0x08
    qDebug() << "[" << rec << "]<<<<<";
#endif


}

void RepositoryTest::testRepoOpenUninitialized()
{
    dork::Repository *repo = new dork::Repository();
    dork::Repository::RepoError re;

    if(repo==NULL){
        QFAIL("new dork::Repository() failed");
    }
    re = repo->repoOpen(urlstring);
    delete repo;
    QVERIFY(re==repo->errIsNoRepo);
}

void RepositoryTest::testRepoInitDirectory()
{
    dork::Repository *repo = new dork::Repository();
    dork::Repository::RepoError re;

    if(repo==NULL){
        QFAIL("new dork::Repository() failed");
    }


    re = repo->repoOpen(urlstring);
    if(re!=repo->errIsNoRepo){
        qDebug() << "UNEXPECTED RETURN:" << re;
        QFAIL(" WOOOO ");
    }
    re = repo->repoInit();
    delete repo;
    QVERIFY(re==repo->errOK);
}


#include "tst_repositorytest.moc"

#include <QtTest/QtTest>
#include "tst_branchtest.h"
#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlError>


#include <branch.h>
#include <repository.h>

#include <QDjangoModel.h>
#include <QDjangoQuerySet.h>

BranchTest::BranchTest(void)
{
    repo = new dork::Repository();
}

BranchTest::~BranchTest(void)
{
    if(repo!=NULL){
        repo->repoClose();
        delete repo;
    }
}

void BranchTest::initTestCase()
{
    dork::Repository::RepoError re;
    QVERIFY2(repo!=NULL,"Invalid Pointer");
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
        re = repo->repoOpen(urlstring);
        if(re==repo->errIsNoRepo){
            re=repo->repoInit();
            if(re!=repo->errOK){
                delete repo;
                QFAIL("X");
            }
        }else{
            QFAIL("Y");
        }

}

void BranchTest::cleanupTestCase()
{
    QVERIFY2(repo!=NULL,"Invalid Pointer");
    repo->repoClose();
    delete repo;
	delRecursive(trd);
	trd.cdUp();
	trd.rmdir("trepo");
}
#define DEL_REC_LOG 0x04
void BranchTest::delRecursive( QDir d,int rec/*=0*/ )
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

void BranchTest::simpleAddElement()
{
	dork::Branch *b = new dork::Branch();
	b->Name("master");
	b->BranchId("0000-5334-5097-affe");
	b->CurrentHeadId("000x000x001");
	b->Desc("Beschreibung 1");
        if(!b->save()){
            QSqlDatabase db = QSqlDatabase::database("repobase");
            qDebug() << "Database says: " << db.lastError().text();
            QFAIL("DB001");
        }
	delete b;
	b = new dork::Branch();
	b->Name("lala");
	b->BranchId("baum-5334-5097-affe");
	b->CurrentHeadId("5334x000x001");
	b->Desc("Beschreibung 1");
        if(!b->save()){
            QSqlDatabase db = QSqlDatabase::database("repobase");
            qDebug() << "Database says: " << db.lastError().text();
            QFAIL("DB002");
        }
	delete b;
	b = new dork::Branch();
        b->Name("lala2");
        b->BranchId("baum-5334-5097-ente");
	b->CurrentHeadId("5334x000x001");
	b->Desc("Beschreibung 1");
        if(!b->save()){
            QSqlDatabase db = QSqlDatabase::database("repobase");
            qDebug() << "Database says: " << db.lastError().text();
            QFAIL("DB003");
        }
	delete b;

        b = ::byPK<dork::Branch>(QVariant("0000-5334-5097-affe"));
        if(b!=NULL){
            QVERIFY(b->Name()=="master");
        }


}

#ifdef _MSC_VER
#if 1
#ifndef NDEBUG
#include "GeneratedFiles/Debug/moc_tst_branchtest.cpp"
#else
 #include "GeneratedFiles/Release/moc_tst_branchtest.cpp"
 #endif
#endif
#else
//#include "debug/moc_tst_branchest.cpp"
#include "moc_tst_branchtest.cpp"
#endif

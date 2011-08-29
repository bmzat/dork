#include "repotest.h"
#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QUrl>
#include <repository.h>




void RepoTest::initTestCase()
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

void RepoTest::cleanupTestCase()
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

void RepoTest::testNewInstanceRepo()
{
	dork::Repository *repo = new dork::Repository();

	if(repo==NULL){
		QFAIL("new dork::Repository() failed");
	}
	delete repo;
}

void RepoTest::testRepoOpenUnsupp()
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
void RepoTest::testRepoOpenRemote()
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




#define DEL_REC_LOG 0 //0x09
void RepoTest::delRecursive(QDir d,int rec)
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

void RepoTest::testRepoOpenUninitialized()
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

void RepoTest::testRepoInitDirectory()
{
	dork::Repository *repo = new dork::Repository();
	dork::Repository::RepoError re;
	QString sv_repoversion;
	if(repo==NULL){
		QFAIL("new dork::Repository() failed");
	}


	re = repo->repoOpen(urlstring);
	if(re!=repo->errIsNoRepo){
		qDebug() << "UNEXPECTED RETURN:" << re;
		QFAIL(" WOOOO ");
	}
	repo->svRepoVersion("testing 123");
	re = repo->repoInit();
	if(re==repo->errOK){
		sv_repoversion = repo->svRepoVersion();
		qDebug() << repo->getDRC("cl_willi").toString();
	}
	delete repo;
	QVERIFY(sv_repoversion!="");
}



#ifdef _MSC_VER
#if 0
#ifndef NDEBUG
#include "GeneratedFiles/Debug/moc_repotest.cpp"
#else
#include "GeneratedFiles/Release/moc_repotest.cpp"
#endif
#endif
#else
#include "repotest.moc"
#endif
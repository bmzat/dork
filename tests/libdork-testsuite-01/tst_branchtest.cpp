#include <QtTest/QtTest>
#include "tst_branchtest.h"
#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QUrl>

BranchTest::BranchTest(void)
{
}

BranchTest::~BranchTest(void)
{
}

void BranchTest::initTestCase()
{

}

void BranchTest::cleanupTestCase()
{

}

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

#ifdef _MSC_VER
#if 0
#ifndef NDEBUG
#include "GeneratedFiles/Debug/moc_tst_branchtest.cpp"
#else
#include "GeneratedFiles/Release/moc_tst_branchtest.cpp"
#endif
#endif
#else
#include "tst_branchtest.moc"
#endif
#include "tst_repositorytest.h"
#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QDir>
#include <QUrl>
#include <repository.h>
#include "repotest.h"
#include "tst_branchtest.h"


//QTEST_MAIN(RepoTest);

int main(int argc, char *argv[])
{
	//Q_INIT_RESOURCE(application);
        QCoreApplication app(argc,argv);
	int errc=0;

	{
		RepoTest rt;
		errc += QTest::qExec(&rt);
	}

	{
		BranchTest bt;
		errc += QTest::qExec(&bt);
	}

	qDebug() << "Total FAILS:" << errc;
	return errc;
}


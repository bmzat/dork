#include <QObject>
#include <QDir>
#include <QtTest/QtTest>

#ifndef tst_BranchTest_h__
#define tst_BranchTest_h__



class BranchTest : public QObject
{
	Q_OBJECT
public:
	BranchTest(void);
	~BranchTest(void);
private Q_SLOTS:
		void initTestCase();
		void cleanupTestCase();
		void delRecursive(QDir d,int rec=0);
};





#endif // tst_BranchTest_h__

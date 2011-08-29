#ifndef REPOTEST_H
#define REPOTEST_H

#include <QObject>
#include <QDir>



class RepoTest : public QObject
{
	Q_OBJECT
public:
private:

	QDir trd;
	void delRecursive(QDir d,int rec=0);
	QString urlstring;

	private slots:
		void initTestCase();
		void cleanupTestCase();
		void testNewInstanceRepo();
		void testRepoOpenUnsupp();
		void testRepoOpenRemote();
		void testRepoOpenUninitialized();
		void testRepoInitDirectory();	
};

#endif // REPOTEST_H

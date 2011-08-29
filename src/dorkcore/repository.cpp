#include "repository.h"
#include <QUrl>
#include <QSqlDatabase>
#include <QDebug>
#include <QScriptSyntaxCheckResult>
#include <QDjango.h>
#include <QDjangoScript.h>
#include <blob.h>
#include <branch.h>

inline void init3123(){
	Q_INIT_RESOURCE(dorkcore);
}

namespace dork {

                const unsigned long rfDirty	=0x0001; //Repo is dirty, check it
                const unsigned long rfInit	=0x0002; //Valid repo, proceed
                const unsigned long rfNoRepo    =0x0004; //No repo here, init?
                const unsigned long rfNeedMkDir =0x0008; //No dir there, mkdir?
                const unsigned long rfNotOPN=0x0000;     //Nothing opened, so what

    Repository::Repository()
    {
		::init3123();
    	rflags = rfNotOPN;
        url="";
        //qse = new QScriptEngine();
        QSqlDatabase::addDatabase("QSQLITE","repobase");
      basedir = "";
      sv_url = "";
      sv_basedir = "";
      sv_repoversion = "";
      sv_plugins = "";
      qse.globalObject().setProperty("sv_url",sv_url);
      qse.globalObject().setProperty("sv_basedir",sv_basedir);
      qse.globalObject().setProperty("sv_repoversion",sv_repoversion);
      qse.globalObject().setProperty("sv_plugin",sv_url);
	  QDjango::setDatabase(QSqlDatabase::database("repobase"));
	  QDjango::registerModel<Blob>();
      QDjango::registerModel<Branch>();
    }

    Repository::~Repository(){

		
        QSqlDatabase::removeDatabase("repobase");
    }

                Repository::RepoError Repository::repoOpen(QString url)
		{

			 QUrl u(url);
                         qDebug() << "Received url:" << url;
                         qDebug() << "Received path:" << u.path();
                         if(!u.scheme().isEmpty()&&(u.scheme()!="file")){
                             qDebug() << "INVALID PROTOCOL: " << u.scheme();
                                        return errTransportNotSupported;
			 }
			 if(!u.host().isEmpty()&&(u.host()!="localhost")){
                             qDebug() << "INVALID HOST: " << u.host();
                                        return errOpNotSupported;
			 }
                         QDir bdir = u.path();
                        // bdir.setCurrent(bdir.absolutePath());

                         QFile drc;
                         drc.setFileName(bdir.absolutePath()+QString("/repo.drk"));
                         if(!bdir.exists()){
                             qDebug() << "DIR does not exist:" << bdir.absolutePath();
                             rflags = rfNoRepo|rfNeedMkDir;
                             sv_url.setData(url);
                             dirBase = bdir;
                             return errIsNoRepo;
                         }
                         if(!drc.exists()){
                             qDebug() << "DRK not found:" << drc.fileName();
                             rflags = rfNoRepo;
                             sv_url.setData(url);
                             dirBase = bdir;
                             return errIsNoRepo;
                         }

                         return errOK;
		}

}

void dork::Repository::svUrl(QString url)
{
    sv_url.setData(url);
}

QString dork::Repository::svUrl()
{
    return qse.globalObject().property("sv_url").toString();
}

QString dork::Repository::svPlugins()
{ return qse.globalObject().property("sv_plugins").toString();
}

void dork::Repository::svPlugins(QString val)
{
    qse.globalObject().setProperty("sv_plugins",val);
}

dork::Repository::RepoError dork::Repository::repoInit()
{
    if(!(rflags&rfNoRepo)||(rflags&rfInit)){
        qDebug() << "rflags:" << rflags;
        return errOpInvalid; // Repository
    }

    if(rflags&rfNeedMkDir){
        dirBase.mkpath(dirBase.absolutePath());
    }

    QFile drc;
    drc.setFileName(dirBase.absolutePath()+QString("/repo.drk"));

    if(drc.open(QFile::WriteOnly)){
		drc.close();	
		drc.remove();
		QFile::copy(":/repo/resources/repo.js",dirBase.absolutePath()+QString("/repo.drk"));
    }else{
        qDebug() << "could not create File: " << drc.fileName();
        return errWriteFailed;
    }
    execScript(dirBase.absolutePath()+QString("/repo.drk"));
#if 1
	qDebug() << qse.globalObject().property("cl_willi").toString();
#endif
    return errOK;
}

bool dork::Repository::execScript(QString fileName)
{
    QFile scriptFile(fileName);
    if (!scriptFile.open(QIODevice::ReadOnly))
        return false;
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();
    //qDebug() << QString("SCRIPT: \n") << contents << "\n\n";
    QScriptSyntaxCheckResult sr=qse.checkSyntax(contents);
    if(sr.state()!=sr.Valid){
        qWarning() << sr.errorMessage();
    }
    qse.evaluate(contents, fileName);
    //qDebug() << qse.globalObject().property("cl_plugins").toString();
    //qDebug() << qse.globalObject().property("sv_repoversion").toString();
    return true;
}

void dork::Repository::svRepoVersion(QString val)
{
    qse.globalObject().setProperty("sv_repoversion",val);
}

QString dork::Repository::svRepoVersion()
{
    return qse.globalObject().property("sv_repoversion").toString();
}

QScriptValue dork::Repository::getDRC(QString name)
{
    return qse.globalObject().property(name);
}

dork::Repository::RepoError dork::Repository::repoClose()
{
    return errOpNotSupported;
}
// namespace dork

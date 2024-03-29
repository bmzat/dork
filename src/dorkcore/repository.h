#ifndef DORK_REPOSITORY_H
#define DORK_REPOSITORY_H

#include <QObject>
#include <QScriptable>
#include <QSqlDatabase>
#include <QIODevice>
#include <QScriptEngine>
#include <QScriptValue>
#include <QDir>
#include "libdork_global.h"

#include "blob.h"

namespace dork {

    class LIBDORKSHARED_EXPORT Repository : public QObject, protected QScriptable {
        Q_OBJECT
    public:

    	  
        Repository();
        virtual ~Repository();
        
        enum RepoError{
	        		errOK=0,
	        		errIsNoRepo,
	        		errBlobAlreadyKnown,
	        		
	        		errFailure,
	        		errOpNotSupported,
                                errOpInvalid,
	        		// File-System Errors
	        		errNoFSAcces,
	        		errReadFailed,
	        		errWriteFailed,
	        		errNoSpaceAvail,
	        		// Repository Errors
	        		errRepoIsOld,
	        		errRepoIsNew,
	        		errNoOpen,
	        		errDirty,
                                errTransportNotSupported,
	        		
	        		// sql Errors
	        		errSQL,
	        		
	        		// blob storage
	        		
	        		
	        		
	        		errMAXERR
	        };
	        
	        /** @brief open a repository for further access to it
	        *   
	        *  repoOpen primes the Repository instance for work to be done. Internally this
	        *  cause a few reads from the repositories location as well as a peek into the repo
	        *  database.
	        *
	        *  @param[in] url A QString containing the repository URL in the form of
	        *  						[protocol://]<user:[auth]>@<host>/path
	        *  @returns an RepoError error code  
	        *  @retval errOK				Everything went just fine
	        *  @retval errIsNoRepo	Directory is accessible but is no repo, you can init it none the less
	        *  @retval errRepoIsOld The repo can be opened but was made with an older version, it can be upgraded
	        *  @retval errRepoIsNew The repo was created using a newer version of dork, just read access and you should update
	        *                      the client      
	        *  @retval errTramsportNotSupported The transport protocol given in url is not supported (yet)
	        *  @retval errDirty       
	        */
	        RepoError repoOpen(QString url);
	        
	        /** @brief initialize an opened and previously empty repository
	        *
	        * @returs an Error code that should be Checked
	        * @retval errOK 					Initialized correctly
	        * @retval errWriteFailed	no writeing for some reason
	        * @retval errSQL					something went wrong in the internal database
	        */
	        RepoError repoInit();
	        
	        /** @brief close an opened repo, store everything, flush buffers and leave a consitent state
	        *
	        * @returns ErrorCode
	        * @retval errOK Everything went well
	        * @retval errWriteFailed some write operations failed
	        * @retval errSQL some database operation failed
                * @retval errOpInvalid we are in an already initialized repository
	        */
	        RepoError repoClose();
        
        	/** @brief perform a consistency check on the repository
        	*
        	* @param[in] level of scrutinity with wich to check 0=fast and 3=secure
        	*/
          RepoError repoFSCK(unsigned int level);
          
          /** @brief create a BLOB from a file from Disk
          *
          * For the creation of a BLOB the file and its size get hashed together
          * to create the id of the blob. If a file has the same size an the same checksum, as
          * another file they are assumed to be the same an no further storage is performed.
          * If the file is not yet in the repository, it is copied into the vault and entered into
          * the database for tracking. Additional Metadata can be accessed using the blob object
          * and if necessary metadata extensions
          *
          * @param[in] src path to the source file on the filesystem
          * @param[out] err pointer to a RepoError var that receives the error code
          * @retuns The Blob object created or associated with the content
          * @retval NULL in case of error, inspect the value of err to get more information
          * @retval Pointer to a valid Blob object, caller is responsible for deletion of returned object
          */
          Blob* blobCreateFromFile(QString src,RepoError *err);
          
          /** @brief create a BLOB from a QIODevice
          *
          * For the creation of a BLOB the file and its size get hashed together
          * to create the id of the blob. If a file has the same size an the same checksum, as
          * another file they are assumed to be the same an no further storage is performed.
          * If the file is not yet in the repository, it is copied into the vault and entered into
          * the database for tracking. Additional Metadata can be accessed using the blob object
          * and if necessary metadata extensions
          *
          * @param[in] src QIODevice containing the BLOB content
          * @param[out] err pointer to a RepoError var that receives the error code
          * @retuns The Blob object created or associated with the content
          * @retval NULL in case of error, inspect the value of err to get more information
          * @retval Pointer to a valid Blob object, caller is responsible for deletion of returned object
          */   
          Blob* blobCreateFromIO(QIODevice *src,RepoError *err);    
          
          QString svUrl();
          void svUrl(QString url);

          QString svPlugins();
          void svPlugins(QString val);

          QString svRepoVersion();
          void svRepoVersion(QString val);

          QScriptValue getDRC(QString name);

          private:
          	QString url;
                QSqlDatabase db;
          	QString basedir;
                QScriptEngine qse;
          	unsigned long rflags;
          	QString qsCFG;
          	QString qsRepo;
          	QScriptValue sv_url,sv_basedir,sv_dbfile,sv_repoversion,sv_plugins;
                QDir dirBase;
                QDir dirVault;
                bool execScript(QString fileName);
          	     
    };


} // namespace dork
#endif // DORK_REPOSITORY_H

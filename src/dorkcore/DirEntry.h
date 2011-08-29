#ifndef DirEntry_h__
#define DirEntry_h__

#include <QDjangoModel.h>


namespace dork{
	class DirEntry :
		public QDjangoModel
	{
		Q_OBJECT
	public:
		DirEntry(void);
		virtual ~DirEntry(void);
	private:
		QString mPrarentId;
		QString mEntryId;
		bool isSubTree;
	
	};
}
#endif // DirEntry_h__

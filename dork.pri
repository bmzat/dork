BASEDIR = $$system(cd)

INCLUDEPATH+= $$BASEDIR/src/qdjango $$BASEDIR/src/dorkcore
LIBS+= -L$$BASEDIR/src/qdjango -L$$BASEDIR/src/dorkcore -L$$BASEDIR/bin
#OBJECTS_DIR=$$BASEDIR/obj

g++{
    QMAKE_LFLAGS_SHLIB += -r
    QMAKE_LFLAGS_SHAPP += -Ur
}

#defineReplace(winCopyLib) {

#    excludefile = $$winPath($${DESTDIR}/xcopy_exclude.txt)
#    libdir = ./bin
#    files = $$winPath($${DESTDIR}/$${TARGET}*)

#    copy_cmd  =   @echo .exp >  $$excludefile
#    copy_cmd += | @echo .ilk >> $$excludefile
#    copy_cmd += | xcopy/C/R/Y/EXCLUDE:$$excludefile $$files $$libdir

#    return($$copy_cmd)
#}

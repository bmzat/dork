TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += qdjango dorkcore

dorkcore.depends += qdjango

TEMPLATE = subdirs

SUBDIRS += \
    common \
    common_test \
    mgr \
    us

mgr.depends = common
us.depends = common

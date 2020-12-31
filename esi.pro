TEMPLATE = subdirs

SUBDIRS += \
    common \
    common_test \
    img \
    mgr \
    us

mgr.depends = common
us.depends = common
img.depends = common

TEMPLATE = subdirs

CONFIG = warn_on

SUBDIRS = \
  src \
  app \
  test

app.depends = src
test.depends = src

# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


HEADERS += ../../editors/ComponentEditor/common/IPXactSystemVerilogParser.h \
    ../../editors/ComponentEditor/common/ListParameterFinder.h \
    ../../editors/ComponentEditor/common/SystemVerilogExpressionParser.h \
    ../../editors/ComponentEditor/common/SystemVerilogSyntax.h \
    ../common/NameGenerationPolicy.h \
    ./MakeCommon.h \
    ./MakefileGenerator.h \
    ./MakefileParser.h \
    ./SWStackParser.h \
    ./makefilegenerator_global.h \
    ../PluginSystem/GeneratorPlugin/FileOutput.h \
    ../PluginSystem/GeneratorPlugin/FileOutputWidget.h \
    ./MakeConfiguration.h \
    ./MakeParametersDialog.h \
    ./MakefileGeneratorPlugin.h
SOURCES += ../../editors/ComponentEditor/common/IPXactSystemVerilogParser.cpp \
    ../../editors/ComponentEditor/common/ListParameterFinder.cpp \
    ../../editors/ComponentEditor/common/SystemVerilogExpressionParser.cpp \
    ../common/NameGenerationPolicy.cpp \
    ../PluginSystem/GeneratorPlugin/FileOutput.cpp \
    ../PluginSystem/GeneratorPlugin/FileOutputWidget.cpp \
    ./MakeConfiguration.cpp \
    ./MakefileGenerator.cpp \
    ./MakefileGeneratorPlugin.cpp \
    ./MakefileParser.cpp \
    ./MakeParametersDialog.cpp \
    ./SWStackParser.cpp
RESOURCES += MakefileGenerator.qrc

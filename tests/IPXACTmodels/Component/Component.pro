#-----------------------------------------------------------------------------
# File: ComponentModel.pro
#-----------------------------------------------------------------------------
# Project: Kactus 2
# Author: Mikko Teuho
# Date: 16.09.2015
#
# Description:
# Qt project file template for running unit tests in Component Model.
#-----------------------------------------------------------------------------

TEMPLATE = subdirs

CONFIG += testcase
SUBDIRS += Model\tst_ViewWriter.pro \
		   Model\tst_ViewReader.pro \
		   Model\tst_InstantiationsWriter.pro \
		   Model\tst_InstantiationsReader.pro \
		   Model\tst_ComponentPortWriter.pro \
		   Model\tst_ComponentPortReader.pro \
		   MemoryMaps\tst_EnumeratedValueWriter.pro \
		   MemoryMaps\tst_EnumeratedValueReader.pro \
		   MemoryMaps\tst_FieldWriter.pro \
		   MemoryMaps\tst_FieldReader.pro \
		   MemoryMaps\tst_RegisterWriter.pro \
		   MemoryMaps\tst_RegisterReader.pro \
		   MemoryMaps\tst_AddressBlockWriter.pro \
		   MemoryMaps\tst_AddressBlockReader.pro \
		   MemoryMaps\tst_MemoryMapWriter.pro \
		   MemoryMaps\tst_MemoryMapReader.pro \
		   MemoryMaps\tst_MemoryMapBaseReader.pro \
		   MemoryMaps\tst_MemoryMapBaseWriter.pro \
		   tst_CPUReader.pro \
		   tst_CPUWriter.pro \
		   tst_FileWriter.pro \
		   tst_FileReader.pro \
		   tst_FileSetWriter.pro \
		   tst_FileSetReader.pro \
		   tst_ChannelReader.pro \
		   tst_ChannelWriter.pro \
		   tst_ChoiceReader.pro \
		   tst_ChoiceWriter.pro \
		   tst_businterfaceReader.pro \
		   tst_businterfaceWriter.pro \
		   tst_RemapStateWriter.pro \
		   tst_RemapStateReader.pro \
		   tst_AddressSpaceReader.pro \
		   tst_AddressSpaceWriter.pro